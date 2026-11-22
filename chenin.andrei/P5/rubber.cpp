#include "rubber.hpp"
#include <cmath>
#include <stdexcept>

namespace chenin
{
    Rubber::Rubber(const point_t &innerCenter, double innerRadius,
                   const point_t &outerCenter, double outerRadius)
        : innerCenter_(innerCenter),
          innerRadius_(innerRadius),
          outerCenter_(outerCenter),
          outerRadius_(outerRadius)
    {
        if (innerRadius_ <= 0.0 || outerRadius_ <= 0.0)
        {
            throw std::invalid_argument("Rubber radii must be positive");
        }
        double dx = outerCenter_.x - innerCenter_.x;
        double dy = outerCenter_.y - innerCenter_.y;
        double dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= 1e-12)
        {
            throw std::invalid_argument("Rubber circles must not be concentric");
        }
        if (dist + innerRadius_ >= outerRadius_)
        {
            throw std::invalid_argument("Inner circle must lie inside outer circle");
        }
    }

    double Rubber::getArea() const
    {
        const double pi = std::acos(-1.0);
        return pi * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
    }

    rectangle_t Rubber::getFrameRect() const
    {
        return {2.0 * outerRadius_, 2.0 * outerRadius_, outerCenter_};
    }

    void Rubber::move(double dx, double dy)
    {
        innerCenter_.x += dx;
        innerCenter_.y += dy;
        outerCenter_.x += dx;
        outerCenter_.y += dy;
    }

    void Rubber::move(const point_t &pos)
    {
        move(pos.x - innerCenter_.x, pos.y - innerCenter_.y);
    }

    void Rubber::scale(double k)
    {
        if (k <= 0.0)
        {
            throw std::invalid_argument("Scale factor must be positive");
        }
        innerRadius_ *= k;
        outerRadius_ *= k;
        outerCenter_.x = innerCenter_.x + (outerCenter_.x - innerCenter_.x) * k;
        outerCenter_.y = innerCenter_.y + (outerCenter_.y - innerCenter_.y) * k;
    }
}