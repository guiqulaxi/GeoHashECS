#ifndef UTIL_H
#define UTIL_H

#include<algorithm>
#include <math.h>

template <class T>
T limit(T angle,int base)
{
    if(0<=angle&&angle<=base)
    {
        return angle;
    }
    else if(angle<0)
    {

        angle=(int)(angle)%base+base+abs(angle)-floor(abs(angle));

    }
    else
    {
        angle=(int)(angle)%base+angle-std::floor(angle);
    }
    return angle;
}
template <class T>
T diffAngle(T a,T b)
{
    a=limit(a,(T)360);
    b=limit(b,(T)360);
    if(a>b)
    {
        T diff=a-b;
        if(diff>180)
        {
            return (T)360-diff;
        }else
        {
            return (T)(-1)*diff;
        }

    }
    else
    {
        T diff=b-a;
        if(diff>180)
        {
            return (T)(-1)*((T)360-diff);
        }else
        {
            return diff;
        }

    }

}
struct geod_geodesic;
class GEO {
public:
/**
* @brief 求两经纬度距离
 *
* @param lon1
*            第一点的经度
* @param lat1
*            第一点的纬度
* @param lon2
*            第二点的经度
* @param lat2
*           第二点的纬度
* @return 两点距离，单位m
* */
static double distance(double lon1, double lat1, double lon2,double lat2) ;
/**
       * 求两经纬度方向角
       *
       * @param lon1
       *            第一点的经度
       * @param lat1
       *            第一点的纬度
       * @param lon2
       *            第二点的经度
       * @param lat2
       *            第二点的纬度
       * @return 方位角，角度（单位：°）
       * */
static double azimuth(double lon1, double lat1, double lon2,double lat2);
/**
       * 已知一点经纬度A，和与另一点B的距离和方位角，求B的经纬度
       *
       * @param lon1
       *            A的经度
       * @param lat1
       *            A的纬度
       * @param distance
       *            AB距离（单位：米）
       * @param azimuth
       *            AB方位角
       * @return B的经纬度
       * */
static void polar(double lon1, double lat1,double distance, double azimuth,double &lon,double& lat);

static int  init(double a = 6378137, double f = 1/298.257223563); /* WGS84 */

private:
    static int _init;
    static struct geod_geodesic *_g;
};



#endif // UTIL_H
