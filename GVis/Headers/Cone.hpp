//
//  Cone.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Cone_hpp
#define Cone_hpp

#include "Shape.hpp"
class Cone:public Shape
{
    vector_float3 center;
    float radius;
    float height;
public:
    void rasterize();
    
};

#endif /* Cone_hpp */
