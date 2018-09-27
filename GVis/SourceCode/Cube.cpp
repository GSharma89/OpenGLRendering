//
//  Cube.cpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Cube.hpp"
void Cube::rasterize()
{
    shared_ptr<vector_float4> normals[] =
                                    {
                                        make_shared<vector_float4>(0,0,-1,1),
                                        make_shared<vector_float4>(0,0,1,1),
                                        make_shared<vector_float4>(0,-1,0,1),
                                        make_shared<vector_float4>(0,1,0,1),
                                        make_shared<vector_float4>(-1,0,0,1),
                                        make_shared<vector_float4>(-1,0,0,1)
                                        
                                    };
    
    shared_ptr<vector_float4> texCords[] =
                                    {
                                        //back face
                                        make_shared<vector_float4>(0.333333,0.50,0,0),
                                        make_shared<vector_float4>(0.666666,0.50,0,0),
                                        make_shared<vector_float4>(0.333333,0.75,0,0),
                                        make_shared<vector_float4>(0.666666,0.75,0,0),
                                        //front face
                                        make_shared<vector_float4>(0.333333,0.25,0,0),
                                        make_shared<vector_float4>(0.666666,0.25,0,0),
                                        make_shared<vector_float4>(0.333333,0,0,0),
                                        make_shared<vector_float4>(0.666666,0,0,0),
                                        //bottom face
                                        make_shared<vector_float4>(0.333333,0.50,0,0),
                                        make_shared<vector_float4>(0.666666,0.50,0,0),
                                        make_shared<vector_float4>(0.333333,0.25,0,0),
                                        make_shared<vector_float4>(0.666666,0.25,0,0),
                                        //top face
                                        make_shared<vector_float4>(0.333333,0.75,0,0),
                                        make_shared<vector_float4>(0.666666,0.75,0,0),
                                        make_shared<vector_float4>(0.333333,0,0,0),
                                        make_shared<vector_float4>(0.666666,0,0,0),
                                        //left face
                                        make_shared<vector_float4>(0.333333,0.50,0,0),
                                        make_shared<vector_float4>(0.0,0.50,0,0),
                                        make_shared<vector_float4>(0.333333,0.25,0,0),
                                        make_shared<vector_float4>(0.0,0.25,0,0),
                                        //right face
                                        make_shared<vector_float4>(0.666666,0.50,0,0),
                                        make_shared<vector_float4>(1.0,0.50,0,0),
                                        make_shared<vector_float4>(0.666666,0.25,0,0),
                                        make_shared<vector_float4>(1.0,0.25,0,0),
                                    };

    int tex_cord_ind = 0;
    int a = 1;
    int b = 1;
    int c = 1;
    for(int i=0;i<6;i++)
    {
        c = -1*c;
        for(int j=0;j<2;j++)
        {
            b = -1*b;
            for(int k=0;k<2;k++)
            {
                a = -1*a;
                shared_ptr<vector_float4> position(nullptr);
                if(i == 0 || i==1)//specifying xy plane along z-axe,0 is back face,1 is front face
                {
                    position = make_shared<vector_float4>(a * side/2,b * side/2,c * side/2,1);
                    //vertices.append()
                }
                else if(i==2 || i==3)//specifying xz plane along y-axe,2 is bottom face,3 is top face
                {
                    position = make_shared<vector_float4>(a*side/2,c*side/2,b*side/2,1);
                    
                }
                else if(i==4 || i==5)//speciying yz plane along x-axe,4 is left face and 5 is right face
                {
                    position = make_shared<vector_float4>(c*side/2,a*side/2,b*side/2,1);
                }
                
                shared_ptr<Vertex> vert = make_shared<Vertex>();
                vert->position = position;
                vert->normal = normals[i];
                vert->textCoords = texCords[tex_cord_ind];
                ++tex_cord_ind;
                vertices.push_back(vert);
            }
        }
        indices.push_back(4*i);
        indices.push_back(4*i+1);
        indices.push_back(4*i+2);
        
        indices.push_back(4*i+1);
        indices.push_back(4*i+3);
        indices.push_back(4*i+2);
    }

    configureVertexDataForGPU();
}
    

