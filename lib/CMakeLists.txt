cmake_minimum_required(VERSION 3.20)

project(atunnel LANGUAGES C)

find_package(OpenSSL REQUIRED)

set(LIB_SOURCES
    atunnel.c include/atunnel.h
    connections.c connections.h
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)


add_library(atunnel::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include DESTINATION include COMPONENT Devel)

