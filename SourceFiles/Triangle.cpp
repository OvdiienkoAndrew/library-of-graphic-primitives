#include "Segment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

Triangle::Triangle() : Shape(0, 0, 0, 0, 0, 0), x2(0), y2(0), x3(0), y3(0), Head(nullptr) {}
Triangle::Triangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b, bool visible) : Shape(x, y, r, g, b, visible), x2(x2), y2(y2), x3(x3), y3(y3), Head(nullptr) {}
Triangle::~Triangle() {}

void Triangle::addList(Graphics &graphics)
{

    addListTriangle(x, y, x2, y2, x3, y3, r, g, b);
}
void Triangle::addListTriangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b)
{
    List *current = new List;
    current->triangle.x = x;
    current->triangle.y = y;
    current->triangle.x2 = x2;
    current->triangle.y2 = y2;
    current->triangle.x3 = x3;
    current->triangle.y3 = y3;
    current->triangle.r = r;
    current->triangle.g = g;
    current->triangle.b = b;
    current->next = Head;
    Head = current;
    Count++;
}

void Triangle::draw(Graphics &graphics)
{
    if (visible)
    {
        graphics.setColor(r, g, b);
        graphics.drawTriangle(x, y, x2, y2, x3, y3);
    }
}

void Triangle::drawTrail(Graphics &graphics)
{
    if (visible)
    {
        List *current = Head;

        while (current != nullptr)
        {
            graphics.setColor(current->triangle.r, current->triangle.g, current->triangle.b);
            graphics.drawTriangle(current->triangle.x, current->triangle.y, current->triangle.x2, current->triangle.y2, current->triangle.x3, current->triangle.y3);
            current = current->next;
        }
    }
}

void Triangle::hide(Graphics &graphics)
{
    graphics.setColor(0, 0, 0);
    graphics.drawTriangle(x, y, x2, y2, x3, y3);
    visible = false;
}

void Triangle::move(double dx, double dy, Graphics &graphics)
{

    hide(graphics);

    x += dx;
    y += dy;

    x2 += dx;
    y2 += dy;

    x3 += dx;
    y3 += dy;

    show(graphics);
}

void Triangle::resize(double factor, Graphics &graphics)
{
    hide(graphics);

    double centerX = (x + x2 + x3) / 3;
    double centerY = (y + y2 + y3) / 3;

    x = centerX + (x - centerX) * factor;
    y = centerY + (y - centerY) * factor;

    x2 = centerX + (x2 - centerX) * factor;
    y2 = centerY + (y2 - centerY) * factor;

    x3 = centerX + (x3 - centerX) * factor;
    y3 = centerY + (y3 - centerY) * factor;

    show(graphics);
}

std::ifstream &Triangle::read(std::ifstream &is)
{
    is >> x >> y >> x2 >> y2 >> x3 >> y3;

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
        double sx, sy, sx2, sy2, sx3, sy3;
        int sr, sg, sb;

        if (!(is >> sx >> sy >> sx2 >> sy2 >> sx3 >> sy3 >> sr >> sg >> sb))
        {
            if (is.eof() || is.bad())
                break;
            else
            {
                std::cerr << "Error reading circle trail data" << std::endl;
                break;
            }
        }

        addListTriangle(sx, sy, sx2, sy2, sx3, sy3, sr, sg, sb);
    }

    return is;
}

std::ofstream &Triangle::write(std::ofstream &os)
{

    os << "t ";
    os << getX() << " "
       << getY() << " "
       << getX2() << " "
       << getY2() << " "
       << getX3() << " "
       << getY3() << " "
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
            os << current->triangle.x << " "
               << current->triangle.y << " "
               << current->triangle.x2 << " "
               << current->triangle.y2 << " "
               << current->triangle.x3 << " "
               << current->triangle.y3 << " "
               << current->triangle.r << " "
               << current->triangle.g << " "
               << current->triangle.b << " ";
            current = current->next;
        }
    }

    return os;
}

void Triangle::setX2(double x2) { Triangle::x2 = x2; }
void Triangle::setY2(double y2) { Triangle::y2 = y2; }
void Triangle::setX3(double x3) { Triangle::x3 = x3; }
void Triangle::setY3(double y3) { Triangle::y3 = y3; }

double Triangle::getX2() { return x2; }
double Triangle::getY2() { return y2; }
double Triangle::getX3() { return x3; }
double Triangle::getY3() { return y3; }

bool Triangle::intersects(Shape &other)
{
    return other.intersects(*this);
}

bool Triangle::intersects(Circle &circle)
{
    Segment segment1(getX(), getY(), getX2(), getY2());
    Segment segment2(getX2(), getY2(), getX3(), getY3());
    Segment segment3(getX3(), getY3(), getX(), getY());

    bool in = false;

    double ABC = S(getX(), getY(), getX2(), getY2(), getX3(), getY3());

    double ABO = S(circle.getX(), circle.getY(), getX2(), getY2(), getX3(), getY3());
    double AOC = S(getX(), getY(), circle.getX(), circle.getY(), getX3(), getY3());
    double OBC = S(getX(), getY(), getX2(), getY2(), circle.getX(), circle.getY());

    in = (myFabs(ABC - ABO - AOC - OBC) < 0.01) ? true : false;

    return circle.intersects(segment1) || circle.intersects(segment2) || circle.intersects(segment3) || in;
}

bool Triangle::intersects(Segment &segment)
{

    double x1 = x, y1 = y;
    double x2 = Triangle::x2, y2 = Triangle::y2;
    double x3 = Triangle::x3, y3 = Triangle::y3;

    double sx1 = segment.getX(), sy1 = segment.getY();
    double sx2 = segment.getX2(), sy2 = segment.getY2();

    if (checkIntersection(sx1, sy1, sx2, sy2, x1, y1, x2, y2))
        return true;
    if (checkIntersection(sx1, sy1, sx2, sy2, x2, y2, x3, y3))
        return true;
    if (checkIntersection(sx1, sy1, sx2, sy2, x3, y3, x1, y1))
        return true;

    bool in1 = false;

    double ABC1 = S(getX(), getY(), getX2(), getY2(), getX3(), getY3());

    double ABO1 = S(sx1, sy1, getX2(), getY2(), getX3(), getY3());
    double AOC1 = S(getX(), getY(), sx1, sy1, getX3(), getY3());
    double OBC1 = S(getX(), getY(), getX2(), getY2(), sx1, sy1);

    bool in2 = false;

    double ABO2 = S(sx2, sy2, getX2(), getY2(), getX3(), getY3());
    double AOC2 = S(getX(), getY(), sx2, sy2, getX3(), getY3());
    double OBC2 = S(getX(), getY(), getX2(), getY2(), sx2, sy2);

    in1 = (myFabs(ABC1 - ABO1 - AOC1 - OBC1) < 0.01) ? true : false;
    in2 = (myFabs(ABC1 - ABO2 - AOC2 - OBC2) < 0.01) ? true : false;

    return (in1 || in2);
}

bool Triangle::intersects(Rectangle &rectangle)
{

    double ulx = rectangle.getX(), uly = rectangle.getY();
    double dlx = rectangle.getX(), dly = rectangle.getY() + rectangle.getHeight();
    double urx = rectangle.getX() + rectangle.getWidth(), ury = rectangle.getY();
    double drx = rectangle.getX() + rectangle.getWidth(), dry = rectangle.getY() + rectangle.getHeight();

    Triangle t1(dlx, dly, ulx, uly, urx, ury, 0, 0, 0, false);
    Triangle t2(dlx, dly, drx, dry, urx, ury, 0, 0, 0, false);
    Triangle t3(x, y, x2, y2, x3, y3, 0, 0, 0, false);

    return t1.intersects(t3) || t2.intersects(t3);
}

bool Triangle::intersects(Triangle &other)
{
    Segment side1(x, y, x2, y2);
    Segment side2(x2, y2, x3, y3);
    Segment side3(x3, y3, x, y);

    if (side1.intersects(other) || side2.intersects(other) || side2.intersects(other))
    {
        return true;
    }

    bool in1 = false;

    double ABC = S(other.getX(), other.getY(), other.getX2(), other.getY2(), other.getX3(), other.getY3());

    double ABO = S(x, y, other.getX2(), other.getY2(), other.getX3(), other.getY3());
    double AOC = S(other.getX(), other.getY(), x, y, other.getX3(), other.getY3());
    double OBC = S(other.getX(), other.getY(), other.getX2(), other.getY2(), x, y);

    in1 = (myFabs(ABC - ABO - AOC - OBC) < 0.01) ? true : false;

    bool in2 = false;

    double ABC2 = S(getX(), getY(), getX2(), getY2(), getX3(), getY3());

    double ABO2 = S(other.getX(), other.getY(), getX2(), getY2(), getX3(), getY3());
    double AOC2 = S(getX(), getY(), other.getX(), other.getY(), getX3(), getY3());
    double OBC2 = S(getX(), getY(), getX2(), getY2(), other.getX(), other.getY());

    in2 = (myFabs(ABC2 - ABO2 - AOC2 - OBC2) < 0.01) ? true : false;

    return in1 || in2;
}
