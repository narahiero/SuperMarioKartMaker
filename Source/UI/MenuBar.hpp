//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QMenuBar>

class Project;

class MenuBar final : public QMenuBar
{
    Q_OBJECT

public:

    explicit MenuBar(QWidget* parent = nullptr);
    ~MenuBar();

signals:

    void newProject();
    void closeProject();
    void exit();

private:

    // initializers

    void createFileMenu();
    void connectAll();

    // slots

    void activeProjectChanged(const std::shared_ptr<Project>& project);

    // fields

    QAction* m_closeProject;
};
