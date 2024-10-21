#!/bin/bash

g++ shape_demo.cpp SourceFiles/Graphics.cpp SourceFiles/Shape.cpp  SourceFiles/Segment.cpp SourceFiles/Circle.cpp SourceFiles/Rectangle.cpp SourceFiles/Triangle.cpp  SourceFiles/Group.cpp SourceFiles/SuperGroup.cpp -o shape_demo -IHeaderFiles -I/opt/homebrew/include -L/opt/homebrew/lib -lGL -lsfml-graphics -lsfml-window -lsfml-system

./shape_demo




