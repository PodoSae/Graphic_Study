#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>     // c++ 17 부터 사용 가능 . 값이 있거나 없는 경우 포인터 없이 표현 가능 (포인터 지양을 위해)
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// 매크로 define 에서 \ 를 사용하여 아래 줄도 define 에 포함시킨다
// ## 은 klassName 부분과 그 뒷부분을 붙혀주는 문자이다
#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

// ex) CLASS_PTR(Shader) << 예시처럼 타이핑 하면 아래의 내용이 따라온다고 생각하면 된다
// class Shader;
// using ShaderUPtr = std::unique_ptr<klassName>; 
// using ShaderPtr = std::shared_ptr<klassName>; 
// using ShaderWPtr = std::weak_ptr<klassName>;

std::optional <std::string> LoadTextFile(const std::string& filename);

#endif


// ifndef A - A 가 define 되어 있지 않으면 아래의 define 을 통해서 define
//            A 가 define 되어 있다면 내부 내용을 건너뜀 
//            A 는 고유 값으로 중복하지 않게 만든다
// define
// endif