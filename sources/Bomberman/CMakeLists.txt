add_executable(${PROJECT_NAME}-Bomberman
        Bomberman.cpp)

add_subdirectory(Game)
target_include_directories(${PROJECT_NAME}-Bomberman PRIVATE Game)

add_subdirectory(ECS)
target_include_directories(${PROJECT_NAME}-Bomberman PRIVATE ECS)

add_subdirectory(RaylibWrapper)
target_include_directories(${PROJECT_NAME}-Bomberman PRIVATE RaylibWrapper)

add_subdirectory(Utils)
target_include_directories(${PROJECT_NAME}-Bomberman PRIVATE Utils)

FILE(COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(raylib 3.7.0 QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()

target_link_libraries(${PROJECT_NAME}-Bomberman raylib)