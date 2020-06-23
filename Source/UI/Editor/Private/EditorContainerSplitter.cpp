//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/Private/EditorContainerSplitter.hpp"

#include "UI/Editor/AbstractEditor.hpp"
#include "UI/Editor/EditorContainer.hpp"
#include "UI/Editor/EditorManager.hpp"

EditorContainerSplitter::EditorContainerSplitter(EditorContainer* container) : QSplitter(),
    m_container{container},
    m_isRoot{true}
{
    Q_ASSERT(container != nullptr);

    setChildrenCollapsible(false);
}

EditorContainerSplitter::EditorContainerSplitter(
    EditorContainerSplitter* parent, Qt::Orientation orientation
) :
    QSplitter(orientation),
    m_container{parent->m_container},
    m_isRoot{false}
{
    Q_ASSERT(parent != nullptr);

    setChildrenCollapsible(false);
}

EditorContainerSplitter::~EditorContainerSplitter() = default;

bool EditorContainerSplitter::canRemove(AbstractEditor* editor) const
{
    return !m_isRoot || count() > 1;
}

void EditorContainerSplitter::remove(AbstractEditor* editor)
{
    editor->setParent(nullptr);
    editor->deleteLater();

    if (!m_isRoot && count() == 1)
    {
        EditorContainerSplitter* sp = qobject_cast<EditorContainerSplitter*>(parent());
        sp->replaceWidget(sp->indexOf(this), widget(0));

        deleteLater();
    }
}

void EditorContainerSplitter::split(AbstractEditor* editor, Qt::Orientation o)
{
    if (orientation() == o)
    {
        insertWidget(indexOf(editor) + 1, editor->duplicate());
    }
    else if (m_isRoot && count() == 1)
    {
        setOrientation(o);
        addWidget(editor->duplicate());
    }
    else
    {
        EditorContainerSplitter* sp = new EditorContainerSplitter(this, o);

        replaceWidget(indexOf(editor), sp);

        sp->addWidget(editor);
        sp->addWidget(editor->duplicate());
    }
}

void EditorContainerSplitter::morph(AbstractEditor* editor, int typeId)
{
    auto typeInfo = m_container->manager()->typeInfo(typeId);

    replaceWidget(indexOf(editor), typeInfo->m_factory(m_container));

    editor->deleteLater();
}

EditorContainer* EditorContainerSplitter::container() const
{
    return m_container;
}

bool EditorContainerSplitter::isRoot() const
{
    return m_isRoot;
}
