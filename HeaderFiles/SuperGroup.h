#ifndef _SUPERGROUP_
#define _SUPERGROUP_

#include "Group.h"

class SGroup : public Group
{
    Group **Groups;
    int captain;
    int size;

    void resize(int newCaptain);

public:
    SGroup();
    ~SGroup();

    void addGroup(Group *group);
    void removeGroup(Group *group);

    void setV(bool visible);
    void setVisible();

    void draw(Graphics &graphics);
    void move(double dx, double dy, Graphics &graphics);

    void drawTrail(Graphics &graphics);
    void addList(Graphics &graphics);

    int getSize();

    bool intersects(Group &other);
    void findTheInterects(Shape **shapes, int size2);

    void resize(double factor, Graphics &graphics);

    std::ofstream &write(std::ofstream &os);
};

#endif
