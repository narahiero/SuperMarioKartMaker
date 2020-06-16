//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QMap>
#include <QWidget>

#include "UI/Editor/AbstractEditor.hpp"

class EditorContainer;

class EditorManager final : public QWidget
{
    Q_OBJECT

public:

    enum class EditorType
    {
        Properties
    };

    explicit EditorManager(QWidget* parent = nullptr);
    ~EditorManager();

    // field getters/setters

    EditorContainer* container() const;

    QMap<int, QSharedPointer<AbstractEditor::TypeInfo>> typeInfo() const;
    QSharedPointer<AbstractEditor::TypeInfo> typeInfo(int id) const;

    // templates

    template <class Type>
    void registerEditorType(int id)
    {
        Q_ASSERT(id >= 0);
        Q_ASSERT(!m_typeInfo.contains(id));

        m_typeInfo.insert(id, QSharedPointer<Type::TypeInfo>(new Type::TypeInfo));
    }

private:

    // initializers

    void createContainer();
    void createLayout();

    // fields

    EditorContainer* m_container;

    QMap<int, QSharedPointer<AbstractEditor::TypeInfo>> m_typeInfo;
};
