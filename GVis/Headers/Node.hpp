//
//  Node.hpp
//  GVis
//
//  Created by Gaurav Sharma on 06/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include "DataType.hpp"
#include <string>
#include <vector>
using namespace GVis;
class Node
{
    protected:
        string id;
        matrix_float4x4 model_transform;
        NodeType type;
        vector<shared_ptr<Node>> children;
        shared_ptr<Node> parent;
    
    public:
        virtual shared_ptr<Node> addNode(NodeType);
        void handleEvent(shared_ptr<Event> event);
        void addEventListener();
        NodeType getType() const;
        shared_ptr<Node> getParent() const;
    
};

#endif /* Node_hpp */
