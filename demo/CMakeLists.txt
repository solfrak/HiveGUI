include(FetchContent)

FetchContent_Declare(
        raylib  # A name you choose for the dependency
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
)

FetchContent_MakeAvailable(raylib)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE raylib HiveGUI)
target_include_directories(demo PRIVATE ../include)
