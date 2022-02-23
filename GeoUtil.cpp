#include "GeoUtil.h"
#include "geodesic.h"


double ApproxDistance(double lat1, double lon1, double lat2,
                      double lon2)
{
   lat1 = GEO::DE2RA * lat1;
   lon1 = -GEO::DE2RA * lon1;
   lat2 = GEO::DE2RA * lat2;
   lon2 = -GEO::DE2RA * lon2;

   double F = (lat1 + lat2) / 2.0;
   double G = (lat1 - lat2) / 2.0;
   double L = (lon1 - lon2) / 2.0;

   double sing = sin(G);
   double cosl = cos(L);
   double cosf = cos(F);
   double sinl = sin(L);
   double sinf = sin(F);
   double cosg = cos(G);

   double S = sing*sing*cosl*cosl + cosf*cosf*sinl*sinl;
   double C = cosg*cosg*cosl*cosl + sinf*sinf*sinl*sinl;
   double W = atan2(sqrt(S),sqrt(C));
   double R = sqrt((S*C))/W;
   double H1 = (3 * R - 1.0) / (2.0 * C);
   double H2 = (3 * R + 1.0) / (2.0 * S);
   double D = 2 * W * GEO::ERADM;
   return (D * (1 + GEO::FLATTENING * H1 * sinf*sinf*cosg*cosg -
   GEO::FLATTENING*H2*cosf*cosf*sing*sing));
}
double GCDistance(double lat1, double lon1, double lat2,
                  double lon2)
{
   lat1 *= GEO::DE2RA;
   lon1 *= GEO::DE2RA;
   lat2 *= GEO::DE2RA;
   lon2 *= GEO::DE2RA;
   double d = sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(lon1 -
                                                            lon2);
   return (GEO::AVG_ERADM * acos(d));
}
double EllipseArcLength(double lat1, double lat2,
                        double a ,
                        double f )
{
   double result = 0.0;


   // how many steps to use

   int steps = 100 + 100 * (int)(0.50 + (lat2>lat1) ?
                             (lat2-lat1) : (lat1-lat2));
   steps = (steps > 4000.0) ? 4000.0 : steps;

   double snLat1 = sin(GEO::DE2RA*lat1);
   double snLat2 = sin(GEO::DE2RA*lat2);
   double twoF   = 2 * f - f * f;

   // limits of integration
   double x1 = a * cos(GEO::DE2RA * lat1) /
                   sqrt(1 - twoF*snLat1*snLat1);
   double x2 = a * cos(GEO::DE2RA * lat2) /
                   sqrt(1 - twoF*snLat2*snLat2);

   double dx = (x2 - x1) / (double)(steps - 1);
   double x, y1, y2, dy, dydx;
   double adx = (dx < 0.0) ? -dx : dx;    // absolute value of dx

   double a2 = a * a;
   double oneF = 1 - f;

   // now loop through each step adding up all the little
   // hypotenuses
   for (int i = 0; i < (steps - 1); i++){
      x = x1 + dx * i;
      dydx = ((a * oneF * sqrt((1.0 - ((x+dx)*(x+dx))/a2))) -
         (a * oneF * sqrt((1.0 - (x*x)/a2)))) / dx;
      result += adx * sqrt(1.0 + dydx*dydx);
   }

   return result;
}
double GCAzimuth(double lat1, double lon1, double lat2, double lon2)
{
   double result = 0.0;

   int ilat1 = (int)(0.50 + lat1 * 360000.0);
   int ilat2 = (int)(0.50 + lat2 * 360000.0);
   int ilon1 = (int)(0.50 + lon1 * 360000.0);
   int ilon2 = (int)(0.50 + lon2 * 360000.0);

   lat1 *= GEO::DE2RA;
   lon1 *= GEO::DE2RA;
   lat2 *= GEO::DE2RA;
   lon2 *= GEO::DE2RA;

   if ((ilat1 == ilat2) && (ilon1 == ilon2))
   {
      return result;
   }
   else if (ilon1 == ilon2)
   {
      if (ilat1 > ilat2)
         result = 180.0;
   }
   else
   {
      double c = acos(sin(lat2)*sin(lat1) +
                 cos(lat2)*cos(lat1)*cos((lon2-lon1)));
      double A = asin(cos(lat2)*sin((lon2-lon1))/sin(c));
      result = (A * GEO::RA2DE);

      if ((ilat2 > ilat1) && (ilon2 > ilon1))
      {
      }
      else if ((ilat2 < ilat1) && (ilon2 < ilon1))
      {
         result = 180.0 - result;
      }
      else if ((ilat2 < ilat1) && (ilon2 > ilon1))
      {
         result = 180.0 - result;
      }
      else if ((ilat2 > ilat1) && (ilon2 < ilon1))
      {
         result += 360.0;
      }
   }

   return result;
}
bool GCIntersectSegment(double lat1A, double lon1A, double lat1B,
                        double lon1B, double lat2A, double lon2A,
                        double lat2B, double lon2B, double& lat3A,
                        double& lon3A, double& lat3B, double& lon3B)
{
   bool isInside = false;

   double v1[3], v2[3], v3a[3], v3b[3], n1[3], n2[3];
   double m;

   double d1 = ApproxDistance(lat1A, lon1A, lat1B, lon1B);
   double d2 = ApproxDistance(lat2A, lon2A, lat2B, lon2B);

   //
   // for path 1, setting up my 2 vectors, v1 is vector
   // from center of the Earth to point A, v2 is vector
   // from center of the Earth to point B.
   //
   v1[0] = cos(lat1A * GEO::DE2RA) * cos(lon1A * GEO::DE2RA);
   v1[1] = sin(lat1A * GEO::DE2RA);
   v1[2] = cos(lat1A * GEO::DE2RA) * sin(lon1A * GEO::DE2RA);

   v2[0] = cos(lat1B * GEO::DE2RA) * cos(lon1B * GEO::DE2RA);
   v2[1] = sin(lat1B * GEO::DE2RA);
   v2[2] = cos(lat1B * GEO::DE2RA) * sin(lon1B * GEO::DE2RA);

   //
   // n1 is the normal to the plane formed by the three points:
   // center of the Earth, point 1A, and point 1B
   //
   n1[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
   n1[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
   n1[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);

   //
   // for path 2, setting up my 2 vectors, v1 is vector
   // from center of the Earth to point A, v2 is vector
   // from center of the Earth to point B.
   //
   v1[0] = cos(lat2A * GEO::DE2RA) * cos(lon2A * GEO::DE2RA);
   v1[1] = sin(lat2A * GEO::DE2RA);
   v1[2] = cos(lat2A * GEO::DE2RA) * sin(lon2A * GEO::DE2RA);

   v2[0] = cos(lat2B * GEO::DE2RA) * cos(lon2B * GEO::DE2RA);
   v2[1] = sin(lat2B * GEO::DE2RA);
   v2[2] = cos(lat2B * GEO::DE2RA) * sin(lon2B * GEO::DE2RA);

   //
   // n1 is the normal to the plane formed by the three points:
   // center of the Earth, point 2A, and point 2B
   //
   n2[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
   n2[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
   n2[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);

   //
   // v3 is perpendicular to both normal 1 and normal 2, so
   // it lies in both planes, so it must be the line of
   // intersection of the planes. The question is: does it
   // go towards the correct intersection point or away from
   // it.
   //
   v3a[0] = (n1[1]*n2[2]) - (n1[2]*n2[1]);
   v3a[1] = (n1[2]*n2[0]) - (n1[0]*n2[2]);
   v3a[2] = (n1[0]*n2[1]) - (n1[1]*n2[0]);

   //
   // want to make v3a a unit vector, so first have to get
   // magnitude, then each component by magnitude
   //
   m = sqrt(v3a[0]*v3a[0] + v3a[1]*v3a[1] + v3a[2]*v3a[2]);
   v3a[0] /= m;
   v3a[1] /= m;
   v3a[2] /= m;

   //
   // calculating intersection points 3A & 3B. A & B are
   // arbitrary designations right now, later we make A
   // the one close to, or within, the paths.
   //
   lat3A = asin(v3a[1]);
   if ((lat3A > GEO::EPS) || (-lat3A > GEO::EPS))
      lon3A = asin(v3a[2]/cos(lat3A));
   else
      lon3A = 0.0;

   v3b[0] = (n2[1]*n1[2]) - (n2[2]*n1[1]);
   v3b[1] = (n2[2]*n1[0]) - (n2[0]*n1[2]);
   v3b[2] = (n2[0]*n1[1]) - (n2[1]*n1[0]);

   m = sqrt(v3b[0]*v3b[0] + v3b[1]*v3b[1] + v3b[2]*v3b[2]);
   v3b[0] /= m;
   v3b[1] /= m;
   v3b[2] /= m;

   lat3B = asin(v3b[1]);
   if ((lat3B > GEO::EPS) || (-lat3B > GEO::EPS))
      lon3B = asin(v3b[2]/cos(lat3B));
   else
      lon3B = 0.0;

   //
   // get the distances from the path endpoints to the two
   // intersection points. these values will be used to determine
   // which intersection point lies on the paths, or which one
   // is closer.
   //
   double d1a3a = ApproxDistance(lat1A, lon1A, lat3A, lon3A);
   double d1b3a = ApproxDistance(lat1B, lon1B, lat3A, lon3A);
   double d2a3a = ApproxDistance(lat2A, lon2A, lat3A, lon3A);
   double d2b3a = ApproxDistance(lat2B, lon2B, lat3A, lon3A);

   double d1a3b = ApproxDistance(lat1A, lon1A, lat3B, lon3B);
   double d1b3b = ApproxDistance(lat1B, lon1B, lat3B, lon3B);
   double d2a3b = ApproxDistance(lat2A, lon2A, lat3B, lon3B);
   double d2b3b = ApproxDistance(lat2B, lon2B, lat3B, lon3B);

   if ((d1a3a < d1) && (d1b3a < d1) && (d2a3a < d2)
                    && (d2b3a < d2))
   {
      isInside = true;
   }
   else if ((d1a3b < d1) && (d1b3b < d1) && (d2a3b < d2)
                         && (d2b3b < d2))
   {
      //
      // 3b is inside the two paths, so swap 3a & 3b
      //
      isInside = true;

      m = lat3A;
      lat3A = lat3B;
      lat3B = m;
      m = lon3A;
      lon3A = lon3B;
      lon3B = m;
   }
   else
   {
      //
      // figure out which one is closer to the path
      //
      d1 = d1a3a + d1b3a + d2a3a + d2b3a;
      d2 = d1a3b + d1b3b + d2a3b + d2b3b;

      if (d1 > d2)
      {
         //
         // Okay, we are here because 3b {lat3B,lon3B} is closer to
         // the paths, so we need to swap 3a & 3b. the other case is
         // already the way 3a & 3b are organized, so no need to swap
         //
         m = lat3A;
         lat3A = lat3B;
         lat3B = m;
         m = lon3A;
         lon3A = lon3B;
         lon3B = m;
      }
   }

   //
   // convert the intersection points to degrees
   //
   lat3A *= GEO::RA2DE;
   lon3A *= GEO::RA2DE;
   lat3B *= GEO::RA2DE;
   lon3B *= GEO::RA2DE;

   return isInside;
}



int Geo::_init=init();
struct geod_geodesic * Geo::_g=nullptr;
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
double Geo::distance(double lon1, double lat1, double lon2,double lat2) {
//    double a = 6378137, f = 1/298.257223563; /* WGS84 */
//    double  azi1,azi2, s12;
//    geod_inverse(_g, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2);
//    return s12;

//    double r1 = M_PI/180.0*lat1;
//    double r2 =M_PI/180.0*lon1;
//    double a = M_PI/180.0*lat2;
//    double b = M_PI/180.0*lon2;
//    double s = acos(cos(r1) * cos(a) * cos(r2 - b)
//                    + sin(r1) * sin(a))
//            * 6378137;
//    return s;

    return ApproxDistance(lat1,lon1,lat2,lon2);
}


double Geo::azimuth(double lon1, double lat1, double lon2,double lat2) {
    double a = 6378137, f = 1/298.257223563; /* WGS84 */
    double  azi1,azi2, s12;

    geod_inverse(_g, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2);
    return azi1;
}

void Geo::polar(double lon1, double lat1,
           double distance, double azimuth,double &lon2,double& lat2) {
    double a = 6378137, f = 1/298.257223563; /* WGS84 */
    double  azi2;

    geod_direct(_g, lat1, lon1, azimuth, distance, &lat2, &lon2, &azi2);

}
int Geo::init(double a , double f )
{
    if(!Geo::_g)
        Geo::_g=new struct geod_geodesic;

    geod_init(_g, a, f);
    return 0;
}

