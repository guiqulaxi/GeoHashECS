#pragma once

/**
 * @file point.hpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2021-12-06
 * @copyright Copyright (c) 2021
 *
 * @brief the details
 *        [1] class type
 *              0. Point2<_Ty>, Point3<_Ty>
 *              4. PointSet2<_Ty>. PointSet3<_Ty>
 *              5. RefPoint2<_Ty>, RefPoint3<_Ty>
 *              6. RefPointSet2<_Ty>, RefPointSet3<_Ty>
 *
 */

#include "KDTreeUtil.hpp"

namespace ns_geo
{


#pragma region Point2

    /**
     * \brief a sample template class to describe the 2-dime points
     */
    template <typename _Ty>
    class Point2
    {
    public:
//        using value_type = _Ty;
//        using ary_type = std::array<_Ty, 2>;
//        using self_type = Point2<value_type>;

    private:
        double _x;
        double _y;
        _Ty _value;
    public:
        /**
         * \brief constructors
         */
        Point2() = default;
        Point2(double x, double y) : _x(x), _y(y) {}
        Point2(double x, double y,_Ty value) : _x(x), _y(y),_value(value) {}

        //operator ary_type() const { return ary_type{this->_x, this->_y}; }

        double &x() { return this->_x; }
        double &y() { return this->_y; }
        _Ty &value() { return this->_value; }
        const double &x() const { return this->_x; }
        const double &y() const { return this->_y; }
        const _Ty& value() const{ return this->_value; }

        //static ns_geo::GeometryType type() { return GeometryType::POINT2D; }
    };
    /**
     * \brief overload operator "<<" for Point2
     */
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const Point2<_Ty> &p)
    {
        os << '[' << p.x() << ", " << p.y() << ']';
        return os;
    }

#pragma endregion


#pragma region PointSet2

    template <typename _Ty>
    class PointSet2 : public std::vector<Point2<_Ty>>
    {
    public:
        using value_type = _Ty;
        using point_type = Point2<value_type>;
        using container_type = std::vector<point_type>;
        /**
         * \brief using container_type's constructors
         */
        using container_type::container_type;
        using self_type = PointSet2<value_type>;

        using selector = bool (*)(const point_type &);

    public:
        /**
         * \brief write points to the file
         */
        void write(const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary) const
        {
            std::ofstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
            {
                for (const auto &p : *this)
                    file.write((const char *)(&p), sizeof(point_type));
            }
            else
                for (const auto &point : *this)
                    file << point.x() << ',' << point.y() << '\n';
            return;
        }
        /**
         * \brief read points from the file
         */
        void read(const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)
        {
            std::ifstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
            {
                point_type p;
                file.seekg(0, std::ios::end);
                auto size = file.tellg() / sizeof(point_type);
                file.seekg(0, std::ios::beg);
                int count = 0;
                while (!file.eof() && count < size)
                {
                    file.read((char *)(&p), sizeof(point_type));
                    this->push_back(p);
                    ++count;
                }
            }
            else
            {
                Point2<value_type> point;
                std::string str;
                while (!file.eof())
                {
                    std::getline(file, str);
                    if (str.empty())
                        continue;
                    auto iter = std::find(str.cbegin(), str.cend(), ',');
                    point.x() = static_cast<value_type>(std::stod(std::string(str.cbegin(), iter)));
                    point.y() = static_cast<value_type>(std::stod(std::string(++iter, str.cend())));
                    this->push_back(point);
                }
            }
        }

        /**
         * @brief generate eligible point randomly
         *
         * @param num the number
         * @param x_min the min x value
         * @param x_max the max x value
         * @param y_min the min y value
         * @param y_max the max y value
         * @param slor the selector
         * @return self_type
         */
        static self_type randomGenerator(std::size_t num,
                                         double x_min, double x_max,
                                         double y_min, double y_max,
                                         const selector &slor = nullptr)
        {
            std::uniform_real_distribution<> u_x(static_cast<double>(x_min), static_cast<double>(x_max));
            std::uniform_real_distribution<> u_y(static_cast<double>(y_min), static_cast<double>(y_max));
            self_type ps(num);
            int count = 0;
            while (count != num)
            {
                point_type p(static_cast<_Ty>(u_x(engine)),
                             static_cast<_Ty>(u_y(engine)));
                if (slor == nullptr || slor(p))
                    ps.at(count++) = p;
            }
            return ps;
        }
    };


#pragma endregion


} // namespace ns_geo
