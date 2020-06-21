//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <QVariant>

class QCheckBox;
class QLineEdit;

class AbstractWizardField final : public QObject
{
    Q_OBJECT

public:

    explicit AbstractWizardField(QObject* parent, QLineEdit* lineEdit, bool required = false);
    explicit AbstractWizardField(QObject* parent, QCheckBox* checkBox, bool required = false);
    ~AbstractWizardField();

    bool isFilled() const;

    // field getters/setters

    QVariant value() const;

    bool isRequired() const;

signals:

    void valueChanged(const QVariant& value);

private:

    // slots

    void onValueChangedLineEdit(const QString& value);
    void onValueChangedCheckBox(int state);

    // fields

    QVariant m_value;
    bool m_isRequired;
};
