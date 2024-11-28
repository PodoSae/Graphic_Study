cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Graphic_Study)
set(CMAKE_CXX_STANDARD 17)

set(STUDY_FILE_NAME first_example.cpp)

set(WINDOW_NAME ${STUDY_FILE_NAME})
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)



#최초 - main.cpp
#첫번째 예시 - first_example.cpp


project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} src/${STUDY_FILE_NAME})

include(Dependency.cmake)

target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

add_dependencies(${PROJECT_NAME} ${DEP_LIST})