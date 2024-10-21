#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "Shape.h"

class Triangle : public Shape
{
    double x2, y2, x3, y3;

public:
    struct ListTriangle
    {
        double x;
        double y;
        double x2;
        double y2;
        double x3;
        double y3;
        int r;
        int g;
        int b;
    };

    struct List
    {
        ListTriangle triangle;
        List *next;
    };

    List *Head;

    void addList(Graphics &graphics);

    Triangle();
    Triangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b, bool visible);
    ~Triangle();

    void addListTriangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b);

    void draw(Graphics &graphics);
    void drawTrail(Graphics &graphics);
    void hide(Graphics &graphics);
    void move(double dx, double dy, Graphics &graphics);
    void resize(double factor, Graphics &graphics);

    std::ifstream &read(std::ifstream &is);
    std::ofstream &write(std::ofstream &os);

    void setX2(double x2);
    void setY2(double y2);
    void setX3(double x3);
    void setY3(double y3);

    double getX2();
    double getY2();
    double getX3();
    double getY3();

    bool intersects(Shape &other);
    bool intersects(Segment &other);
    bool intersects(Circle &other);
    bool intersects(Rectangle &other);
    bool intersects(Triangle &other);
};

#endif