//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <string>

#include "Common/Property.hpp"

class Project final
{

public:

    Project();
    Project(const std::string& name);
    ~Project();

    Property<std::string>& name();

    bool hasUnsavedChanges() const;

private:

    Property<std::string> m_name;
};
