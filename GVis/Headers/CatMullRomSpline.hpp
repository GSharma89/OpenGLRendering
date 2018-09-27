//
//  CatMullRomSpline.hpp
//  OpenGLRenderingEngine
//
//  Created by Gaurav Sharma on 10/08/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//
#ifndef CatMullRomSpline_hpp
#define CatMullRomSpline_hpp
#include <vector>
#include <cmath>
using namespace std;
struct Point
{
    float x;
    float y;
    float z;
    float  w;
    Point()
    {
        x=0;
        y=0;
        z=0;
        w=1;
    }

};
class CatMullRomSpline
{
    
 public:
    
    int generateGeometry(vector<Point*> &control_point_list,string &texture_file_path,float geom_width);
    void interpolateCubicRomSpline(Point* p0,Point* p1,Point* p2,Point* p3,vector<Point*> & new_points);
    void generatePointsOfCatmullRomSpline(vector<Point*> &control_point_list,vector<Point*> &new_points);
    static void setProjectionMatrix(float fovy_in_angle,float frustum_width,float frustum_height,float near,float far);
    static void initializeMatrices();
    
};
#endif /* CatMullRomSpline_hpp */
