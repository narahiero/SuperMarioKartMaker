//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/EditorBar.hpp"

#include <QBoxLayout>
#include <QComboBox>
#include <QContextMenuEvent>
#include <QMenu>

#include "UI/Editor/EditorManager.hpp"

EditorBar::EditorBar(AbstractEditor* editor, int typeId) : QWidget(),
    m_editor{editor},
    m_typeId{typeId}
{
    Q_ASSERT(editor != nullptr);

    createLayout();
    createTypeSelect();
    createActions();
}

EditorBar::~EditorBar() = default;

void EditorBar::createLayout()
{
    m_layout = new QHBoxLayout;
    setLayout(m_layout);
}

void EditorBar::createTypeSelect()
{
    m_typeSelect = new QComboBox;
    m_typeSelect->setMinimumWidth(16);

    auto typeInfo = m_editor->manager()->typeInfo();
    for (int typeId : typeInfo.keys())
    {
        m_typeSelect->addItem(typeInfo.value(typeId)->m_name, typeId);
    }

    m_layout->addWidget(m_typeSelect);
}

void EditorBar::createActions()
{
    m_splitH = new QAction(tr("Split &horizontally"));
    m_splitV = new QAction(tr("Split &vertically"));
    m_remove = new QAction(tr("&Close"));

    connect(m_splitH, &QAction::triggered, m_editor, &AbstractEditor::splitH);
    connect(m_splitV, &QAction::triggered, m_editor, &AbstractEditor::splitV);
    connect(m_remove, &QAction::triggered, m_editor, &AbstractEditor::remove);
}

AbstractEditor* EditorBar::editor() const
{
    return m_editor;
}

void EditorBar::contextMenuEvent(QContextMenuEvent* event)
{
    m_remove->setEnabled(m_editor->canRemove());

    QMenu menu;
    menu.addAction(m_splitH);
    menu.addAction(m_splitV);
    menu.addAction(m_remove);
    menu.exec(event->globalPos());
}
