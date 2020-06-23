//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "Core/Callbacks.hpp"

namespace Callbacks
{

ActiveProjectChangedCB s_activeProjectChangedCB;

void setActiveProjectChangedCB(ActiveProjectChangedCB cb)
{
    s_activeProjectChangedCB = cb;
}

void activeProjectChanged(const std::shared_ptr<Project>& project)
{
    if (s_activeProjectChangedCB)
    {
        s_activeProjectChangedCB(project);
    }
}
}
