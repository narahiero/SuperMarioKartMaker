//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QMainWindow>

// TEMP CODE
#include "Common/Property.hpp"

class EditorManager;
class MenuBar;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:

    static MainWindow* instance();

    // TEMP CODE
    static Property<std::string> s_prop0;
    static Property<std::string> s_prop1;
    static Property<std::string> s_prop2;
    static Property<int> s_prop3;
    static Property<float> s_prop4;
    static Property<double> s_prop5;
    static Property<bool> s_prop6;

    explicit MainWindow();
    ~MainWindow();

    // field getter/setters
    
    EditorManager* editorManager() const;

private:

    static MainWindow* s_instance;

    // initializers

    void createMenuBar();
    void createEditorManager();

    // fields

    MenuBar* m_menuBar;

    EditorManager* m_editorManager;
};
