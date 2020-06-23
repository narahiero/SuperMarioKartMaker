//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "Core/Core.hpp"

#include "Core/Callbacks.hpp"
#include "Core/Project.hpp"

namespace Core
{

static std::shared_ptr<Project> s_project;

bool hasActiveProject()
{
    return s_project != nullptr;
}

void setActiveProject(const std::shared_ptr<Project>& project)
{
    s_project = project;
    Callbacks::activeProjectChanged(project);
}

std::shared_ptr<Project> activeProject()
{
    return s_project;
}
}
