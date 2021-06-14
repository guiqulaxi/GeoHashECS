#include "Geohash.h"



/**
 * @brief distance
 * @param lat1
 * @param lng1
 * @param lat2
 * @param lng2
 * @return
 */

int  Geohash::convert(double min, double max, double value, char* list,int bitlen) {
    int size=0;
    while(size <= (bitlen - 1))
    {
        double mid = (max + min) / 2;
        if(value < mid)
        {
            list[size]=0;
            max=mid;
        }
        else
        {
            list[size]=1;
            min=mid;
        }
        size++;
    }
    return size;
}
int   Geohash::base32Encode( const char*  list,int listlen,char *base32) {

    for (int index = 0; index < listlen/5; index ++)
    {
        char base32LookupIndex=0;
        for(int i=0;i<5;i++)
        {
            base32LookupIndex=base32LookupIndex<<1;
            base32LookupIndex|=(list[index*5+i]);

        }
        base32[index]=base32Lookup[base32LookupIndex];
    }

}
int  Geohash::encode(double lat, double lng,char * str,int strlen) {
    if(strlen<MAX_BIT_LEN*2/5)
    {
        return -1;
    }
    char latList[MAX_BIT_LEN] ;
    char lngList[MAX_BIT_LEN] ;
    char list[MAX_BIT_LEN*2] ;
    memset(latList,0,MAX_BIT_LEN);
    memset(lngList,0,MAX_BIT_LEN);
    memset(list,0,MAX_BIT_LEN*2);
    convert(MIN_LAT, MAX_LAT, lat, latList,MAX_BIT_LEN);
    convert(MIN_LNG, MAX_LNG, lng, lngList,MAX_BIT_LEN);

    for (int index = 0; index < MAX_BIT_LEN; index++) {
        list[index*2]=lngList[index];
        list[index*2+1]=latList[index];
    }
    return base32Encode(list,MAX_BIT_LEN*2,str);
}
int Geohash::effectnum(double distance)
{
    int result=0;
    if(distance<=0) result=0;
    else if(distance<19) result=8;
    else if(distance<76) result=7;
    else if(distance<610) result=6;
    else if(distance<2400) result=5;
    else if(distance<20000) result=4;
    else if(distance<78000) result=3;
    else if(distance<630000) result=2;
    else if(distance<2500000) result=1;
    return  result;


}
