//
//  Camera.hpp
//  GVis
//
//  Created by Gaurav Sharma on 14/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp
#include "DataType.hpp"
#include <iostream>
using namespace GVis;
class Camera
{
    shared_ptr<matrix_float4x4> camera_transform;
    shared_ptr<matrix_float4x4> projection_transform;
    float *mat;
    public:
    Camera();
    void setCameraTransfrom(vector_float3 *target,vector_float3 *position,vector_float3 *up);
    void setProjectionTransform(float fovy_in_angle, float frustum_width, float frustum_height,float near, float far);
    void updateOnMouseDownEvent(float mouse_x,float mouse_y);
    void updateOnForwardKeyPress();
    void updateOnBackwardKeyPress();
    void updateOnLeftKeyPress();
    void updateOnRightKeyPress();
    void updateProjectionOnZoomInOut();
    float* getCameraTransform();
    float* getProjectionTransform();
    ~Camera();
    
};

#endif /* Camera_hpp */
