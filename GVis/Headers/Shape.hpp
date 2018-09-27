//
//  Shape.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp
#include <iostream>
#include "DataType.hpp"
#include <vector>
#include "Node.hpp"
#include <GL/glew.h>
using namespace GVis;
class Shape:public Node
{
    protected:
        vector<shared_ptr<Vertex>> vertices;
        vector<uint>  indices;
        bool raster_required;
        string texture_image_name;
        GLuint vertexBuffer;
        GLuint vertexArray;
        GLuint elementBuffer;
        GLuint texture;
        void configureVertexDataForGPU();
    
    public:
        Shape()
        {
            raster_required = false;
            texture_image_name = "";
            glGenVertexArrays(1,&vertexArray);
            glGenBuffers(1,&vertexBuffer);
            glGenBuffers(1,&elementBuffer);

        }
    ~Shape()
    {
        glDeleteTextures(1, &texture);
        glDeleteVertexArrays(1,&vertexArray);
        glDeleteBuffers(1,&vertexBuffer);
        glDeleteBuffers(1,&elementBuffer);
    }
    virtual void rasterize() = 0;
    GLuint getVertexArray() const;
    GLuint getTexture() const;
    
};

#endif /* Shape_hpp */
