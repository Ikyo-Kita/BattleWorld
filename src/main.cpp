#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"Resources/ResourceManager.h"
#include"Renderer/ShaderProgram.h"
#include"Renderer/Texture2D.h"
#include<glm/vec2.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

GLfloat point[] = {//Vector for vertex shader
    0.0f,50.f,0.0f,
    50.f,-50.f,0.0f,
    -50.f,-50.f,0.0f
};

GLfloat colors[] = {//Vector for fragment shader
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
};

GLfloat texCoord[] = {
    0.5f,1.0f,
    1.0f,0.0f,
    0.0f,0.0f
};

glm::ivec2 windowSize(640, 480);


void glfwWindowSizeCallback(GLFWwindow*pWindow,int width,int height)
{
    windowSize.x = width;
    windowSize.y = height;
    glViewport(0, 0, width, height);
}

/*Function for exit from programm if press key Escape*/
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}


int main(int argc,char**argv)
{
    
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit()) {

        std::cout << "glfw Error" << std::endl;
        system("pause");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(windowSize.x, windowSize.y, "BattleWorld", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow Error" << std::endl;

        glfwTerminate();
        system("pause");
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {//Showing load Error GLAB library 

        std::cout << "Can`t load GLAD!" << std::endl;
        system("pause");
        return -1;
    }
    std::cout << "Video Card " << glGetString(GL_RENDERER) << std::endl; ;//Showing a model video card
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;//Showing the version OpenGL and the video card driver version

    glClearColor(1, 1, 0, 1);

  
    {
        ResourceManager resourceManager(argv[0]);//Create Resource Manager
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        /*
        Load shaders with help Resource Manager
        */  
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can`t load shader program  ERROR: " << "DefaultShader" << std::endl;
            system("pause");
            return -1;
        }

        auto  tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");//Load the texture

        GLuint point_vbo = 0;
        glGenBuffers(1, &point_vbo);//Generation the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);//Ñontributing data about vertex shader in video card memory
        //=================================================================
        GLuint color_vbo = 0;
        glGenBuffers(1, &color_vbo);//Generation the colors buffer
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);//Ñontributing data about colors shader in video card memory
        //==================================================================
        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);//Generation the texCoord buffer
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW); 
        //====================================================================
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        //======================================================================
        glEnableVertexAttribArray(0); //bundle vertex the shader
        glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        //======================================================================
        glEnableVertexAttribArray(1);//bundle fragment the shader
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
         //=====================================================================
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 200.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 200.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>( windowSize.x), 0.f, static_cast<float>( windowSize.y), -100.f, 100.f);

        pDefaultShaderProgram->setmatrix4("projectionMat", projectionMatrix);


        /* Loop untilthe user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();//Using the shader program
            tex->bind();
           
            glBindVertexArray(vao);

            pDefaultShaderProgram->setmatrix4("modelMat",modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);//Drawn first triangle

            pDefaultShaderProgram->setmatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);//Drawn second triangle
            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}