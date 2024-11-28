#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename){
    std::ifstream fin(filename);
    if(!fin.is_open())
    {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {};      // optional 타입에서 return 값을 경우 return{} 을 써주면 아무것도 없는 값을 리턴한다.
    }

    //파일을 열었을때
    std::stringstream text; 
    text << fin.rdbuf();    //stringstream 타입에 file을 전부 넣은 후
    return text.str();      //str function 을 이용해 내용을 전부 string으로 변경 하고 리턴될때 자동으로 optional 타입으로 감싸져서 리턴함
}