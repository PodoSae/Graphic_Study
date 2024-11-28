#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>     // c++ 17 부터 사용 가능 . 값이 있거나 없는 경우 포인터 없이 표현 가능 (포인터 지양을 위해)
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

std::optional <std::string> LoadTextFile(const std::string& filename);

#endif


// ifndef A - A 가 define 되어 있지 않으면 아래의 define 을 통해서 define
//            A 가 define 되어 있다면 내부 내용을 건너뜀 
//            A 는 고유 값으로 중복하지 않게 만든다
// define
// endif