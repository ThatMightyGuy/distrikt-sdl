set(ENGINE_SOURCES
    src/engine.c
    src/input.c
    src/scene.c
)

add_library(engine SHARED ${ENGINE_SOURCES})

target_include_directories(engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
)

target_link_libraries(engine PUBLIC vendor)