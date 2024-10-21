#include "Segment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

Rectangle::Rectangle() : Shape(0, 0, 0, 0, 0, 0), width(0), height(0), Head(nullptr) {}
Rectangle::Rectangle(double x, double y, double width, double height, int r, int g, int b, bool visible) : Shape(x, y, r, g, b, visible), width(width), height(height), Head(nullptr) {}
Rectangle::~Rectangle() {}

void Rectangle::addList(Graphics &graphics)
{

    addListRectangle(x, y, width, height, r, g, b);
}

void Rectangle::addListRectangle(double x, double y, double width, double height, int r, int g, int b)
{
    List *current = new List;
    current->rectangle.x = x;
    current->rectangle.y = y;
    current->rectangle.width = width;
    current->rectangle.height = height;
    current->rectangle.r = r;
    current->rectangle.g = g;
    current->rectangle.b = b;
    current->next = Head;
    Head = current;
    Count++;
}

void Rectangle::draw(Graphics &graphics)
{
    if (visible)
    {
        graphics.setColor(r, g, b);
        graphics.drawRectangle(x, y, width, height);
    }
}
void Rectangle::drawTrail(Graphics &graphics)
{
    if (visible)
    {
        List *current = Head;
        while (current != nullptr)
        {
            graphics.setColor(current->rectangle.r, current->rectangle.g, current->rectangle.b);
            graphics.drawRectangle(current->rectangle.x, current->rectangle.y, current->rectangle.width, current->rectangle.height);
            current = current->next;
        }
    }
}

void Rectangle::hide(Graphics &graphics)
{
    graphics.setColor(0, 0, 0);
    graphics.drawRectangle(x, y, width, height);
    visible = false;
}
void Rectangle::move(double dx, double dy, Graphics &graphics)
{

    hide(graphics);

    x += dx;
    y += dy;

    show(graphics);
}

void Rectangle::resize(double factor, Graphics &graphics)
{
    hide(graphics);
    width *= factor;
    height *= factor;
    show(graphics);
}

std::ifstream &Rectangle::read(std::ifstream &is)
{
    is >> x >> y >> width >> height;

    int r, g, b;
    is >> r >> g >> b;
    setColor(r, g, b);

    bool v;
    is >> v;
    setV(v);

    int count;
    is >> count;

    while (count > 0)
    {
        count--;
        double sx, sy, swidth, sheight;
        int sr, sg, sb;

        if (!(is >> sx >> sy >> swidth >> sheight >> sr >> sg >> sb))
        {
            if (is.eof() || is.bad())
                break;
            else
            {
                std::cerr << "Error reading circle trail data" << std::endl;
                break;
            }
        }

        addListRectangle(sx, sy, swidth, sheight, sr, sg, sb);
    }

    return is;
}

std::ofstream &Rectangle::write(std::ofstream &os)
{
    os << "r ";
    os << getX() << " "
       << getY() << " "
       << getWidth() << " "
       << getHeight() << " "
       << getColorRed() << " "
       << getColorGreen() << " "
       << getColorBlue() << " "
       << getVisible() << " ";

    int count = 0;
    {
        List *current = Head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
    }

    os << count << " ";

    if (count > 0)
    {
        List *current = Head;
        while (current != nullptr)
        {
            os << current->rectangle.x << " "
               << current->rectangle.y << " "
               << current->rectangle.width << " "
               << current->rectangle.height << " "
               << current->rectangle.r << " "
               << current->rectangle.g << " "
               << current->rectangle.b << " ";
            current = current->next;
        }
    }
    return os;
}

void Rectangle::setWidth(double width) { Rectangle::width = width; }
void Rectangle::setHeight(double height) { Rectangle::height = height; }
double Rectangle::getWidth() { return width; }
double Rectangle::getHeight() { return height; }

bool Rectangle::intersects(Shape &other)
{
    return other.intersects(*this);
}

bool Rectangle::intersects(Circle &circle)
{

    double closestX = (getX() > ((circle.getX() < getX() + getWidth()) ? circle.getX() : getX() + getWidth())) ? getX() : ((circle.getX() < getX() + getWidth()) ? circle.getX() : getX() + getWidth());
    double closestY = (getY() > ((circle.getY() < getY() + getHeight()) ? circle.getY() : getY() + getHeight())) ? getY() : ((circle.getY() < getY() + getHeight()) ? circle.getY() : getY() + getHeight());

    double dx = circle.getX() - closestX;
    double dy = circle.getY() - closestY;

    return (dx * dx + dy * dy <= circle.getRadius() * circle.getRadius());
}

bool Rectangle::intersects(Segment &segment)
{
    double ulx = x, uly = y;
    double dlx = x, dly = y + height;
    double urx = x + width, ury = y;
    double drx = x + width, dry = y + height;

    Triangle t1(dlx, dly, ulx, uly, urx, ury, 0, 0, 0, 0);
    Triangle t2(dlx, dly, drx, dry, urx, ury, 0, 0, 0, 0);

    return t1.intersects(segment) || t2.intersects(segment);
}

bool Rectangle::intersects(Rectangle &other)
{
    return !(getX() + getWidth() < other.getX() ||
             getX() > other.getX() + other.getWidth() ||
             getY() + getHeight() < other.getY() ||
             getY() > other.getY() + other.getHeight());
}

bool Rectangle::intersects(Triangle &triangle)
{

    double ulx = x, uly = y;
    double dlx = x, dly = y + height;
    double urx = x + width, ury = y;
    double drx = x + width, dry = y + height;

    Triangle t1(dlx, dly, ulx, uly, urx, ury, 0, 0, 0, false);
    Triangle t2(dlx, dly, drx, dry, urx, ury, 0, 0, 0, false);

    return t1.intersects(triangle) || t2.intersects(triangle);
}
