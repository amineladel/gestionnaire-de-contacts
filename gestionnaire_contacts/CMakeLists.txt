cmake_minimum_required(VERSION 3.5)

project(gestionnaire_contacts VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    contact.cpp
    contactmodel.cpp
    database.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    contact.h
    contactmodel.h
    database.h
)

set(PROJECT_FORMS
    mainwindow.ui
)

qt6_wrap_ui(PROJECT_FORMS_HEADERS ${PROJECT_FORMS})
qt6_wrap_cpp(PROJECT_HEADERS_MOC ${PROJECT_HEADERS})

add_executable(gestionnaire_contacts
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS_HEADERS}
    ${PROJECT_HEADERS_MOC}
)

target_include_directories(gestionnaire_contacts PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(gestionnaire_contacts
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)
