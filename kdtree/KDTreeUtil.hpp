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
#include "GeoUtil.h"
namespace ns_geo
{
#pragma region global params
    static std::default_random_engine engine = std::default_random_engine();
#pragma endregion

#pragma region gemetry types

    template <typename _Ty>
    class Point2;
    template <typename _PointType>
    class KdTree2;


#pragma endregion



#pragma region distance

     template <typename _Ty>
    _Ty distanceGeo(const Point2<_Ty> &p1, const Point2<_Ty> &p2)
    {
        return distance1(p1.x() ,p1.y(),p2.x() ,p2.y());
    }

#pragma endregion

#pragma endregion
} // namespace ns_geo
