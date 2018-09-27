//
//  Renderer.hpp
//  GVis
//
//  Created by Gaurav Sharma on 18/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <iostream>
#include <GL/glew.h>
#include "Camera.hpp"
#include "Node.hpp"
#include "Shader.hpp"

class Renderer
{
    GLuint shader_program;//shader program which will be used by renderer to apply transformation,lighting,texture on vertices
    ShaderProgram shader_type;
    float vp_x,vp_y,vp_width,vp_height;//viewport to apply on window
    unique_ptr<Shader> shader;
    void draw(shared_ptr<Node> content_tree);
    public:
        Renderer();
        void setShaderProgram(ShaderProgram program);
        void setViewport(float x,float y,float width,float height);
        void render(shared_ptr<Camera> camera,shared_ptr<Node> content_tree);
    
    
};

#endif /* Renderer_hpp */
