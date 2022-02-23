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

namespace GEO {
   const double PI                = 3.14159265359;
   const double TWOPI             = 6.28318530718;
   const double DE2RA             = 0.01745329252;
   const double RA2DE             = 57.2957795129;
   const double ERAD              = 6378.135;

   const double ERADM             = 6378135.0;
   const double AVG_ERAD          = 6371.378;
    const double AVG_ERADM          = 6371378;
   const double FLATTENING        = 1.0/298.257223563;
                                  // Earth flattening (WGS '84)
   const double EPS               = 0.000000000005;
   const double KM2MI             = 0.621371;
   const double GEOSTATIONARY_ALT = 35786.0;    // km
}
double ApproxDistance(double lat1, double lon1, double lat2,
                      double lon2);
double GCDistance(double lat1, double lon1, double lat2,
                  double lon2);
double EllipseArcLength(double lat1, double lat2,
                        double a = GEO::ERAD,
                        double f = GEO::FLATTENING);
double GCAzimuth(double lat1, double lon1, double lat2, double lon2);
bool GCIntersectSegment(double lat1A, double lon1A, double lat1B,
                        double lon1B, double lat2A, double lon2A,
                        double lat2B, double lon2B, double& lat3A,
                        double& lon3A, double& lat3B, double& lon3B);

struct geod_geodesic;
class Geo {
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
