/**
 * @file question_second.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-26
 *
 * @copyright Copyright (c) 2024
 *
 */

/*
创建一个 C++ 程序，定义一个带有虚函数 calculateArea 的基类 Shape。
从基类派生出两个类 Circle 和 Rectangle。在每个派生类中实现 calculateArea 函数，
分别计算圆形和矩形的面积。在主函数中，创建两个派生类的实例，
分别调用 calculateArea 函数，并显示结果。
*/

#include <iostream>
#define PI 3.14
class Shape
{
public:
    virtual float calculateArea() = 0;
};

class Circle : public Shape
{
public:
    Circle(int r)
    {
        this->r = r;
    }
    float calculateArea()
    {
        return r * r * PI;
    }

private:
    float r;
};

class Rectangle : public Shape
{
public:
    Rectangle(int len, int wid)
    {
        this->length = len;
        this->width = wid;
    }
    float calculateArea()
    {
        return length * width;
    }

private:
    float length;
    float width;
};

int main()
{
    Circle cir(2.5);
    Rectangle rect(6.5,3.5);
    std::cout<<"The area of circle is "<<cir.calculateArea()<<std::endl;
    std::cout<<"The area of rectangle is "<<rect.calculateArea()<<std::endl;
    return 0;
}
