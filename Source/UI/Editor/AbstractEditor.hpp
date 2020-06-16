//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QWidget>

class QLayout;
class QVBoxLayout;

class EditorBar;
class EditorContainer;
class EditorManager;

class AbstractEditor : public QWidget
{
    Q_OBJECT

public:

    struct TypeInfo
    {
        using Factory = AbstractEditor*(*)(EditorContainer*);

        const QString m_name;
        const Factory m_factory;

    protected:

        TypeInfo(const QString& name, Factory factory);
    };

    explicit AbstractEditor(EditorContainer* container, int typeId);
    ~AbstractEditor();

    virtual AbstractEditor* duplicate() const = 0;

    bool canRemove();
    void remove();

    void splitH();
    void splitV();

    // field getters/setters

    EditorManager* manager() const;

    EditorContainer* container() const;

    EditorBar* editorBar() const;

    void setContents(QLayout* layout);
    QLayout* contents() const;

private:

    // initializers

    void createLayout();
    void createEditorBar(int typeId);

    // fields

    EditorManager* m_manager;
    EditorContainer* m_container;

    EditorBar* m_editorBar;

    QVBoxLayout* m_layout;
    QLayout* m_contents;
};


// create required editor type information
#define SMKM_EDITOR_TYPE_INFO(Type, name) \
    struct TypeInfo final : public AbstractEditor::TypeInfo \
    { \
    private: \
        using Base = AbstractEditor::TypeInfo; \
    public: \
        TypeInfo() : Base \
        ( \
            tr( name ), \
            [](EditorContainer* c) -> AbstractEditor* { return new Type(c); } \
        ) \
        { } \
    };
