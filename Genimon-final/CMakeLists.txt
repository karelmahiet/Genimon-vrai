cmake_minimum_required(VERSION 3.16)

project(GenimonV2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        controle.cpp
        controle.h
        controle.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GenimonV2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        capture.h capture.cpp capture.ui
        choixjoueur.h choixjoueur.cpp choixjoueur.ui
        combat.h combat.cpp combat.ui
        commande.h commande.cpp commande.ui
        genidex.h genidex.cpp genidex.ui
        genimon.h genimon.cpp
        GenimonFinal.h GenimonFinal.cpp
        historencontre.h historencontre.cpp historencontre.ui
        json.hpp
        SerialPort.hpp
        unistd.h unistd.cpp
        map.h map.cpp map.ui
        regle.h regle.cpp regle.ui
        pause.h pause.cpp pause.ui
        mainmenu.h mainmenu.cpp mainmenu.ui
        Image.qrc
        Genimonfinal.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GenimonV2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GenimonV2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GenimonV2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GenimonV2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GenimonV2)
endif()
set_target_properties(GenimonV2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GenimonV2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GenimonV2)
endif()
