//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include "UI/Editor/AbstractEditor.hpp"

class QLabel;
class QTreeWidget;
class QVBoxLayout;

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

    // fields

    QVBoxLayout* m_layout;
    QLabel* m_noProject;
    QTreeWidget* m_tree;
};
