//
//  Utils.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include "DataType.hpp"
using namespace GVis;
class Utils
{
    public:
        shared_ptr<vector_float3> crossProduct(shared_ptr<vector_float3> a,shared_ptr<vector_float3> b);
        shared_ptr<vector_float3> normalize(shared_ptr<vector_float3>);
    
};

#endif /* Utils_hpp */
