#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace chenin
{
    Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c)
        : a_(a), b_(b), c_(c)
    {
        if (getArea() <= 1e-12)
        {
            throw std::invalid_argument("Triangle vertices must not be collinear");
        }
    }

    point_t Triangle::getCenter() const
    {
        return {
            (a_.x + b_.x + c_.x) / 3.0,
            (a_.y + b_.y + c_.y) / 3.0};
    }

    double Triangle::getArea() const
    {
        return 0.5 * std::abs(
                         (b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y));
    }

    rectangle_t Triangle::getFrameRect() const
    {
        double minX = std::min(a_.x, std::min(b_.x, c_.x));
        double maxX = std::max(a_.x, std::max(b_.x, c_.x));
        double minY = std::min(a_.y, std::min(b_.y, c_.y));
        double maxY = std::max(a_.y, std::max(b_.y, c_.y));

        return {
            maxX - minX,
            maxY - minY,
            {(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
    }

    void Triangle::move(double dx, double dy)
    {
        a_.x += dx;
        a_.y += dy;
        b_.x += dx;
        b_.y += dy;
        c_.x += dx;
        c_.y += dy;
    }

    void Triangle::move(const point_t &pos)
    {
        point_t center = getCenter();
        move(pos.x - center.x, pos.y - center.y);
    }

    void Triangle::scale(double k)
    {
        if (k <= 0.0)
        {
            throw std::invalid_argument("Scale factor must be positive");
        }
        point_t center = getCenter();
        a_.x = center.x + (a_.x - center.x) * k;
        a_.y = center.y + (a_.y - center.y) * k;
        b_.x = center.x + (b_.x - center.x) * k;
        b_.y = center.y + (b_.y - center.y) * k;
        c_.x = center.x + (c_.x - center.x) * k;
        c_.y = center.y + (c_.y - center.y) * k;
    }
}
