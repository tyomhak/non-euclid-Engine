#include "Engine.h"

#include <string>

// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/geometric.hpp>


Engine::Engine() 
    : window()
    , player()
    , level(portalShader, objectShader)
    , objectShader("./data/shaders/Object_Vertex.shader", "", "./data/shaders/Object_Fragment.shader")
    , portalShader("./data/shaders/Portal_Vertex.shader", "", "./data/shaders/Portal_Fragment.shader")
    , eventHandler(&player, &level, window.GetWindow(), window.GetWidth() / 2, window.GetHeight() / 2, &objectShader, &portalShader)
    , ui(window.GetWindow(), &eventHandler)
{
    SetupWindow();
    window.SetIcon("./data/icons/Euclid.jpg");

    SetupShaders();
}

void Engine::Render()
{
    float previousTime = (float)glfwGetTime();
    int frameCount = 0;

    float lastFrameTime = previousTime;
    float deltaTime = 0.0f;


    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        // Frame Counter
        float currentTime = (float)glfwGetTime();
        if (currentTime - previousTime >= 1.0f)
        {
            std::cout << frameCount << std::endl;
            frameCount = 0;
            previousTime = currentTime;
        }
        ++frameCount;

        //TempTest();

        // Smooth Movement
        // ---------------
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        // input
        // -----
        eventHandler.HandleEvents(deltaTime);

        // render
        // -----
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        UpdateShaders();

        level.Draw(player.GetCamera());
        ui.Render();



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
    glfwTerminate();
}


void Engine::AddObject(std::string objectName, glm::vec3 location)
{
    level.AddObject(objectName, location);
}

void Engine::AddPortal(Portal first, Portal second)
{
    level.AddPortalPair(first, second);
}

void Engine::AddPortal(glm::mat4 locationFirst, 
    glm::mat4 locationSecond, 
    float yawFirst /* = -90.0f */, 
    float yawSecond /* = -90.0f */)
{
    Portal first = ObjectHandler::GetPortal(locationFirst);
    Portal second = ObjectHandler::GetPortal(locationSecond);

    first.yaw = yawFirst;
    second.yaw = yawSecond;

    level.AddPortalPair(first, second);
}

void Engine::MoveObject(glm::vec3 direction, std::string id)
{
    Object* objectToMove = FindObjectById(id);
    objectToMove->Move(direction);
}

void Engine::RotateObject(glm::vec3 direction, float angle, std::string id)
{
    Object* objectToMove = FindObjectById(id);
    objectToMove->Rotate(angle, direction);
}

bool Engine::CheckPlayerCollision(const std::string id)
{
    return CollisionHandler::CheckCollision(player, level.GetObjects().at(id));
}

bool Engine::CheckCubeCollision(const std::string id1, const std::string id2)
{
    // TODO: handle case when element was not found in the map by ID
    return CollisionHandler::CheckCollision(level.GetObjects().at(id1), level.GetObjects().at(id2));
}


// temporary function for testing stuff
// made with purpose to not clutter the render loop
// to be deleted later
void Engine::TempTest() 
{
    bool objects_collision = false;
    bool camera_collision = false;

    static glm::vec3 moveRight = glm::vec3(0.01f, 0.0f, 0.0f);
    static glm::vec3 moveLeft = glm::vec3(-0.01f, 0.0f, 0.0f);
    static glm::vec3 moveUp = glm::vec3(0.0f, 0.0075f, 0.0f);

    // objects collision check
    //objects_collision = check_cube_collision("cube1", "cube2");

    if (objects_collision == false)	// move objects only if they did not collide
    {
        //moveObject(moveRight, "cube1");
        //moveObject(moveLeft, "cube2");
        MoveObject(moveLeft, "cube2");
    }

    // camera collision check
    //camera_collision = check_player_collision("cube1");

    if (camera_collision == true)
    {

    }

    //if (objects_collision == false)
    //{
    //	moveObject(moveRight, "cube1");
    //	rotateObject(glm::vec3(0.1f, 0.0f, 0.1f), 0.01f, "cube1");
    //}

    // Collision check: camera with objects
    //std::cout << "cube1 : " << check_player_collision("cube1")
    //	<< "\tcube2 : "  << check_player_collision("cube2") << std::endl;

        // Collision check: object with object
        /*std::cout << "collision : " << objects_collision << std::endl;*/

}


Object* Engine::FindObjectById(std::string id)
{
    return &level.GetObjects().at(id);
}


void Engine::UpdateShaders()
{
    glm::mat4 view = player.GetCamera().GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.GetAspectRatio(), 0.1f, 100.0f);	//perspective view
    glm::mat4 model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    glm::mat4 mvp = projection* view* model;
    objectShader.Bind();
    objectShader.SetMat4("mvp", mvp);

    //objectShader.update();

    portalShader.Bind();
    portalShader.SetMat4("mvp", mvp);
    //portalShader.unbind();
}


void Engine::CheckSave()
{
    if (glfwGetKey(window.GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
    {
        SaveWorld();
    }
}

void Engine::SaveWorld()
{
    LevelHandler::WriteLevel("./Alternative", level, player.GetCamera());
}

void Engine::SetupShaders()
{
    glm::mat4 view = player.GetCamera().GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), window.GetAspectRatio(), 0.1f, 100.0f);		//perspective view
    glm::mat4 model = glm::mat4(1.0f);

    objectShader.SetView(view);
    objectShader.SetModel(model);
    objectShader.SetProjection(projection);

    portalShader.SetView(view);
    portalShader.SetModel(model);
    portalShader.SetProjection(projection);

}

void Engine::SetupWindow()
{
    glfwMakeContextCurrent(window.GetWindow());
    // resizing controls
    glfwSetFramebufferSizeCallback(window.GetWindow(), EventHandler::framebuffer_size_callback);
    
    // Mouse controls
    // --------------
    glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
}