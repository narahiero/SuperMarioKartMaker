//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/EditorManager.hpp"

#include <QLabel>
#include <QBoxLayout>

#include "UI/Editor/EditorContainer.hpp"

EditorManager::EditorManager(QWidget* parent) : QWidget(parent)
{
    createContainer();
    createLayout();
}

EditorManager::~EditorManager() = default;

void EditorManager::createContainer()
{
    m_container = new EditorContainer(this);
}

void EditorManager::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_container);

    setLayout(layout);
}

EditorContainer* EditorManager::container() const
{
    return m_container;
}

QMap<int, QSharedPointer<AbstractEditor::TypeInfo>> EditorManager::typeInfo() const
{
    return m_typeInfo;
}

QSharedPointer<AbstractEditor::TypeInfo> EditorManager::typeInfo(int id) const
{
    return m_typeInfo.value(id, nullptr);
}
