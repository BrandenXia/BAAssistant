cmake_minimum_required(VERSION 3.29)
project(BAAssistant)

enable_language(OBJCXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_OBJCXX_STANDARD 23)

set(CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer"
)
set(CMAKE_OBJCXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_OBJCXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.mm")
add_executable(BAAssistant ${SOURCES})

find_package(spdlog CONFIG REQUIRED)
include_directories(${spdlog_INCLUDE_DIRS})
if (spdlog_FOUND)
    target_link_libraries(BAAssistant PRIVATE spdlog::spdlog)
endif ()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
if (OpenCV_FOUND)
    target_link_libraries(BAAssistant PRIVATE ${OpenCV_LIBS})
endif ()

find_package(tesseract CONFIG REQUIRED)
include_directories(${tesseract_INCLUDE_DIRS})
if (tesseract_FOUND)
    target_link_libraries(BAAssistant PRIVATE ${tesseract_LIBRARIES})
endif ()

target_link_libraries(BAAssistant
        PRIVATE
        "-framework Foundation"
        "-framework CoreGraphics"
        "-framework ScreenCaptureKit"
)

target_compile_definitions(BAAssistant
        PRIVATE $<$<CONFIG:Debug>:DEBUG>
)
