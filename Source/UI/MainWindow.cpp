//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/MainWindow.hpp"

#include <QCloseEvent>
#include <QMessageBox>

#include "Core/Core.hpp"
#include "Core/Project.hpp"

#include "UI/Editor/EditorManager.hpp"
#include "UI/Editor/SMKM/Editors.hpp"
#include "UI/MenuBar.hpp"
#include "UI/Wizard/SMKM/ProjectWizard.hpp"

// TEMP CODE
#include "UI/Editor/EditorContainer.hpp"

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

    // file menu
    connect(m_menuBar, &MenuBar::newProject, this, &MainWindow::showProjectWizard);
    connect(m_menuBar, &MenuBar::exit, this, &MainWindow::close);

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

bool MainWindow::requestClose()
{
    if (Core::hasActiveProject() && Core::activeProject()->hasUnsavedChanges())
    {
        QMessageBox msgBox(QMessageBox::Warning, "Save Project?", QStringLiteral(
                "Do you want to save your project '%1' before exiting Super Mario Kart Maker?"
            ).arg(QString::fromStdString(Core::activeProject()->name().get())),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
        );

        msgBox.exec();

        int opt = msgBox.result();
        if (opt == QMessageBox::Save)
        {

        }

        if (opt == QMessageBox::Save || opt == QMessageBox::Discard)
        {
            return true;
        }
    }

    return true;
}

void MainWindow::showProjectWizard()
{
    ProjectWizard wizard(this);
    wizard.run();
}

EditorManager* MainWindow::editorManager() const
{
    return m_editorManager;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (requestClose())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
