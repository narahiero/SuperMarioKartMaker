//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <memory>
#include <string>

class Project;

namespace Core
{

bool hasActiveProject();
void setActiveProject(const std::shared_ptr<Project>& project);
std::shared_ptr<Project> activeProject();
}
