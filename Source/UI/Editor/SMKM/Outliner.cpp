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
#include "Core/Project.hpp"

#include "UI/CoreCallbacks.hpp"
#include "UI/Editor/SMKM/Editors.hpp"

Outliner::Outliner(EditorContainer* container) :
    AbstractEditor(container, Editors::Outliner),
    m_hasProject{Core::hasActiveProject()}
{
    createLayout();
    createNoProjectLabel();
    createTree();

    connect(CoreCallbacks::instance(), &CoreCallbacks::activeProjectChanged,
        this, &Outliner::activeProjectChanged);
}

Outliner::~Outliner()
{
    m_noProject->deleteLater();
    m_tree->deleteLater();
}

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

    if (!m_hasProject)
    {
        m_layout->addWidget(m_noProject, 1, Qt::AlignCenter);
    }
}

void Outliner::createTree()
{
    m_tree = new QTreeWidget;
    m_tree->setHeaderHidden(true);
    m_tree->setColumnCount(1);

    if (m_hasProject)
    {
        m_layout->addWidget(m_tree, 1);

        m_projectNode = new OutlinerNode(Core::activeProject()->name(), m_tree);
    }
}

AbstractEditor* Outliner::duplicate() const
{
    return new Outliner(container());
}

void Outliner::activeProjectChanged(const std::shared_ptr<Project>& project)
{
    if (project)
    {
        if (!m_hasProject)
        {
            m_noProject->setParent(nullptr);
            m_layout->addWidget(m_tree, 1);
            m_hasProject = true;
        }

        m_tree->clear();
        m_projectNode = new OutlinerNode(project->name(), m_tree);
    }
    else
    {
        if (m_hasProject)
        {
            m_tree->setParent(nullptr);
            m_layout->addWidget(m_noProject, 1, Qt::AlignCenter);
            m_hasProject = false;
        }
    }
}

////// OutlinerNode class //////////////

OutlinerNode::OutlinerNode(Property<std::string>& name, QTreeWidget* parent) :
    QTreeWidgetItem(parent),
    PropertyObserver(name)
{
    setText(0, QString::fromStdString(name.get()));

    if (parent != nullptr)
    {
        setExpanded(true);
    }
}

OutlinerNode::~OutlinerNode() = default;

void OutlinerNode::valueUpdated(const std::string& name)
{
    setText(0, QString::fromStdString(name));
}
