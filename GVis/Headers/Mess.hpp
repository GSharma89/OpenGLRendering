//
//  Mess.hpp
//  GVis
//
//  Created by Gaurav Sharma on 13/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Mess_hpp
#define Mess_hpp

#include <iostream>
#include "Node.hpp"
#include "DataType.hpp"
#include <vector>
using namespace GVis;
class Mess:public Node
{
    vector<shared_ptr<Vertex>> vertices;
    vector<uint>  indices;
};

#endif /* Mess_hpp */
