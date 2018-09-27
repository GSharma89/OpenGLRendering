//
//  Shader.hpp
//  GVis
//
//  Created by Gaurav Sharma on 14/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <iostream>
#include <GL/glew.h>
#include <vector>
using namespace std;
class Shader
{
    /*Color Shader program*/
    const char *vertexShader1 = "#version 410 core\n"
    "in vec4 position;\n"
    "uniform vec4 color;\n"
    "uniform mat4 projection_matrix;\n"
    "uniform  mat4 view_matrix;\n"
    "uniform mat4 model_matrix;\n"
    
    "void main()\n"
    "{\n"
    "gl_Position = projection_matrix*view_matrix*model_matrix*position;\n"
    "}\0";
    
    const char *fragmentShader1="#version 410 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "fragColor = color;\n"
    "}\0";
    
    //Texture_Program
    const char *vertexShader2 = "#version 410 core\n"
    "in vec4 position;\n"
    "in vec4 inTexCord;\n"
    "uniform mat4 projection_matrix;\n"
    "uniform  mat4 view_matrix;\n"
    "uniform mat4 model_matrix;\n"
    "out vec2 texCord;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection_matrix*view_matrix*model_matrix*position;\n"
    "texCord = vec2(inTexCord.x,inTexCord.y);\n"
    "}\0";
    
    const char *fragmentShader2="#version 410 core\n"
    "in vec2 texCord;\n"
    "uniform sampler2D in_texture;"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "fragColor = texture(in_texture,texCord);\n"
    "}\0";
    
    const char *axisFragmentShader ="#version 410 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "fragColor = vec4(1,1,1,1);\n"
    "}\0";
    public:
        Shader();
        vector<GLuint> shader_program_list;
        GLuint getShaderProgram(const char* vertex_shader,const char* fragment_shader);
};

#endif /* Shader_hpp */
