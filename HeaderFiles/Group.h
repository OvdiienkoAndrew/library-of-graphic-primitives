#ifndef _GROUP_
#define _GROUP_

#include "Shape.h"

class Group : public Shape
{

    Shape **Shapes;
    int captain;
    int size;

public:
    void resize(int newCaptain);

    Group();

    ~Group();
    void addShape(Shape *shape);

    void removeShape(Shape *shape);
    void setV(bool visible);
    void setVisible();
    void draw(Graphics &graphics);

    void move(double dx, double dy, Graphics &graphics);

    void drawTrail(Graphics &graphics);
    void addList(Graphics &graphics);
    int getSize();

    bool intersects(Shape &other);
    void findTheInterects(Shape **shapes, int size2);
    void resize(double factor, Graphics &graphics);

    std::ofstream &write(std::ofstream &os);

    bool compare(Group *group);
};
#endif
