//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/SMKM/PropertiesEditor.hpp"

#include "UI/Editor/SMKM/Editors.hpp"

// TEMP CODE
#include "UI/MainWindow.hpp"
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

    pane->addStringProperty("s_prop0", MainWindow::s_prop0);
    pane->addStringProperty("s_prop1", MainWindow::s_prop1);
    pane->addFilePathProperty("s_prop2", MainWindow::s_prop2);

    pane->addSpacing();

    pane->addIntProperty("s_prop3", MainWindow::s_prop3);
    pane->addFloatProperty("s_prop4", MainWindow::s_prop4);
    pane->addDoubleProperty("s_prop5", MainWindow::s_prop5);
    pane->addBoolProperty("s_prop6", MainWindow::s_prop6);

    pane->addSeparator();

    pane->addStringProperty("s_prop0", MainWindow::s_prop0);

    MainWindow::s_prop3.set(8);
}

PropertiesEditor::~PropertiesEditor() = default;

AbstractEditor* PropertiesEditor::duplicate() const
{
    return new PropertiesEditor(container());
}
