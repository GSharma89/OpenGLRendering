//
//  Server.hpp
//  GVis
//
//  Created by Gaurav Sharma on 19/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "DataType.hpp"
#include "Node.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
class Server
{
    EventType previous_event_type;
    shared_ptr<Node> content_node_tree;//to update tree when server gets any event from OS
    GLFWwindow *window;//on which server will recieve events
    shared_ptr<Camera> camera;//update camera when event is captured on window.
    unique_ptr<Renderer> renderer;
    public:
        void processEvent(shared_ptr<GVis::Event> event);
        shared_ptr<Node> createRootNode();
        shared_ptr<Camera> getCamera();
        Server(float width,float height);
        ~Server();
    
};
#endif /* Server_hpp */
