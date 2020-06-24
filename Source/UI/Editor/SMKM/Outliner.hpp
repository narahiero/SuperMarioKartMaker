//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include "UI/Editor/AbstractEditor.hpp"

#include <QTreeWidget>

#include "Common/Property.hpp"

class QLabel;
class QVBoxLayout;

class Project;

class OutlinerNode;

class Outliner final : public AbstractEditor
{
    Q_OBJECT

public:

    SMKM_EDITOR_TYPE_INFO(Outliner, "Outliner")

    explicit Outliner(EditorContainer* container);
    ~Outliner();

    AbstractEditor* duplicate() const override;

private:

    // initializers

    void createLayout();
    void createNoProjectLabel();
    void createTree();

    // slots

    void activeProjectChanged(const std::shared_ptr<Project>& project);

    // fields

    QVBoxLayout* m_layout;
    bool m_hasProject;

    QLabel* m_noProject;

    QTreeWidget* m_tree;
    OutlinerNode* m_projectNode;
};

class OutlinerNode final : public QTreeWidgetItem, public PropertyObserver<std::string>
{

public:

    explicit OutlinerNode(Property<std::string>& name, QTreeWidget* parent = nullptr);
    ~OutlinerNode();

    void valueUpdated(const std::string& name) override;
};
