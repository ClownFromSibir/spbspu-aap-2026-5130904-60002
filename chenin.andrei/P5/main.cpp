#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "rubber.hpp"

namespace chenin
{
    void isoScale(Shape &shape, const point_t &anchor, double k)
    {
        if (k <= 0.0)
        {
            throw std::invalid_argument("Scale factor must be positive");
        }
        point_t b1 = shape.getFrameRect().pos;
        shape.move(anchor);
        point_t b2 = shape.getFrameRect().pos;
        shape.scale(k);
        shape.move(k * (b1.x - b2.x), k * (b1.y - b2.y));
    }

    void isoScaleAll(Shape *const *shapes, std::size_t count,
                     const point_t &anchor, double k)
    {
        if (k <= 0.0)
        {
            throw std::invalid_argument("Scale factor must be positive");
        }
        for (std::size_t i = 0; i < count; ++i)
        {
            isoScale(*shapes[i], anchor, k);
        }
    }

    rectangle_t getTotalFrameRect(const Shape *const *shapes, std::size_t count)
    {
        rectangle_t first = shapes[0]->getFrameRect();
        double minX = first.pos.x - first.width / 2.0;
        double maxX = first.pos.x + first.width / 2.0;
        double minY = first.pos.y - first.height / 2.0;
        double maxY = first.pos.y + first.height / 2.0;

        for (std::size_t i = 1; i < count; ++i)
        {
            rectangle_t r = shapes[i]->getFrameRect();
            minX = std::min(minX, r.pos.x - r.width / 2.0);
            maxX = std::max(maxX, r.pos.x + r.width / 2.0);
            minY = std::min(minY, r.pos.y - r.height / 2.0);
            maxY = std::max(maxY, r.pos.y + r.height / 2.0);
        }

        return {
            maxX - minX,
            maxY - minY,
            {(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
    }

    void printReport(const Shape *const *shapes, std::size_t count)
    {
        double totalArea = 0.0;
        for (std::size_t i = 0; i < count; ++i)
        {
            double area = shapes[i]->getArea();
            rectangle_t frame = shapes[i]->getFrameRect();
            totalArea += area;

            std::cout << "Shape #" << i << ": area=" << area
                      << ", frame=(w=" << frame.width
                      << ", h=" << frame.height
                      << ", pos=(" << frame.pos.x << ", " << frame.pos.y << "))\n";
        }

        rectangle_t totalFrame = getTotalFrameRect(shapes, count);
        std::cout << "Total area=" << totalArea << "\n";
        std::cout << "Total frame=(w=" << totalFrame.width
                  << ", h=" << totalFrame.height
                  << ", pos=(" << totalFrame.pos.x << ", " << totalFrame.pos.y << "))\n";
    }

    void freeShapes(Shape **shapes, std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            delete shapes[i];
            shapes[i] = nullptr;
        }
    }
}

int main()
{
    using namespace chenin;

    const std::size_t count = 3;
    Shape *shapes[count] = {nullptr, nullptr, nullptr};

    try
    {
        shapes[0] = new Rectangle(4.0, 2.0, {1.0, 1.0});
        shapes[1] = new Triangle({0.0, 0.0}, {3.0, 0.0}, {0.0, 4.0});
        shapes[2] = new Rubber({1.0, 0.0}, 1.0, {0.0, 0.0}, 5.0);

        std::cout << "--- BEFORE ---\n";
        printReport(shapes, count);

        point_t anchor{0.0, 0.0};
        double k = 1.0;
        if (!(std::cin >> anchor.x >> anchor.y >> k))
        {
            std::cerr << "Error: invalid input\n";
            freeShapes(shapes, count);
            return 1;
        }

        isoScaleAll(shapes, count, anchor, k);

        std::cout << "--- AFTER ---\n";
        printReport(shapes, count);

        freeShapes(shapes, count);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        freeShapes(shapes, count);
        return 1;
    }

    return 0;
}
