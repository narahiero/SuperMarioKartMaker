//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/SMKM/Outliner.hpp"

#include <QBoxLayout>
#include <QLabel>
#include <QTreeWidget>

#include "Core/Core.hpp"

#include "UI/Editor/SMKM/Editors.hpp"

Outliner::Outliner(EditorContainer* container) :
    AbstractEditor(container, Editors::Outliner)
{
    createLayout();
    createNoProjectLabel();
    createTree();
}

Outliner::~Outliner() = default;

void Outliner::createLayout()
{
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);

    setContents(m_layout);
}

void Outliner::createNoProjectLabel()
{
    m_noProject = new QLabel(tr("No active project to show outline from..."));
    m_noProject->setWordWrap(true);

    if (!Core::hasActiveProject())
    {
        m_layout->addWidget(m_noProject, 1, Qt::AlignCenter);
    }
}

void Outliner::createTree()
{
    m_tree = new QTreeWidget;
    m_tree->setHeaderHidden(true);
    m_tree->setColumnCount(1);

    if (Core::hasActiveProject())
    {
        m_layout->addWidget(m_tree, 1);
    }
}

AbstractEditor* Outliner::duplicate() const
{
    return new Outliner(container());
}
