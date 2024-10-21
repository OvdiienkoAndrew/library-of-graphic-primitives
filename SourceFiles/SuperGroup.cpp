#include "SuperGroup.h"

void SGroup::resize(int newCaptain)
{
    Group **newShapes = new Group *[newCaptain];
    for (long long i = 0; i < size; i++)
    {
        newShapes[i] = Groups[i];
    }
    delete[] Groups;
    Groups = newShapes;
    captain = newCaptain;
}

SGroup::SGroup() : Groups(nullptr), captain(0), size(0) {}

SGroup::~SGroup()
{
    if (Groups)
    {
        for (int i = 0; i < size; ++i)
        {
            delete Groups[i];
            Groups[i] = nullptr;
        }
        delete[] Groups;
        Groups = nullptr;
    }
}

void SGroup::addGroup(Group *group)
{
    if (group == nullptr)
        return;
    if (size >= captain)
    {
        resize(captain == 0 ? 1 : captain * 2);
    }
    Groups[size++] = group;
}

void SGroup::removeGroup(Group *group)
{
    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] == group)
        {
            for (int j = i; j < size - 1; j++)
            {
                Groups[j] = Groups[j + 1];
            }
            Groups[size - 1] = nullptr;
            size--;
            return;
        }
    }
}

void SGroup::setV(bool visible)
{
    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->setV(visible);
        }
    }
}

void SGroup::setVisible()
{
    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->setVisible();
        }
    }
}

void SGroup::draw(Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->draw(graphics);
        }
    }
}

void SGroup::move(double dx, double dy, Graphics &graphics)
{

    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->move(dx, dy, graphics);
        }
    }
}

void SGroup::drawTrail(Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->drawTrail(graphics);
        }
    }
}

void SGroup::addList(Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->addList(graphics);
        }
    }
}

int SGroup::getSize() { return size; }

bool SGroup::intersects(Group &other)
{
    for (int i = 0; i < size; i++)
    {
        if (Groups[i] != nullptr && Groups[i]->intersects(other))
        {
            return true;
        }
    }
    return false;
}

void SGroup::findTheInterects(Shape **shapes, int size2)
{
    for (int i = 0; i < size; ++i)
    {
        Groups[i]->findTheInterects(shapes, size2);
    }
}

void SGroup::resize(double factor, Graphics &graphics)
{
    for (int i = 0; i < size; i++)
    {
        if (Groups[i] != nullptr)
        {
            Groups[i]->resize(factor, graphics);
        }
    }
}

std::ofstream &SGroup::write(std::ofstream &os)
{
    os << size << " ";
    for (int i = 0; i < size; i++)
    {
        if (Groups[i] != nullptr)
        {
            os << *Groups[i] << " ";
        }
    }
    return os;
}