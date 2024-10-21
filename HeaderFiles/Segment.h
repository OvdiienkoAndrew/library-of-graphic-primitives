#ifndef _SEGMENT_
#define _SEGMENT_

#include "Shape.h"

class Segment : public Shape
{
    double x2, y2;

public:
    struct ListSegment
    {
        double x;
        double y;
        double x2;
        double y2;
        int r;
        int g;
        int b;
    };

    struct List
    {
        ListSegment segment;
        List *next;
    };

    List *Head;

    void addList(Graphics &graphics);
    Segment();
    Segment(double x, double y, double x2, double y2);
    Segment(double x, double y, double x2, double y2, int r, int g, int b, bool visible);
    ~Segment();

    void addListSegment(double x, double y, double x2, double y2, int r, int g, int b);

    void draw(Graphics &graphics);
    void drawTrail(Graphics &graphics);
    void hide(Graphics &graphics);
    void move(double dx, double dy, Graphics &graphics);
    void resize(double factor, Graphics &graphics);

    std::ifstream &read(std::ifstream &is);
    std::ofstream &write(std::ofstream &os);

    void setX2(double x2);
    void setY2(double y2);

    double getX2();
    double getY2();

    bool intersects(Shape &other);
    bool intersects(Segment &other);
    bool intersects(Circle &other);
    bool intersects(Rectangle &other);
    bool intersects(Triangle &other);
    double direction(double ax, double ay, double bx, double by, double cx, double cy);
    bool onSegment(double x1, double y1, double x2, double y2, double px, double py);
};

#endif