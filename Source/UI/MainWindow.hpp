//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QMainWindow>

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

    void showProjectWizard();

    // field getter/setters

    EditorManager* editorManager() const;

protected:

    void closeEvent(QCloseEvent* event) override;

private:

    static MainWindow* s_instance;

    // initializers

    void createMenuBar();
    void createEditorManager();

    // fields

    MenuBar* m_menuBar;

    EditorManager* m_editorManager;
};
