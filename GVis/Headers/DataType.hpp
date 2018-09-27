//
//  DataType.hpp
//  GVis
//
//  Created by Gaurav Sharma on 05/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef DataType_h
#define DataType_h
#include<memory>
using namespace std;
namespace GVis
{
    
    struct vector_float4
    {
        float x;
        float y;
        float z;
        float w;
        vector_float4()
        {
            x=0;
            y=0;
            z=0;
            w=1;
        }
        vector_float4(float a,float b,float c,float d)
        {
            x = a;
            y = b;
            z = c;
            w = d;
        }
    };

    struct vector_float3
    {
        float x;
        float y;
        float z;
        vector_float3()
        {
            x=0;
            y=0;
            z=0;
        }
        vector_float3(float a,float b,float c)
        {
            x = a;
            y = b;
            z = c;
        }
    
    };
    struct matrix_float4x4
    {
        shared_ptr<vector_float4> columns[4];
        matrix_float4x4()
        {
            for(int i=0;i<4;i++)
            {
                columns[i] = shared_ptr<vector_float4>();
            }
        }
        matrix_float4x4(vector_float4 *col1,vector_float4 *col2,vector_float4 *col3, vector_float4 *col4)
        {
        
            columns[0] = shared_ptr<vector_float4>(col1);
            columns[1] = shared_ptr<vector_float4>(col2);
            columns[2] = shared_ptr<vector_float4>(col3);;
            columns[3] = shared_ptr<vector_float4>(col4);;
        
        }
    };
    struct Vertex
    {
        shared_ptr<vector_float4> position;
        shared_ptr<vector_float4> normal;
        shared_ptr<vector_float4> textCoords;
    };
    enum EventType
    {
        MOUSE_LEFT_DOWN,
        MOUSE_LEFT_UP,
        MOUSE_RIGHT_DOWN,
        MOUSE_RIGHT_UP,
        MOUSE_MOVE,
        KEY_PRESS,
        KEY_UP,
        RENDER_CONTENT,
        INVALID
    };
    enum ShaderProgram
    {
        COLOR_SHADER=0,
        TEXTURE_SHADER=1,
        LIGHTING_SHADER=2,
        AXIS_SHADER=3
    };
//GVis->Gaurav Visualization tool
    enum NodeType
    {
        GVis_PLANET,
    
        GVis_CUBE,
    
        GVis_RECT,
    
        GVis_GROUP,
        /*node that already is in mess form so we need not to generate mess for that node.such nodes are loaded from .obj,.stl,
         .asm data exchange files. mess means that vertices data is already available.*/
        GVis_MESS
        
    };
    enum KeyCode
    {
        FORWARD_KEY,
        BACKWARD_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        UNKNOWN_KEY
    };
    struct Event
    {
        float mouse_x,mouse_y;
        EventType type;
        KeyCode event_code;
        Event()
        {
            mouse_x = 0;
            mouse_x = 0;
            type = INVALID;
            event_code = UNKNOWN_KEY;
        }
    };
    
}
#endif /* DataType_h */
