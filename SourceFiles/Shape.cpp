#include "Shape.h"

double Shape::S(double x1, double y1, double x2, double y2, double x3, double y3) { return 0.5 * myFabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)); }

template <typename T>
T Shape::myFabs(T x)
{
    return (x < 0.00) ? -x : x;
}

double Shape::mySqrt(double x)
{
    if (x < 0)
        return -1;
    if (x == 0 || x == 1)
        return x;
    double guess = x / 2.0;
    double epsilon = 1e-10;
    while (true)
    {
        double newGuess = (guess + x / guess) / 2.0;
        if (myFabs(newGuess - guess) < epsilon)
            break;
        guess = newGuess;
    }
    return guess;
}

Shape::Shape() : x(0), y(0), r(0), g(0), b(0), visible(true), Count(0) {}
Shape::Shape(double x, double y, int r, int g, int b, bool visible) : x(x), y(y), r(r), g(g), b(b), visible(visible), Count(0) {}

Shape::~Shape() {}

double Shape::getX() { return x; }
double Shape::getY() { return y; }
double Shape::getRadius() { return 0.00; }
int Shape::getColorRed() { return r; }
int Shape::getColorGreen() { return g; }
int Shape::getColorBlue() { return b; }
bool Shape::getVisible() { return visible; }

void Shape::setX(double x) { Shape::x = x; }
void Shape::setY(double y) { Shape::y = y; }
void Shape::setColor(int r, int g, int b)
{
    Shape::r = r;
    Shape::g = g;
    Shape::b = b;
}
void Shape::setVisible() { visible = !visible; }
void Shape::setV(bool visible) { Shape::visible = visible; }

double Shape::intersects(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

bool Shape::onSegment(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2 <= (x1 > x3 ? x1 : x3) && x2 >= (x1 < x3 ? x1 : x3) &&
            y2 <= (y1 > y3 ? y1 : y3) && y2 >= (y1 < y3 ? y1 : y3));
}

void Shape::setColorRed(int r) { Shape::r = r; }
void Shape::setColorGreen(int g) { Shape::g = g; }
void Shape::setColorBlue(int b) { Shape::b = b; }

void Shape::add(Shape *shape) {}

void Shape::remove(Shape *shape) {}
void Shape::addTrail(double prevX, double prevY, int r, int g, int b) {}
bool Shape::intersects(Shape &externalShape, int r1, int g1, int b1, int r2, int g2, int b2) { return false; }

void Shape::addTrail(double prevX, double prevY, double prevX2, double prevY2, int r, int g, int b) {}

void Shape::draw(Graphics &graphics) {}
void Shape::drawTrail(Graphics &graphics) {}
void Shape::show(Graphics &graphics)
{
    visible = true;
    draw(graphics);
}
void Shape::hide(Graphics &graphics) {}
void Shape::move(double dx, double dy, Graphics &graphics) {}
void Shape::resize(double factor, Graphics &graphics) {}
std::ifstream &Shape::read(std::ifstream &is) { return is; }
std::ofstream &Shape::write(std::ofstream &os) { return os; }

double Shape::getX2() { return 1; }
double Shape::getY2() { return 1; }
double Shape::getX3() { return 1; }
double Shape::getY3() { return 1; }

bool Shape::intersects(Shape &other) { return false; }
bool Shape::intersects(Segment &other) { return false; }
bool Shape::intersects(Circle &other) { return false; }
bool Shape::intersects(Rectangle &other) { return false; }
bool Shape::intersects(Triangle &other) { return false; }

double Shape::sizeLine(double Ax, double Ay, double Bx, double By)
{
    return mySqrt((Bx - Ax) * (Bx - Ax) + (By - Ay) * (By - Ay));
}

std::ofstream &operator<<(std::ofstream &os, Shape &shape)
{
    shape.write(os);
    return os;
}

std::ifstream &operator>>(std::ifstream &os, Shape &shape)
{
    shape.read(os);
    return os;
}

void Shape::addListSegment(double x, double y, double x2, double y2, int r, int g, int b) {}
void Shape::addListCircle(double x, double y, double radius, int r, int g, int b) {}
void Shape::addListRectangle(double x, double y, double width, double height, int r, int g, int b) {}
void Shape::addListTriangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b) {}

double Shape::getWidth() { return 0; }
double Shape::getHeight() { return 0; }

bool Shape::doIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    double d1 = direction(x1, y1, x2, y2, x3, y3);
    double d2 = direction(x1, y1, x2, y2, x4, y4);
    double d3 = direction(x3, y3, x4, y4, x1, y1);
    double d4 = direction(x3, y3, x4, y4, x2, y2);

    if (d1 != d2 && d3 != d4)
    {
        return true;
    }

    if (d1 == 0 && onSegment(x1, y1, x3, y3, x2, y2))
        return true;
    if (d2 == 0 && onSegment(x1, y1, x4, y4, x2, y2))
        return true;
    if (d3 == 0 && onSegment(x3, y3, x1, y1, x4, y4))
        return true;
    if (d4 == 0 && onSegment(x3, y3, x2, y2, x4, y4))
        return true;

    return false;
}

bool Shape::checkIntersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

    double d1 = direction(x3, y3, x4, y4, x1, y1);
    double d2 = direction(x3, y3, x4, y4, x2, y2);
    double d3 = direction(x1, y1, x2, y2, x3, y3);
    double d4 = direction(x1, y1, x2, y2, x4, y4);
    if (d1 * d2 < 0 && d3 * d4 < 0)
    {
        return true;
    }

    return false;
}

double Shape::direction(double x1, double y1, double x2, double y2, double x3, double y3)
{

    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

bool Shape::isPointInTriangle(double px, double py, double x1, double y1, double x2, double y2, double x3, double y3)
{

    double d1 = direction(px, py, x1, y1, x2, y2);
    double d2 = direction(px, py, x2, y2, x3, y3);
    double d3 = direction(px, py, x3, y3, x1, y1);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void Shape::addList(Graphics &graphics) {}
void Shape::addShape(Shape *shape) {}
void Shape::removeShape(Shape *shape) {}
int Shape::getSize() { return 1; }

void Shape::findTheInterects(Shape **shape, int shapeSize) {}
void Shape::addGroup(Group *shape) {}
void Shape::removeGroup(Group *group) {}

bool Shape::compare(Group *group) { return false; }