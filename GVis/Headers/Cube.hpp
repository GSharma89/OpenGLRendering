//
//  Cube.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp
#include <iostream>
#include "DataType.hpp"
#include "Shape.hpp"
class Cube:public Shape
{
    float side;
    public:
        void rasterize();
        
    
};

#endif /* Cube_hpp */
