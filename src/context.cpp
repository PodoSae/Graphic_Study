#include "context.h"

ContextUPtr Context::Create()
{
    auto context= ContextUPtr(new Context());
    if (!context -> Init())
        return nullptr;
    
    return std::move(context);
}

bool Context::Init()
{
    // 사각형 예시
    // float vertices[] = {
    //     0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    // };

    float vertices[] ={
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    m_vertexLayout = VertexLayout::Create();
    // glGenVertexArrays(1, &m_vertexArrayObject);
    // glBindVertexArray(m_vertexArrayObject);

    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER,
        GL_STATIC_DRAW, vertices , sizeof(float)* 12);

    // 위의 줄로 리펙토링함
    // glGenBuffers(1, &m_vertexBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 12 , vertices, GL_STATIC_DRAW);

    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 , 0);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, sizeof(float)* 3, 0);

    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER,
        GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);

    // 위의 줄로 리펙토링함
    // glGenBuffers(1, &m_indexBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6,
    //     indices, GL_STATIC_DRAW);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    
    if (!vertShader || !fragShader)
        return false;

    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if (!m_program)
        return false;

    SPDLOG_INFO("program id: {}" , m_program ->Get());

    glClearColor(0.0f , 0.1f, 0.2f, 0.0f);

    // uint32_t vao = 0;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    return true;
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //glUseProgram(m_program->Get());
    m_program->Use();

    // glDrawArrays(GL_TRIANGLES, 0 , 6); // GL_POINTS <- 점
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT , 0);
}