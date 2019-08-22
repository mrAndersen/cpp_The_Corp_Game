cmake_minimum_required(VERSION 3.8)
set(CMAKE_BUILD_TYPE "Debug")

#set(COMPILER "MSVC")
set(COMPILER "GCC")

project(the_corp_game)
set(CMAKE_CXX_STANDARD 14)

if(COMPILER STREQUAL "GCC")
    # Detect and add SFML on Linux
#    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/vendor/sfml-2.5.1-linux/lib/cmake/SFML")
    set(SFML_DIR "${PROJECT_SOURCE_DIR}/vendor/sfml-2.5.1-linux/lib/cmake/SFML")

    set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/gcc-${CMAKE_BUILD_TYPE}")
    set(CMAKE_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/vendor/sfml-2.5.1-linux/include")
endif()

if(COMPILER STREQUAL "MSVC")
#    set(WINDOWS_KIT_VERSION "10.0.14393.0")
#    set(WINDOWS_LIB_DIRECTORY "C:/Program Files (x86)/Windows Kits/10/Lib/${WINDOWS_KIT_VERSION}/um/x86")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/msvc-${CMAKE_BUILD_TYPE}")
    set(CMAKE_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(SFML_ROOT "${PROJECT_SOURCE_DIR}/vendor/sfml-2.4.2-windows")
    set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/vendor/sfml-2.4.2-windows/include")

#    set(OTHER_DEPENDENCIES "${PROJECT_SOURCE_DIR}/vendor/yaml/libyaml-cppmd.lib")
endif()

add_subdirectory(vendor/yaml-cpp)
add_subdirectory(vendor/sfml)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("vendor/yaml-cpp/include")

file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "corpgame")
add_executable(
        ${EXECUTABLE_NAME}

        main.cpp
        main.rc

        version.h

        src/System/mingw.mutex.h
        src/System/mingw.condition_variable.h
        src/System/mingw.thread.h

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
        src/System/DebugPattern.h

        src/Ui/Popup.cpp src/Ui/Popup.h
        src/Ui/PopupButton.cpp
        src/Ui/PopupButton.h

        src/Ui/ControlButtonAddAccountant.cpp
        src/Ui/ControlButtonAddAccountant.h

        src/Characters/Accountant.cpp
        src/Characters/Accountant.h

        src/Ui/Questions/QAddAccountant.cpp
        src/Ui/Questions/QAddAccountant.h
        src/Background/Cloud.cpp src/Background/Cloud.h src/Ui/MainPanel/Cog.cpp src/Ui/MainPanel/Cog.h src/System/SaveManager.cpp src/System/SaveManager.h src/Objects/Door.cpp src/Objects/Door.h)

set(SFML_LIBRARIES sfml-graphics sfml-audio sfml-network sfml-system sfml-window)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} yaml-cpp ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

if(COMPILER STREQUAL "GCC")
    set(CMAKE_CXX_FLAGS "-pthread")
    set(CMAKE_C_FLAGS "-pthread")

    target_link_libraries(${EXECUTABLE_NAME} /usr/lib/x86_64-linux-gnu/libz.so)
endif()