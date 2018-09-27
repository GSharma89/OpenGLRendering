//
//  Cylinder.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Cylinder_hpp
#define Cylinder_hpp

#include "Shape.hpp"
class Cylinder:public Shape
{
    vector_float3 center;
    float radius;
    float height;
    public:
    void rasterize();
    
};

#endif /* Cylinder_hpp */
