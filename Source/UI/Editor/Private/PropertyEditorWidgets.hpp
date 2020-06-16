//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <limits>
#include <type_traits>

#include <QFrame>
#include <QWidget>

#include "Common/Property.hpp"

class QCheckBox;
class QDoubleSpinBox;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QSpinBox;

template <class Type>
class PropertyEditorWidget : public PropertyObserver<Type>, public QWidget
{

public:

    PropertyEditorWidget(Property<Type>& property) : PropertyObserver(property), QWidget() {}
    ~PropertyEditorWidget() = default;
};

template <class Type>
class NumberPropertyEditor : public PropertyEditorWidget<Type>
{

public:

    using Base = std::conditional_t<
        std::is_same_v<Type, double> || std::is_same_v<Type, float>, double, int>;

    explicit NumberPropertyEditor(
        Property<Type>& property, const QString& label, Base min = BASE_MIN, Base max = BASE_MAX,
        Base step = 0, const QString& prefix = QString(), const QString& suffix = QString()
    );
    ~NumberPropertyEditor();

    void valueUpdated(const Type& value) override;

private:

    using SpinBox = std::conditional_t<std::is_same_v<Base, double>, QDoubleSpinBox, QSpinBox>;

    constexpr static Base BASE_MIN = std::numeric_limits<Base>::lowest();
    constexpr static Base BASE_MAX = std::numeric_limits<Base>::max();

    // initializers

    void createLayout(const QString& label);
    void createSpinBox(Base min, Base max, Base step, const QString& prefix, const QString& suffix);

    // slots

    void onEditingFinished();

    // fields

    QHBoxLayout* m_layout;
    SpinBox* m_spinBox;
};

class BoolPropertyEditor : public PropertyEditorWidget<bool>
{

public:

    explicit BoolPropertyEditor(Property<bool>& property, const QString& label);
    ~BoolPropertyEditor();

    void valueUpdated(const bool& value) override;

private:

    // initializers

    void createLayout(const QString& label);
    void createCheckBox();

    // slots

    void onStateChanged(Qt::CheckState state);

    // fields

    QHBoxLayout* m_layout;
    QCheckBox* m_checkBox;
};

class StringPropertyEditor : public PropertyEditorWidget<std::string>
{

public:

    enum class Type
    {
        Default, FilePath, DirPath
    };

    explicit StringPropertyEditor(
        Property<std::string>& property, const QString& label, Type type = Type::Default
    );
    ~StringPropertyEditor();

    void valueUpdated(const std::string& value) override;

    // field getters/setters

    Type type() const;

private:

    // initializers

    void createLayouts(const QString& label);
    void createLineEdit();
    void createTypeSpecificWidgets();

    // slots

    void onEditingFinished();
    void onBrowseClicked();

    // helpers

    bool hasBrowseButton() const;

    // fields

    const Type m_type;

    QHBoxLayout* m_layout;

    QHBoxLayout* m_subLayout;
    QLineEdit* m_lineEdit;
    QPushButton* m_browse;
};

class PropertyEditorSeparator final : public QFrame
{

public:

    explicit PropertyEditorSeparator(QWidget* parent = nullptr);
    ~PropertyEditorSeparator();
};
