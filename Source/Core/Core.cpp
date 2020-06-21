//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "Core/Core.hpp"

#include "Core/Project.hpp"

namespace Core
{

static std::shared_ptr<Project> s_project;

bool hasActiveProject()
{
    return s_project != nullptr;
}

std::shared_ptr<Project> newActiveProject(const std::string& name)
{
    s_project = std::make_shared<Project>(name);
    return s_project;
}

std::shared_ptr<Project> activeProject()
{
    return s_project;
}
}
