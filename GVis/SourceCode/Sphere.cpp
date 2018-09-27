//
//  Sphere.cpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Sphere.hpp"
#include <math.h>
void Sphere::rasterize()
{
    uint slices = 1000;
    uint slice_triangles = 1000;
    
    float pi = M_PI;
    float delta_theta = (2 * pi) / slice_triangles;
    float delta_phi = pi / slices;
    
    float phi = 0;//-Float(M_PI/2)
    for (int i=0; i<=slices;i++)
    {
        float theta = 0;
        for(int j=0;j<=slice_triangles;j++)
        {
            float a = sin(phi) * cos(theta);
            float b = cos(phi);
            float c = sin(phi) * sin(theta);
            
            shared_ptr<vector_float4> pos = make_shared<vector_float4>(center.x + radius*a,center.y + radius*b,center.z + radius*c,1);
            /*
             normal of sphere for phi and theta parameter is given by vector (a,b,c).
             Finding normal of sphere surface
             --------------------------------
             1.we have parametric coordinates of sphere as given below-
             x = r*sin(phi)*cos(theta),y = r*sin(phi)*sin(theta),z=r*cos(theta)
             where phi is angle between z-axis and point(x,y,z) and theta is angle between x-axis and
             projectionpoint(x,y,z) in xy plane.r is radius
             so the equation of surface of sphere is represented as-
             
             T = xi + yj + zk
             2.then find  two tangent vectors in suface T which are T(phi) and T(theta) by partial differentiation of T with respect to phi and theta respectively
             
             3.now compute cross product of T(phi) and T(theta) and compute magnitude of resultant cross product.
             
             4.now divide cross product vector by magnitude that gives us unit normal vector which is exactly same as we set below.
             */
            shared_ptr<vector_float4> norm = make_shared<vector_float4>(a,b,c,0);
            
            /*
             Finding texture coordinate(u,v) corresponding to point(x,y,z) on sphere surface
             -------------------------------------------------------------------------------
             
             1. we know that theta and phi are the angles which are variable to produce point(x,y,z).so we mapped theta's range which is 0 to 2pi to the width of our 2d texture and similarly phi angle which has range 0 to pi is mapped to height of our 2d texure.
             
             2.if (theta,phi) is equal to (2pi,pi) then resulantant point(x,y,z) will be textured by pixel at (1,1) position of our given 2d texture.if (theta,phi) is equal to (0,0) then resultant (x,y,z) will be texture by pixel at (0,0) position of texture.
             */
            float u = theta / (2*pi);
            
            float v = phi / pi;
            
            shared_ptr<vector_float4> tex_cord = make_shared<vector_float4>(u,v,0,0);
            
            shared_ptr<Vertex> vert = make_shared<Vertex>();
            vert->position = pos;
            vert->textCoords = tex_cord;
            vert->normal = norm;
            vertices.push_back(vert);
            theta = theta + delta_theta;
            
        }
        
        phi = phi+delta_phi;
        
        
    }
    /*
     we can visualize the subdivision of sphere surface in quads such that two points will be on a particular slice and other
     two points will be on just below slice of that particular slice.
     */
    for (uint slice_index=0 ;slice_index<slices;++slice_index)
    {
        for (uint slice_triangle_index=0; slice_triangle_index<slice_triangles;++slice_triangle_index)
        {
            
            //these four indices give us four vertices on shpere surface.these four vertices form a quadilateral by which we
            // form two triangles
            uint i0 = slice_triangle_index + slice_index * slice_triangles;
            
            //this is to handle a situation when we cross boundary of current slice
            uint i1 = ((i0 + 1) % (slice_triangles)) + (slice_index * slice_triangles);
            
            uint i2 = i0 + slice_triangles;
            
            //this is to handle a situation when we cross boundary of slice next to current slice
            uint i3 = ((i2 + 1) % (slice_triangles)) + ((slice_index + 1) * slice_triangles);
            
            
            //a triangle vertices' indices
            indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i3);
            
            //a triangle vertices' indices
            indices.push_back(i0);
            indices.push_back(i3);
            indices.push_back(i2);
            
            
        }
    
    }
    configureVertexDataForGPU();
    
}
