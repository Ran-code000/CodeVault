# include <iostream>
# include <string>
# include <cmath>
# include <iomanip>

inline double calculatedistance(double x1,double x2,double y1,double y2)
{
    double dis = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    return dis;
}

inline double calculatePerimeter(double dis1,double dis2,double dis3)
{
    double girth = dis1 + dis2 + dis3;
    return girth;
}

int main()
{
    double x1,x2,x3;
    double y1,y2,y3;

    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    std::cin >> x3 >> y3;

    double dis1 = calculatedistance(x1,x2,y1,y2);
    double dis2 = calculatedistance(x1,x3,y1,y3);
    double dis3 = calculatedistance(x2,x3,y2,y3);

    double perimeter = calculatePerimeter(dis1,dis2,dis3);

    std::cout << std::fixed << std::setprecision(2) << perimeter;

    return 0;
}