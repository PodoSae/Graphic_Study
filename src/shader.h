#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader
{
public :
    static ShaderUPtr CreateFromFile(const std::string& filename , GLenum shaderType);

    ~Shader();
    uint32_t Get() const {return m_shader; }
private :
    Shader() {}
    bool LoadFile(const std::string& filename , GLenum shaderType); // return 값이 bool 인 이유 - 생성에 실패할 경우 false 를 리턴하기 위해서
    uint32_t m_shader { 0 };
};
// 생성자를 private으로 두고 클래스를 생성할 수 있는 방법을 CreateFromFile(static function)을 call 하는 것 이외에는 없게끔 만듬
// Class 생성 원직 
// Get O , Set X -> Shader 오브젝트의 생성 관리는 Shader 내부에서만 관리하게


#endif