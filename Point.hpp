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
 *        [2] methods
 *              0. azimuthRHR, azimuthLHR
 *              1. distance
 *              2. operator "<<" for Point2<_Ty>, Point3<_Ty>
 *              3. operator "<<" for RefPoint2<_Ty>, RefPoint3<_Ty>
 */

#include "utility.hpp"

namespace ns_geo
{
#pragma region geometry
    /**
     * @brief the types of the geometry
     */
    enum class GeometryType
    {
        POINT2D,
        POINT3D,
        LINE2D,
        LINE3D,
        LINESTRING2D,
        LINESTRING3D,
        POLYGON,
        RECTANGLE,
        TRIANGLE2D,
        TRIANGLE3D
    };

    static std::ostream &operator<<(std::ostream &os, GeometryType geoty)
    {
        switch (geoty)
        {
        case GeometryType::POINT2D:
            os << "POINT2D";
            break;
        case GeometryType::POINT3D:
            os << "POINT3D";
            break;
        case GeometryType::LINE2D:
            os << "LINE2D";
            break;
        case GeometryType::LINE3D:
            os << "LINE3D";
            break;
        case GeometryType::LINESTRING2D:
            os << "LINESTRING2D";
            break;
        case GeometryType::LINESTRING3D:
            os << "LINESTRING3D";
            break;
        case GeometryType::POLYGON:
            os << "POLYGON";
            break;
        case GeometryType::RECTANGLE:
            os << "RECTANGLE";
            break;
        case GeometryType::TRIANGLE2D:
            os << "TRIANGLE2D";
            break;
        case GeometryType::TRIANGLE3D:
            os << "TRIANGLE3D";
            break;
        default:
            break;
        }
        return os;
    }

    /**
     * @brief the types of the reference geometry
     */
    enum class RefGeometryType
    {
        REFPOINT2D,
        REFPOINT3D,
        REFLINE2D,
        REFLINE3D,
        REFLINESTRING2D,
        REFLINESTRING3D,
        REFPOLYGON,
        REFRECTANGLE,
        REFTRIANGLE2D,
        REFTRIANGLE3D
    };

    static std::ostream &operator<<(std::ostream &os, RefGeometryType geoty)
    {
        switch (geoty)
        {
        case RefGeometryType::REFPOINT2D:
            os << "REFPOINT2D";
            break;
        case RefGeometryType::REFPOINT3D:
            os << "REFPOINT3D";
            break;
        case RefGeometryType::REFLINE2D:
            os << "REFLINE2D";
            break;
        case RefGeometryType::REFLINE3D:
            os << "REFLINE3D";
            break;
        case RefGeometryType::REFLINESTRING2D:
            os << "REFLINESTRING2D";
            break;
        case RefGeometryType::REFLINESTRING3D:
            os << "REFLINESTRING3D";
            break;
        case RefGeometryType::REFPOLYGON:
            os << "REFPOLYGON";
            break;
        case RefGeometryType::REFRECTANGLE:
            os << "REFRECTANGLE";
            break;
        case RefGeometryType::REFTRIANGLE2D:
            os << "REFTRIANGLE2D";
            break;
        case RefGeometryType::REFTRIANGLE3D:
            os << "REFTRIANGLE3D";
            break;
        default:
            break;
        }
        return os;
    }

#pragma endregion

#pragma region Point2

    /**
     * \brief a sample template class to describe the 2-dime points
     */
    template <typename _Ty = float>
    class Point2
    {
    public:
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 2>;
        using self_type = Point2<value_type>;

    private:
        value_type _x;
        value_type _y;

    public:
        /**
         * \brief constructors
         */
        Point2() = default;
        Point2(value_type x, value_type y) : _x(x), _y(y) {}
        Point2(const ary_type &p) : _x(p[0]), _y(p[1]) {}
        Point2(const value_type p[2]) : _x(p[0]), _y(p[1]) {}

        operator ary_type() const { return ary_type{this->_x, this->_y}; }

        value_type &x() { return this->_x; }
        value_type &y() { return this->_y; }

        const value_type &x() const { return this->_x; }
        const value_type &y() const { return this->_y; }

        static ns_geo::GeometryType type() { return GeometryType::POINT2D; }
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

#pragma region Point3

    /**
     * \brief a sample template class to describe the 3-dime points
     */
    template <typename _Ty = float>
    class Point3
    {
    public:
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 3>;
        using self_type = Point3<value_type>;

    private:
        value_type _x;
        value_type _y;
        value_type _z;

    public:
        /**
         * \brief constructors
         */
        Point3() = default;
        Point3(value_type x, value_type y, value_type z) : _x(x), _y(y), _z(z) {}
        Point3(const ary_type &p) : _x(p[0]), _y(p[1]), _z(p[2]) {}
        Point3(const value_type p[3]) : _x(p[0]), _y(p[1]), _z(p[2]) {}

        operator ary_type() const { return ary_type{this->_x, this->_y, this->_z}; }

        value_type &x() { return this->_x; }
        value_type &y() { return this->_y; }
        value_type &z() { return this->_z; }

        const value_type &x() const { return this->_x; }
        const value_type &y() const { return this->_y; }
        const value_type &z() const { return this->_z; }

        static ns_geo::GeometryType type() { return GeometryType::POINT3D; }
    };
    /**
     * \brief overload operator "<<" for Point3
     */
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const Point3<_Ty> &p)
    {
        os << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']';
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
                                         _Ty x_min, _Ty x_max,
                                         _Ty y_min, _Ty y_max,
                                         const selector &slor = nullptr)
        {
            std::uniform_real_distribution<> u_x(static_cast<float>(x_min), static_cast<float>(x_max));
            std::uniform_real_distribution<> u_y(static_cast<float>(y_min), static_cast<float>(y_max));
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
    /**
     * \brief some Commonly used PointSet2 types
     */
    using PointSet2i = PointSet2<int>;
    using PointSet2f = PointSet2<float>;
    using PointSet2d = PointSet2<double>;

#pragma endregion

#pragma region PointSet3

    template <typename _Ty>
    class PointSet3 : public std::vector<Point3<_Ty>>
    {
    public:
        using value_type = _Ty;
        using point_type = Point3<value_type>;
        using container_type = std::vector<point_type>;
        /**
         * \brief using container_type's constructors
         */
        using container_type::container_type;
        using self_type = PointSet3<value_type>;

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
                    file << point.x() << ',' << point.y() << ',' << point.z() << '\n';
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
                Point3<value_type> point;
                std::string str;
                while (!file.eof())
                {
                    std::getline(file, str);
                    if (str.empty())
                        continue;
                    auto iter = std::find(str.cbegin(), str.cend(), ',');
                    point.x() = static_cast<value_type>(std::stod(std::string(str.cbegin(), iter)));
                    auto iter2 = std::find(++iter, str.cend(), ',');
                    point.y() = static_cast<value_type>(std::stod(std::string(iter, iter2)));
                    point.z() = static_cast<value_type>(std::stod(std::string(++iter2, str.cend())));
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
         * @param z_min the min z value
         * @param z_max the max z value 
         * @param slor the selector
         * @return self_type 
         */
        static self_type randomGenerator(std::size_t num,
                                         _Ty x_min, _Ty x_max,
                                         _Ty y_min, _Ty y_max,
                                         _Ty z_min, _Ty z_max,
                                         const selector &slor = nullptr)
        {
            std::uniform_real_distribution<> u_x(static_cast<float>(x_min), static_cast<float>(x_max));
            std::uniform_real_distribution<> u_y(static_cast<float>(y_min), static_cast<float>(y_max));
            std::uniform_real_distribution<> u_z(static_cast<float>(z_min), static_cast<float>(z_max));
            self_type ps(num);
            int count = 0;
            while (count != num)
            {
                point_type p(static_cast<_Ty>(u_x(engine)),
                             static_cast<_Ty>(u_y(engine)),
                             static_cast<_Ty>(u_z(engine)));
                if (slor == nullptr || slor(p))
                    ps.at(count++) = p;
            }
            return ps;
        }
    };
    /**
     * \brief some Commonly used PointSet3 types
     */
    using PointSet3i = PointSet3<int>;
    using PointSet3f = PointSet3<float>;
    using PointSet3d = PointSet3<double>;
#pragma endregion

#pragma region RefPoint2
    template <typename _Ty = float>
    class RefPoint2 : public Point2<_Ty>
    {
    public:
        using id_type = uint;
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 2>;
        using self_type = RefPoint2<value_type>;

    private:
        id_type _id;

    public:
        /**
         * \brief constructors
         */
        RefPoint2() = default;
        RefPoint2(id_type id, value_type x, value_type y)
            : _id(id), Point2<_Ty>(x, y) {}
        RefPoint2(id_type id, const ary_type &p)
            : _id(id), Point2<_Ty>(p[0], p[1]) {}
        RefPoint2(id_type id, const value_type p[2])
            : _id(id), Point2<_Ty>(p[0], p[1]) {}

        const id_type &id() const { return this->_id; }

        static RefGeometryType type() { return ns_geo::RefGeometryType::REFPOINT2D; }
    };
    /**
     * \brief overload operator "<<" for RefPoint2
     */
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefPoint2<_Ty> &p)
    {
        os << '{' << p.id() << ": " << '[' << p.x() << ", " << p.y() << ']' << '}';
        return os;
    }
#pragma endregion

#pragma region RefPoint3
    template <typename _Ty = float>
    class RefPoint3 : public Point3<_Ty>
    {
    public:
        using id_type = uint;
        using value_type = _Ty;
        using ary_type = std::array<_Ty, 3>;
        using self_type = RefPoint3<value_type>;

    private:
        id_type _id;

    public:
        /**
         * \brief constructors
         */
        RefPoint3() = default;
        RefPoint3(id_type id, value_type x, value_type y, value_type z)
            : _id(id), Point3<_Ty>(x, y, z) {}
        RefPoint3(id_type id, const ary_type &p)
            : _id(id), Point3<_Ty>(p[0], p[1], p[2]) {}
        RefPoint3(id_type id, const value_type p[3])
            : _id(id), Point3<_Ty>(p[0], p[1], p[2]) {}

        const id_type &id() const { return this->_id; }

        static RefGeometryType type() { return ns_geo::RefGeometryType::REFPOINT3D; }
    };
    /**
     * \brief overload operator "<<" for RefPoint3
     */
    template <typename _Ty>
    std::ostream &operator<<(std::ostream &os, const RefPoint3<_Ty> &p)
    {
        os << '{' << p.id() << ": " << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']' << '}';
        return os;
    }

#pragma endregion

#pragma region RefPointSet2

    template <typename _Ty,
              typename _Hash = std::hash<uint>,
              typename _Pred = std::equal_to<uint>>
    class RefPointSet2 : public std::unordered_map<uint, RefPoint2<_Ty>, _Hash, _Pred>
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = RefPoint2<value_type>;
        using container_type = std::unordered_map<id_type, refpoint_type, _Hash, _Pred>;
        /**
         * \brief using container_type's constructors
         */
        using container_type::container_type;
        using selector = bool (*)(const refpoint_type &);

        using self_type = RefPointSet2<value_type>;

    public:
        /**
         * \brief insert a reference point to the refpointset
         */
        void
        insert(const refpoint_type &p)
        {
            return container_type::insert(std::make_pair(p.id(), p));
        }
        /**
         * \brief write points to the file
         */
        void write(const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary) const
        {
            std::ofstream file(filePath, mode);
            if (!file.is_open())
                throw std::ios_base::failure("File Open Failed");
            if (std::ios::binary == (mode & std::ios::binary))
                for (const auto &[id, refp] : *this)
                    file.write((const char *)(&refp), sizeof(refpoint_type));
            else
                for (const auto &[id, refp] : *this)
                    file << id << ',' << refp.x() << ',' << refp.y() << '\n';
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
                refpoint_type refp;
                file.seekg(0, std::ios::end);
                auto size = file.tellg() / sizeof(refpoint_type);
                file.seekg(0, std::ios::beg);
                int count = 0;
                while (!file.eof() && count < size)
                {
                    file.read((char *)(&refp), sizeof(refpoint_type));
                    this->insert(refp);
                    ++count;
                }
            }
            else
            {
                refpoint_type refp;
                std::string str;
                while (!file.eof())
                {
                    std::getline(file, str);
                    if (str.empty())
                        continue;
                    auto iter = std::find(str.cbegin(), str.cend(), ',');
                    const_cast<id_type &>(refp.id()) = static_cast<id_type>(std::stoi(std::string(str.cbegin(), iter)));
                    auto iter2 = std::find(++iter, str.cend(), ',');
                    refp.x() = static_cast<value_type>(std::stod(std::string(iter, iter2)));
                    refp.y() = static_cast<value_type>(std::stod(std::string(++iter2, str.cend())));
                    this->insert(refp);
                }
            }
        }

    public:
        /**
         * \brief create reference geometries[2d] by the reference point set
         */
        RefLine2<value_type> createRefLine2(id_type pid1, id_type pid2) const
        {
            return RefLine2<value_type>(pid1, pid2, this);
        }

        RefRectangle<value_type> createRefRectangle(id_type topLeftID, id_type lowerRightID) const
        {
            return RefRectangle<value_type>(topLeftID, lowerRightID, this);
        }

        RefTriangle2<value_type> createRefTriangle2(id_type pid1, id_type pid2, id_type pid3) const
        {
            return RefTriangle2<value_type>(pid1, pid2, pid3, this);
        }

        RefPolygon<value_type> createRefPolygon(const std::initializer_list<id_type> &pidls) const
        {
            return RefPolygon<value_type>(pidls, this);
        }

        RefLineString2<value_type> createRefLineString2(const std::initializer_list<id_type> &pidls) const
        {
            return RefLineString2<value_type>(pidls, this);
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
                                         _Ty x_min, _Ty x_max,
                                         _Ty y_min, _Ty y_max,
                                         const selector &slor = nullptr)
        {
            std::uniform_real_distribution<> u_x(static_cast<float>(x_min), static_cast<float>(x_max));
            std::uniform_real_distribution<> u_y(static_cast<float>(y_min), static_cast<float>(y_max));
            self_type ps;
            int count = 0;
            while (count != num)
            {
                refpoint_type p(count,
                                static_cast<_Ty>(u_x(engine)),
                                static_cast<_Ty>(u_y(engine)));
                if (slor == nullptr || slor(p))
                    ps.insert(p), ++count;
            }
            return ps;
        }

    private:
        /**
         * \brief dangerous function has been deleted
         */
        refpoint_type &operator[](const id_type &id) = delete;
    };
    /**
     * \brief some Commonly used RefPointSet2 types
     */
    using RefPointSet2i = RefPointSet2<int>;
    using RefPointSet2f = RefPointSet2<float>;
    using RefPointSet2d = RefPointSet2<double>;
#pragma endregion

#pragma region RefPointSet3
    template <typename _Ty,
              typename _Hash = std::hash<uint>,
              typename _Pred = std::equal_to<uint>>
    class RefPointSet3 : public std::unordered_map<uint, RefPoint3<_Ty>, _Hash, _Pred>
    {
    public:
        using value_type = _Ty;
        using id_type = uint;
        using refpoint_type = RefPoint3<value_type>;
        using container_type = std::unordered_map<id_type, refpoint_type, _Hash, _Pred>;
        /**
         * \brief using container_type's constructors
         */
        using container_type::container_type;

        using selector = bool (*)(const refpoint_type &);

        using self_type = RefPointSet3<value_type>;

    public:
        /**
         * \brief insert a reference point to the refpointset
         */
        void insert(const refpoint_type &p)
        {
            return container_type::insert(std::make_pair(p.id(), p));
        }
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
                for (const auto &[id, refp] : *this)
                    file.write((const char *)(&refp), sizeof(refpoint_type));
            }
            else
                for (const auto &[id, refp] : *this)
                    file << refp.id() << ',' << refp.x() << ',' << refp.y() << ',' << refp.z() << '\n';
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
                refpoint_type refp;
                file.seekg(0, std::ios::end);
                auto size = file.tellg() / sizeof(refpoint_type);
                file.seekg(0, std::ios::beg);
                int count = 0;
                while (!file.eof() && count < size)
                {
                    file.read((char *)(&refp), sizeof(refpoint_type));
                    this->insert(refp);
                    ++count;
                }
            }
            else
            {
                refpoint_type refp;
                std::string str;
                while (!file.eof())
                {
                    std::getline(file, str);
                    if (str.empty())
                        continue;
                    auto iter = std::find(str.cbegin(), str.cend(), ',');
                    const_cast<uint &>(refp.id()) = static_cast<uint>(std::stoi(std::string(str.cbegin(), iter)));
                    auto iter2 = std::find(++iter, str.cend(), ',');
                    refp.x() = static_cast<value_type>(std::stod(std::string(iter, iter2)));
                    auto iter3 = std::find(++iter2, str.cend(), ',');
                    refp.y() = static_cast<value_type>(std::stod(std::string(iter2, iter3)));
                    refp.z() = static_cast<value_type>(std::stod(std::string(++iter3, str.cend())));
                    this->insert(refp);
                }
            }
        }

    public:
        /**
         * \brief create reference geometries[3d] by the reference point set
         */
        RefLine3<value_type> createRefLine3(id_type pid1, id_type pid2) const
        {
            return RefLine3<value_type>(pid1, pid2, this);
        }

        RefTriangle3<value_type> createRefTriangle3(id_type pid1, id_type pid2, id_type pid3) const
        {
            return RefTriangle3<value_type>(pid1, pid2, pid3, this);
        }

        RefLineString3<value_type> createRefLineString3(const std::initializer_list<id_type> &pidls) const
        {
            return RefLineString3<value_type>(pidls, this);
        }

        /**
         * @brief generate eligible point randomly
         * 
         * @param num the number
         * @param x_min the min x value
         * @param x_max the max x value
         * @param y_min the min y value
         * @param y_max the max y value      
         * @param z_min the min z value
         * @param z_max the max z value 
         * @param slor the selector
         * @return self_type 
         */
        static self_type randomGenerator(std::size_t num,
                                         _Ty x_min, _Ty x_max,
                                         _Ty y_min, _Ty y_max,
                                         _Ty z_min, _Ty z_max,
                                         const selector &slor = nullptr)
        {
            std::uniform_real_distribution<> u_x(static_cast<float>(x_min), static_cast<float>(x_max));
            std::uniform_real_distribution<> u_y(static_cast<float>(y_min), static_cast<float>(y_max));
            std::uniform_real_distribution<> u_z(static_cast<float>(z_min), static_cast<float>(z_max));

            self_type ps;
            int count = 0;
            while (count != num)
            {
                refpoint_type p(count,
                                static_cast<_Ty>(u_x(engine)),
                                static_cast<_Ty>(u_y(engine)),
                                static_cast<_Ty>(u_z(engine)));

                if (slor == nullptr || slor(p))
                    ps.insert(p), ++count;
            }
            return ps;
        }

    private:
        /**
         * \brief dangerous function has been deleted
         */
        refpoint_type &operator[](const id_type &id) = delete;
    };
    /**
     * \brief some Commonly used RefPointSet3 types
     */
    using RefPointSet3i = RefPointSet3<int>;
    using RefPointSet3f = RefPointSet3<float>;
    using RefPointSet3d = RefPointSet3<double>;
#pragma endregion
} // namespace ns_geo
