#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
int main()
{
    Mat image = imread("img/src.jpg");
    resize(image, image, Size(), 0.3, 0.3);
    imshow("before", image);
    Mat kernel;
    kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat grayimg, binimg, fiximg;
    Mat drawimg = Mat::zeros(image.size(), CV_8UC3);
    cvtColor(image, grayimg, COLOR_BGR2GRAY);
    imshow("gray", grayimg);
    threshold(grayimg, binimg, 165, 255, THRESH_BINARY);
    imshow("bin", binimg);
    morphologyEx(binimg, fiximg, MORPH_OPEN, kernel, Point(-1, -1));
    imshow("fix", fiximg);
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(fiximg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); i++)
    {
        Rect rect = boundingRect(contours[i]);
        if (rect.width > image.cols / 5)
        {
            drawContours(drawimg, contours, i, Scalar(255, 0, 0), 2, 8, hierarchy);
        }
    }
    imshow("now", drawimg);

    std::vector<Vec4i> lines;
    Mat lineimg = Mat::zeros(image.size(), CV_8UC3);
    Mat lineimg1 = Mat::zeros(image.size(), CV_8UC3);
    cvtColor(drawimg, drawimg, COLOR_BGR2GRAY);
    HoughLinesP(drawimg, lines, 1, CV_PI / 180.0, 230, 0, 0);
    for (int i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(lineimg, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, 8, 0);
    }
    imshow("lineimg", lineimg);
    Vec4i topline, bottomline, leftline, rightline;
    for (int i = 0; i < lines.size(); i++)
    {
        Vec4i ln = lines[i];
        if (ln[3] < lineimg.rows / 2.0 && ln[1] < lineimg.rows / 2.0 && ln[0] < lineimg.cols / 2.0 && ln[2] > lineimg.cols / 2.0)
            topline = lines[i];
        if (ln[3] > lineimg.rows / 2.0 && ln[1] > lineimg.rows / 2.0 && ln[0] < lineimg.cols / 2.0 && ln[2] > lineimg.cols / 2.0)
            bottomline = lines[i];
        if (ln[0] < lineimg.cols / 2.0 && ln[2] < lineimg.cols / 2.0)
            leftline = lines[i];
        if (ln[0] > lineimg.cols / 2.0 && ln[2] > lineimg.cols / 2.0)
            rightline = lines[i];
    }
    std::cout << topline[0] << "," << topline[1] << "," << topline[2] << "," << topline[3] << std::endl;
    std::cout << bottomline[0] << "," << bottomline[1] << "," << bottomline[2] << "," << bottomline[3] << std::endl;
    std::cout << leftline[0] << "," << leftline[1] << "," << leftline[2] << "," << leftline[3] << std::endl;
    std::cout << rightline[0] << "," << rightline[1] << "," << rightline[2] << "," << rightline[3] << std::endl;
    line(lineimg1, Point(topline[0], topline[1]), Point(topline[2], topline[3]), Scalar(0, 0, 255), 2, 8, 0);
    line(lineimg1, Point(bottomline[0], bottomline[1]), Point(bottomline[2], bottomline[3]), Scalar(0, 0, 255), 2, 8, 0);
    line(lineimg1, Point(leftline[0], leftline[1]), Point(leftline[2], leftline[3]), Scalar(0, 0, 255), 2, 8, 0);
    line(lineimg1, Point(rightline[0], rightline[1]), Point(rightline[2], rightline[3]), Scalar(0, 0, 255), 2, 8, 0);
    std::cout << lines.size() << std::endl;
    float k1, c1, k2, c2, k3, c3, k4, c4;
    k1 = float(topline[3] - topline[1]) / float(topline[2] - topline[0]);
    c1 = topline[1] - k1 * topline[0];

    k2 = float(bottomline[3] - bottomline[1]) / float(bottomline[2] - bottomline[0]);
    c2 = bottomline[1] - k2 * bottomline[0];

    k3 = float(leftline[3] - leftline[1]) / float(leftline[2] - leftline[0]);
    c3 = leftline[1] - k3 * leftline[0];

    k4 = float(rightline[3] - rightline[1]) / float(rightline[2] - rightline[0]);
    c4 = rightline[1] - k4 * rightline[0];

    Point p1, p2, p3, p4;
    p1.x = static_cast<int>(c1 - c3) / (k3 - k1);
    p1.y = static_cast<int>(k3 * p1.x + c3);

    p2.x = static_cast<int>(c1 - c4) / (k4 - k1);
    p2.y = static_cast<int>(k1 * p2.x + c1);

    p3.x = static_cast<int>(c2 - c3) / (k3 - k2);
    p3.y = static_cast<int>(k3 * p3.x + c3);

    p4.x = static_cast<int>(c2 - c4) / (k4 - k2);
    p4.y = static_cast<int>(k4 * p4.x + c4);

    std::cout << p1.x << "," << p1.y << std::endl;
    std::cout << p2.x << "," << p2.y << std::endl;
    std::cout << p3.x << "," << p3.y << std::endl;
    std::cout << p4.x << "," << p4.y << std::endl;

    Mat dotimg = image.clone();
    circle(dotimg, p1, 2, Scalar(0, 255, 0), 2, 8, 0);
    circle(dotimg, p2, 2, Scalar(0, 255, 0), 2, 8, 0);
    circle(dotimg, p3, 2, Scalar(0, 255, 0), 2, 8, 0);
    circle(dotimg, p4, 2, Scalar(0, 255, 0), 2, 8, 0);
    imshow("dot", dotimg);

    std::vector<Point2f> src(4);
    src[0] = p1;
    src[1] = p2;
    src[2] = p4;
    src[3] = p3;
    std::vector<Point2f> dst(4);
    dst[0] = Point(0, 0);
    dst[1] = Point(image.cols, 0);
    dst[2] = Point(image.cols, image.rows);
    dst[3] = Point(0, image.rows);
    Mat finalimg;
    Mat warp = getPerspectiveTransform(src, dst);
    warpPerspective(image, finalimg, warp, image.size(), INTER_LINEAR);
    imshow("dst", finalimg);

    waitKey(0);
    destroyAllWindows();
    return 0;
}