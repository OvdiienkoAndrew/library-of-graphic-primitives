#include "Group.h"

void Group::resize(int newCaptain)
{
    Shape **newShapes = new Shape *[newCaptain];
    for (long long i = 0; i < size; i++)
    {
        newShapes[i] = Shapes[i];
    }
    delete[] Shapes;
    Shapes = newShapes;
    captain = newCaptain;
}

Group::Group() : Shapes(nullptr), captain(0), size(0) {}

Group::~Group()
{
    if (Shapes)
    {
        for (int i = 0; i < size; ++i)
        {
            delete Shapes[i];
            Shapes[i] = nullptr;
        }
        delete[] Shapes;
        Shapes = nullptr;
    }
}

void Group::addShape(Shape *shape)
{
    if (shape == nullptr)
        return;
    if (size >= captain)
    {
        resize(captain == 0 ? 1 : captain * 2);
    }
    Shapes[size++] = shape;
}

void Group::removeShape(Shape *shape)
{
    for (int i = 0; i < size; ++i)
    {
        if (Shapes[i] == shape)
        {
            for (int j = i; j < size - 1; j++)
            {
                Shapes[j] = Shapes[j + 1];
            }
            Shapes[size - 1] = nullptr;
            size--;
            return;
        }
    }
}

void Group::setV(bool visible)
{
    for (int i = 0; i < size; ++i)
    {
        Shapes[i]->setV(visible);
    }
}

void Group::setVisible()
{
    for (int i = 0; i < size; ++i)
    {
        Shapes[i]->setV(!(Shapes[i]->getVisible()));
    }
}

void Group::draw(Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Shapes[i] != nullptr)
        {
            Shapes[i]->draw(graphics);
        }
    }
}

void Group::move(double dx, double dy, Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Shapes[i] != nullptr)
        {
            Shapes[i]->move(dx, dy, graphics);
        }
    }
}

void Group::drawTrail(Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Shapes[i] != nullptr)
        {
            Shapes[i]->drawTrail(graphics);
        }
    }
}

void Group::addList(Graphics &graphics)
{
    for (int i = 0; i < size; ++i)
    {
        if (Shapes[i] != nullptr)
        {
            Shapes[i]->addList(graphics);
        }
    }
}

int Group::getSize() { return size; }

bool Group::intersects(Shape &other)
{
    for (int i = 0; i < size; i++)
    {
        if (Shapes[i] != nullptr && Shapes[i]->intersects(other))
        {
            return true;
        }
    }
    return false;
}

void Group::findTheInterects(Shape **shapes, int size2)
{
    for (int j = 0; j < size; j++)
        for (int i = 0; i < size2; ++i)
        {
            if (shapes[i] == Shapes[j])
                continue;
            if (Shapes[j]->intersects(*shapes[i]))
            {
                Shapes[j]->setColor(
                    (Shapes[j]->getColorRed() + 10) % 256,
                    (Shapes[j]->getColorGreen() + 10) % 256,
                    (Shapes[j]->getColorBlue() + 10) % 256);
            }
        }
}

void Group::resize(double factor, Graphics &graphics)
{
    for (int i = 0; i < size; i++)
    {
        if (Shapes[i] != nullptr)
        {
            Shapes[i]->resize(factor, graphics);
        }
    }
}

std::ofstream &Group::write(std::ofstream &os)
{
    os << size << " ";
    for (int i = 0; i < size; i++)
    {
        if (Shapes[i] != nullptr)
        {
            os << *Shapes[i] << " ";
        }
    }
    return os;
}

bool Group::compare(Group *group)
{
    if (size != group->size)
        return false;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < group->size; j++)
        {
            if (i != j)
                continue;
            if (Shapes[i]->getX() == group->Shapes[i]->getX() && Shapes[i]->getY() == group->Shapes[i]->getY() && Shapes[i]->getColorRed() == group->Shapes[i]->getColorRed() && Shapes[i]->getColorGreen() == group->Shapes[i]->getColorGreen() && Shapes[i]->getColorBlue() == group->Shapes[i]->getColorBlue())
            {
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}