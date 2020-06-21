//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/SMKM/PropertiesEditor.hpp"

#include "UI/Editor/SMKM/Editors.hpp"

// TEMP CODE
#include "UI/Editor/PropertyEditorPane.hpp"
#include <QBoxLayout>

PropertiesEditor::PropertiesEditor(EditorContainer* container) :
    AbstractEditor(container, Editors::Properties)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    PropertyEditorPane* pane = new PropertyEditorPane;
    layout->addWidget(pane);
    setContents(layout);
}

PropertiesEditor::~PropertiesEditor() = default;

AbstractEditor* PropertiesEditor::duplicate() const
{
    return new PropertiesEditor(container());
}
