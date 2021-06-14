#ifndef GEOHASH_H
#define GEOHASH_H


#include <memory.h>
#include <math.h>
#include "Util.h"
#define MAX_BIT_LEN 20
#define MAX_LAT 90.
#define MIN_LAT -90.
#define MAX_LNG 180.
#define MIN_LNG -180.
//double latUnit = (Max_Lat - Min_Lat) / (1 << 20);
//    double lngUnit = (Max_Lng - Min_Lng) / (1 << 20);
namespace  Geohash
{

static char base32Lookup[32] =
{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
 'j', 'k', 'm', 'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
/**
 * @brief distance
 * @param lat1
 * @param lng1
 * @param lat2
 * @param lng2
 * @return
 */


int  convert(double min, double max, double value, char* list,int bitlen) ;
int  base32Encode( const char*  list,int listlen,char *base32) ;
int  encode(double lat, double lng,char * str,int strlen) ;
int effectnum(double distance);

};

#endif // GEOHASH_H
