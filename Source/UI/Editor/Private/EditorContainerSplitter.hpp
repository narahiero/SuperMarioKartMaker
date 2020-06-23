//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QSplitter>

class AbstractEditor;
class EditorContainer;

class EditorContainerSplitter final : public QSplitter
{
    Q_OBJECT

public:

    explicit EditorContainerSplitter(EditorContainer* container);
    explicit EditorContainerSplitter(EditorContainerSplitter* parent, Qt::Orientation orientation);
    ~EditorContainerSplitter();

    bool canRemove(AbstractEditor* editor) const;
    void remove(AbstractEditor* editor);

    void split(AbstractEditor* editor, Qt::Orientation orientation);

    void morph(AbstractEditor* editor, int typeId);

    // field getters/setters

    EditorContainer* container() const;

    bool isRoot() const;

private:

    // fields

    EditorContainer* m_container;

    bool m_isRoot;
};
