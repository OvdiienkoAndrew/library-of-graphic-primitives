#include "Segment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

Circle::Circle() : Shape(0, 0, 0, 0, 0, 0), radius(0), Head(nullptr) {}
Circle::Circle(double x, double y, double radius, int r, int g, int b, bool visible) : Shape(x, y, r, g, b, visible), radius(radius), Head(nullptr) {}
Circle::~Circle() {}

void Circle::addList(Graphics &graphics)
{

    addListCircle(x, y, radius, r, g, b);
}

void Circle::addListCircle(double x, double y, double radius, int r, int g, int b)
{
    List *current = new List;

    current->circle.x = x;
    current->circle.y = y;
    current->circle.radius = radius;
    current->circle.r = r;
    current->circle.g = g;
    current->circle.b = b;

    current->next = Head;
    Head = current;

    Count++;
}
void Circle::draw(Graphics &graphics)
{
    if (visible)
    {
        graphics.setColor(r, g, b);
        graphics.drawCircle(x, y, radius);
    }
}
void Circle::drawTrail(Graphics &graphics)
{
    if (visible)
    {
        List *current = Head;

        while (current != nullptr)
        {
            graphics.setColor(current->circle.r, current->circle.g, current->circle.b);
            graphics.drawCircle(current->circle.x, current->circle.y, current->circle.radius);

            current = current->next;
        }
    }
}
void Circle::hide(Graphics &graphics)
{
    graphics.setColor(0, 0, 0);
    graphics.drawCircle(x, y, radius);
    visible = false;
}
void Circle::move(double dx, double dy, Graphics &graphics)
{

    hide(graphics);

    Circle::x += dx;
    Circle::y += dy;

    show(graphics);
}
void Circle::resize(double factor, Graphics &graphics)
{

    hide(graphics);

    radius *= factor;

    show(graphics);
}

std::ifstream &Circle::read(std::ifstream &is)
{
    is >> x >> y >> radius;

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
        double sx, sy, sradius;
        int sr, sg, sb;

        if (!(is >> sx >> sy >> sradius >> sr >> sg >> sb))
        {
            if (is.eof() || is.bad())
                break;
            else
            {
                std::cerr << "Error reading circle trail data" << std::endl;
                break;
            }
        }

        addListCircle(sx, sy, sradius, sr, sg, sb);
    }

    return is;
}

std::ofstream &Circle::write(std::ofstream &os)
{
    os << "c ";
    os << getX() << " "
       << getY() << " "
       << getRadius() << " "
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
            os << current->circle.x << " "
               << current->circle.y << " "
               << current->circle.radius << " "
               << current->circle.r << " "
               << current->circle.g << " "
               << current->circle.b << " ";
            current = current->next;
        }
    }

    return os;
}

void Circle::setRadius(double radius) { Circle::radius = radius; }
double Circle::getRadius() { return radius; }

bool Circle::intersects(Shape &other)
{
    return other.intersects(*this);
}

bool Circle::intersects(Segment &segment)
{
    double cx = x;
    double cy = y;
    double radius = Circle::radius;

    double Ax = segment.getX();
    double Ay = segment.getY();
    double Bx = segment.getX2();
    double By = segment.getY2();

    double segmentLength = mySqrt((Bx - Ax) * (Bx - Ax) + (By - Ay) * (By - Ay));

    if (segmentLength < 0.01)
    {
        double distToCenter = mySqrt((Ax - cx) * (Ax - cx) + (Ay - cy) * (Ay - cy));
        return distToCenter <= radius;
    }

    int numSegments = 1;
    if (segmentLength > 0.01)
    {
        numSegments = (int)(segmentLength / 0.01);
    }

    double dx = (Bx - Ax) / numSegments;
    double dy = (By - Ay) / numSegments;

    for (int i = 0; i <= numSegments; ++i)
    {
        double px = Ax + i * dx;
        double py = Ay + i * dy;

        double distToCenter = mySqrt((px - cx) * (px - cx) + (py - cy) * (py - cy));

        if (distToCenter <= radius)
        {
            return true;
        }
    }

    return false;
}

bool Circle::intersects(Circle &other)
{
    double Radius = radius + other.getRadius();
    double Distance = sizeLine(x, y, other.getX(), other.getY());
    return Radius >= Distance;
}

bool Circle::intersects(Rectangle &rectangle)
{
    double closestX = (getX() < rectangle.getX()) ? rectangle.getX() : (getX() > rectangle.getX() + rectangle.getWidth()) ? rectangle.getX() + rectangle.getWidth()
                                                                                                                          : getX();

    double closestY = (getY() < rectangle.getY()) ? rectangle.getY() : (getY() > rectangle.getY() + rectangle.getHeight()) ? rectangle.getY() + rectangle.getHeight()
                                                                                                                           : getY();

    double dx = getX() - closestX;
    double dy = getY() - closestY;

    return (dx * dx + dy * dy <= getRadius() * getRadius());
}

bool Circle::intersects(Triangle &triangle)
{
    Segment segment1(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2());
    Segment segment2(triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());
    Segment segment3(triangle.getX3(), triangle.getY3(), triangle.getX(), triangle.getY());

    bool in = false;

    double ABC = S(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());

    double ABO = S(x, y, triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());
    double AOC = S(triangle.getX(), triangle.getY(), x, y, triangle.getX3(), triangle.getY3());
    double OBC = S(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2(), x, y);

    in = (myFabs(ABC - ABO - AOC - OBC) < 0.01) ? true : false;

    return intersects(segment1) || intersects(segment2) || intersects(segment3) || in;
}
