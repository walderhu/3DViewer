cmake_minimum_required(VERSION 3.5)

project(3DViever VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/Qt/6.7.2/gcc_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        glwid.h
        glwid.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViever
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        parser.c
        affine.c
        3DViever.h
        ./QtGifImage/src/3rdParty/giflib/gif_err.c
        ./QtGifImage/src/3rdParty/giflib/dgif_lib.c
        ./QtGifImage/src/3rdParty/giflib/egif_lib.c
        ./QtGifImage/src/3rdParty/giflib/gif_hash.c
        ./QtGifImage/src/3rdParty/giflib/gifalloc.c
        ./QtGifImage/src/3rdParty/giflib/quantize.c
        ./QtGifImage/src/gifimage/qgifimage.cpp
        ./QtGifImage/src/gifimage/qgifimage.h

    )
else()
    if(ANDROID)
        add_library(3DViever SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(3DViever
            ${PROJECT_SOURCES}
        )
    endif()
endif()


# TODO флажки надо включить, но либа ругается
# target_compile_options(3DViever PRIVATE
#     $<$<COMPILE_LANGUAGE:C>:-Wall>
#     $<$<COMPILE_LANGUAGE:C>:-Werror>
#     $<$<COMPILE_LANGUAGE:C>:-Wextra>
#     $<$<COMPILE_LANGUAGE:C>:-std=c11>
# )


target_link_libraries(3DViever PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViever PRIVATE Qt6::OpenGL)
target_link_libraries(3DViever PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(3DViever PRIVATE Qt6::Gui)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.3DViever)
endif()
set_target_properties(3DViever PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 3DViever
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViever)
endif()
