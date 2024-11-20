cmake_minimum_required(VERSION 3.29)
project(BAAssistant)

set(CMAKE_CXX_STANDARD 20)
enable_language(OBJCXX)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.mm")
add_executable(BAAssistant ${SOURCES})

find_package(spdlog CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

target_link_libraries(BAAssistant
        PRIVATE spdlog::spdlog
        PRIVATE ${OpenCV_LIBS}

        "-framework Foundation"
        "-framework CoreGraphics"
        "-framework ScreenCaptureKit"
)
target_compile_definitions(BAAssistant
        PRIVATE $<$<CONFIG:Debug>:DEBUG>
)

set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer"
)
set(CMAKE_OBJCXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_OBJCXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
