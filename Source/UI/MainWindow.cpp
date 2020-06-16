//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/MainWindow.hpp"

#include "UI/Editor/EditorManager.hpp"
#include "UI/Editor/SMKM/Editors.hpp"
#include "UI/MenuBar.hpp"

// TEMP CODE
#include "UI/Editor/EditorContainer.hpp"
Property<std::string> MainWindow::s_prop0("some def value");
Property<std::string> MainWindow::s_prop1("1 value");
Property<std::string> MainWindow::s_prop2(":3 =^.^=");
Property<int> MainWindow::s_prop3(32);
Property<float> MainWindow::s_prop4(135.75f);
Property<double> MainWindow::s_prop5(9120.8325);
Property<bool> MainWindow::s_prop6(true);

MainWindow* MainWindow::s_instance = nullptr;

MainWindow* MainWindow::instance()
{
    return s_instance;
}

MainWindow::MainWindow() : QMainWindow()
{
    Q_ASSERT(s_instance == nullptr);
    s_instance = this;

    setWindowTitle("Super Mario Kart Maker");
    resize(1080, 720);

    createMenuBar();
    createEditorManager();
}

MainWindow::~MainWindow() = default;

void MainWindow::createMenuBar()
{
    m_menuBar = new MenuBar(this);

    setMenuBar(m_menuBar);
}

void MainWindow::createEditorManager()
{
    m_editorManager = new EditorManager(this);

    Editors::registerEditors(m_editorManager);

    // TEMP CODE
    m_editorManager->container()->temp();

    setCentralWidget(m_editorManager);
}

EditorManager* MainWindow::editorManager() const
{
    return m_editorManager;
}
