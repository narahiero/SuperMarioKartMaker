//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/AbstractEditor.hpp"

#include <QBoxLayout>

#include "UI/Editor/EditorBar.hpp"
#include "UI/Editor/EditorContainer.hpp"

AbstractEditor::AbstractEditor(EditorContainer* container, int typeId) : QWidget(),
    m_manager{container->manager()},
    m_container{container}
{
    Q_ASSERT(container != nullptr);

    createLayout();
    createEditorBar(typeId);
}

AbstractEditor::~AbstractEditor() = default;

void AbstractEditor::createLayout()
{
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    setLayout(m_layout);
}

void AbstractEditor::createEditorBar(int typeId)
{
    m_editorBar = new EditorBar(this, typeId);
    m_layout->addWidget(m_editorBar);
}

bool AbstractEditor::canRemove()
{
    return m_container->canRemove(this);
}

void AbstractEditor::remove()
{
    m_container->remove(this);
}

void AbstractEditor::splitH()
{
    m_container->split(this, Qt::Horizontal);
}

void AbstractEditor::splitV()
{
    m_container->split(this, Qt::Vertical);
}

EditorManager* AbstractEditor::manager() const
{
    return m_manager;
}

EditorContainer* AbstractEditor::container() const
{
    return m_container;
}

EditorBar* AbstractEditor::editorBar() const
{
    return m_editorBar;
}

void AbstractEditor::setContents(QLayout* layout)
{
    if (m_layout->count() > 1)
    {
        m_layout->removeItem(m_contents);
        m_contents->deleteLater();
    }

    m_layout->addLayout(layout, 1);
    m_contents = layout;
}

QLayout* AbstractEditor::contents() const
{
    return m_contents;
}

AbstractEditor::TypeInfo::TypeInfo(const QString& name, Factory factory) :
    m_name{name},
    m_factory{factory}
{

}
