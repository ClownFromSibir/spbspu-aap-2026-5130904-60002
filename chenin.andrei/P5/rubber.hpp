#ifndef RUBBER_HPP
#define RUBBER_HPP

#include "shape.hpp"

namespace chenin
{
    class Rubber : public Shape
    {
    public:
        Rubber(const point_t &innerCenter, double innerRadius,
               const point_t &outerCenter, double outerRadius);

        double getArea() const override;
        rectangle_t getFrameRect() const override;
        void move(const point_t &pos) override;
        void move(double dx, double dy) override;
        void scale(double k) override;

    private:
        point_t innerCenter_;
        double innerRadius_;
        point_t outerCenter_;
        double outerRadius_;
    };
}

#endif