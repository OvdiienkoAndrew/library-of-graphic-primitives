#include "Segment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

Segment::Segment() : Shape(0, 0, 0, 0, 0, 0), x2(0), y2(0), Head(nullptr) {}
Segment::Segment(double x, double y, double x2, double y2) : Shape(x, y, 0, 0, 0, 0), x2(x2), y2(y2) {}
Segment::Segment(double x, double y, double x2, double y2, int r, int g, int b, bool visible) : Shape(x, y, r, g, b, visible), x2(x2), y2(y2), Head(nullptr) {}
Segment::~Segment() {}

void Segment::addList(Graphics &graphics)
{

    addListSegment(x, y, x2, y2, r, g, b);
}
void Segment::addListSegment(double x, double y, double x2, double y2, int r, int g, int b)
{
    List *current = new List;
    current->segment.x = x;
    current->segment.y = y;
    current->segment.x2 = x2;
    current->segment.y2 = y2;
    current->segment.r = r;
    current->segment.g = g;
    current->segment.b = b;
    current->next = Head;
    Head = current;
    Count++;
}
void Segment::draw(Graphics &graphics)
{
    if (visible)
    {
        graphics.setColor(r, g, b);
        graphics.drawSegment(x, y, x2, y2);
    }
}
void Segment::drawTrail(Graphics &graphics)
{
    if (visible)
    {
        List *current = Head;

        while (current != nullptr)
        {
            graphics.setColor(current->segment.r, current->segment.g, current->segment.b);
            graphics.drawSegment(current->segment.x, current->segment.y, current->segment.x2, current->segment.y2);
            current = current->next;
        }
    }
}

void Segment::hide(Graphics &graphics)
{
    graphics.setColor(0, 0, 0);
    graphics.drawSegment(x, y, x2, y2);
    visible = false;
}
void Segment::move(double dx, double dy, Graphics &graphics)
{

    hide(graphics);

    x += dx;
    y += dy;

    x2 += dx;
    y2 += dy;

    show(graphics);
}

void Segment::resize(double factor, Graphics &graphics)
{
    hide(graphics);

    double dx = x2 - x;
    double dy = y2 - y;

    x2 = x + dx * factor;
    y2 = y + dy * factor;

    show(graphics);
}

std::ifstream &Segment::read(std::ifstream &is)
{
    is >> x >> y >> x2 >> y2;

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
        double sx, sy, sx2, sy2;
        int sr, sg, sb;

        if (!(is >> sx >> sy >> sx2 >> sy2 >> sr >> sg >> sb))
        {
            if (is.eof() || is.bad())
                break;
            else
            {
                std::cerr << "Error reading circle trail data" << std::endl;
                break;
            }
        }

        addListSegment(sx, sy, sx2, sy2, sr, sg, sb);
    }

    return is;
}

std::ofstream &Segment::write(std::ofstream &os)
{
    os << "s ";
    os << getX() << " "
       << getY() << " "
       << getX2() << " "
       << getY2() << " "
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
            os << current->segment.x << " "
               << current->segment.y << " "
               << current->segment.x2 << " "
               << current->segment.y2 << " "
               << current->segment.r << " "
               << current->segment.g << " "
               << current->segment.b << " ";
            current = current->next;
        }
    }

    return os;
}

void Segment::setX2(double x2) { Segment::x2 = x2; }
void Segment::setY2(double y2) { Segment::y2 = y2; }
double Segment::getX2() { return x2; }
double Segment::getY2() { return y2; }

bool Segment::intersects(Shape &other)
{
    return other.intersects(*this);
}

bool Segment::intersects(Circle &circle)
{
    double cx = circle.getX();
    double cy = circle.getY();
    double radius = circle.getRadius();

    double Ax = x;
    double Ay = y;

    double Bx = x2;
    double By = y2;

    double segmentLength = (mySqrt((Bx - Ax) * (Bx - Ax) + (By - Ay) * (By - Ay)));

    int numSegments = segmentLength / 0.01;

    double dx = (Bx - Ax) / numSegments;
    double dy = (By - Ay) / numSegments;

    for (int i = 0; i <= numSegments; ++i)
    {

        double px = Ax + i * dx;
        double py = Ay + i * dy;

        double distToCenter = (mySqrt((px - cx) * (px - cx) + (py - cy) * (py - cy)));

        if (distToCenter <= radius)
            return true;
    }

    return false;
}

bool Segment::intersects(Segment &other)
{
    double x1 = Segment::x;
    double y1 = Segment::y;
    double x2 = Segment::x2;
    double y2 = Segment::y2;

    double x3 = other.x;
    double y3 = other.y;
    double x4 = other.x2;
    double y4 = other.y2;

    double d1 = direction(x1, y1, x2, y2, x3, y3);
    double d2 = direction(x1, y1, x2, y2, x4, y4);
    double d3 = direction(x3, y3, x4, y4, x1, y1);
    double d4 = direction(x3, y3, x4, y4, x2, y2);

    if ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0) || (d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))
    {
        return true;
    }

    if (d1 == 0 && onSegment(x1, y1, x2, y2, x3, y3))
        return true;
    if (d2 == 0 && onSegment(x1, y1, x2, y2, x4, y4))
        return true;
    if (d3 == 0 && onSegment(x3, y3, x4, y4, x1, y1))
        return true;
    if (d4 == 0 && onSegment(x3, y3, x4, y4, x2, y2))
        return true;

    if (d1 == 0 && d2 == 0)
    {
        return (onSegment(x1, y1, x2, y2, x3, y3) ||
                onSegment(x1, y1, x2, y2, x4, y4) ||
                onSegment(x3, y3, x4, y4, x1, y1) ||
                onSegment(x3, y3, x4, y4, x2, y2));
    }

    return false;
}

bool Segment::intersects(Rectangle &rectangle)
{

    double ulx = rectangle.getX();
    double uly = rectangle.getY();
    double dlx = rectangle.getX();
    double dly = rectangle.getY() + rectangle.getHeight();
    double urx = rectangle.getX() + rectangle.getWidth();
    double ury = rectangle.getY();
    double drx = rectangle.getX() + rectangle.getWidth();
    double dry = rectangle.getY() + rectangle.getHeight();

    Triangle t1(dlx, dly, ulx, uly, urx, ury, 0, 0, 0, false);
    Triangle t2(dlx, dly, drx, dry, urx, ury, 0, 0, 0, false);

    return intersects(t1) || intersects(t2);
}

bool Segment::intersects(Triangle &triangle)
{
    double x1 = triangle.getX(), y1 = triangle.getY();
    double x2 = triangle.getX2(), y2 = triangle.getY2();
    double x3 = triangle.getX3(), y3 = triangle.getY3();

    double sx1 = Segment::x, sy1 = Segment::y;
    double sx2 = Segment::x2, sy2 = Segment::y2;

    if (checkIntersection(sx1, sy1, sx2, sy2, x1, y1, x2, y2))
        return true;
    if (checkIntersection(sx1, sy1, sx2, sy2, x2, y2, x3, y3))
        return true;
    if (checkIntersection(sx1, sy1, sx2, sy2, x3, y3, x1, y1))
        return true;

    bool in1 = false;

    double ABC1 = S(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());

    double ABO1 = S(sx1, sy1, triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());
    double AOC1 = S(triangle.getX(), triangle.getY(), sx1, sy1, triangle.getX3(), triangle.getY3());
    double OBC1 = S(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2(), sx1, sy1);

    bool in2 = false;

    double ABC2 = S(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());

    double ABO2 = S(sx2, sy2, triangle.getX2(), triangle.getY2(), triangle.getX3(), triangle.getY3());
    double AOC2 = S(triangle.getX(), triangle.getY(), sx2, sy2, triangle.getX3(), triangle.getY3());
    double OBC2 = S(triangle.getX(), triangle.getY(), triangle.getX2(), triangle.getY2(), sx2, sy2);

    in1 = (myFabs(ABC1 - ABO1 - AOC1 - OBC1) < 0.01) ? true : false;
    in2 = (myFabs(ABC2 - ABO2 - AOC2 - OBC2) < 0.01) ? true : false;

    return (in1 || in2);
}

double Segment::direction(double ax, double ay, double bx, double by, double cx, double cy)
{
    return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}
bool Segment::onSegment(double x1, double y1, double x2, double y2, double px, double py)
{
    bool withinX = (px >= x1 && px <= x2) || (px >= x2 && px <= x1);
    bool withinY = (py >= y1 && py <= y2) || (py >= y2 && py <= y1);
    return withinX && withinY;
}
