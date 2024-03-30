#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
int main()
{
    Mat image = imread("img/count.png");
    if (image.empty())
    {
        std::cout << "wrong" << std::endl;
    }
    imshow("before", image);
    Mat binimg;
    cvtColor(image, binimg, COLOR_BGR2GRAY);
    threshold(binimg, binimg, 125, 255, THRESH_BINARY);
    binimg = ~binimg;
    imshow("bin", binimg);
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    Mat dst = Mat::zeros(binimg.size(), CV_8UC3);
    int numbers = 0;
    char ch[10];
    Mat labels, stats, centroids;
    int numComponents = connectedComponentsWithStats(binimg, labels, stats, centroids);
    for (int i = 1; i < numComponents; i++)
    {
        if (stats.at<int>(i, CC_STAT_AREA) >= 3000 && stats.at<int>(i, CC_STAT_AREA) <= 8000)
        {
            numbers++;
            char n[10];
            sprintf(n,"num.%d",numbers);
            Rect boundingRect(stats.at<int>(i, CC_STAT_LEFT), stats.at<int>(i, CC_STAT_TOP), stats.at<int>(i, CC_STAT_WIDTH), stats.at<int>(i, CC_STAT_HEIGHT));
            rectangle(image, boundingRect, Scalar(0, 255, 0), 2, 8, 0);
            putText(image, n, Point(boundingRect.x, boundingRect.y + 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, 8, false);
        }
    }
    sprintf(ch, "total:%d", numbers);
    putText(image, ch, Point(0, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, 8, false);
    imshow("now", image);
    waitKey(0);
    return 0;
}