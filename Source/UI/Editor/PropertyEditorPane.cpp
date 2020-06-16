//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/PropertyEditorPane.hpp"

#include <QBoxLayout>

#include "UI/Editor/Private/PropertyEditorWidgets.hpp"

PropertyEditorPane::PropertyEditorPane(QWidget* parent) : QScrollArea(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(true);

    createWidget();
    createLayout();
}

PropertyEditorPane::~PropertyEditorPane() = default;

void PropertyEditorPane::createWidget()
{
    m_widget = new QWidget(this);
    setWidget(m_widget);
}

void PropertyEditorPane::createLayout()
{
    m_layout = new QVBoxLayout;
    m_layout->setAlignment(Qt::AlignTop);

    m_widget->setLayout(m_layout);
}

void PropertyEditorPane::addIntProperty(
    const QString& label, Property<int>& property, int min, int max, int step,
    const QString& prefix, const QString& suffix
)
{
    m_layout->addWidget(new NumberPropertyEditor<int>(
        property, label, min, max, step, prefix, suffix
    ));
}

void PropertyEditorPane::addShortProperty(
    const QString& label, Property<short>& property, short min, short max, short step,
    const QString& prefix, const QString& suffix
)
{
    m_layout->addWidget(new NumberPropertyEditor<short>(
        property, label, min, max, step, prefix, suffix
    ));
}

void PropertyEditorPane::addDoubleProperty(
    const QString& label, Property<double>& property, double min, double max, double step,
    const QString& prefix, const QString& suffix
)
{
    m_layout->addWidget(new NumberPropertyEditor<double>(
        property, label, min, max, step, prefix, suffix
    ));
}

void PropertyEditorPane::addFloatProperty(
    const QString& label, Property<float>& property, float min, float max, float step,
    const QString& prefix, const QString& suffix
)
{
    m_layout->addWidget(new NumberPropertyEditor<float>(
        property, label, min, max, step, prefix, suffix
    ));
}

void PropertyEditorPane::addBoolProperty(const QString& label, Property<bool>& property)
{
    m_layout->addWidget(new BoolPropertyEditor(property, label));
}

void PropertyEditorPane::addStringProperty(const QString& label, Property<std::string>& property)
{
    m_layout->addWidget(new StringPropertyEditor(property, label));
}

void PropertyEditorPane::addFilePathProperty(
    const QString& label, Property<std::string>& property, bool dir
)
{
    m_layout->addWidget(new StringPropertyEditor(property, label,
        dir ? StringPropertyEditor::Type::DirPath : StringPropertyEditor::Type::FilePath
    ));
}

void PropertyEditorPane::addSpacing()
{
    m_layout->addSpacerItem(new QSpacerItem(0, 16));
}

void PropertyEditorPane::addSeparator()
{
    m_layout->addWidget(new PropertyEditorSeparator);
}
