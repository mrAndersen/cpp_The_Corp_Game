cmake_minimum_required(VERSION 3.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(the_corp_game)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")


set(SFML_ROOT "${PROJECT_SOURCE_DIR}/vendor/mingw_sfml-2.4.2")
#set(SFML_ROOT "${PROJECT_SOURCE_DIR}/vendor/sfml-2.4.2-windows")
set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/vendor/mingw_sfml-2.4.2/include")
#set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/vendor/sfml-2.4.2-windows/include")

include_directories("${PROJECT_SOURCE_DIR}/src")

file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}")

# Set version information in a config.h file
set(the_corp_game_VERSION_MAJOR 1)
set(the_corp_game_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "corpgame")
add_executable(
        ${EXECUTABLE_NAME}

        WIN32

        main.cpp
        main.rc

        src/System/EntityContainer.h
        src/System/EntityContainer.cpp

        src/Basic/Entity.h
        src/Basic/Entity.cpp

        src/Characters/Clerk.h
        src/Characters/Clerk.cpp

        src/Basic/Movable.h
        src/Basic/Movable.cpp

        src/System/Enum.h

        src/System/ResourceLoader.h
        src/System/ResourceLoader.cpp

        src/System/ViewHandler.h
        src/System/ViewHandler.cpp

        src/System/System.h
        src/System/System.cpp

        src/Background/Ground.h
        src/Background/Ground.cpp

        src/System/ControlPanel.h
        src/System/ControlPanel.cpp

        src/Ui/ControlButtonAddClerk.h
        src/Ui/ControlButtonAddClerk.cpp

        src/Ui/ControlButtonAddOffice.h
        src/Ui/ControlButtonAddOffice.cpp

        src/Office/OfficeClerk.h
        src/Office/OfficeClerk.cpp

        src/System/SaveManager.h
        src/System/SaveManager.cpp

        src/Office/Office.h
        src/Office/Office.cpp
        src/System/GameTime.cpp
        src/System/GameTime.h

        src/Objects/ElevatorShaftMiddle.cpp
        src/Objects/ElevatorShaftMiddle.h

        src/Text/TextEntity.cpp
        src/Text/TextEntity.h

        src/Ui/ControlButtonAddElevatorShaftMiddle.cpp
        src/Ui/ControlButtonAddElevatorShaftMiddle.h

        src/Ui/ControlButtonAddElevatorShaftTop.cpp
        src/Ui/ControlButtonAddElevatorShaftTop.h

        src/Objects/ElevatorShaftTop.cpp
        src/Objects/ElevatorShaftTop.h

        src/Objects/ElevatorCabin.cpp
        src/Objects/ElevatorCabin.h

        src/Ui/ControlButtonAddElevatorCabin.cpp
        src/Ui/ControlButtonAddElevatorCabin.h

        src/Component/Elevator.cpp
        src/Component/Elevator.h

        src/Component/WorkPlace.cpp
        src/Component/WorkPlace.h

        src/Basic/Animation.cpp
        src/Basic/Animation.h

        src/Office/Chair.cpp
        src/Office/Chair.h

        src/Ui/MoneyIndicator.cpp
        src/Ui/MoneyIndicator.h

        src/Ui/Questions/Question.cpp
        src/Ui/Questions/Question.h

        src/Ui/BasicUi.cpp
        src/Ui/BasicUi.h

        src/Ui/ControlButtonAddElevator.cpp
        src/Ui/ControlButtonAddElevator.h

        src/Ui/Questions/QAddClerk.cpp
        src/Ui/Questions/QAddClerk.h

        src/Ui/Questions/QAddOffice.cpp
        src/Ui/Questions/QAddOffice.h

        src/Ui/Questions/QAddElevator.cpp
        src/Ui/Questions/QAddElevator.h

        src/Background/Tree.cpp
        src/Background/Tree.h

        src/Background/GroundArtifact.cpp
        src/Background/GroundArtifact.h

        src/Ui/MainPanel/MainPanelOverlay.cpp
        src/Ui/MainPanel/MainPanelOverlay.h

        src/Ui/MainPanel/ButtonPause.cpp
        src/Ui/MainPanel/ButtonPause.h

        src/Ui/MainPanel/Button1x.cpp
        src/Ui/MainPanel/Button1x.h

        src/Ui/MainPanel/Button5x.cpp
        src/Ui/MainPanel/Button5x.h

        src/Ui/MainPanel/Button10x.cpp
        src/Ui/MainPanel/Button10x.h

        src/Component/Destination.cpp
        src/Component/Destination.h

        src/Ui/ControlButtonAddManager.cpp
        src/Ui/ControlButtonAddManager.h

        src/Characters/Manager.cpp
        src/Characters/Manager.h

        src/Ui/Questions/QAddManager.cpp
        src/Ui/Questions/QAddManager.h

        src/System/DebugPattern.cpp
        src/System/DebugPattern.h src/Ui/Popup.cpp src/Ui/Popup.h)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
message(STATUS "Library (SFML_LIBRARIES): ${SFML_LIBRARIES}")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    FIND_LIBRARY (PSAPI Psapi)

    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${PSAPI} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${the_corp_game_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${the_corp_game_VERSION_MINOR}")
include(CPack)