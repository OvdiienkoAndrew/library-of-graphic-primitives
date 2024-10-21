#include "Graphics.h"
#include <iostream>
namespace GLF
{

    void Graphics::draw(const sf::Text &drawable)
    {
        window.draw(drawable);
    }

    void Graphics::job_information()
    {
        sf::Font font;
        if (!font.loadFromFile("Font/Times_New_Roman-font.ttf"))
        {
            std::cerr << "Error loading font." << std::endl;
            return;
        }

        const char text[] = "Hints:\n\n\t1\t-\tadd circle;\n\t2\t-\tadd line;\n\t3\t-\tadd rectangle;\n\t4\t-\tadd triangle;\n\n\th\t -\twork with one shape;\n\tg\t -\twork with groups of figures;\n\tf\t -\twork with groups of groups of figures;\n\n\tspace\t-\tswitch visible;\n\n\t+\t-\tincrease the size of the shape;\n\t- \t-\treduce the size of the shape;\n\n\ttab\t-\tswitch shape;\n\n\tw   -\tmoves the shape up;\n\ts\t-\tmoves the shape down;\n\ta\t-\tmoves the shape left;\n\td\t-\tmoves the shape right;\n\n\tt\t-\tadd the trace;\n\n\tk\t-\tsave the program;\n\tl \t-\tload the program;\n\n\tz\t-\tmovement memorization;\n\tx\t-\treproduce the memorized movement;\n\tc\t-\tremove the memorized movement;\n\n\tn\t -\tcreate an aggregate;\n\tm\t-\tcreate an aggregate of aggregates;\n\n\ty\t-\tadd an aggregate to an aggregate group;\n\tu\t-\tremove an aggregate from an aggregate group;\n\ti \t-   add a figure to an aggregate;\n\to\t-\tremove a figure from an aggregate;\n\n\tesc\t-\tclose the window.";

        Graphics graphics(1200, 1000, "Shapes Demo Hints");

        sf::Text message(text, font, 19);
        message.setFillColor(sf::Color::White);
        message.setPosition((1200 - message.getGlobalBounds().width) / 2, (1000 - message.getGlobalBounds().height) / 2);

        while (graphics.open())
        {
            sf::Event event;

            while (graphics.pollEvent(event))
            {
                if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                {
                    graphics.close();
                }
            }

            graphics.clear();
            graphics.draw(message);
            graphics.display();
        }
    }

    Graphics::Graphics(double width, double height, const char *window_name) : window(sf::VideoMode(width, height), window_name), r(255), g(255), b(255) {}

    bool Graphics::open()
    {
        return window.isOpen();
    }

    void Graphics::clear()
    {
        window.clear(sf::Color(0, 0, 0));
    }

    void Graphics::display()
    {
        window.display();
    }

    void Graphics::close()
    {
        window.close();
    }

    bool Graphics::pollEvent(sf::Event &event)
    {
        return window.pollEvent(event);
    }

    void Graphics::setColor(int r, int g, int b)
    {
        Graphics::r = r;
        Graphics::g = g;
        Graphics::b = b;
    }

    void Graphics::drawSegment(double x1, double y1, double x2, double y2)
    {
        sf::Vertex segment[] = {
            sf::Vertex(sf::Vector2f(x1, y1), sf::Color(r, g, b)),
            sf::Vertex(sf::Vector2f(x2, y2), sf::Color(r, g, b))};
        window.draw(segment, 2, sf::Lines);
    }

    void Graphics::drawCircle(double x, double y, double radius)
    {
        sf::CircleShape circle(radius);
        circle.setPosition(x - radius, y - radius);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color(r, g, b));
        window.draw(circle);
    }

    void Graphics::drawRectangle(double x1, double y1, double width, double hiegh)
    {
        sf::RectangleShape rectangle(sf::Vector2f(width, hiegh));
        rectangle.setPosition(x1, y1);
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(sf::Color(r, g, b));
        window.draw(rectangle);
    }

    void Graphics::drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        sf::Vertex triangle[] = {
            sf::Vertex(sf::Vector2f(x1, y1), sf::Color(r, g, b)),
            sf::Vertex(sf::Vector2f(x2, y2), sf::Color(r, g, b)),
            sf::Vertex(sf::Vector2f(x3, y3), sf::Color(r, g, b))};

        sf::Vertex outline[] = {
            triangle[0], triangle[1],
            triangle[1], triangle[2],
            triangle[2], triangle[0]};

        window.draw(outline, 6, sf::Lines);
    }

}
