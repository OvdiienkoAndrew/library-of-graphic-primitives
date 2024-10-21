#ifndef _RECTANGLE_
#define _RECTANGLE_

#include "Shape.h"

class Rectangle : public Shape
{
    double width, height;

public:
    struct ListRectangle
    {
        double x;
        double y;
        double width;
        double height;
        int r;
        int g;
        int b;
    };

    struct List
    {
        ListRectangle rectangle;
        List *next;
    };

    List *Head;

    void addList(Graphics &graphics);
    Rectangle();
    Rectangle(double x, double y, double width, double height, int r, int g, int b, bool visible);
    ~Rectangle();

    void addListRectangle(double x, double y, double width, double height, int r, int g, int b);

    void draw(Graphics &graphics);
    void drawTrail(Graphics &graphics);
    void hide(Graphics &graphics);
    void move(double dx, double dy, Graphics &graphics);
    void resize(double factor, Graphics &graphics);
    std::ifstream &read(std::ifstream &is);
    std::ofstream &write(std::ofstream &os);

    void setWidth(double width);
    void setHeight(double height);

    double getWidth();
    double getHeight();

    bool intersects(Shape &other);
    bool intersects(Segment &other);
    bool intersects(Circle &other);
    bool intersects(Rectangle &other);
    bool intersects(Triangle &other);
};

#endif
