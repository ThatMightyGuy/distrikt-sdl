set(SOURCES
    scene/game/scene.c
    scene/menu/scene.c
)

add_executable(${PROJECT_NAME} main.c ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
