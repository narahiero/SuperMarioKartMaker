//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QMainWindow>

class Project;

class CoreCallbacks;
class EditorManager;
class MenuBar;

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:

    static MainWindow* instance();

    explicit MainWindow();
    ~MainWindow();

    bool requestClose();

    bool closeActiveProject();

    void showProjectWizard();

    // field getter/setters

    CoreCallbacks* coreCallbacks() const;

    EditorManager* editorManager() const;

protected:

    void closeEvent(QCloseEvent* event) override;

private:

    static MainWindow* s_instance;

    // initializers

    void createCoreCallbacks();
    void createMenuBar();
    void createEditorManager();

    // slots

    void activeProjectChanged(const std::shared_ptr<Project>& project);

    // fields

    CoreCallbacks* m_coreCBs;

    MenuBar* m_menuBar;

    EditorManager* m_editorManager;
};
