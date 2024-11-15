cv::Mat ImageProcessor::convertToColorscale(const cv::Mat& img) {
    if (img.empty()) {
        std::cerr << "Error: Input image is empty!" << std::endl;
        return cv::Mat(); // 返回空的 Mat
    }

    // 加载深度学习模型
    std::string protoFile = "D:\\Deep learning model\\colorization-caffe\\models\\colorization_deploy_v2.prototxt";
    std::string weightsFile = "D:\\Deep learning model\\colorization-caffe\\models\\dummy.caffemodel";
    std::string ptsFile = "D:\\Deep learning model\\colorization - caffe\\resources\\pts_in_hull.npy";

    cv::dnn::Net net = cv::dnn::readNetFromCaffe(protoFile, weightsFile);
    cv::Mat ptsInHull = loadPtsInHull(ptsFile);

    // 检查通道并处理
    cv::Mat grayImage;
    if (img.channels() == 1) {
        grayImage = img.clone(); // 如果已经是灰度图
    } else {
        cv::cvtColor(img, grayImage, cv::COLOR_RGB2GRAY);
    }

    // 转换为 Lab 空间
    cv::Mat labImage;
    cv::cvtColor(grayImage, labImage, cv::COLOR_GRAY2RGB);
    labImage.convertTo(labImage, CV_32F, 1.0 / 255);
    cv::cvtColor(labImage, labImage, cv::COLOR_RGB2Lab);
    
    std::vector<cv::Mat> labPlanes(3);
    cv::split(labImage, labPlanes);
    cv::Mat l = labPlanes[0];
    l -= 50;

    // 前向传播
    cv::Mat inputBlob = cv::dnn::blobFromImage(l);
    net.setInput(inputBlob);
    cv::Mat ab = net.forward();

    // 后处理
    cv::Size imgSize = img.size();
    cv::resize(ab, ab, imgSize);
    std::vector<cv::Mat> labPlanesOut(3);
    labPlanesOut[0] = l + 50;
    cv::split(ab, labPlanesOut);
    cv::merge(labPlanesOut, labImage);
    cv::cvtColor(labImage, labImage, cv::COLOR_Lab2BGR);
    labImage.convertTo(labImage, CV_8U, 255);

    return labImage;
}