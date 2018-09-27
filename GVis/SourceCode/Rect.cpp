//
//  Rect.cpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Rect.hpp"
Rect::Rect(float x,float y,float w,float h):x(x),y(y),width(w),height(h)
{
    raster_required = true;
}
void Rect::rasterize()
{
    shared_ptr<vector_float4> position = make_shared<vector_float4>(x,y,0,1);
    shared_ptr<vector_float4> textCord = make_shared<vector_float4>(0,0,0,0);
    shared_ptr<vector_float4> normal = make_shared<vector_float4>(0,0,1,1);//z axis
    shared_ptr<Vertex> vert = make_shared<Vertex>();
    vert->position = position;
    vert->textCoords = textCord;
    vert->normal = normal;
    vertices.push_back(vert);
     
    position = make_shared<vector_float4>(x+width,y,0,1);
    textCord = make_shared<vector_float4>(1,0,0,0);
    vert->position = position;
    vert->textCoords = textCord;
    vert->normal = normal;
    vertices.push_back(vert);

     
    position = make_shared<vector_float4>(x+width,y+height,0,1);
    textCord = make_shared<vector_float4>(1,1,0,0);
    vert->position = position;
    vert->textCoords = textCord;
    vert->normal = normal;
    vertices.push_back(vert);
    
     
    position = make_shared<vector_float4>(x,y+height,0,1);
    textCord = make_shared<vector_float4>(0,1,0,0);
    vert->position = position;
    vert->textCoords = textCord;
    vert->normal = normal;
    vertices.push_back(vert);
     
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
     
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    configureVertexDataForGPU();
}
