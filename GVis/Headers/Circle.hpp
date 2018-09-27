//
//  Circle.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp
#include "Shape.hpp"
#include <iostream>
class Circle:public Shape
{
    public:
        void rasterize();
};

#endif /* Circle_hpp */
