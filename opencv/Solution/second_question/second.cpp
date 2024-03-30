#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat image = imread("img/img.png");
    imshow("before", image);

    Mat kernel_rect = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat kernel_ellipse = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));
    Mat kernel_cross = getStructuringElement(MORPH_CROSS, Size(10, 10));

    Mat erode_img1 = Mat::zeros(image.size(), image.type());
    erode(image, erode_img1, kernel_rect);
    imshow("erode_rect", erode_img1);

    Mat erode_img2 = Mat::zeros(image.size(), image.type());
    erode(image, erode_img2, kernel_ellipse);
    imshow("erode_ellipse", erode_img2);

    Mat erode_img3 = Mat::zeros(image.size(), image.type());
    erode(image, erode_img3, kernel_cross);
    imshow("erode_cross", erode_img3);

    Mat dilate_img1 = Mat::zeros(image.size(), image.type());
    dilate(image, dilate_img1, kernel_rect);
    imshow("dilate_rect", dilate_img1);

    Mat dilate_img2 = Mat::zeros(image.size(), image.type());
    dilate(image, dilate_img2, kernel_ellipse);
    imshow("dilate_ellipse", dilate_img2);

    Mat dilate_img3 = Mat::zeros(image.size(), image.type());
    dilate(image, dilate_img3, kernel_cross);
    imshow("dilate_cross", dilate_img3);

    Mat open_img1 = Mat::zeros(image.size(), image.type());
    Mat close_img1 = Mat::zeros(image.size(), image.type());
    Mat open_img2 = Mat::zeros(image.size(), image.type());
    Mat close_img2 = Mat::zeros(image.size(), image.type());
    Mat open_img3 = Mat::zeros(image.size(), image.type());
    Mat close_img3 = Mat::zeros(image.size(), image.type());
    morphologyEx(image, open_img1, MORPH_OPEN, kernel_rect);
    morphologyEx(image, close_img1, MORPH_CLOSE, kernel_rect);

    morphologyEx(image, open_img2, MORPH_OPEN, kernel_ellipse);
    morphologyEx(image, close_img2, MORPH_CLOSE, kernel_ellipse);

    morphologyEx(image, open_img3, MORPH_OPEN, kernel_cross);
    morphologyEx(image, close_img3, MORPH_CLOSE, kernel_cross);

    imshow("open_rect", open_img1);
    imshow("close_rect", close_img1);
    imshow("open_ellipse", open_img2);
    imshow("close_ellipse", close_img2);
    imshow("open_cross", open_img3);
    imshow("close_cross", close_img3);

    waitKey(0);
    return 0;
}
