#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>


#include"Renderer/ShaderProgram.h"


GLfloat point[] = {//Vector for vertex shader
    0.0f,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f
};

GLfloat colors[] = {//Vector for fragment shader
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
};

const char* vertex_shader =//Vertex shader
"#version 460\n"
"layout(location=0) in vec3 vertex_pos;"
"layout(location=1) in vec3 vertex_col;"
"out vec3 color;"
"void main(){"
"   color=vertex_col;"
"   gl_Position=vec4(vertex_pos,1.0);"
"}";
const char* fragment_shader =//Fragment shader
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"   frag_color=vec4(color,1.0);"
"}";


int windowSizeX = 640;
int windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow*pWindow,int width,int height)
{
    windowSizeX = width;
    windowSizeY = height;
    glViewport(0, 0, windowSizeX, windowSizeY);
}

/*Function for exit from programm if press key Escape*/
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}


int main(void)
{

    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit()) {

        std::cout << "glfw Error" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(windowSizeX, windowSizeY, "BattleWorld", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow Error" << std::endl;
        glfwTerminate();
        return -1;
    }



    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);



    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {//Showing load Error GLAB library 

        std::cout << "Can`t load GLAD!" << std::endl;
        return -1;
    }
    std::cout << "Video Card " << glGetString(GL_RENDERER) << std::endl; ;//Showing a model video card
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;//Showing the version OpenGL

    glClearColor(1, 1, 0, 1);


    std::string vertexShader(vertex_shader);
    std::string fragmentShader(fragment_shader);
    Renderer::ShaderProgram shaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram.isCompiled())
    {
        std::cerr << "Can`t create shader program!" << std::endl;
        return -1;
    }
    

    GLuint point_vbo = 0;
    glGenBuffers(1, &point_vbo);//Generation the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);//Ñontributing data about vertex shader in video card memory

    GLuint color_vbo = 0;
    glGenBuffers(1, &color_vbo);//Generation the colors buffer
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);//Ñontributing data about colors shader in video card memory

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0); //bundle vertex the shader
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);//bundle fragment the shader
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);//Drawn from the shaders


        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}