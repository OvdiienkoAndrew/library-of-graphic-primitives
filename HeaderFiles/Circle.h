#ifndef _CIRCLE_
#define _CIRCLE_

#include "Shape.h"

class Circle : public Shape
{
    double radius;

public:
    struct ListCircle
    {
        double x;
        double y;
        double radius;
        int r;
        int g;
        int b;
    };

    struct List
    {
        ListCircle circle;
        List *next;
    };
    List *Head;

    void addList(Graphics &graphics);
    Circle();
    Circle(double x, double y, double radius, int r, int g, int b, bool visible);
    ~Circle();

    void addListCircle(double x, double y, double radius, int r, int g, int b);

    void draw(Graphics &graphics);
    void drawTrail(Graphics &graphics);
    void hide(Graphics &graphics);
    void move(double dx, double dy, Graphics &graphics);
    void resize(double factor, Graphics &graphics);

    std::ifstream &read(std::ifstream &is);
    std::ofstream &write(std::ofstream &os);

    void setRadius(double radius);
    double getRadius();

    bool intersects(Shape &other);
    bool intersects(Segment &other);
    bool intersects(Circle &other);
    bool intersects(Rectangle &other);
    bool intersects(Triangle &other);
};

#endif
