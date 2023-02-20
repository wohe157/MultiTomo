#include "mt/definitions.hpp"

bool mt::Shape2d::operator==(const Shape2d& rhs) const
{
    return rows == rhs.rows && cols == rhs.cols;
}

bool mt::Shape3d::operator==(const Shape3d& rhs) const
{
    return rows == rhs.rows && cols == rhs.cols && slices == rhs.slices;
}

bool mt::Subscript2d::operator==(const Subscript2d& rhs) const
{
    return i == rhs.i && j == rhs.j;
}

bool mt::Subscript3d::operator==(const Subscript3d& rhs) const
{
    return i == rhs.i && j == rhs.j && k == rhs.k;
}
