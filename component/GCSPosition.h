#ifndef GCSPOSITION_H
#define GCSPOSITION_H
#include "EntityFu.h"
#include "system/DetctionSystem.h"
#include <string>
struct GCSPosition:Entity::Component
{


    GCSPosition(double lon, double lat,float z) : lon(lon), lat(lat),z(z) {
        geohash=DetctionSystem::_geohash.Encode(lat,lon,9);
    }
    GCSPosition() {}

    double lon;
    double lat;
    float z;
    std::string geohash;
    static Cid cid;
};

#endif // GCSPOSITION_H
