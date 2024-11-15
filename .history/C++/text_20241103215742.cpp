#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>

// Function to load pts_in_hull.npy file
cv::Mat loadPtsInHull(const std::string &npyFile) {
    // Use numpy to load the npy file into a Mat
    cv::Mat ptsInHull;
    std::ifstream input(npyFile, std::ios::binary);
    if (input.is_open()) {
        // Read the npy header
        char header[256];
        input.read(header, 256);

        // Read the data
        int numPts = 313, numDims = 2;
        ptsInHull.create(numPts, numDims, CV_32F);
        input.read(reinterpret_cast<char*>(ptsInHull.data), numPts * numDims * sizeof(float));
        input.close();
    }
    return ptsInHull;
}

int main() {
    // 读取灰度图像
    cv::Mat grayImage = cv::imread("path_to_your_gray_image.jpg", cv::IMREAD_GRAYSCALE);
    if (grayImage.empty()) {
        std::cerr << "无法读取图像文件!" << std::endl;
        return -1;
    }

    // 加载深度学习模型
    std::string protoFile = "D:\\Deep learning model\\colorization-caffe\\models\\colorization_deploy_v2.prototxt";
std::string weightsFile = "D:\\Deep learning model\\colorization-caffe\\models\\dummy.caffemodel";
std::string ptsFile = "D:\\Deep learning model\\colorization - caffe\\resources\\pts_in_hull.npy";

    cv::dnn::Net net = cv::dnn::readNetFromCaffe(protoFile, weightsFile);

    // 读取类中心点
    cv::Mat ptsInHull = loadPtsInHull(ptsFile);

    // 调整网络的最后一层
    cv::Mat pts(1, ptsInHull.total(), CV_32F, ptsInHull.ptr<float>());
    cv::Mat class8_ab(1, ptsInHull.total(), CV_32F, ptsInHull.ptr<float>());
    
    // Create a blob from the data and set it to the network
    std::vector<cv::Mat> blobs;
    blobs.push_back(cv::Mat(1, 1, CV_32F, cv::Scalar(0)));
    blobs.push_back(class8_ab);

    net.getLayer(net.getLayerId("class8_ab"))->blobs = blobs;

    // 预处理图像
    cv::Mat labImage, l;
    cv::cvtColor(grayImage, labImage, cv::COLOR_GRAY2RGB);
    labImage.convertTo(labImage, CV_32F, 1.0 / 255);
    cv::cvtColor(labImage, labImage, cv::COLOR_RGB2Lab);
    std::vector<cv::Mat> labPlanes(3);
    cv::split(labImage, labPlanes);
    l = labPlanes[0];
    l -= 50;

    // 前向传播
    cv::Mat inputBlob = cv::dnn::blobFromImage(l);
    net.setInput(inputBlob);
    cv::Mat ab = net.forward();

    // 后处理
    cv::Size imgSize = grayImage.size();
    cv::resize(ab, ab, imgSize);
    std::vector<cv::Mat> labPlanesOut(3);
    labPlanesOut[0] = l + 50;
    cv::split(ab, labPlanesOut.begin() + 1);
    cv::merge(labPlanesOut, labImage);
    cv::cvtColor(labImage, labImage, cv::COLOR_Lab2BGR);
    labImage.convertTo(labImage, CV_8U, 255);

    return labImage;
}
