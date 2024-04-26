cmake_minimum_required(VERSION 3.6)
project(PacMan)

add_subdirectory(Amugen)
#add_dependencies(Amugen)

set(TARGET_NAME PacMan)
set(GAME_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GameFiles)

# list source files here
set(PAC_MAN_SOURCE_FILES
  "${GAME_FILES_DIR}/GameLoad.h"    
  "${GAME_FILES_DIR}/Main.cpp"    
  "${GAME_FILES_DIR}/Components/FPSComponent.cpp"    
  "${GAME_FILES_DIR}/Components/HealthComponent.cpp" 
  "${GAME_FILES_DIR}/Components/DisplayComponent.cpp"
  "${GAME_FILES_DIR}/Components/ScoreComponent.cpp"  
)

add_executable(${TARGET_NAME} ${PAC_MAN_SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC
    ${GAME_FILES_DIR}
	)

# enable c++20 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
# set minigin as the default startup project
if(WIN32)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
endif()

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

set_property(TARGET ${TARGET_NAME} PROPERTY
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)

target_link_libraries(${TARGET_NAME} PRIVATE Amugen)