//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "Core/Project.hpp"

Project::Project() : Project("Untitled")
{

}

Project::Project(const std::string& name) :
    m_name{name}
{

}

Project::~Project() = default;

Property<std::string>& Project::name()
{
    return m_name;
}

bool Project::hasUnsavedChanges() const
{
    return false;
}
