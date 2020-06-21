//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Wizard/Private/AbstractWizardField.hpp"

#include <QCheckBox>
#include <QLineEdit>

AbstractWizardField::AbstractWizardField(QObject* parent, QLineEdit* lineEdit, bool required) :
    QObject(parent),
    m_isRequired{required}
{
    Q_ASSERT(lineEdit != nullptr);

    m_value = QVariant::fromValue(lineEdit->text());
    connect(lineEdit, &QLineEdit::textChanged, this, &AbstractWizardField::onValueChangedLineEdit);
}

AbstractWizardField::AbstractWizardField(QObject* parent, QCheckBox* checkBox, bool required) :
    QObject(parent),
    m_isRequired{required}
{
    Q_ASSERT(checkBox != nullptr);

    m_value = QVariant::fromValue(checkBox->checkState() == Qt::Checked);
    connect(checkBox, &QCheckBox::stateChanged, this, &AbstractWizardField::onValueChangedCheckBox);
}

AbstractWizardField::~AbstractWizardField() = default;

bool AbstractWizardField::isFilled() const
{
    if (m_value.type() == QVariant::String)
    {
        return !m_value.toString().isEmpty();
    }
    return true;
}

QVariant AbstractWizardField::value() const
{
    return m_value;
}

bool AbstractWizardField::isRequired() const
{
    return m_isRequired;
}

void AbstractWizardField::onValueChangedLineEdit(const QString& value)
{
    m_value.setValue(value);
    emit valueChanged(m_value);
}

void AbstractWizardField::onValueChangedCheckBox(int state)
{
    m_value.setValue(state == Qt::Checked);
    emit valueChanged(m_value);
}
