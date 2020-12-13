#ifndef GCSPOSITION_H
#define GCSPOSITION_H
#include "EntityFu.h"
struct GCSPosition:Entity::Component
{


    GCSPosition(double lon, double lat,float z) : lon(lon), lat(lat),z(z) {}
    GCSPosition() {}

    double lon;
    double lat;
    float z;

    static Cid cid;
};

#endif // GCSPOSITION_H
