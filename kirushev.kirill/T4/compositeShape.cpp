#include <limits>
#include <stdexcept>
#include "compositeShape.h"

void CompositeShape::addShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalArea = 0;
    for (const auto& shape : shapes) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& shape : shapes)
    {
        Point c = shape->getCenter();

        if (c.x < minX) minX = c.x;
        if (c.x > maxX) maxX = c.x;
        if (c.y < minY) minY = c.y;
        if (c.y > maxY) maxY = c.y;
    }

    Point center;
    center.x = (minX + maxX) / 2;
    center.y = (minY + maxY) / 2;

    return center;
}

void CompositeShape::move(const double dx, const double dy) {
    for (const auto& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(const double k) {
    if (k <= 0) {
        throw std::invalid_argument("The factor must be greater than 0.");
    }

    Point center = getCenter();

    for (const auto& shape : shapes)
    {
        Point c = shape->getCenter();

        double dx = (c.x - center.x) * (k - 1);
        double dy = (c.y - center.y) * (k - 1);

        shape->move(dx, dy);
        shape->scale(k);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

const std::vector<std::shared_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes;
}
