//
//  CatMullRomSpline.cpp
//  OpenGLRenderingEngine
//
//  Created by Gaurav Sharma on 10/08/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "CatMullRomSpline.hpp"
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <cstdlib>
#include <GLFW/glfw3.h>
float axis_vertices [] =
{

    -1440,0,0,1,
    1440,0,0,1,
    0,900,0,1,
    0,-900,0,1
    
};
    
/*vertex and fragment shaders*/
const char *vertexShader = "#version 410 core\n"
"in vec4 position;\n"
"uniform mat4 projection_matrix;\n"
"uniform  mat4 view_matrix;\n"
"uniform mat4 model_matrix;\n"
//"out vec2 texCord;\n"
"void main()\n"
"{\n"
   "gl_Position = projection_matrix*view_matrix*model_matrix*position;\n"
   //"gl_Position = position;\n"
   //"texCord = vec2(position.x,position.y);\n"
"}\0";

const char *fragmentShader="#version 410 core\n"
"out vec4 fragColor;\n"
//"in vec2 texCord;\n"
//"uniform sampler2D spline_texture;"
"void main()\n"
"{\n"
    //"fragColor = texture(spline_texture,texCord);\n"
    "fragColor = vec4(1,0,0,1);\n"
"}\0";

const char *axisFragmentShader="#version 410 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"fragColor = vec4(1,1,1,1);\n"
"}\0";

static float t = 0.5;
static float projection_matrix[4][4];
static float view_matrix[4][4];
static float model_matrix[4][4];
void applyProjectionTransform()
{
    
    for(int k=0;k<12;)
    {
        float vec1[4];
        float vec[4];
        vec1[0] = axis_vertices[k];
        vec1[1] = axis_vertices[k+1];
        vec1[2] = axis_vertices[k+2];
        vec1[3] = axis_vertices[k+3];
        for(int i=0;i<4;i++)
        {
            
            float mul = 0;
            for(int j=0;j<4;j++)
            {
                mul = mul + projection_matrix[i][j]*vec1[j];
            }
            vec[i] = mul;
        }
        cout<<"projection transform point:";
        axis_vertices[k] = vec[0]/vec[3];
        axis_vertices[k+1] = vec[1]/vec[3];
        axis_vertices[k+2] = vec[2]/vec[3];
        axis_vertices[k+3] = vec[3]/vec[3];
        cout<<axis_vertices[k]<<" "<<axis_vertices[k+1]<<" "<<axis_vertices[k+2]<<" "<<axis_vertices[k+3]<<endl;
        k = k+4;
        
    }
    
}
void applyViewTransform()
{
    
    for(int k=0;k<12;)
    {
        float vec1[4];
        float vec[4];
        vec1[0] = axis_vertices[k];
        vec1[1] = axis_vertices[k+1];
        vec1[2] = axis_vertices[k+2];
        vec1[3] = axis_vertices[k+3];
        for(int i=0;i<4;i++)
        {
            
            float mul = 0;
            for(int j=0;j<4;j++)
            {
                mul = mul + view_matrix[j][i]*vec1[j];
            }
            vec[i] = mul;
        }
        cout<<"view transform point:";
        cout<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<" "<<vec[3]<<endl;
        axis_vertices[k] = vec[0];
        axis_vertices[k+1] = vec[1];
        axis_vertices[k+2] = vec[2];
        axis_vertices[k+3] = vec[3];
        k = k+4;
        
    }
    
}
void setViewMatrix(float *dir ,float *up/*up is already in normalized form*/,float *pos)
{
    
    float x_axis[] = {0,0,0};
    float y_axis[] = {0,0,0};
    float z_axis[] = {0,0,0};
    z_axis[0] = dir[0]-pos[0];
    z_axis[1] = dir[1]-pos[1];
    z_axis[2] = dir[2]-pos[2];
    
    //normalization of z_axis
    float m1 = sqrt(z_axis[0]*z_axis[0]+z_axis[1]*z_axis[1]+z_axis[2]*z_axis[2]);
    z_axis[0] = z_axis[0]/m1;
    z_axis[1] = z_axis[1]/m1;
    z_axis[2] = z_axis[2]/m1;
    
    
    //cross product of z-axis and y-axis
    x_axis[0] = up[2]*z_axis[1]-z_axis[2]*up[1];
    x_axis[1] = up[0]*z_axis[2]-up[2]*z_axis[0];
    x_axis[2] = up[1]*z_axis[0]-z_axis[1]*up[0];
    
    //finding y_axis again by cross product of x-axis and z-axis
    y_axis[0] = x_axis[1]*z_axis[2]-x_axis[2]*z_axis[1];
    y_axis[1] = z_axis[0]*x_axis[2]-x_axis[0]*z_axis[2];
    y_axis[2] = x_axis[0]*z_axis[1]-x_axis[1]*z_axis[0];
    
    
    view_matrix[0][0] = x_axis[0];
    view_matrix[0][1] = x_axis[1];
    view_matrix[0][2] = x_axis[2];
    view_matrix[0][3] = 0;
    
    view_matrix[1][0] = y_axis[0];
    view_matrix[1][1] = y_axis[1];
    view_matrix[1][2] = y_axis[2];
    view_matrix[1][3] = 0;
    
    view_matrix[2][0] = -z_axis[0];
    view_matrix[2][1] = -z_axis[1];
    view_matrix[2][2] = -z_axis[2];
    view_matrix[2][3] = 0;
    
    view_matrix[3][0] = -pos[0];
    view_matrix[3][1] = -pos[1];
    view_matrix[3][2] = -pos[2];
    view_matrix[3][3] = 1;
    
    
}

void getProjectionMatrix(float *matrix,float fovy_in_angle,float frustum_width,float frustum_height,float near,float far)
{
    float d =  1/tan(fovy_in_angle * 0.5 * 3.14 / 180 );
    float aspectRatio = frustum_width / frustum_height;
    matrix[0] = d/aspectRatio;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = d;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = 0.0;
    matrix[9] = 0.0;
    matrix[10] = -(far + near) / (far-near);
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = - 2*far*near/(far-near);
    matrix[15] = 0.0;
    
}

void CatMullRomSpline::setProjectionMatrix(float fovy_in_angle,float frustum_width,float frustum_height,float near,float far)
{
    
    //setting projection matrix
    /*
     the perspective projection row -wise matrix:
     _                                                                                  _
     | d/aspect_ratio    0                     0                             0            |
     |                                                                                    |
     |    0              d                     0                             0            |
     |                                                                                    |
     |    0              0               -(far+near)/(far-near) - 2*far*near/(far-near)   |
     |                                                                                    |
     |_    0             0                  -1                               0           _|
     
     where d is distance between camera and projection plane i.e d = 1/tan(verticalFieldOfView/2) and far and near are
     distance from camera to far and near plane respectively.
     
     */
    float d =  1/tan(fovy_in_angle * 0.5 * 3.14 / 180 );
    
    float aspectRatio = frustum_width / frustum_height;
    projection_matrix[0][0] = d/aspectRatio;
    projection_matrix[1][1] = d;
    projection_matrix[2][2] =  -(far+near)/(far-near);
    projection_matrix[2][3] = -2*far*near/(far-near);
    projection_matrix[3][2] = -1;
    projection_matrix[3][3] = 0;
}
void CatMullRomSpline::initializeMatrices()
{
    //view and model matrix are identities
    view_matrix[0][0] = 1;
    view_matrix[1][1] = 1;
    view_matrix[2][2] = 1;
    view_matrix[3][3] = 1;
    model_matrix[0][0] = 1;
    model_matrix[1][1] = 1;
    model_matrix[2][2] = 1;
    model_matrix[3][3] = 1;
    projection_matrix[0][0] =1;
    projection_matrix[1][1] =1;
    projection_matrix[2][2] =1;
    projection_matrix[3][3] =1;
}

float getValue5thDecimalPoint(float value)
{
    
    double v = value*100000;
    int int_part = v;
    value = float(int_part)/100000;
    return value;
}
/*this is the recursive method to give all points on a cubic cat mull rom spline in new_points vector*/
void CatMullRomSpline::interpolateCubicRomSpline(Point* p0,Point* p1,Point* p2,Point* p3,vector<Point*> & new_points)
{
    float x[4];
    x[0]=p0->x;
    x[1]=p1->x;
    x[2]=p2->x;
    x[3]=p3->x;
    
    float y[4];
    y[0]=p0->y;
    y[1]=p1->y;
    y[2]=p2->y;
    y[3]=p3->y;
    
    //this is the new point on the curve between points p1 and p2 at t=0.5
    Point* new_point = new Point;
    new_point->x = x[1] + 0.5*t*(-x[0]+x[2]) + t*t*(x[0] - 2.5*x[1] + 2*x[2] - 0.5*x[3])+ t*t*t*(-0.5*x[0] + 1.5*x[1] - 1.5*x[2] + 0.5*x[3]);
    new_point->y = y[1] + 0.5*t*(-y[0]+y[2]) + t*t*(y[0] - 2.5*y[1] + 2*y[2] - 0.5*y[3]) + t*t*t*(-0.5*y[0] + 1.5*y[1] - 1.5*y[2] + 0.5*y[3]);
    //now check p1 ,new_point and p2 are collinear,if it is so then add in list
    float d1 = sqrt((p1->x-new_point->x)*(p1->x-new_point->x)+(p1->y-new_point->y)*(p1->y-new_point->y));
    float d2 = sqrt((p2->x-new_point->x)*(p2->x-new_point->x)+(p2->y-new_point->y)*(p2->y-new_point->y));
    float d =  sqrt((p2->x-p1->x)*(p2->x-p1->x)+(p2->y-p1->y)*(p2->y-p1->y));
    d1 = getValue5thDecimalPoint(d1);
    d2 = getValue5thDecimalPoint(d2);
    d = getValue5thDecimalPoint(d);
    //if still curvature then continue interpolation further
    if(d!=d1+d2)
    {
        interpolateCubicRomSpline(p0, p1, new_point, p2, new_points);
        new_points.push_back(new_point);
        interpolateCubicRomSpline(p1, new_point, p2, p3,new_points);
    }
}

/*this is the method which gives all points on nth order catmull rom spline in new_points vector*/
void CatMullRomSpline::generatePointsOfCatmullRomSpline(vector<Point*> &control_point_list,vector<Point*> &new_points)
{
    size_t n = control_point_list.size();
    //normalize x and y
    float mean_x = 0.0;
    float min_x  = control_point_list.at(0)->x;
    float max_x = 0.0;
    float mean_y = 0.0;
    float min_y = control_point_list.at(0)->y;
    float max_y = 0.0;
    for (int i=0; i<n; i++)
    {
        mean_x = mean_x + control_point_list.at(i)->x;
        mean_y = mean_x + control_point_list.at(i)->y;
        if(control_point_list.at(i)->x<min_x)
        {
            min_x = control_point_list.at(i)->x;
        }
        if(control_point_list.at(i)->y<min_y)
        {
            min_y = control_point_list.at(i)->y;
        }
        
        if(control_point_list.at(i)->x>max_x)
        {
            max_x = control_point_list.at(i)->x;
        }
        if(control_point_list.at(i)->y>max_y)
        {
            max_y = control_point_list.at(i)->y;
        }
    }
    mean_x = mean_x/n;
    mean_y = mean_y/n;
    
    for (int i=0; i<n; i++)
    {
        Point *p = control_point_list.at(i);
        if(max_x!=min_x)
        {
            p->x = (p->x-mean_x)/(max_x-min_x);
            
        }
        if(max_y!=min_y)
        {
            p->y = (p->y-mean_y)/(max_y-min_y);
            
        }
    }
    
    
    int i=0;
    Point *p = NULL;
    p = control_point_list.at(i);
    new_points.push_back(p);
    interpolateCubicRomSpline(control_point_list.at(i), control_point_list.at(i), control_point_list.at(i+1), control_point_list.at(i+2), new_points);
    p = control_point_list.at(i+1);
    new_points.push_back(p);
    
    while(n-i>3)
    {
        interpolateCubicRomSpline(control_point_list.at(i), control_point_list.at(i+1), control_point_list.at(i+2), control_point_list.at(i+3), new_points);
        p = control_point_list.at(i+2);
        new_points.push_back(p);
        i++;
    }
    interpolateCubicRomSpline(control_point_list.at(i), control_point_list.at(i+1), control_point_list.at(i+2), control_point_list.at(i+2), new_points);
    p = control_point_list.at(i+2);
    new_points.push_back(p);
    
}

/*this is the method which will be called from main function and will take all the inputs from user as mentioned in assignment2 text file and this method generates all the point of the gemetry of given width along the given catmull rom spline
 .this method also uses opengl code to render the geometry.*/
int CatMullRomSpline::generateGeometry(vector<Point*> &control_point_list,string &texture_file_path,float geom_width)
{
    size_t n_control_points = control_point_list.size();
    if(n_control_points<4)
    {
        cout<<"Spline can't be generated because at least 4 points are required for catmull-spline"<<endl;
        return -1;
        
    }
    vector<Point*> points_on_spline;
    generatePointsOfCatmullRomSpline(control_point_list, points_on_spline);
    size_t n = points_on_spline.size();
    
    
    float *vertices_on_spline = new float[sizeof(Point)*(n-1)];
    /*because here we will get points 4 points from normals and one point is intesection point of two successive lines*/
    float *vertices = new float[sizeof(Point)*5*(n-1)];
    //one line will give us two triangles by normals and additional two triangle will be there because of the point
    //where two continous line are crossing each other
    unsigned int *indices = new unsigned int[sizeof(unsigned int)*12*(n-1)];
    //cout<<" Below are interpolated points generated for given CatMullRom-Spline"<<endl;
    for(int i=0;i<n-1;i++)
    {
        Point* p1 = points_on_spline.at(i);
        vertices_on_spline[4*i] = p1->x;
        vertices_on_spline[4*i+1] = p1->y;
        vertices_on_spline[4*i+2] = p1->z;
        vertices_on_spline[4*i+3] = p1->w;
        
        Point* p2 = points_on_spline.at(i+1);
        cout<<p1->x<<","<<p1->y<<","<<p1->z<<","<<p1->w<<endl;
        //these are the points of four normal of line p1p2.p1 has two normal on either side and each at perpedicular distance
        // of geom_width/2.similarly point p2 has two normals.
        float x[5],y[5];
        if(p2->x==p1->x)//line is vertical to x-axis so slope is infinite
        {
            x[0] = p1->x+geom_width/2;
            y[0] = p1->y;
            x[1] = p2->x+geom_width/2;
            y[1] = p2->y;
            x[2] = p2->x-geom_width/2;
            y[2] = p2->y;
            x[3] = p1->x-geom_width/2;
            y[3] = p1->y;
        }
        else if(p2->y==p1->y)//line is parallel to x-axis so slope is 0
        {
            x[0] = p1->x;
            y[0] = p1->y+geom_width/2;
            x[1] = p2->x;
            y[1] = p2->y+geom_width/2;
            x[2]= p2->x;
            y[2] = p2->y-geom_width/2;
            x[3] = p1->x;
            y[3] = p1->y-geom_width/2;
        }
        else//in this case line is inclined and make an angle with x-axis so slope will be non-zero.
        {
            //this is the value of tan_theta,where theta is angle of line p1p2 with respect of x-axis
            float tan_theta = (p2->y-p1->y)/(p2->x-p1->x);
            float cos_theta = (1/(1+(tan_theta*tan_theta)));
            float sin_theta = (tan_theta/(1+(tan_theta*tan_theta)));
            if(tan_theta<0)
            {
                x[0] = p1->x+(geom_width*cos_theta/2);
                y[0] = p1->y+(geom_width*sin_theta/2);
                x[1] = p2->x+(geom_width*cos_theta/2);
                y[1] = p2->y+(geom_width*sin_theta/2);
                x[2] = p2->x-(geom_width*cos_theta/2);
                y[2] = p2->y-(geom_width*sin_theta/2);
                x[3] = p1->x-(geom_width*cos_theta/2);
                y[3] = p1->y-(geom_width*sin_theta/2);
            }
            else
            {
                x[0] = p1->x-(geom_width*cos_theta/2);
                y[0] = p1->y+(geom_width*sin_theta/2);
                x[1] = p2->x-(geom_width*cos_theta/2);
                y[1] = p2->y+(geom_width*sin_theta/2);
                x[2] = p2->x+(geom_width*cos_theta/2);
                y[2] = p2->y-(geom_width*sin_theta/2);
                x[3] = p1->x+(geom_width*cos_theta/2);
                y[3]= p1->y-(geom_width*sin_theta/2);
            }
        }
        x[4] = p2->x;
        y[4] = p2->y;
        int k =0;
        /*these are the vertices of new geometry along given catmullrom-spline*/
        for(int j=i;j<i+5;j++)
        {
            vertices[4*j]=x[k];
            vertices[4*j+1]=y[k];
            vertices[4*j+2]=0;
            vertices[4*j+3]=1;
            k++;
        }
        
        indices[12*i]= 5*i;
        indices[12*i+1]= 5*i+1;
        indices[12*i+2]= 5*i+2;
        
        indices[12*i+3]= 5*i+2;
        indices[12*i+4]= 5*i+3;
        indices[12*i+5]= 5*i;
        
        indices[12*i+6]= 5*i+1;
        indices[12*i+7]= 5*i+4;
        indices[12*i+8]= 5*i+5;
        
        indices[12*i+9]= 5*i+2;
        indices[12*i+10]= 5*i+4;
        indices[12*i+11]= 5*i+8;
        
        
    }
    
    /*this is the total indices we will store in element buffer*/
    size_t no_of_indices = 12*n-18;
    /*these are total vertices of new geometry.these vertices will be stored in vertex buffer object*/
    size_t no_of_vertices = 5*n-6;
    /*all the triplets of new gemetry*/
    cout<<"\n\n triplets of new geometry along catmullRom Spline"<<endl;
    /*for(int i=0;i<no_of_vertices;)
    {
        cout<<vertices[4*i]<<","<<vertices[4*i+1]<<endl;
        i = i+4;
        
    }*/
    
    if(!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    GLFWwindow *window = glfwCreateWindow(2880, 1800, "GVisWindow", NULL, NULL);
    
    if(!window)
    {
        cout<<"window creation is failed\n";
        glfwTerminate();
        return -1;
    }
   
    glfwMakeContextCurrent(window);
    
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    //create shader and build
    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader,1,&vertexShader,NULL);
    glCompileShader(vertex_shader);
    char log[400];
    int is_ok;
    glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetShaderInfoLog(vertex_shader,400,NULL,log);
        cout<<"Vertex shader compilation failed\n"<<log<<endl;
    }
    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader,1,&fragmentShader,NULL);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader,GL_COMPILE_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetShaderInfoLog(frag_shader,400,NULL,log);
        cout<<"Fragment shader compilation failed\n"<<log<<endl;
    }
    int axis_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(axis_frag_shader,1,&axisFragmentShader,NULL);
    glCompileShader(axis_frag_shader);
    glGetShaderiv(axis_frag_shader,GL_COMPILE_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetShaderInfoLog(axis_frag_shader,400,NULL,log);
        cout<<"Axis Fragment shader compilation failed\n"<<log<<endl;
    }
    GLuint shader_program =  glCreateProgram();
    glAttachShader(shader_program,vertex_shader);
    glAttachShader(shader_program,frag_shader);
    glLinkProgram(shader_program);
    
    glGetProgramiv(shader_program,GL_LINK_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetProgramInfoLog(shader_program,400,NULL,log);
        cout<<"shader program linking failed\n"<<log<<endl;
    }
    GLuint axisProgram =  glCreateProgram();
    glAttachShader(axisProgram,vertex_shader);
    glAttachShader(axisProgram,axis_frag_shader);
    glLinkProgram(axisProgram);
    glGetProgramiv(axisProgram,GL_LINK_STATUS,&is_ok);
    if(!is_ok)
    {
        glGetProgramInfoLog(axisProgram,400,NULL,log);
        cout<<"shader program linking failed\n"<<log<<endl;
    }
    glDeleteShader(axis_frag_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
    
    GLuint vbo,vao,vao1,vbo1,ebo;
    
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glBindVertexArray(vao);
    //vertext array object configuration
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axis_vertices), axis_vertices, GL_STATIC_DRAW);
    GLint loc = glGetAttribLocation(axisProgram,"position");
    glVertexAttribPointer(loc,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
    glEnableVertexAttribArray(loc);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
    
    glGenVertexArrays(1,&vao1);
    glGenBuffers(1,&vbo1);
    glGenBuffers(1,&ebo);
    //vertext array object configuration
    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER,vbo1);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*no_of_vertices, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*(n-1), vertices_on_spline, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*no_of_indices,indices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    loc = glGetAttribLocation(shader_program,"position");
    glVertexAttribPointer(loc,4,GL_FLOAT,GL_FALSE,sizeof(Point),(void*)0);
    glEnableVertexAttribArray(loc);
    glBindVertexArray(0);
    
    
    
    //load and create texture
    GLuint texture;
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
    
    glUniform1i(glGetUniformLocation(shader_program, "spline_texture"), 0);
    float dir[3] = {0,0,0};
    float up[3] = {0,1,0};
    float pos[3] = {0,0,40};
    initializeMatrices();
    //glPointSize(10);
    setViewMatrix(dir, up, pos);
    //applyViewTransform();
    setProjectionMatrix(170, 2880, 1800, 0.1, 10000);
    //applyProjectionTransform();//just for testing
    //until user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, 2800, 1800);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        
        
        glUseProgram(axisProgram);
        int loc   = glGetUniformLocation(axisProgram, "projection_matrix");
        glUniformMatrix4fv(loc, 1, GL_TRUE,&projection_matrix[0][0]);
        loc   = glGetUniformLocation(axisProgram, "view_matrix");
        glUniformMatrix4fv(loc, 1, GL_FALSE,&view_matrix[0][0]);
        loc   = glGetUniformLocation(axisProgram, "model_matrix");
        glUniformMatrix4fv(loc, 1, GL_FALSE,&model_matrix[0][0]);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, 4);
        
        glUseProgram(shader_program);
        initializeMatrices();
        loc   = glGetUniformLocation(shader_program, "projection_matrix");
        glUniformMatrix4fv(loc, 1, GL_TRUE,&projection_matrix[0][0]);
        loc   = glGetUniformLocation(shader_program, "view_matrix");
        glUniformMatrix4fv(loc, 1, GL_FALSE,&view_matrix[0][0]);
        loc   = glGetUniformLocation(shader_program, "model_matrix");
        glUniformMatrix4fv(loc, 1, GL_FALSE,&model_matrix[0][0]);
        glBindVertexArray(vao1);
        //glDrawElements(GL_TRIANGLES, (GLsizei)no_of_indices, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_LINES, 0, (GLsizei)n-1);
        //swap buffers
        glfwSwapBuffers(window);
        //pool for and prcess event
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao1);
    glDeleteBuffers(1, &vbo1);
    glfwTerminate();
    
    return 0;
}




