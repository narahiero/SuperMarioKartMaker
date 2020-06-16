########################################
# Find and setup Qt 5
########################################

if(NOT Qt5_DIR)
    message(FATAL_ERROR
        "You must set Qt5_DIR to your local installation of Qt 5!"
    )
endif()

find_package(Qt5 REQUIRED COMPONENTS Gui Widgets)

if(NOT ${Qt5Core_VERSION} MATCHES "5.14.1" AND NOT SMKM_NO_WARNINGS)
    message(WARNING
        "Your version of Qt (${Qt5Core_VERSION}) does not match the recommended version (5.14.1)."
        "\nIf you wish to disable those warnings, set SMKM_NO_WARNINGS."
    )
endif()

set(CMAKE_AUTOMOC ON)


########################################
# Setup target
########################################

add_executable(SMKM
    main.cpp

    MainWindow.cpp
    MainWindow.hpp
    MenuBar.cpp
    MenuBar.hpp

    # Editor
    Editor/AbstractEditor.cpp
    Editor/AbstractEditor.hpp
    Editor/EditorBar.cpp
    Editor/EditorBar.hpp
    Editor/EditorContainer.cpp
    Editor/EditorContainer.hpp
    Editor/EditorManager.cpp
    Editor/EditorManager.hpp
    Editor/Private/EditorContainerSplitter.cpp
    Editor/Private/EditorContainerSplitter.hpp
    Editor/Private/PropertyEditorWidgets.cpp
    Editor/Private/PropertyEditorWidgets.hpp
    Editor/PropertyEditorPane.cpp
    Editor/PropertyEditorPane.hpp

    Editor/SMKM/Editors.cpp
    Editor/SMKM/Editors.hpp
    Editor/SMKM/PropertiesEditor.hpp
    Editor/SMKM/PropertiesEditor.cpp
)

target_link_libraries(SMKM Common Qt5::Widgets)


########################################
# Windows-specific setup
########################################

if(WIN32)
    set_target_properties(SMKM PROPERTIES
        WIN32_EXECUTABLE TRUE
        DEBUG_POSTFIX "D"
    )

    # Deploy Qt on Windows

    # Find Qt binaries directory
    get_target_property(MOC_EXE_LOC Qt5::moc IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${MOC_EXE_LOC}" DIRECTORY)
    find_program(WINDEPLOYQT_EXE windeployqt HINTS "${QT_BIN_DIR}")

    # Add windeployqt command
    add_custom_command(TARGET SMKM POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E env PATH="${QT_BIN_DIR}"
            "${WINDEPLOYQT_EXE}"
                $<IF:$<CONFIG:Debug>,--debug,--release>
                "$<TARGET_FILE:SMKM>"
    )
endif()
