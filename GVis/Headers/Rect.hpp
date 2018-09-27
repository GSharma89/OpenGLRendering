//
//  Rect.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Rect_hpp
#define Rect_hpp
#include "Shape.hpp"
class Rect:public Shape
{
        float x,y,width,height;
    public:
    Rect(float x,float y,float width,float height);
    void setAttributes(float x,float y,float width,float height);
    void rasterize();
};

#endif /* Rect_hpp */
