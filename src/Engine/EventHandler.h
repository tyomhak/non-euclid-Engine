#pragma once


//#include "Camera.h"
//#include "IncludeHeaders.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "Level.h"
#include "Portal.h"

// Before Using Set the camera and the lastX lastY position of the mouse!
class EventHandler {
public:
    EventHandler()
    {}

    EventHandler(Player* player_, Level * level_,  GLFWwindow* window_, float lastX, float lastY, Shader *objShader, Shader *portShader) :
        player(player_), 
        window(window_),
        level(level_),
        lastMouseX(lastX), 
        lastMouseY(lastY),
        cursorEnabled(false),
        creativeEnabled(false),
        objectShader(objShader),
        portalShader(portShader)
    {}


    void HandleEvents(float deltaTime);

    void MoveSelectedObjectToPosition(glm::vec3 position);

    void MoveCreateObjectToPosition(glm::vec3 position);


    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void SaveObject();

    void SelectObject();

    void DeleteObject();

    // add the object into the level and return the id of created object
    string AddObject(string name, glm::vec3 Position);

    void AddPortals();

private:

    void ProcessInput(float deltaTime);

    bool CheckObjectCollision(Object obj) const;

    bool CheckMovement(Player dummy_player);

    void MouseCallback();

    void CastRay();

public:
    float lastMouseX;
    float lastMouseY;
    GLFWwindow* window;
    Level * level;
    Player* player;
    
    const float minDistance = 2.0f;
    float distance = 5.0f;
    float rotation_degree = 0.01f;


    bool isPassing;
    bool cursorEnabled;
    bool creativeEnabled;
    
    static string underViewObjectId;
    static string updateObjectId;

    Shader *objectShader;
    Shader *portalShader;

    bool isPortalVisible = true;
};


