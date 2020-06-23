//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QWidget>

class QComboBox;
class QHBoxLayout;

class AbstractEditor;

class EditorBar final : public QWidget
{
    Q_OBJECT

public:

    explicit EditorBar(AbstractEditor* editor, int typeId);
    ~EditorBar();

    // field getters/setters

    AbstractEditor* editor() const;

protected:

    void contextMenuEvent(QContextMenuEvent* event) override;

private:

    // initializers

    void createLayout();
    void createTypeSelect();
    void createActions();

    // slots

    void onTypeSelected(int typeId);

    // fields

    AbstractEditor* m_editor;
    int m_typeId;

    QHBoxLayout* m_layout;
    QComboBox* m_typeSelect;

    QAction* m_splitH;
    QAction* m_splitV;
    QAction* m_remove;
};
