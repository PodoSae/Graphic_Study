#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType)
{
    auto shader = std::unique_ptr<Shader> (new Shader());

    if (!shader -> LoadFile(filename, shaderType))
    {
        return nullptr;
    }
    return std::move(shader);
}

Shader::~Shader()
{
    if(m_shader)
    {
        glDeleteShader(m_shader); // 쉐이더가 소멸할 때 m_shader 정수 값이 들어가 있다면 OpenGL 오브젝트가 만들어져 있는 것. -> 따라서 제거를 위한 함수
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType)
{
    auto result = LoadTextFile(filename);
    if (!result.has_value())
        return false;

    auto& code = result.value(); 
    //std::string code = result.value();
    //std::string& code = result.value();
    //std::string* code = &result.value();
    //result 안에 있는 string 이 길 경우에 위에 이미 result 가 메모리 할당이 되어 있으니 해당 함수 끝나기 전까지 새로 메모리 할당 할 필요가 없다
    // 따라서 주소값 만 가지고 있는것 이 메모리를 아낄 수 있음

    const char* codePtr = code.c_str(); //c_str() => const string 의 ptr 를 받아올 수 있음
    int32_t codeLength = (int32_t) code.length();

    // 비트수가 명시적으로 표현 되어있는 타입을 사용하는 것이 좋다
    // uint8_t = unsigned char
    // int8_t = char

    // uint16_t = unsigned short
    // int16_t = short

    // uint32_t = unsigned int
    // int32_t = int

    // uint64_t = unsigned long long
    // int64_t = long long


    m_shader = glCreateShader(shaderType); //glCreateShader -> 쉐이터 생성  / return int (핸들 번호)
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); // 쉐이더에 로딩한 코드를 넣는 것
    glCompileShader(m_shader); //세팅 되어 있는 것들을 컴파일함

    int success = 0;
    glGetShaderiv(m_shader , GL_COMPILE_STATUS, &success); 
    // 쉐이더에 있는 정보를 얻어오는 함수
    // GL_COMPILE_STATUS -> 컴파일 상태가 성공 실패 인지를 얻어오기 위한 플래그
    // iv -> integer vector(pointer) 정수형 포인터를 인자로 넣어라

    if (!success)
    {
        char infoLog[1024]; //버퍼
        glGetShaderInfoLog(m_shader, 1024, nullptr , infoLog); //에러의 내용을 infoLog 안에 받는다
        SPDLOG_ERROR("failed to complie shader: \"{}\"", filename);
        SPDLOG_ERROR("reason : {}" , infoLog);
        return false;
    }
    return true;
}