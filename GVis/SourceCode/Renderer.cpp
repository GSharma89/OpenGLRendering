//
//  Renderer.cpp
//  GVis
//
//  Created by Gaurav Sharma on 18/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Renderer.hpp"
#include "Shape.hpp"
Renderer::Renderer()
{
    shader = unique_ptr<Shader>();
    setShaderProgram(COLOR_SHADER);
    shader_type = COLOR_SHADER;
}
void Renderer::setShaderProgram(ShaderProgram program)
{
    shader_program = shader->shader_program_list.at(int(program));
}

void Renderer::setViewport(float x,float y,float width,float height)
{
    vp_x = x;
    vp_y = y;
    vp_width = width;
    vp_height = height;
}
void Renderer::render(shared_ptr<Camera> camera,shared_ptr<Node> content_node_tree)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(vp_x, vp_y, vp_width, vp_height);
    glUseProgram(shader_program);
    int loc   = glGetUniformLocation(shader_program, "projection_matrix");
    glUniformMatrix4fv(loc, 1, GL_FALSE,camera->getProjectionTransform());
    loc   = glGetUniformLocation(shader_program, "view_matrix");
    glUniformMatrix4fv(loc, 1, GL_FALSE,camera->getCameraTransform());
    draw(content_node_tree);
}
/*recursive function this will render contents of each node in frame buffer with current shader program and will set transform matrices in that shader as per node
 this function will accumulate transform matrices from root to shape node and then accumulated transform will be set to shader program*/
void Renderer::draw(shared_ptr<Node> node)
{
    NodeType type  = node->getType();
    if(type != GVis_GROUP && type !=GVis_MESS)
    {
        shared_ptr<Shape> shape = static_pointer_cast<Shape>(node);
        glBindVertexArray(shape->getVertexArray());
        //int loc  = glGetAttribLocation(shader_program,"")
    
        
        
        
        
        switch (shader_type) {
                case GVis::COLOR_SHADER:
            
            break;
        case GVis::TEXTURE_SHADER:
            break;
        case Gvis::LIGHTING_SHADER:
        default:
            break;
    }
        
    }
}
