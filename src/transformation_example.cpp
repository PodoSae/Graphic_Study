#include "context.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h>
//glfw 이전에 glad 를 추가해야함

#include <GLFW/glfw3.h>

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height)
{
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    auto context = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
    // glViewport(0, 0, width, height); //OpenGL이 그림을 그릴 화면의 위치및 크기 설정 - State Setting Function
    
    context->Reshape(width, height);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action , int mods){
    SPDLOG_INFO("key: {}, scancode: {}, action:{}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" : 
        action == GLFW_RELEASE ? "Release" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown" , 
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

}

int main(int argc, const char** argv)
{
    SPDLOG_INFO("Start Program");

    SPDLOG_INFO("");
    if (!glfwInit())
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
        nullptr, nullptr);
    
    if (!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //glad 를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();

        return -1;
    }

    //이후 OpenGL 사용가능

    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGl context version: {}", reinterpret_cast<const char*>(glVersion));

    auto context = Context::Create();
    if (!context)
    {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;

    }

    

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs" , GL_FRAGMENT_SHADER);
    SPDLOG_INFO("vertex shader id: {}" , vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}" , fragShader->Get());

    auto program = Program::Create({fragShader, vertShader});
    SPDLOG_INFO("program id: {}" , program ->Get());

    glfwSetWindowUserPointer(window, context.get());

    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window , OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.1f, 0.2f, 0.0f);   // 컬러 프레임 버퍼 화면을 클리어 할 색상 지정 - State Setting Function

        context->ProcessInput(window);
        context -> Render();
        // -> Render 내부에 있는 내용     //glClear(GL_COLOR_BUFFER_BIT);           // 프레임 버퍼 클리어 - State Using Function
        glfwSwapBuffers(window);
    }
    //context 가 가지고 있던 메모리 할당 해제 
    // context = nullptr; <- 로 대체 가능
    context.reset();



    glfwTerminate();
    return 0;
}
