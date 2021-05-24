#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image/stb_image.h>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "ObjHandler.h"
#include "Level.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

// logs
int success;
char infoLog[512];

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// Camera system
Camera myCamera;
LevelHandler levelHandler;
ObjectHandler objectHandler;
Level *activeLevel;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

float deltaTime = 0.0f;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Mouse controls
    // --------------
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // flip textures on y-axis
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW); 

    // Create our shader program
    // -----------------------------------------
    Shader objectShader("./data/shaders/object.vert", "./data/shaders/object.frag");
    Shader portalShader("./data/shaders/portal.vert", "./data/shaders/portal.frag");

    std::cout << &objectShader << " : " << &portalShader << std::endl;
    std::cout << "Oxxxxxasdbjsd " << std::endl;

     //Shader portalShader = objectShader;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(objectShader.ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(objectShader.ID, "view");
    unsigned int projectionLoc  = glGetUniformLocation(objectShader.ID, "projection");

    GLuint projectionPortal = glGetUniformLocation(portalShader.ID, "projection");
    glUniformMatrix4fv(projectionPortal, 1, GL_FALSE, &projection[0][0]);

    Level myLevel = Level(portalShader, objectShader);

    glm::mat4 location(1.0f);
    location = glm::translate(location, glm::vec3(0.0f, 0.0f, 0.0f));
    myLevel.AddObject(objectHandler.GetObject("backpack", location));
    
    Portal first = objectHandler.GetPortal();
    Portal second = objectHandler.GetPortal();

    first.Move(glm::vec3(-10.0f, 0.0f, 0.0f));
    second.Move(glm::vec3(10.0f, 0.0f, 10.0f));

    first.RotateHoriz(90.0f);
    second.SetYaw(-90.0f);

    myLevel.AddPortalPair(first, second);
    
    float previousTime = glfwGetTime();
    int frameCount = 0;

    float lastFrameTime = previousTime;


    activeLevel = &myLevel;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Frame Counter
        float currentTime = glfwGetTime();
        if (currentTime - previousTime >= 1.0f)
        {
            // std::cout << frameCount << std::endl;
            frameCount = 0;
            previousTime = currentTime;
        }
        ++frameCount;

        // Smooth Movement
        // ---------------
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;


        // input
        // -----
        processInput(window);

        // render
        // -----
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objectShader.use();
        
        view = myCamera.GetView();


        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

        // myModel.Draw(objectShader);
        // backPack_01.Draw(objectShader);
        // backPack_02.Draw(objectShader);
        myLevel.Draw(myCamera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            deltaTime *= 2.0f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            myCamera.Walk(myCamera.GetCameraSpeed() * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
           myCamera.WalkBack(myCamera.GetCameraSpeed() * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            myCamera.StrafeLeft(myCamera.GetCameraSpeed() * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            myCamera.StrafeRight(myCamera.GetCameraSpeed() * deltaTime);

        // switch polygon mode to LINE
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        // switch polygon mode to FILL
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            LevelHandler tempLevHan;
            tempLevHan.WriteLevel("./Alternative", *activeLevel, myCamera);
        }
            
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    myCamera.MoveMouse(xoffset, yoffset);
}