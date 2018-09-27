//
//  Shape.cpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Shape.hpp"
GLuint Shape::getVertexArray() const
{
    return vertexArray;
}
GLuint Shape::getTexture() const
{
    return texture;
}
void Shape::configureVertexDataForGPU()
{
    size_t vertices_count = vertices.size();
    size_t indices_count = indices.size();
    if(vertices_count)
    {
        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
        Vertex *vertices_base_ptr = vertices.at(0).get();
        glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices_count,vertices_base_ptr,GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elementBuffer);
        uint *indices_base_ptr = &(indices.at(0));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(uint)*indices_count,indices_base_ptr,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
    if(texture_image_name!="")
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /*int w ,h,no_of_channels;
         unsigned char *data = NULL;//here we need to use any library which can load image
         if (data)
         {
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
         }
         else
         {
         std::cout << "Failed to load texture" << std::endl;
         cout<<"Please use image loading library to see texture on curve"<<endl;
         //return -1;
         }*/
    }
}
