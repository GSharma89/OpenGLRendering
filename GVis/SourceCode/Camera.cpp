//
//  Camera.cpp
//  GVis
//
//  Created by Gaurav Sharma on 14/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#include "Camera.hpp"
#include "Utils.hpp"
#include <cmath>
Camera::Camera()
{
    mat = new float[16];//matrix in column wise order
    projection_transform=nullptr;
    camera_transform = nullptr;
    
}
Camera::~Camera()
{
    delete mat;
}
/*here target is the 3d vector where camera or eye is looking at,positon is the 3d vector where camera is positioned
and up is 3d vector which represents camera's orientation  */
void Camera::setCameraTransfrom(vector_float3 *target,vector_float3 *position,vector_float3 *up)
{
    Utils utils;
    /*forward vector with respect to target where camera is looking at,here this will give us coordinate system in respect of target but
     we need it in respect of camera position so we will set inverse values in camera_transform look further code*/
    shared_ptr<vector_float3> z_axis;
    z_axis->x = -position->x+target->x;
    z_axis->y = -position->y+target->y;
    z_axis->z = -position->z+target->z;
    //normalization of z_axis
    z_axis = utils.normalize(z_axis);
    //cross product of z-axis and y-axis
    shared_ptr<vector_float3> x_axis = utils.crossProduct(z_axis, shared_ptr<vector_float3>(up));
    
    //finding y_axis again by cross product of x-axis and z-axis
    shared_ptr<vector_float3> y_axis = utils.crossProduct(x_axis, z_axis);
    camera_transform->columns[0]->x = x_axis->x;
    camera_transform->columns[0]->y = x_axis->y;
    camera_transform->columns[0]->z = x_axis->z;
    camera_transform->columns[0]->w = 0;
    //setting camera transform in column-wise order
    camera_transform->columns[1]->x = y_axis->x;
    camera_transform->columns[1]->y = y_axis->y;
    camera_transform->columns[1]->z = y_axis->z;
    camera_transform->columns[1]->w = 0;
    
    camera_transform->columns[2]->x = -z_axis->x;
    camera_transform->columns[2]->y = -z_axis->y;
    camera_transform->columns[2]->z = -z_axis->z;
    camera_transform->columns[2]->w = 0;
    
    camera_transform->columns[3]->x = -position->x;
    camera_transform->columns[3]->y = -position->y;
    camera_transform->columns[3]->z = -position->z;
    camera_transform->columns[3]->w = 1;
    
}
void Camera::setProjectionTransform(float fovy_in_angle, float frustum_width, float frustum_height,float near, float far)
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
    projection_transform->columns[0]->x = d/aspectRatio;
    projection_transform->columns[0]->y = 0;
    projection_transform->columns[0]->z = 0;
    projection_transform->columns[0]->w = 0;
    
    projection_transform->columns[1]->x = 0;
    projection_transform->columns[1]->y = d;
    projection_transform->columns[1]->z = 0;
    projection_transform->columns[1]->w = 0;
    
    projection_transform->columns[2]->x = 0;
    projection_transform->columns[2]->y = 0;
    projection_transform->columns[2]->z = -(far+near)/(far-near);
    projection_transform->columns[2]->w = -1;
    
    projection_transform->columns[2]->x = 0;
    projection_transform->columns[2]->y = 0;
    projection_transform->columns[2]->z = - 2*far*near/(far-near);
    projection_transform->columns[2]->w = 0;
}
void Camera:: updateOnMouseDownEvent(float mouse_x,float mouse_y)
{
    
}
void Camera::updateOnForwardKeyPress()
{
    
}
void Camera::updateOnBackwardKeyPress()
{
    
}
void Camera::updateOnLeftKeyPress()
{
    
}
void Camera::updateOnRightKeyPress()
{
    
}
float* Camera:: getCameraTransform()
{
    if(camera_transform!=nullptr)
    {
        int j= 0;
        for(int i=0;i<4;++i)
        {
            mat[j] =   camera_transform->columns[i]->x;
            mat[j+1] = camera_transform->columns[i]->y;
            mat[j+2] = camera_transform->columns[i]->z;
            mat[j+3] = camera_transform->columns[i]->w;
            j = j+4;
        }
        return mat;
    }
    else
        return nullptr;
    
}
float* Camera::getProjectionTransform()
{
    if(projection_transform!=nullptr)
    {
        int j= 0;
        for(int i=0;i<4;++i)
        {
            mat[j] =   projection_transform->columns[i]->x;
            mat[j+1] = projection_transform->columns[i]->y;
            mat[j+2] = projection_transform->columns[i]->z;
            mat[j+3] = projection_transform->columns[i]->w;
            j = j+4;
        }
        return mat;
    }
    else
        return nullptr;
}
