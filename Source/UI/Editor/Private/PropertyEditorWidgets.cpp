//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Editor/Private/PropertyEditorWidgets.hpp"

#include <QBoxLayout>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

#include "UI/MainWindow.hpp"


//////////////////////////////////
////// NumberPropertyEditor //////

template <class Type>
NumberPropertyEditor<Type>::NumberPropertyEditor(
    Property<Type>& property, const QString& label, Base min, Base max, Base step,
    const QString& prefix, const QString& suffix
) :
    PropertyEditorWidget(property)
{
    createLayout(label);
    createSpinBox(min, max, step, prefix, suffix);
}

template <class Type>
NumberPropertyEditor<Type>::~NumberPropertyEditor() = default;

template <class Type>
void NumberPropertyEditor<Type>::createLayout(const QString& text)
{
    m_layout = new QHBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    QLabel* label = new QLabel(text);
    label->setMinimumWidth(16);

    m_layout->addWidget(label, 1, Qt::AlignRight);
}

template <class Type>
void NumberPropertyEditor<Type>::createSpinBox(
    Base min, Base max, Base step, const QString& prefix, const QString& suffix
)
{
    m_spinBox = new SpinBox;
    m_spinBox->setMinimumWidth(16);

    m_spinBox->setRange(min, max);
    m_spinBox->setSingleStep(step);
    m_spinBox->setPrefix(prefix);
    m_spinBox->setSuffix(suffix);
    m_spinBox->setValue(static_cast<Base>(observedProperty().get()));

    m_layout->addWidget(m_spinBox, 1);

    connect(m_spinBox, &QAbstractSpinBox::editingFinished,
        this, &NumberPropertyEditor<Type>::onEditingFinished);
}

template <class Type>
void NumberPropertyEditor<Type>::valueUpdated(const Type& value)
{
    m_spinBox->setValue(static_cast<Base>(value));
}

template <class Type>
void NumberPropertyEditor<Type>::onEditingFinished()
{
    observedProperty().set(static_cast<Type>(m_spinBox->value()));
}

#define SMKM_SPECIALIZE_NUMBER_PROPERTY_EDITOR(Type) \
template NumberPropertyEditor<Type>::NumberPropertyEditor( \
    Property<Type>&, const QString& label, Base, Base, Base, const QString&, const QString& \
); \
template NumberPropertyEditor<Type>::~NumberPropertyEditor(); \
template void NumberPropertyEditor<Type>::valueUpdated(const Type&); \
template void NumberPropertyEditor<Type>::onEditingFinished()

SMKM_SPECIALIZE_NUMBER_PROPERTY_EDITOR(int);
SMKM_SPECIALIZE_NUMBER_PROPERTY_EDITOR(short);
SMKM_SPECIALIZE_NUMBER_PROPERTY_EDITOR(double);
SMKM_SPECIALIZE_NUMBER_PROPERTY_EDITOR(float);


////////////////////////////////
////// BoolPropertyEditor //////

BoolPropertyEditor::BoolPropertyEditor(Property<bool>& property, const QString& label) :
    PropertyEditorWidget(property)
{
    createLayout(label);
    createCheckBox();
}

BoolPropertyEditor::~BoolPropertyEditor() = default;

void BoolPropertyEditor::createLayout(const QString& text)
{
    m_layout = new QHBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    QLabel* label = new QLabel(text);
    label->setMinimumWidth(16);

    m_layout->addWidget(label, 1, Qt::AlignRight);
}

void BoolPropertyEditor::createCheckBox()
{
    m_checkBox = new QCheckBox;
    m_checkBox->setCheckState(observedProperty().get() ? Qt::Checked : Qt::Unchecked);

    m_layout->addWidget(m_checkBox, 0, Qt::AlignRight);
}

void BoolPropertyEditor::valueUpdated(const bool& value)
{
    m_checkBox->setCheckState(value ? Qt::Checked : Qt::Unchecked);
}

void BoolPropertyEditor::onStateChanged(Qt::CheckState state)
{
    observedProperty().set(state == Qt::Checked);
}


//////////////////////////////////
////// StringPropertyEditor //////

StringPropertyEditor::StringPropertyEditor(
    Property<std::string>& property, const QString& label, Type type
) :
    PropertyEditorWidget(property),
    m_type{type}
{
    createLayouts(label);
    createLineEdit();
    createTypeSpecificWidgets();
}

StringPropertyEditor::~StringPropertyEditor() = default;

void StringPropertyEditor::createLayouts(const QString& text)
{
    m_layout = new QHBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    QLabel* label = new QLabel(text);
    label->setMinimumWidth(16);

    m_layout->addWidget(label, 1, Qt::AlignRight);

    m_subLayout = new QHBoxLayout;
    m_subLayout->setContentsMargins(0, 0, 0, 0);

    m_layout->addLayout(m_subLayout, 1);
}

void StringPropertyEditor::createLineEdit()
{
    m_lineEdit = new QLineEdit;
    m_lineEdit->setText(QString::fromStdString(observedProperty().get()));
    m_lineEdit->setMinimumWidth(16);

    m_subLayout->addWidget(m_lineEdit);

    connect(m_lineEdit, &QLineEdit::editingFinished, this, &StringPropertyEditor::onEditingFinished);
}

void StringPropertyEditor::createTypeSpecificWidgets()
{
    if (hasBrowseButton())
    {
        m_browse = new QPushButton("Browse");
        m_browse->setMinimumWidth(16);

        m_subLayout->addWidget(m_browse);

        connect(m_browse, &QPushButton::clicked, this, &StringPropertyEditor::onBrowseClicked);
    }
}

void StringPropertyEditor::valueUpdated(const std::string& value)
{
    m_lineEdit->setText(QString::fromStdString(value));
}

StringPropertyEditor::Type StringPropertyEditor::type() const
{
    return m_type;
}

void StringPropertyEditor::onEditingFinished()
{
    observedProperty().set(m_lineEdit->text().toStdString());
}

void StringPropertyEditor::onBrowseClicked()
{
    QFileDialog dialog(MainWindow::instance(), tr("Browse"));

    QFileInfo info(m_lineEdit->text());
    if (info.exists())
    {
        dialog.setDirectory(info.absoluteDir());
    }

    if (m_type == Type::FilePath)
    {
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setLabelText(QFileDialog::Accept, tr("Select"));
    }
    else if (m_type == Type::DirPath)
    {
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly, true);
    }

    if (dialog.exec())
    {
        observedProperty().set(dialog.selectedFiles().at(0).toStdString());
    }
}

bool StringPropertyEditor::hasBrowseButton() const
{
    return m_type == Type::FilePath || m_type == Type::DirPath;
}


/////////////////////////////////////
////// PropertyEditorSeparator //////

PropertyEditorSeparator::PropertyEditorSeparator(QWidget* parent) : QFrame(parent)
{
    setFrameStyle(QFrame::HLine);
    setMinimumHeight(24);
}

PropertyEditorSeparator::~PropertyEditorSeparator() = default;
