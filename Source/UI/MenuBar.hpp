//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QMenuBar>

class MenuBar final : public QMenuBar
{
    Q_OBJECT

public:

    explicit MenuBar(QWidget* parent = nullptr);
    ~MenuBar();

signals:

    void exit();

private:

    // initializers

    void createFileMenu();
};
