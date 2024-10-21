#include <iostream>
#include <fstream>
#include <ctime>
#include "Graphics.h"
#include "Shape.h"
#include "Group.h"
#include "Segment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Group.h"
#include "SuperGroup.h"
using namespace GLF;
using namespace std;
void input(Shape **&Shapes, int &sizeShape, Shape **&GroupsOfShapes, int &sizeGroup, Shape **&GroupsOfGroups, int &sizeGroups);
void output(Shape **&Shapes, int &sizeShape, Shape **&GroupsOfShapes, int &sizeGroup, Shape **&GroupsOfGroups, int &sizeGroups);
void push_back(Shape **&arr, int &size, Shape *value);
void addToTrajectory(double *&DX, double *&DY, double dx, double dy, int &sizet);
void moveAlongTrajectory(double *&DX, double *&DY, int sizeTheTrail, Shape **Shapes, Shape **GroupsOfShapes, Shape **GroupsOfGroups, Graphics &graphics, bool trail, int sizeShape, int sizeGroup, int sizeGroups, int ShapeI, int GroupI, int GroupsI, bool isShape, bool isGroup, bool isGroups);
void clearTrajectory(double *&DX, double *&DY, int &sizet);

void OpenFileFromArgv(const char *filename, Shape **&Shapes, int &sizeShape, Shape **&GroupsOfShapes, int &sizeGroup, Shape **&GroupsOfGroups, int &sizeGroups);
char *GetFileFromArgv(int argc, char *argv[]);

const double STEP = 5.5, FACTOR1 = 1.1, FACTOR2 = 0.9;

Shape **Shapes = nullptr;
Shape **GroupsOfShapes = nullptr;
Shape **GroupsOfGroups = nullptr;

int sizeShape = 0;
int sizeGroup = 0;
int sizeGroups = 0;

int ShapeI = 0;
int GroupI = 0;
int GroupsI = 0;

bool isShape = false;
bool isGroup = false;
bool isGroups = false;

double *DX = nullptr, *DY = nullptr;
int sizeTheTrail = 0;
bool traectory = false;
bool trail = false;

bool show = false;

int main(int argc, char *argv[])
{

    char *text = GetFileFromArgv(argc, argv);

    if (text)
    {
        OpenFileFromArgv(text, Shapes, sizeShape, GroupsOfShapes, sizeGroup, GroupsOfGroups, sizeGroups);
    }

    srand(time(nullptr));
    Graphics graphics(800, 600, "Shapes Demo");

    while (graphics.open())
    {
        sf::Event event;
        graphics.clear();

        while (graphics.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                graphics.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {

                int r = rand() % 256;
                int g = rand() % 256;
                int b = rand() % 256;

                switch (event.key.code)
                {

                case sf::Keyboard::F1:
                    graphics.job_information();
                    break;

                case sf::Keyboard::G:
                    isShape = false;
                    isGroup = true;
                    isGroups = false;
                    break;

                case sf::Keyboard::H:
                    isShape = true;
                    isGroup = false;
                    isGroups = false;
                    break;

                case sf::Keyboard::F:
                    isShape = false;
                    isGroup = false;
                    isGroups = true;
                    break;

                case sf::Keyboard::Tab:

                    if (isShape && isShape > 0)
                    {
                        ShapeI = (ShapeI + 1) % sizeShape;
                    }
                    else if (isGroup && sizeGroup > 0)
                    {
                        GroupI = (GroupI + 1) % sizeGroup;
                    }
                    else if (isGroups && sizeGroups > 0)
                    {
                        GroupsI = (GroupsI + 1) % sizeGroups;
                    }

                    break;

                case sf::Keyboard::Num1:
                    push_back(Shapes, sizeShape, new Circle(25, 25, 25, r, g, b, true));
                    break;

                case sf::Keyboard::Num2:
                {
                    push_back(Shapes, sizeShape, new Segment(10, 10, 75, 75, r, g, b, true));
                }
                break;

                case sf::Keyboard::Num3:
                {
                    push_back(Shapes, sizeShape, new Rectangle(10, 10, 50, 100, r, g, b, true));
                }
                break;

                case sf::Keyboard::Num4:
                {
                    push_back(Shapes, sizeShape, new Triangle(20, 75, 60, 75, 40, 30, r, g, b, true));
                }
                break;

                case sf::Keyboard::N:
                {
                    push_back(GroupsOfShapes, sizeGroup, new Group());
                }
                break;

                case sf::Keyboard::M:
                {
                    push_back(GroupsOfGroups, sizeGroups, (Group *)new SGroup());
                }
                break;

                case sf::Keyboard::Y:

                    if (sizeGroup > 0 && sizeGroups > 0)
                        GroupsOfGroups[GroupsI]->addGroup((Group *)GroupsOfShapes[GroupI]);

                    break;

                case sf::Keyboard::U:

                    if (sizeGroups > 0 && GroupsOfShapes != nullptr && sizeGroups > 0 && GroupsOfShapes != nullptr && Shapes != nullptr && sizeShape > 0)
                    {
                        GroupsOfGroups[GroupsI]->removeGroup((Group *)GroupsOfShapes[GroupI]); // не работает

                        if (isShape && isShape > 0)
                        {
                            ShapeI = ShapeI % sizeShape;
                        }
                        else if (isGroup && sizeGroup > 0)
                        {
                            GroupI = GroupI % sizeGroup;
                        }
                        else if (isGroups && sizeGroups > 0)
                        {
                            GroupsI = GroupsI % sizeGroups;
                        }
                    }

                    break;

                case sf::Keyboard::I:

                    if (sizeShape > 0 && GroupsOfShapes != nullptr)
                        GroupsOfShapes[GroupI]->addShape(Shapes[ShapeI]);

                    break;

                case sf::Keyboard::O:

                    if (Shapes != nullptr && GroupsOfShapes != nullptr && sizeGroup > 0 && sizeShape > 0)
                    {
                        GroupsOfShapes[GroupI]->removeShape(Shapes[ShapeI]);

                        if (isShape && isShape > 0)
                        {
                            ShapeI = ShapeI % sizeShape;
                        }
                        else if (isGroup && sizeGroup > 0)
                        {
                            GroupI = GroupI % sizeGroup;
                        }
                        else if (isGroups && sizeGroups > 0)
                        {
                            GroupsI = GroupsI % sizeGroups;
                        }
                    }

                    break;

                case sf::Keyboard::W:
                case sf::Keyboard::S:
                case sf::Keyboard::D:
                case sf::Keyboard::A:
                {
                    double dx = (event.key.code == sf::Keyboard::D) ? STEP : (event.key.code == sf::Keyboard::A) ? -STEP
                                                                                                                 : 0;
                    double dy = (event.key.code == sf::Keyboard::W) ? -STEP : (event.key.code == sf::Keyboard::S) ? STEP
                                                                                                                  : 0;

                    if (isShape && sizeShape > 0)
                    {

                        Shapes[ShapeI]->move(dx, dy, graphics);

                        for (int i = 0; i < sizeShape; i++)
                        {
                            if (ShapeI != i)
                            {

                                if (Shapes[ShapeI]->intersects(*Shapes[i]))
                                {
                                    Shapes[ShapeI]->setColor((Shapes[ShapeI]->getColorRed() + 10) % 256,
                                                             (Shapes[ShapeI]->getColorGreen() + 10) % 256,
                                                             (Shapes[ShapeI]->getColorBlue() + 10) % 256);
                                    break;
                                }
                            }
                        }

                        if (trail)
                        {
                            if (typeid(*Shapes[ShapeI]) == typeid(Segment))
                            {
                                Shape *segment = (Segment *)(Shapes[ShapeI]);
                                segment->addListSegment(segment->getX(), segment->getY(), segment->getX2(), segment->getY2(), segment->getColorRed(), segment->getColorGreen(), segment->getColorBlue());
                            }
                            else if (typeid(*Shapes[ShapeI]) == typeid(Circle))
                            {
                                Shape *circle = (Circle *)(Shapes[ShapeI]);
                                circle->addListCircle(circle->getX(), circle->getY(), circle->getRadius(), circle->getColorRed(), circle->getColorGreen(), circle->getColorBlue());
                            }
                            else if (typeid(*Shapes[ShapeI]) == typeid(Rectangle))
                            {
                                Shape *rectangle = (Rectangle *)(Shapes[ShapeI]);
                                rectangle->addListRectangle(rectangle->getX(), rectangle->getY(), rectangle->getWidth(), rectangle->getHeight(), rectangle->getColorRed(), rectangle->getColorGreen(), rectangle->getColorBlue());
                            }
                            else if (typeid(*Shapes[ShapeI]) == typeid(Triangle))
                            {
                                Shape *triangle = (Triangle *)(Shapes[ShapeI]);
                                triangle->addListTriangle(triangle->getX(), triangle->getY(), triangle->getX2(), triangle->getY2(), triangle->getX3(), triangle->getY3(), triangle->getColorRed(), triangle->getColorGreen(), triangle->getColorBlue());
                            }
                        }
                    }
                    else if (isGroup && sizeGroup > 0)
                    {

                        GroupsOfShapes[GroupI]->move(dx, dy, graphics);
                        GroupsOfShapes[GroupI]->findTheInterects(Shapes, sizeShape);

                        if (trail)
                        {
                            GroupsOfShapes[GroupI]->addList(graphics);
                        }
                    }
                    else if (isGroups && sizeGroups > 0)
                    {
                        GroupsOfGroups[GroupsI]->move(dx, dy, graphics);
                        GroupsOfGroups[GroupsI]->findTheInterects(Shapes, sizeShape);

                        if (trail)
                        {
                            GroupsOfGroups[GroupsI]->addList(graphics);
                        }
                    }

                    if (traectory)
                        addToTrajectory(DX, DY, dx, dy, sizeTheTrail);
                }

                break;

                case sf::Keyboard::Equal:
                case sf::Keyboard::Dash:

                {
                    double factor = (event.key.code == sf::Keyboard::Equal) ? FACTOR1 : FACTOR2;

                    if (isShape && sizeShape > 0)
                    {

                        Shapes[ShapeI]->resize(factor, graphics);

                        for (int i = 0; i < sizeShape; i++)
                        {
                            if (ShapeI != i)
                            {

                                if (Shapes[ShapeI]->intersects(*Shapes[i]))
                                {
                                    Shapes[ShapeI]->setColor((Shapes[ShapeI]->getColorRed() + 10) % 256,
                                                             (Shapes[ShapeI]->getColorGreen() + 10) % 256,
                                                             (Shapes[ShapeI]->getColorBlue() + 10) % 256);
                                    break;
                                }
                            }
                        }
                    }
                    else if (isGroup && sizeGroup > 0)
                    {
                        GroupsOfShapes[GroupI]->resize(factor, graphics);
                        GroupsOfShapes[GroupI]->findTheInterects(Shapes, sizeShape);

                        if (trail)
                        {
                            GroupsOfShapes[GroupI]->addList(graphics);
                        }
                    }
                    else if (isGroups && sizeGroups > 0)
                    {
                        GroupsOfGroups[GroupsI]->resize(factor, graphics);
                        GroupsOfGroups[GroupsI]->findTheInterects(Shapes, sizeShape);

                        if (trail)
                        {
                            GroupsOfGroups[GroupsI]->addList(graphics);
                        }
                    }
                }

                break;

                case sf::Keyboard::Space:

                    if (isShape && sizeShape > 0)
                    {
                        Shapes[ShapeI]->setVisible();
                    }
                    else if (isGroup && sizeGroup > 0)
                    {
                        GroupsOfShapes[GroupI]->setVisible();
                    }
                    else if (isGroups && sizeGroups > 0)
                    {
                        GroupsOfGroups[GroupsI]->setVisible();
                    }

                    break;

                case sf::Keyboard::T:
                    trail = !trail;
                    break;

                case sf::Keyboard::K:
                    input(Shapes, sizeShape, GroupsOfShapes, sizeGroup, GroupsOfGroups, sizeGroups);
                    break;

                case sf::Keyboard::L:
                    output(Shapes, sizeShape, GroupsOfShapes, sizeGroup, GroupsOfGroups, sizeGroups);
                    break;

                case sf::Keyboard::Z:
                    traectory = !traectory;
                    break;

                case sf::Keyboard::X:
                    show = !show;
                    break;

                case sf::Keyboard::C:
                    clearTrajectory(DX, DY, sizeTheTrail);
                    break;

                default:
                    break;
                }
            }
        }

        graphics.clear();

        for (int i = 0; i < sizeShape; i++)
        {
            if (Shapes != nullptr && Shapes[i] != nullptr)
            {
                Shapes[i]->draw(graphics);
                if (trail && isShape)
                {
                    Shapes[ShapeI]->drawTrail(graphics);
                }
            }
        }

        for (int i = 0; i < sizeGroup; i++)
        {
            if (GroupsOfShapes != nullptr && GroupsOfShapes[i] != nullptr)
            {
                GroupsOfShapes[i]->draw(graphics);
                if (trail && isGroup)
                {
                    GroupsOfShapes[GroupI]->drawTrail(graphics);
                }
            }
        }

        for (int i = 0; i < sizeGroups; i++)
        {
            if (GroupsOfGroups != nullptr && GroupsOfGroups[i] != nullptr)
            {
                GroupsOfGroups[i]->draw(graphics);
                if (trail && isGroups)
                {
                    GroupsOfGroups[GroupsI]->drawTrail(graphics);
                }
            }
        }

        if (show)
        {
            moveAlongTrajectory(DX, DY, sizeTheTrail, Shapes, GroupsOfShapes, GroupsOfGroups, graphics, trail, sizeShape, sizeGroup, sizeGroups, ShapeI, GroupI, GroupsI, isShape, isGroup, isGroups);
            show = !show;
        }

        graphics.display();
    }

    return 0;
}

void input(Shape **&Shapes, int &sizeShape, Shape **&GroupsOfShapes, int &sizeGroup, Shape **&GroupsOfGroups, int &sizeGroups)
{
    sf::Font font;
    if (!font.loadFromFile("Font/Times_New_Roman-font.ttf"))
    {
        cerr << "Error loading font.\n";
        return;
    }

    const int MAX_LENGHT = 151;
    char inputText[MAX_LENGHT] = {'\0'};

    const int WIDTH = 1700, HEIGHT = 900;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Save Window");

    bool isResult = false;

    sf::Text label("Enter the file name to save:", font, 24);
    label.setFillColor(sf::Color::White);
    label.setPosition((WIDTH - label.getGlobalBounds().width) / 2, HEIGHT / 2 - 50);

    sf::Text inputField("", font, 24);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition((WIDTH - inputField.getGlobalBounds().width) / 2, HEIGHT / 2);

    sf::Text result("The program saved.", font, 24);
    result.setFillColor(sf::Color::White);
    result.setPosition((WIDTH - result.getGlobalBounds().width) / 2, HEIGHT / 2 + 50);

    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color::Black);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
            {
                if (event.text.unicode == '\b')
                {
                    int len = strlen(inputText);
                    if (len > 0)
                        inputText[len - 1] = '\0';
                }
                else if (event.text.unicode != '\r')
                {
                    int len = strlen(inputText);
                    if (len < MAX_LENGHT - 1)
                    {
                        inputText[len] = (char)(event.text.unicode);
                        inputText[len + 1] = '\0';
                    }
                }
                inputField.setString(inputText);
                inputField.setPosition((WIDTH - inputField.getGlobalBounds().width) / 2,
                                       (HEIGHT - label.getGlobalBounds().height) / 2 + label.getGlobalBounds().height + 100);
            }

            if (!isResult && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                ofstream file;
                file.open(inputText);
                if (!file.is_open())
                {
                    cerr << "Error opening file.\n";
                }
                else
                {
                    file << sizeShape << "\n";
                    for (int i = 0; i < sizeShape; i++)
                    {
                        file << *Shapes[i] << "\n";
                    }

                    file << "\n"
                         << sizeGroup << "\n";
                    for (int i = 0; i < sizeGroup; i++)
                    {
                        file << *GroupsOfShapes[i] << "\n";
                    }

                    file << "\n"
                         << sizeGroups << "\n";

                    for (int i = 0; i < sizeGroups; i++)
                    {
                        file << *GroupsOfGroups[i] << "\n";
                    }

                    file << "\n";

                    file.close();
                }

                isResult = true;
            }
        }
        if (isResult)
        {
            window.draw(result);
        }
        else
        {
            window.draw(label);
            window.draw(inputField);
        }
        window.display();
    }
}

void output(Shape **&Shapes, int &sizeShape, Shape **&GroupsOfShapes, int &sizeGroup, Shape **&GroupsOfGroups, int &sizeGroups)
{
    sf::Font font;
    if (!font.loadFromFile("Font/Times_New_Roman-font.ttf"))
    {
        cerr << "Error loading font.\n";
        return;
    }

    const int MAX_LENGHT = 151;
    char inputText[MAX_LENGHT] = {'\0'};

    const int WIDTH = 1700, HEIGHT = 900;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Load Window");

    bool isResult = false;

    sf::Text label("Enter the file name to load:", font, 24);
    label.setFillColor(sf::Color::White);
    label.setPosition((WIDTH - label.getGlobalBounds().width) / 2, HEIGHT / 2 - 50);

    sf::Text inputField("", font, 24);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition((WIDTH - inputField.getGlobalBounds().width) / 2, HEIGHT / 2);

    sf::Text result("The program loaded.", font, 24);
    result.setFillColor(sf::Color::White);
    result.setPosition((WIDTH - result.getGlobalBounds().width) / 2, HEIGHT / 2 + 50);
    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color::Black);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
            {
                if (event.text.unicode == '\b')
                {
                    int len = strlen(inputText);
                    if (len > 0)
                        inputText[len - 1] = '\0';
                }
                else if (event.text.unicode != '\r')
                {
                    int len = strlen(inputText);
                    if (len < MAX_LENGHT - 1)
                    {
                        inputText[len] = (char)(event.text.unicode);
                        inputText[len + 1] = '\0';
                    }
                }
                inputField.setString(inputText);
                inputField.setPosition((WIDTH - inputField.getGlobalBounds().width) / 2,
                                       (HEIGHT - label.getGlobalBounds().height) / 2 + label.getGlobalBounds().height + 100);
            }

            if (!isResult && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                ifstream file;
                file.open(inputText);
                if (!file.is_open())
                {
                    cerr << "Error opening file.\n";
                }
                else
                {
                    if (Shapes)
                    {
                        for (int i = 0; i < sizeShape; i++)
                        {
                            Shapes[i] = nullptr;
                        }
                        Shapes = nullptr;
                    }

                    file >> sizeShape;

                    Shapes = new Shape *[sizeShape];

                    for (int i = 0; i < sizeShape; i++)
                    {
                        char type = '\0';
                        file >> type;
                        Shape *shape = nullptr;

                        switch (type)
                        {
                        case 'c':
                            shape = new Circle();
                            break;
                        case 's':
                            shape = new Segment();
                            break;
                        case 't':
                            shape = new Triangle();
                            break;
                        case 'r':
                            shape = new Rectangle();
                            break;
                        default:
                            continue;
                        }

                        if (shape)
                        {
                            file >> *shape;
                            Shapes[i] = shape;
                        }
                    }

                    if (GroupsOfShapes != nullptr)
                    {
                        for (int i = 0; i < sizeGroup; i++)
                        {
                            GroupsOfShapes[i] = nullptr;
                        }
                        GroupsOfShapes = nullptr;
                    }

                    file >> sizeGroup;

                    GroupsOfShapes = new Shape *[sizeGroup];

                    for (int i = 0; i < sizeGroup; i++)
                    {
                        GroupsOfShapes[i] = new Group();

                        int a = 0;
                        file >> a;

                        for (int j = 0; j < a; j++)
                        {
                            char type = '\0';
                            file >> type;
                            Shape *shape = nullptr;

                            switch (type)
                            {
                            case 'c':
                                shape = new Circle();
                                break;
                            case 's':
                                shape = new Segment();
                                break;
                            case 't':
                                shape = new Triangle();
                                break;
                            case 'r':
                                shape = new Rectangle();
                                break;
                            default:
                                continue;
                            }

                            file >> *shape;

                            for (int k = 0; k < sizeShape; k++)
                            {
                                if (((Shapes[k]->getX() - shape->getX()) < 0.000001) && ((Shapes[k]->getY() - shape->getY()) < 0.000001) && (Shapes[k]->getColorRed() - shape->getColorRed() == 0) && (Shapes[k]->getColorGreen() - shape->getColorGreen() == 0) && (Shapes[k]->getColorBlue() - shape->getColorBlue() == 0))
                                {
                                    GroupsOfShapes[i]->addShape(Shapes[k]);
                                }
                            }
                        }
                    }

                    if (GroupsOfGroups != nullptr)
                    {
                        for (int i = 0; i < sizeGroups; i++)
                        {
                            GroupsOfGroups[i] = nullptr;
                        }
                        GroupsOfGroups = nullptr;
                    }

                    int count = 0;
                    sizeGroups = 0;

                    file >> count;

                    GroupsOfGroups = new Shape *[count];

                    for (int i = 0; i < count; i++)
                    {
                        GroupsOfGroups[i] = new SGroup();
                    }

                    for (int i = 0; i < count; i++)
                    {
                        int Groupsi = 0;
                        file >> Groupsi;

                        for (int j = 0; j < Groupsi; j++)
                        {
                            int Shapesi = 0;
                            file >> Shapesi;

                            Shape *t = new Group();

                            for (int k = 0; k < Shapesi; k++)
                            {
                                char type = '\0';
                                file >> type;
                                Shape *shape = nullptr;

                                switch (type)
                                {
                                case 'c':
                                    shape = new Circle();
                                    break;
                                case 's':
                                    shape = new Segment();
                                    break;
                                case 't':
                                    shape = new Triangle();
                                    break;
                                case 'r':
                                    shape = new Rectangle();
                                    break;
                                default:
                                    continue;
                                }

                                file >> *shape;

                                for (int m = 0; m < sizeShape; m++)
                                {
                                    if (((Shapes[m]->getX() - shape->getX()) < 0.000001) && ((Shapes[m]->getY() - shape->getY()) < 0.000001) && (Shapes[m]->getColorRed() - shape->getColorRed() == 0) && (Shapes[m]->getColorGreen() - shape->getColorGreen() == 0) && (Shapes[m]->getColorBlue() - shape->getColorBlue() == 0))
                                    {
                                        t->addShape(Shapes[m]);
                                    }
                                }
                            }

                            for (int k = 0; k < sizeGroup; k++)
                            {
                                if (t->compare((Group *)GroupsOfShapes[k]))
                                {
                                    GroupsOfGroups[i]->addGroup((Group *)GroupsOfShapes[k]);
                                    break;
                                }
                            }
                        }
                    }
                    sizeGroups = count;
                    file.close();
                }

                isResult = true;
            }
        }
        if (isResult)
        {
            window.draw(result);
        }
        else
        {
            window.draw(label);
            window.draw(inputField);
        }
        window.display();
    }
}

void push_back(Shape **&arr, int &size, Shape *value)
{
    Shape **newArray = new Shape *[size + 1];

    for (int i = 0; i < size; i++)
    {
        newArray[i] = arr[i];
    }

    newArray[size] = value;

    delete[] arr;
    arr = nullptr;
    arr = newArray;
    size++;
}

void addToTrajectory(double *&DX, double *&DY, double dx, double dy, int &sizet)
{
    double *newDX = new double[sizet + 1];
    double *newDY = new double[sizet + 1];
    for (int i = 0; i < sizet; i++)
    {
        newDX[i] = DX[i];
        newDY[i] = DY[i];
    }
    newDX[sizet] = dx;
    newDY[sizet] = dy;
    delete[] DX;
    delete[] DY;
    DX = newDX;
    DY = newDY;
    sizet++;
}

void moveAlongTrajectory(double *&DX, double *&DY, int sizeTheTrail, Shape **Shapes, Shape **GroupsOfShapes, Shape **GroupsOfGroups, Graphics &graphics, bool trail, int sizeShape, int sizeGroup, int sizeGroups, int ShapeI, int GroupI, int GroupsI, bool isShape, bool isGroup, bool isGroups)
{
    if (DX != nullptr && DY != nullptr)
    {
        for (int i = 0; i < sizeTheTrail; i++)
        {
            graphics.clear();

            if (isShape && sizeShape > 0)
            {

                Shapes[ShapeI]->move(DX[i], DY[i], graphics);

                for (int i = 0; i < sizeShape; i++)
                {
                    if (ShapeI != i)
                    {

                        if (Shapes[ShapeI]->intersects(*Shapes[i]))
                        {
                            Shapes[ShapeI]->setColor((Shapes[ShapeI]->getColorRed() + 10) % 256,
                                                     (Shapes[ShapeI]->getColorGreen() + 10) % 256,
                                                     (Shapes[ShapeI]->getColorBlue() + 10) % 256);
                            break;
                        }
                    }
                }

                if (trail)
                {
                    if (typeid(*Shapes[ShapeI]) == typeid(Segment))
                    {
                        Shape *segment = (Segment *)(Shapes[ShapeI]);
                        segment->addListSegment(segment->getX(), segment->getY(), segment->getX2(), segment->getY2(), segment->getColorRed(), segment->getColorGreen(), segment->getColorBlue());
                    }
                    else if (typeid(*Shapes[ShapeI]) == typeid(Circle))
                    {
                        Shape *circle = (Circle *)(Shapes[ShapeI]);
                        circle->addListCircle(circle->getX(), circle->getY(), circle->getRadius(), circle->getColorRed(), circle->getColorGreen(), circle->getColorBlue());
                    }
                    else if (typeid(*Shapes[ShapeI]) == typeid(Rectangle))
                    {
                        Shape *rectangle = (Rectangle *)(Shapes[ShapeI]);
                        rectangle->addListRectangle(rectangle->getX(), rectangle->getY(), rectangle->getWidth(), rectangle->getHeight(), rectangle->getColorRed(), rectangle->getColorGreen(), rectangle->getColorBlue());
                    }
                    else if (typeid(*Shapes[ShapeI]) == typeid(Triangle))
                    {
                        Shape *triangle = (Triangle *)(Shapes[ShapeI]);
                        triangle->addListTriangle(triangle->getX(), triangle->getY(), triangle->getX2(), triangle->getY2(), triangle->getX3(), triangle->getY3(), triangle->getColorRed(), triangle->getColorGreen(), triangle->getColorBlue());
                    }
                }
            }
            else if (isGroup && sizeGroup > 0)
            {

                GroupsOfShapes[GroupI]->move(DX[i], DY[i], graphics);
                GroupsOfShapes[GroupI]->findTheInterects(Shapes, sizeShape);

                if (trail)
                {
                    GroupsOfShapes[GroupI]->addList(graphics);
                }
            }
            else if (isGroups && sizeGroups > 0)
            {
                GroupsOfGroups[GroupsI]->move(DX[i], DY[i], graphics);
                GroupsOfGroups[GroupsI]->findTheInterects(Shapes, sizeShape);

                if (trail)
                {
                    GroupsOfGroups[GroupsI]->addList(graphics);
                }
            }

            for (int i = 0; i < sizeShape; i++)
            {
                if (Shapes[i] != nullptr)
                {
                    Shapes[i]->draw(graphics);
                    if (trail && isShape)
                    {
                        Shapes[ShapeI]->drawTrail(graphics);
                    }
                }
            }

            for (int i = 0; i < sizeGroup; i++)
            {
                if (GroupsOfShapes[i] != nullptr)
                {
                    GroupsOfShapes[i]->draw(graphics);
                    if (trail && isGroup)
                    {
                        GroupsOfShapes[GroupI]->drawTrail(graphics);
                    }
                }
            }

            for (int i = 0; i < sizeGroups; i++)
            {
                if (GroupsOfGroups[i] != nullptr)
                {
                    GroupsOfGroups[i]->draw(graphics);
                    if (trail && isGroups)
                    {
                        GroupsOfGroups[GroupsI]->drawTrail(graphics);
                    }
                }
            }

            graphics.display();
            sf::sleep(sf::seconds(0.1));
        }
    }
}

void clearTrajectory(double *&DX, double *&DY, int &sizet)
{
    delete[] DX;
    delete[] DY;
    DX = nullptr;
    DY = nullptr;
    sizet = 0;
}

char *GetFileFromArgv(int argc, char *argv[])
{
    return (argc > 1) ? argv[1] : nullptr;
}

void OpenFileFromArgv(const char *filename, Shape **&Shapes, int &sizeShape, Shape **&GroupsOfShapes, int &sizeGroup, Shape **&GroupsOfGroups, int &sizeGroups)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    if (Shapes)
    {
        for (int i = 0; i < sizeShape; i++)
        {
            Shapes[i] = nullptr;
        }
        Shapes = nullptr;
    }

    file >> sizeShape;

    Shapes = new Shape *[sizeShape];

    for (int i = 0; i < sizeShape; i++)
    {
        char type = '\0';
        file >> type;
        Shape *shape = nullptr;

        switch (type)
        {
        case 'c':
            shape = new Circle();
            break;
        case 's':
            shape = new Segment();
            break;
        case 't':
            shape = new Triangle();
            break;
        case 'r':
            shape = new Rectangle();
            break;
        default:
            continue;
        }

        if (shape)
        {
            file >> *shape;
            Shapes[i] = shape;
        }
    }

    if (GroupsOfShapes != nullptr)
    {
        for (int i = 0; i < sizeGroup; i++)
        {
            GroupsOfShapes[i] = nullptr;
        }
        GroupsOfShapes = nullptr;
    }

    file >> sizeGroup;

    GroupsOfShapes = new Shape *[sizeGroup];

    for (int i = 0; i < sizeGroup; i++)
    {
        GroupsOfShapes[i] = new Group();

        int a = 0;
        file >> a;

        for (int j = 0; j < a; j++)
        {
            char type = '\0';
            file >> type;
            Shape *shape = nullptr;

            switch (type)
            {
            case 'c':
                shape = new Circle();
                break;
            case 's':
                shape = new Segment();
                break;
            case 't':
                shape = new Triangle();
                break;
            case 'r':
                shape = new Rectangle();
                break;
            default:
                continue;
            }

            file >> *shape;

            for (int k = 0; k < sizeShape; k++)
            {
                if (((Shapes[k]->getX() - shape->getX()) < 0.000001) && ((Shapes[k]->getY() - shape->getY()) < 0.000001) && (Shapes[k]->getColorRed() - shape->getColorRed() == 0) && (Shapes[k]->getColorGreen() - shape->getColorGreen() == 0) && (Shapes[k]->getColorBlue() - shape->getColorBlue() == 0))
                {
                    GroupsOfShapes[i]->addShape(Shapes[k]);
                }
            }
        }
    }

    if (GroupsOfGroups != nullptr)
    {
        for (int i = 0; i < sizeGroups; i++)
        {
            GroupsOfGroups[i] = nullptr;
        }
        GroupsOfGroups = nullptr;
    }

    int count = 0;
    sizeGroups = 0;

    file >> count;

    GroupsOfGroups = new Shape *[count];

    for (int i = 0; i < count; i++)
    {
        GroupsOfGroups[i] = new SGroup();
    }

    for (int i = 0; i < count; i++)
    {
        int Groupsi = 0;
        file >> Groupsi;

        for (int j = 0; j < Groupsi; j++)
        {
            int Shapesi = 0;
            file >> Shapesi;

            Shape *t = new Group();

            for (int k = 0; k < Shapesi; k++)
            {
                char type = '\0';
                file >> type;
                Shape *shape = nullptr;

                switch (type)
                {
                case 'c':
                    shape = new Circle();
                    break;
                case 's':
                    shape = new Segment();
                    break;
                case 't':
                    shape = new Triangle();
                    break;
                case 'r':
                    shape = new Rectangle();
                    break;
                default:
                    continue;
                }

                file >> *shape;

                for (int m = 0; m < sizeShape; m++)
                {
                    if (((Shapes[m]->getX() - shape->getX()) < 0.000001) && ((Shapes[m]->getY() - shape->getY()) < 0.000001) && (Shapes[m]->getColorRed() - shape->getColorRed() == 0) && (Shapes[m]->getColorGreen() - shape->getColorGreen() == 0) && (Shapes[m]->getColorBlue() - shape->getColorBlue() == 0))
                    {
                        t->addShape(Shapes[m]);
                    }
                }
            }

            for (int k = 0; k < sizeGroup; k++)
            {
                if (t->compare((Group *)GroupsOfShapes[k]))
                {
                    GroupsOfGroups[i]->addGroup((Group *)GroupsOfShapes[k]);
                    break;
                }
            }
        }
    }
    sizeGroups = count;
    file.close();
}
