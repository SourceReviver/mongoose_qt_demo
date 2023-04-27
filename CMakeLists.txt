cmake_minimum_required(VERSION 3.26)
project(mongoose_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(MONGOOSE_SRC mongoose/mongoose.c mongoose/mongoose.h)

add_executable(mongoose_qt
        main.cpp
        ${MONGOOSE_SRC}
        dictionary.cpp
        dictionary.h
        webserver.cpp
        webserver.h
        webserverController.cpp
        webserverController.h
        )

target_link_libraries(mongoose_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

target_compile_definitions(mongoose_qt PUBLIC  MG_ENABLE_LOG)