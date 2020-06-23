//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/SMKM/Editors.hpp"

#include "UI/Editor/EditorManager.hpp"
#include "UI/Editor/SMKM/Outliner.hpp"
#include "UI/Editor/SMKM/PropertiesEditor.hpp"

void Editors::registerEditors(EditorManager* manager)
{
    manager->registerEditorType<::Outliner>(Outliner);
    manager->registerEditorType<PropertiesEditor>(Properties);
}
