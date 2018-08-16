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
    float geom_width=0;
    cout<<"\nEnter Path of the Texture Image:";
    string str;
    getline(cin, str);
    vector<Point*> control_point_list;
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
    cin>>geom_width;
    CatMullRomSpline cat_mull_rom_spline;
    cat_mull_rom_spline.generateGeometry(control_point_list, str, geom_width);
    for (int i=0; i<n; i++)
    {
        
        delete control_point_list.at(i);
    }
    
    return 0;
}
