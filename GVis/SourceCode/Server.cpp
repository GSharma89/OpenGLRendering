//
//  Server.cpp
//  GVis
//
//  Created by Gaurav Sharma on 19/09/18.
//  Copyright © 2018 Gaurav Sharma. All rights reserved.
//
//this class is main class and will be responsible to do general tasks like event routing,third party libraries initialization,window creation
//giving content root handle to the application and so mainly app and other objects will talk to server for everything and then server will decide what to do.
#include "Server.hpp"
Server::Server(float width,float height)
{
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    if(!glfwInit())
    {
        cout<<"glfw library failed to be initialized";
        return;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    window = glfwCreateWindow(width, height, "GVisWindow", NULL, NULL);
    
    if(!window)
    {
        cout<<"window creation is failed\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    content_node_tree = nullptr;
    camera = shared_ptr<Camera>();
    previous_event_type = INVALID;
    renderer = unique_ptr<Renderer>();
    
}
/*this is the function which will be called in infinite loop untill window closes*/
void Server::processEvent(shared_ptr<GVis::Event> event)
{
    content_node_tree->handleEvent(event);
    if(previous_event_type==MOUSE_LEFT_DOWN && event->type==MOUSE_MOVE)
    {
        camera->updateOnMouseDownEvent(event->mouse_x, event->mouse_y);
    }
    else if(event->type==KEY_PRESS)
    {
        switch (event->event_code) {
            case GVis::LEFT_KEY:
                camera->updateOnLeftKeyPress();
                break;
            case GVis::RIGHT_KEY:
                camera->updateOnRightKeyPress();
                break;
            case GVis::FORWARD_KEY:
                camera->updateOnForwardKeyPress();
                break;
            case GVis::BACKWARD_KEY:
                camera->updateOnBackwardKeyPress();
                break;
            default:
                cout<<"Unknown key is pressed";
                break;
        }
    }
    else if(event->type==RENDER_CONTENT)
    {
        renderer->render(camera, content_node_tree);
        glfwSwapBuffers(window);
    }
    
}
shared_ptr<Node> Server::createRootNode()
{
    if(content_node_tree==nullptr)
    {
        content_node_tree = shared_ptr<Node>();
    }
    return content_node_tree;
}
shared_ptr<Camera> Server::getCamera()
{
    return camera;
}
Server::~Server()
{
    glfwTerminate();
}
