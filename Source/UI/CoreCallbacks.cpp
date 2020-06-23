//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/CoreCallbacks.hpp"

#include "Core/Callbacks.hpp"
#include "Core/Project.hpp"

#include "UI/MainWindow.hpp"

CoreCallbacks* CoreCallbacks::instance()
{
    return MainWindow::instance()->coreCallbacks();
}

CoreCallbacks::CoreCallbacks(QObject* parent) : QObject(parent)
{
    Callbacks::setActiveProjectChangedCB([this](const auto& project) {
        QMetaObject::invokeMethod(qApp, [&, this]() { emit activeProjectChanged(project); });
    });
}

CoreCallbacks::~CoreCallbacks() = default;
