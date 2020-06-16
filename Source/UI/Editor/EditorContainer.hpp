//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QWidget>

// TEMP CODE
#include "UI/Editor/Private/EditorContainerSplitter.hpp"
#include "UI/Editor/SMKM/PropertiesEditor.hpp"

class AbstractEditor;
class EditorContainerSplitter;
class EditorManager;

class EditorContainer final : public QWidget
{
    Q_OBJECT

public:

    explicit EditorContainer(EditorManager* manager);
    ~EditorContainer();

    bool canRemove(AbstractEditor* editor) const;
    void remove(AbstractEditor* editor);

    void split(AbstractEditor* editor, Qt::Orientation orientation);

    // TEMP CODE
    void temp()
    {
        m_root->addWidget(new PropertiesEditor(this));
    }

    // field getters/setters

    EditorManager* manager() const;

private:

    // initializers

    void createRoot();
    void createLayout();

    // fields

    EditorManager* m_manager;

    EditorContainerSplitter* m_root;
};
