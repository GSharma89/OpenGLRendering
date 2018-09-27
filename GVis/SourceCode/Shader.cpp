//
//  Shader.cpp
//  GVis
//
//  Created by Gaurav Sharma on 14/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Shader.hpp"
Shader::Shader()
{
    /*this will give us color shader program all vertices will be colored by specified color value using this program*/
    getShaderProgram(vertexShader1, fragmentShader1);
    /*this one will give us shader program which will render vertices with specified texture image*/
    getShaderProgram(vertexShader2, fragmentShader2);
    /*this one will give us shader program to render white colored x-y axis*/
    getShaderProgram(vertexShader1, axisFragmentShader);
}
GLuint Shader::getShaderProgram(const char* vertexShader, const char *fragmentShader)
{
    
    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader,1,&vertexShader,NULL);
    glCompileShader(vertex_shader);
    char log[400];
    int is_ok;
    glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetShaderInfoLog(vertex_shader,400,NULL,log);
        return -1;//error
    }
    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader,1,&fragmentShader,NULL);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader,GL_COMPILE_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetShaderInfoLog(frag_shader,400,NULL,log);
        return -1;
    }
    
    GLuint shader_program =  glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,frag_shader);
    glLinkProgram(shader_program);
    
    glGetProgramiv(shader_program,GL_LINK_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetProgramInfoLog(shader_program,400,NULL,log);
        return -1;//error
    }
    shader_program_list.push_back(shader_program);
    return shader_program;
    
}
