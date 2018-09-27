//
//  Sphere.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp
#include <iostream>
#include "DataType.hpp"
#include "Shape.hpp"
using namespace GVis;
class Sphere:public Shape
{
    vector_float3 center;
    float radius;
    public :
    void rasterize();
    
};

#endif /* Sphere_hpp */
