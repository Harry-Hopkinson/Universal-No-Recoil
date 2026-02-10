cmake_minimum_required(VERSION 3.20)
project(UniversalNoRecoil LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Gather all source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(RESOURCE_FILES src/resource/resource.rc)

include_directories(${CMAKE_SOURCE_DIR})

# Enable Link-Time Optimization (LTO)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# Windows GUI executable
add_executable(UniversalNoRecoil WIN32 ${SRC_FILES} ${RESOURCE_FILES})

target_compile_definitions(UniversalNoRecoil PRIVATE
    WIN32_LEAN_AND_MEAN
    NOCOMM
    NOSERVICE
    NOHELP
)

# Copy assets
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(UniversalNoRecoil PRIVATE xinput)
target_link_libraries(UniversalNoRecoil PRIVATE msimg32)

if(MINGW)
    target_compile_options(UniversalNoRecoil PRIVATE
        -O2
        -Wall
        -Wextra

        -Wpedantic
        -Wshadow
        -Wunused
        -Wunused-variable
        -Wunused-function
        -Wunused-parameter
        -Wunused-but-set-variable
        -Wunused-result

        -Wno-missing-field-initializers
        -fno-exceptions
        -fno-rtti
        -ffunction-sections
        -fdata-sections
        -fstack-protector-strong
    )

    target_link_options(UniversalNoRecoil PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
        -Wl,--gc-sections
        -s
        -mwindows
        -Wl,--nxcompat
        -Wl,--dynamicbase
    )

elseif(MSVC)
    # Suppress CRT warnings
    target_compile_definitions(UniversalNoRecoil PRIVATE _CRT_SECURE_NO_WARNINGS _AMD64_=1 _M_X64=100)

    foreach(flag_var
        CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS_DEBUG   CMAKE_CXX_FLAGS_DEBUG)
        string(REPLACE "/MD" "/MD" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
    endforeach()

    # Compile options for MSVC
    target_compile_options(UniversalNoRecoil PRIVATE
        $<$<CONFIG:Release>:/W4 /Os /GL /Gy /Zc:inline /Zc:preprocessor /utf-8 /GS /MD>
        $<$<CONFIG:Debug>:/W3 /Od /Zi /utf-8 /MDd>
    )

    # Link options for MSVC
    target_link_options(UniversalNoRecoil PRIVATE
        $<$<CONFIG:Release>:/LTCG /INCREMENTAL:NO /OPT:REF /OPT:ICF /DYNAMICBASE /NXCOMPAT /SUBSYSTEM:WINDOWS>
        $<$<CONFIG:Debug>:/INCREMENTAL /SUBSYSTEM:WINDOWS>
    )
endif()

add_custom_command(TARGET UniversalNoRecoil POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

foreach(FILE Config.toml)
    add_custom_command(TARGET UniversalNoRecoil POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/data/${FILE}
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${FILE}
    )
endforeach()

message(STATUS "========================================")
message(STATUS "Project: Universal-No-Recoil")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "========================================")
