//
//  Utils.cpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Utils.hpp"
#include <math.h>
shared_ptr<vector_float3> Utils::crossProduct(shared_ptr<vector_float3> a,shared_ptr<vector_float3> b)
{
    shared_ptr<vector_float3> r = make_shared<vector_float3>();
    r->x = a->y*b->z - a->z*b->y;
    r->y = a->z*b->x - a->x*b->z;
    r->z = a->x*b->y - a->y*b->x;
    return r;
}


shared_ptr<vector_float3> Utils::normalize(shared_ptr<vector_float3> a)
{
    shared_ptr<vector_float3> r = make_shared<vector_float3>();
    float m = sqrt((a->x*a->x)+(a->y*a->y)+(a->z*a->z));
    r->x = a->x/m;
    r->y = a->y/m;
    r->z = a->z/m;
    return r;
}
