#include "GeoUtil.h"
#include "geodesic.h"
int GEO::_init=init();
struct geod_geodesic * GEO::_g=nullptr;
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
double GEO::distance(double lon1, double lat1, double lon2,double lat2) {
    double a = 6378137, f = 1/298.257223563; /* WGS84 */
    double  azi1,azi2, s12;
    geod_inverse(_g, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2);
    return s12;
}


double GEO::azimuth(double lon1, double lat1, double lon2,double lat2) {
    double a = 6378137, f = 1/298.257223563; /* WGS84 */
    double  azi1,azi2, s12;

    geod_inverse(_g, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2);
    return azi1;
}

void GEO::polar(double lon1, double lat1,
           double distance, double azimuth,double &lon2,double& lat2) {
    double a = 6378137, f = 1/298.257223563; /* WGS84 */
    double  azi2;

    geod_direct(_g, lat1, lon1, azimuth, distance, &lat2, &lon2, &azi2);

}
int GEO::init(double a , double f )
{
    if(!GEO::_g)
        GEO::_g=new struct geod_geodesic;

    geod_init(_g, a, f);
    return 0;
}

