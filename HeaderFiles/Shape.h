#ifndef _SHAPE_
#define _SHAPE_

#include "Graphics.h"
#include <fstream>
#include <iostream>
using namespace GLF;

class Circle;
class Segment;
class Rectangle;
class Triangle;
class Group;

class Shape
{
protected:
    template <typename T>
    T myFabs(T x);
    double mySqrt(double x);
    double S(double x1, double y1, double x2, double y2, double x3, double y3);
    bool visible;
    double x, y;
    int r, g, b;
    int Count;

public:
    virtual void addTrail(double prevX, double prevY, double prevX2, double prevY2, int r, int g, int b);

    void setColorRed(int r);
    void setColorGreen(int g);
    void setColorBlue(int b);
    virtual void add(Shape *shape);

    virtual void remove(Shape *shape);
    virtual void addTrail(double prevX, double prevY, int r, int g, int b);
    virtual bool intersects(Shape &externalShape, int r1, int g1, int b1, int r2, int g2, int b2);

    Shape();
    Shape(double x, double y, int r, int g, int b, bool visible);
    virtual ~Shape();

    virtual void draw(Graphics &graphics);
    virtual void drawTrail(Graphics &graphics);
    virtual void show(Graphics &graphics);
    virtual void hide(Graphics &graphics);
    virtual void move(double dx, double dy, Graphics &graphics);
    virtual void resize(double factor, Graphics &graphics);
    virtual std::ifstream &read(std::ifstream &is);
    virtual std::ofstream &write(std::ofstream &os);

    virtual double getX();
    virtual double getY();
    virtual double getX2();
    virtual double getY2();
    virtual double getX3();
    virtual double getY3();
    virtual double getRadius();

    virtual int getColorRed();
    virtual int getColorGreen();
    virtual int getColorBlue();
    virtual bool getVisible();

    virtual void setX(double x);
    virtual void setY(double y);
    virtual void setColor(int r, int g, int b);
    virtual void setVisible();
    virtual void setV(bool visible);

    virtual bool intersects(Shape &other);
    virtual bool intersects(Segment &other);
    virtual bool intersects(Circle &other);
    virtual bool intersects(Rectangle &other);
    virtual bool intersects(Triangle &other);

    virtual double intersects(double x1, double y1, double x2, double y2, double x3, double y3);
    virtual bool onSegment(int x1, int y1, int x2, int y2, int x3, int y3);

    virtual bool doIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

    virtual bool checkIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

    virtual double direction(double x1, double y1, double x2, double y2, double x3, double y3);

    virtual bool isPointInTriangle(double px, double py, double x1, double y1, double x2, double y2, double x3, double y3);

    virtual double sizeLine(double Ax, double Ay, double Bx, double By);

    friend std::ofstream &operator<<(std::ofstream &os, Shape &shape);

    friend std::ifstream &operator>>(std::ifstream &os, Shape &shape);

    virtual void addListSegment(double x, double y, double x2, double y2, int r, int g, int b);
    virtual void addListCircle(double x, double y, double radius, int r, int g, int b);
    virtual void addListRectangle(double x, double y, double width, double height, int r, int g, int b);
    virtual void addListTriangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b);

    virtual double getWidth();
    virtual double getHeight();

    virtual void addList(Graphics &graphics);
    virtual void addShape(Shape *shape);
    virtual void removeShape(Shape *shape);
    virtual int getSize();

    virtual void findTheInterects(Shape **shape, int shapeSize);
    virtual void addGroup(Group *shape);
    virtual void removeGroup(Group *group);

    virtual bool compare(Group *group);
};

#endif
