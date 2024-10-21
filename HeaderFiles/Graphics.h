#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <SFML/Graphics.hpp>

namespace GLF {

class Graphics {
private:
    sf::RenderWindow window;
    int r, g, b;

public:
    Graphics(double width, double height, const char* window_name);
    void job_information();
    void draw(const sf::Text& drawable);

    bool open();
    void clear();
    void display();
    void close();
    bool pollEvent(sf::Event& event);

    void setColor(int r, int g, int b);
    void drawSegment(double x1, double y1, double x2, double y2);
    void drawCircle(double x, double y, double radius);
    void drawRectangle(double x1, double y1, double x2, double y2);
    void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3); 

};

}

#endif 
