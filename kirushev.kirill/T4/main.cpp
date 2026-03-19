#include <iostream>
#include <iomanip>

#include "point.h"
#include "shape.h"
#include "rectangle.h"
#include "square.h"
#include "compositeShape.h"

void printShape(const std::shared_ptr<Shape>& shape)
{
    Point c = shape->getCenter();
    printf("[%s, (%.2f, %.2f), %.2f]\n", shape->getName().c_str(), c.x, c.y, shape->getArea());
}

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;

    shapes.push_back(std::make_shared<Rectangle>(Point(0,0), Point(4,2)));
    shapes.push_back(std::make_shared<Rectangle>(Point(2,2), Point(6,5)));
    shapes.push_back(std::make_shared<Square>(Point(0, 0), 4));
    shapes.push_back(std::make_shared<Rectangle>(Point(5,-1), Point(8,1)));

    auto comp = std::make_shared<CompositeShape>();

    comp->addShape(std::make_shared<Rectangle>(Point(10,10), Point(12,12)));
    comp->addShape(std::make_shared<Square>(Point(4,10), 3));

    shapes.push_back(comp);

    std::cout << "Before scaling:\n";

    for (const auto& shape : shapes)
        printShape(shape);

    for (const auto& shape : shapes)
        shape->scale(2);

    std::cout << "\nAfter scaling:\n";

    for (const auto& s : shapes)
        printShape(s);

    return 0;
}
