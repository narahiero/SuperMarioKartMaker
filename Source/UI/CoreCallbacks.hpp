//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QApplication>

class Project;

class CoreCallbacks final : public QObject
{
    Q_OBJECT

public:

    static CoreCallbacks* instance();

    explicit CoreCallbacks(QObject* parent = nullptr);
    ~CoreCallbacks();

signals:

    void activeProjectChanged(const std::shared_ptr<Project>& project);
};
