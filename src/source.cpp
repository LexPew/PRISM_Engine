#include <fmt/core.h>

//Include GLAD first
#include <glad/glad.h>

#include <glm/vec3.hpp>
#include  <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;

    //Initialize the library
    if(!glfwInit()){
        return -1;
    }
    //Apply Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a windowed mode window 
    window = glfwCreateWindow(600,400, "Hello World", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    while(!glfwWindowShouldClose(window)){
        //Render
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}