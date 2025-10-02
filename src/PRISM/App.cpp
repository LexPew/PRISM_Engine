#include <PRISM/App.h>
#include <PRISM/Utils/FLoader.h>
#include <PRISM/Shader.h>
#include <fmt/core.h>
#include <tinyObjLoader/tiny_obj_loader.h>

void ResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool App::Run()
{
    // Setup GLFW
    if (!InitializeGLFW())
    {
        Cleanup();
        return false;
    }
    // Try load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fmt::println("Failed to load GLAD");
        Cleanup();
        return false;
    }

    // If all goes well start the loop
    Loop();
    return true;
}

bool App::InitializeGLFW()
{
    // Try init GLFW
    if (!glfwInit())
    {
        fmt::println("Error: GLFW failed to initialize");
        return false;
    }

    // Apply window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    window = glfwCreateWindow(680, 480, "P.R.I.S.M", NULL, NULL);

    if (!window)
    {
        fmt::println("Error: Failed to create window");
        return false;
    }

    // Set current context to window
    glfwMakeContextCurrent(window);

    // Set Resize
    glfwSetWindowSizeCallback(window, ResizeCallback);
    return true;
}

void App::Cleanup()
{
    glfwTerminate();
}

void App::Loop()
{

    // Create Default Shaders
    Shader defaultShader(FLoader::LoadFile("shaders/default.vert"),
                         FLoader::LoadFile("shaders/default.frag"));
    // Initialize It
    defaultShader.Initialize();


    //---Triangle Drawing---
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //---End---

    // defaultShader.Initialize();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        defaultShader.Enable();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }
}
