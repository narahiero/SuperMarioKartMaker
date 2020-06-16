//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include "UI/Editor/AbstractEditor.hpp"

class PropertiesEditor final : public AbstractEditor
{
    Q_OBJECT

public:

    SMKM_EDITOR_TYPE_INFO(PropertiesEditor, "Properties")

    explicit PropertiesEditor(EditorContainer* container);
    ~PropertiesEditor();

    AbstractEditor* duplicate() const override;
};
