//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <functional>
#include <memory>

class Project;

namespace Callbacks
{

using ActiveProjectChangedCB = std::function<void(const std::shared_ptr<Project>&)>;

void setActiveProjectChangedCB(ActiveProjectChangedCB cb);

void activeProjectChanged(const std::shared_ptr<Project>& project);
}
