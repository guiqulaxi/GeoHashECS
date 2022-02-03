#pragma once

/**
 * @file utility.hpp
 * @author csl (3079625093@qq.com)
 * @brief Provide operation support for point classes
 * @version 0.1
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <array>
#include <vector>
#include <unordered_map>
#include <random>
#include <geoutil.h>
namespace ns_geo
{
#pragma region global params
    static std::default_random_engine engine = std::default_random_engine();
#pragma endregion

#pragma region gemetry types
    enum class GeometryType;

    enum class RefGeometryType;

    template <typename _Ty>
    class Point2;
    /**
     * \brief some Commonly used Point2 types
     */
    using Point2f = Point2<float>;
    using Point2d = Point2<double>;
    using Point2i = Point2<int>;
    using Point2geo = Point2<double>;

    template <typename _Ty>
    class RefPoint2;
    /**
     * \brief some Commonly used RefPoint2 types
     */
    using RefPoint2f = RefPoint2<float>;
    using RefPoint2d = RefPoint2<double>;
    using RefPoint2i = RefPoint2<int>;

    template <typename _Ty>
    class Line2;
    /**
     * \brief some Commonly used Line2 types
     */
    using Line2d = Line2<double>;
    using Line2f = Line2<float>;
    using Line2i = Line2<int>;

    template <typename _Ty>
    class RefLine2;
    /**
     * \brief some Commonly used RefLine2 types
     */
    using RefLine2d = RefLine2<double>;
    using RefLine2f = RefLine2<float>;
    using RefLine2i = RefLine2<int>;

    template <typename _Ty>
    class Line3;
    /**
     * \brief some Commonly used Line3 types
     */
    using Line3d = Line3<double>;
    using Line3f = Line3<float>;
    using Line3i = Line3<int>;

    template <typename _Ty>
    class RefLine3;
    /**
     * \brief some Commonly used RefLine3 types
     */
    using RefLine3d = RefLine3<double>;
    using RefLine3f = RefLine3<float>;
    using RefLine3i = RefLine3<int>;

    template <typename _Ty>
    class Rectangle;
    /**
     * \brief some Commonly used Rectangle types
     */
    using Rectangled = Rectangle<double>;
    using Rectanglef = Rectangle<float>;
    using Rectanglei = Rectangle<int>;

    template <typename _Ty>
    class RefRectangle;
    /**
     * \brief some Commonly used RefRectangle types
     */
    using RefRectangled = RefRectangle<double>;
    using RefRectanglef = RefRectangle<float>;
    using RefRectanglei = RefRectangle<int>;

    template <typename _Ty>
    class Triangle2;
    /**
     * \brief some Commonly used Triangle2 types
     */
    using Triangle2d = Triangle2<double>;
    using Triangle2f = Triangle2<float>;
    using Triangle2i = Triangle2<int>;

    template <typename _Ty>
    class RefTriangle2;
    /**
     * \brief some Commonly used RefTriangle2 types
     */
    using RefTriangle2d = RefTriangle2<double>;
    using RefTriangle2f = RefTriangle2<float>;
    using RefTriangle2i = RefTriangle2<int>;

    template <typename _Ty>
    class Triangle3;
    /**
     * \brief some Commonly used Triangle3 types
     */
    using Triangle3d = Triangle3<double>;
    using Triangle3f = Triangle3<float>;
    using Triangle3i = Triangle3<int>;

    template <typename _Ty>
    class RefTriangle3;
    /**
     * \brief some Commonly used RefTriangle3 types
     */
    using RefTriangle3d = RefTriangle3<double>;
    using RefTriangle3f = RefTriangle3<float>;
    using RefTriangle3i = RefTriangle3<int>;

    template <typename _Ty>
    class Polygon;
    /**
     * \brief some Commonly used Polygon types
     */
    using Polygond = Polygon<double>;
    using Polygonf = Polygon<float>;
    using Polygoni = Polygon<int>;

    template <typename _Ty>
    class RefPolygon;
    /**
     * \brief some Commonly used RefPolygon types
     */
    using RefPolygond = RefPolygon<double>;
    using RefPolygonf = RefPolygon<float>;
    using RefPolygoni = RefPolygon<int>;

    template <typename _Ty>
    class LineString2;
    /**
     * \brief some Commonly used LineString2 types
     */
    using LineString2d = LineString2<double>;
    using LineString2f = LineString2<float>;
    using LineString2i = LineString2<int>;

    template <typename _Ty>
    class RefLineString2;
    /**
     * \brief some Commonly used RefLineString2 types
     */
    using RefLineString2d = RefLineString2<double>;
    using RefLineString2f = RefLineString2<float>;
    using RefLineString2i = RefLineString2<int>;

    template <typename _Ty>
    class LineString3;
    /**
     * \brief some Commonly used LineString3 types
     */
    using LineString3d = LineString3<double>;
    using LineString3f = LineString3<float>;
    using LineString3i = LineString3<int>;

    template <typename _Ty>
    class RefLineString3;
    /**
     * \brief some Commonly used RefLineString3 types
     */
    using RefLineString3d = RefLineString3<double>;
    using RefLineString3f = RefLineString3<float>;
    using RefLineString3i = RefLineString3<int>;

    template <typename _PointType>
    class KdTree2;
    using KdTree2i = KdTree2<Point2i>;
    using KdTree2f = KdTree2<Point2f>;
    using KdTree2d = KdTree2<Point2d>;




    template <typename _PointType>
    class RefKdTree2;
    using RefKdTree2i = RefKdTree2<RefPoint2i>;
    using RefKdTree2f = RefKdTree2<RefPoint2f>;
    using RefKdTree2d = RefKdTree2<RefPoint2d>;



#pragma endregion

#pragma region helpers

#pragma region stride
    /**
     * @brief calculate the stride between the 'from' point to the 'to' point
     *
     * @tparam _Ty the type of value
     * @param from the start point
     * @param to the end point
     * @return std::array<_Ty, 3> return a array contains three elements
     */
    template <typename _Ty>
    std::array<_Ty, 2> stride(const Point2<_Ty> &from, const Point2<_Ty> &to)
    {
        return std::array<_Ty, 2>{to.x() - from.x(), to.y() - from.y()};
    }
#pragma endregion

#pragma region distance
    /**
     * @brief Calculate the distance between two points
     *
     * @tparam _Ty the type of value
     * @param p1 one of two points
     * @param p2 one of two points
     * @return float the distance between two points
     */
    template <typename _Ty>
    float distance(const Point2<_Ty> &p1, const Point2<_Ty> &p2)
    {
        return static_cast<float>(std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2)));
    }

    template <typename _Ty>
    float distance(const Point2<_Ty> &p1, const Point2<_Ty> &p2, float p)
    {
        return static_cast<float>(std::pow(std::pow(p1.x() - p2.x(), p) + std::pow(p1.y() - p2.y(), p), 1.0f / p));
    }
     template <typename _Ty>
    _Ty distanceGeo(const Point2<_Ty> &p1, const Point2<_Ty> &p2)
    {
        return distance1(p1.x() ,p1.y(),p2.x() ,p2.y());
    }
    /**
     * @brief calculate the distance from the point to the line
     *
     * @tparam _Ty the type of value
     * @param p the point
     * @param l the line
     * @return float the distance from the point to the line
     */
    template <typename _Ty>
    float distance(const Point2<_Ty> &p, const Line2<_Ty> &l)
    {
        auto vec1 = stride(l.p1(), l.p2());
        auto vec2 = stride(l.p1(), p);
        float z = vec1[0] * vec2[1] - vec1[1] * vec2[0];
        float dis = std::abs(z) / distance(l.p1(), l.p2());
        return dis;
    }

#pragma endregion

#pragma region vector compute
    /**
     * @brief calculate the dot produce of two vectors
     * 
     * @tparam _Ty the vaule type
     * @tparam size the size of the vector
     * @param vec1 the first vector
     * @param vec2 the second vector
     * @return _Ty the return value type
     */
    template <typename _Ty, std::size_t size>
    _Ty dot(const std::array<_Ty, size> &vec1, const std::array<_Ty, size> &vec2)
    {
        _Ty res = _Ty(0.0f);
        for (int i = 0; i != size; ++i)
            res += vec1[i] * vec2[i];
        return res;
    }

    /**
     * @brief calculate the cross produce of two vectors
     * 
     * @tparam _Ty the vaule type
     * @param vec1 the first vector
     * @param vec2 the second vector
     * @return std::array<_Ty, 3> 
     */
    template <typename _Ty>
    std::array<_Ty, 3> cross(const std::array<_Ty, 3> &vec1, const std::array<_Ty, 3> &vec2)
    {
        std::array<_Ty, 3> res;
        res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
        res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
        return res;
    }

    /**
     * @brief calculate the norm of the vector
     * 
     * @tparam _Ty the vaule type
     * @tparam size the size of the vector
     * @param vec the vector
     * @return float 
     */
    template <typename _Ty, std::size_t size>
    float norm(const std::array<_Ty, size> &vec)
    {
        float nor = 0.0f;
        for (int i = 0; i != size; ++i)
            nor += vec[i] * vec[i];
        nor = std::sqrt(nor);
        return nor;
    }

    /**
     * @brief normalize a vector
     * 
     * @tparam _Ty the vaule type
     * @tparam size the size of the vector
     * @param vec the vector
     * @return void 
     */
    template <typename _Ty, std::size_t size>
    void normalize(std::array<_Ty, size> &vec)
    {
        auto nor = ns_geo::norm(vec);
        for (int i = 0; i != size; ++i)
            vec[i] /= nor;
        return;
    }

    /**
     * @brief calculate the normalized vector of a vector
     * 
     * @tparam _Ty the vaule type
     * @tparam size the size of the vector
     * @param vec the vector
     * @return std::array<_Ty, size> 
     */
    template <typename _Ty, std::size_t size>
    std::array<_Ty, size> normalized(std::array<_Ty, size> vec)
    {
        normalize(vec);
        return vec;
    }
#pragma endregion

    namespace RHandRule
    {
        /**
         * @brief calculate the azimuth according the left hand rule
         *
         * @tparam _Ty the type of value
         * @param from start point
         * @param to end point
         * @return float the azimuth[radian]
         */
        template <typename _Ty>
        float azimuth(const Point2<_Ty> &from, const Point2<_Ty> &to)
        {
            float detaX = to.x() - from.x();
            float detaY = to.y() - from.y();
            float angle = std::atan2(detaX, detaY);
            if (detaX < 0.0)
                angle += 2 * M_PI;
            return angle;
        }




        /**
         * @brief judge whether the point is at the left of the line
         *
         * @tparam _Ty the template type
         * @param p the point[2d]
         * @param l the line[2d]
         * @return true
         * @return false
         */
        template <typename _Ty>
        bool palleft(const Point2<_Ty> &p, const Line2<_Ty> &l)
        {
            auto v1 = stride(l.p1(), l.p2());
            auto v2 = stride(l.p1(), p);
            return static_cast<float>(v1[0] * v2[1] - v1[1] * v2[0]) > 0.0;
        }

        /**
         * @brief judge whether the point is at the right of the line
         *
         * @tparam _Ty the template type
         * @param p the point[2d]
         * @param l the line[2d]
         * @return true
         * @return false
         */
        template <typename _Ty>
        bool palright(const Point2<_Ty> &p, const Line2<_Ty> &l)
        {
            auto v1 = stride(l.p1(), l.p2());
            auto v2 = stride(l.p1(), p);
            return static_cast<float>(v1[0] * v2[1] - v1[1] * v2[0]) < 0.0;
        }

        /**
         * @brief calculate the target pos references the center, distancee and azimuth
         * 
         * @tparam _Ty the template type
         * @param center the center position 
         * @param distance the distance from the center to the target pos
         * @param azimuth the azimuth[radian]
         * @return Point2<_Ty> 
         */
        template <typename _Ty>
        Point2<_Ty> polarCoorMap(const Point2<_Ty> &center, float distance, float azimuth)
        {
            Point2<_Ty> pos;
            pos.x() = center.x() + distance * std::sin(azimuth);
            pos.y() = center.y() + distance * std::cos(azimuth);
            return pos;
        }


    } // namespace RHandRule

    namespace LHandRule
    {
        /**
         * @brief calculate the azimuth according the left hand rule
         *
         * @tparam _Ty the type of value
         * @param from start point
         * @param to end point
         * @return float the azimuth[radian]
         */
        template <typename _Ty>
        float azimuth(const Point2<_Ty> &from, const Point2<_Ty> &to)
        {
            float detaX = to.x() - from.x();
            float detaY = to.y() - from.y();
            float angle = std::atan2(detaY, detaX);
            if (detaY < 0.0)
                angle += 2 * M_PI;
            return angle;
        }


        /**
         * @brief judge whether the point is at the left of the line
         *
         * @tparam _Ty the template type
         * @param p the point[2d]
         * @param l the line[2d]
         * @return true
         * @return false
         */
        template <typename _Ty>
        bool palleft(const Point2<_Ty> &p, const Line2<_Ty> &l)
        {
            auto v1 = stride(l.p1(), l.p2());
            auto v2 = stride(l.p1(), p);
            return static_cast<float>(v1[0] * v2[1] - v1[1] * v2[0]) < 0.0;
        }

        /**
         * @brief judge whether the point is at the right of the line
         *
         * @tparam _Ty the template type
         * @param p the point[2d]
         * @param l the line[2d]
         * @return true
         * @return false
         */
        template <typename _Ty>
        bool palright(const Point2<_Ty> &p, const Line2<_Ty> &l)
        {
            auto v1 = stride(l.p1(), l.p2());
            auto v2 = stride(l.p1(), p);
            return static_cast<float>(v1[0] * v2[1] - v1[1] * v2[0]) > 0.0;
        }

        /**
         * @brief calculate the target pos references the center, distancee and azimuth
         * 
         * @tparam _Ty the template type
         * @param center the center position 
         * @param distance the distance from the center to the target pos
         * @param azimuth the azimuth[radian]
         * @return Point2<_Ty> 
         */
        template <typename _Ty>
        Point2<_Ty> polarCoorMap(const Point2<_Ty> &center, float distance, float azimuth)
        {
            Point2<_Ty> pos;
            pos.x() = center.x() + distance * std::cos(azimuth);
            pos.y() = center.y() + distance * std::sin(azimuth);
            return pos;
        }


    } // namespace LHandRule

#pragma endregion
} // namespace ns_geo
