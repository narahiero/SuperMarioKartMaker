//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/EditorContainer.hpp"

#include <QBoxLayout>

#include "UI/Editor/AbstractEditor.hpp"
#include "UI/Editor/Private/EditorContainerSplitter.hpp"

EditorContainer::EditorContainer(EditorManager* manager) : QWidget(),
    m_manager{manager}
{
    Q_ASSERT(manager != nullptr);

    createRoot();
    createLayout();
}

EditorContainer::~EditorContainer() = default;

void EditorContainer::createRoot()
{
    m_root = new EditorContainerSplitter(this);
}

void EditorContainer::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_root);

    setLayout(layout);
}

bool EditorContainer::canRemove(AbstractEditor* editor) const
{
    Q_ASSERT(editor != nullptr);

    EditorContainerSplitter* sp = qobject_cast<EditorContainerSplitter*>(editor->parent());
    return sp != nullptr && sp->container() == this && sp->canRemove(editor);
}

void EditorContainer::remove(AbstractEditor* editor)
{
    Q_ASSERT(canRemove(editor));

    EditorContainerSplitter* sp = qobject_cast<EditorContainerSplitter*>(editor->parent());
    sp->remove(editor);
}

void EditorContainer::split(AbstractEditor* editor, Qt::Orientation orientation)
{
    Q_ASSERT(editor != nullptr);

    EditorContainerSplitter* sp = qobject_cast<EditorContainerSplitter*>(editor->parent());

    Q_ASSERT(sp != nullptr);
    Q_ASSERT(sp->container() == this);

    sp->split(editor, orientation);
}

void EditorContainer::morph(AbstractEditor* editor, int typeId)
{
    Q_ASSERT(editor != nullptr);

    EditorContainerSplitter* sp = qobject_cast<EditorContainerSplitter*>(editor->parent());

    Q_ASSERT(sp != nullptr);
    Q_ASSERT(sp->container() == this);

    sp->morph(editor, typeId);
}

EditorManager* EditorContainer::manager() const
{
    return m_manager;
}
