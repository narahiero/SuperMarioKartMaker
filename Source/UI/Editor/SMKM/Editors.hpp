//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

class EditorManager;

class Editors final
{

public:

    enum EditorType
    {
        Outliner,
        Properties
    };

    static void registerEditors(EditorManager* manager);
};
