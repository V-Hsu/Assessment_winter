#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
Mat myGammaTransform(Mat &img, double gamma)
{
    unsigned char mygamma[256];
    for (int i = 0; i < 256; i++)
    {
        mygamma[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
    }
    Mat gamma_img = img.clone();
    if (img.channels() == 1)
    {
        MatIterator_<uchar> iterator = gamma_img.begin<uchar>();
        MatIterator_<uchar> iteratorEnd = gamma_img.end<uchar>();
        for (; iterator != iteratorEnd; iterator++)
        {
            *iterator = mygamma[(*iterator)];
        }
    }
    else if (img.channels() == 3)
    {
        MatIterator_<Vec3b> iterator = gamma_img.begin<Vec3b>();
        MatIterator_<Vec3b> iteratorEnd = gamma_img.end<Vec3b>();
        for (; iterator != iteratorEnd; iterator++)
        {
            (*iterator)[0] = mygamma[((*iterator)[0])];
            (*iterator)[1] = mygamma[((*iterator)[1])];
            (*iterator)[2] = mygamma[((*iterator)[2])];
        }
    }
    return gamma_img;
}
int main()
{
    Mat image1 = imread("img/people.png");
    Mat image2 = imread("img/abstract.jpg");
    if (image1.empty() || image2.empty())
    {
        std::cout << "wrong" << std::endl;
        return -1;
    }
    imshow("before1", image1);
    imshow("before2", image2);
    double gamma1 = 1.0 / 3.3, gamma2 = 1.0 / 0.33;
    Mat gamma1_img1 = myGammaTransform(image1, gamma1);
    Mat gamma1_img2 = myGammaTransform(image1, gamma2);

    Mat gamma2_img1 = myGammaTransform(image2, gamma1);
    Mat gamma2_img2 = myGammaTransform(image2, gamma2);

    imshow("gamma1 3.3", gamma1_img1);
    imshow("gamma1 0.33", gamma1_img2);
    imshow("gamma2 3.3", gamma2_img1);
    imshow("gamma2 0.33", gamma2_img2);
    waitKey(0);
    destroyAllWindows();
    return 0;
}