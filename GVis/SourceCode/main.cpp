//
//  main.cpp
//  OpenGLRenderingEngine
//
//  Created by Gaurav Sharma on 10/08/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//


#include "CatMullRomSpline.hpp"
#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    
    size_t n=0;
    float x=0,y=0;
    float geom_width=5;
    string str="";
     vector<Point*> control_point_list;
    /*cout<<"\nEnter Path of the Texture Image:";
    
    getline(cin, str);
   
    cout<<"\nEnter Number of Control Points:";
    cin>>n;
    cout<<"\nEnter Control Point in x y format:";
    for(int i=0;i<n;i++)
    {
        cout<<"\nControl Point "<<(i+1)<<":";
        cin>>x>>y;
        Point *p = new Point;
        p->x = x;
        p->y = y;
        control_point_list.push_back(p);
    }
    cout<<"\nEnter width of Geometry you want to create along CatMullRomSpline:";
    cin>>geom_width;*/
    Point *p1 = new Point;
    p1->x = 1;
    p1->y = 1;
    
    Point *p2 = new Point;
    p2->x = 200;
    p2->y = 200;
    
    Point *p3 = new Point;
    p3->x = 14;
    p3->y = 13;
    
    Point *p4 = new Point;
    p4->x = 25;
    p4->y = 11;
    
    control_point_list.push_back(p1);
    control_point_list.push_back(p2);
    control_point_list.push_back(p3);
    control_point_list.push_back(p4);
    CatMullRomSpline cat_mull_rom_spline;
    cat_mull_rom_spline.generateGeometry(control_point_list, str, geom_width);
    for (int i=0; i<n; i++)
    {
        
        delete control_point_list.at(i);
    }
    
    return 0;
}
