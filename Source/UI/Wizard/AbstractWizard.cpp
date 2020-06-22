//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Wizard/AbstractWizard.hpp"

#include <QBoxLayout>
#include <QPushButton>

#include "UI/Wizard/Private/AbstractWizardField.hpp"

AbstractWizard::AbstractWizard(QWidget* parent) : QDialog(parent),
    m_startId{-1},
    m_curr{nullptr}
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setMinimumSize(400, 240);

    createLayout();
    createButtons();
}

AbstractWizard::~AbstractWizard() = default;

void AbstractWizard::createLayout()
{
    m_layout = new QVBoxLayout;
    setLayout(m_layout);
}

void AbstractWizard::createButtons()
{
    m_nextButton = new QPushButton(tr("&Next"));
    m_backButton = new QPushButton(tr("&Back"));
    m_cancelButton = new QPushButton(tr("&Cancel"));

    m_nextButton->setDefault(true);

    m_buttonLayout = new QHBoxLayout;
    m_buttonLayout->setAlignment(Qt::AlignRight);

    m_buttonLayout->addWidget(m_backButton);
    m_buttonLayout->addWidget(m_nextButton);
    m_buttonLayout->addSpacerItem(new QSpacerItem(8, 0));
    m_buttonLayout->addWidget(m_cancelButton);

    m_layout->addLayout(m_buttonLayout);

    connect(m_nextButton, &QPushButton::clicked, this, &AbstractWizard::nextPage);
    connect(m_backButton, &QPushButton::clicked, this, &AbstractWizard::prevPage);
    connect(m_cancelButton, &QPushButton::clicked, this, &AbstractWizard::close);
}

int AbstractWizard::run()
{
    Q_ASSERT(m_startId >= 0);

    m_curr = m_pages[m_startId];
    m_layout->insertWidget(0, m_curr, 1);

    m_backButton->setDisabled(true);

    if (m_curr->finalPage())
    {
        m_nextButton->setText(tr("&Finish"));
    }
    m_nextButton->setEnabled(m_curr->isComplete());

    return exec();
}

void AbstractWizard::setPage(int id, AbstractWizardPage* page)
{
    Q_ASSERT(id >= 0);
    Q_ASSERT(page != nullptr);
    Q_ASSERT(!m_pages.contains(id));

    m_pages.insert(id, page);
    page->addedAsPage(this, id);

    connect(page, &AbstractWizardPage::completeChanged, this, &AbstractWizard::onCompleteChanged);
}

void AbstractWizard::finished()
{

}

AbstractWizardPage* AbstractWizard::page(int id) const
{
    return m_pages.value(id, nullptr);
}

void AbstractWizard::setStartId(int id)
{
    Q_ASSERT(m_pages.contains(id));

    m_startId = id;
}

int AbstractWizard::startId() const
{
    return m_startId;
}

QVariant AbstractWizard::field(const QString& name) const
{
    Q_ASSERT(m_fields.contains(name));
    return m_fields[name]->value();
}

void AbstractWizard::setRetVal(int retVal)
{
    m_retVal = retVal;
}

int AbstractWizard::retVal() const
{
    return m_retVal;
}

void AbstractWizard::nextPage()
{
    Q_ASSERT(m_curr != nullptr);

    if (m_curr->finalPage())
    {
        finished();
        done(m_retVal);
    }
    else
    {
        Q_ASSERT(m_pages.contains(m_curr->nextId()));

        AbstractWizardPage* old = m_curr;

        m_idStack.push(m_curr->id());
        m_curr = m_pages[m_curr->nextId()];

        m_layout->replaceWidget(old, m_curr);

        if (m_curr->finalPage())
        {
            m_nextButton->setText(tr("&Finish"));
        }
        m_nextButton->setEnabled(m_curr->isComplete());
    }
}

void AbstractWizard::prevPage()
{
    Q_ASSERT(!m_idStack.empty());

    m_curr = m_pages[m_idStack.pop()];

    if (m_idStack.empty())
    {
        m_backButton->setDisabled(true);
    }
}

void AbstractWizard::onCompleteChanged(bool isComplete)
{
    m_nextButton->setEnabled(isComplete);
}

void AbstractWizard::registerField(const QString& name, AbstractWizardField* field)
{
    Q_ASSERT(!m_fields.contains(name));
    m_fields.insert(name, field);
}

/// AbstractWizardPage class ///////////

AbstractWizardPage::AbstractWizardPage(QWidget* parent) : QWidget(parent),
    m_id{-1},
    m_isComplete{true}
{

}

AbstractWizardPage::~AbstractWizardPage() = default;

void AbstractWizardPage::registerField(const QString& name, QLineEdit* lineEdit, bool required)
{
    AbstractWizardField* field = new AbstractWizardField(this, lineEdit, required);
    m_fields.insert(name, field);

    if (required)
    {
        m_isComplete = m_isComplete && field->isFilled();
    }

    connect(field, &AbstractWizardField::valueChanged, this, &AbstractWizardPage::onFieldValueChanged);
}

int AbstractWizardPage::nextId() const
{
    return m_id + 1;
}

bool AbstractWizardPage::finalPage() const
{
    return true;
}

AbstractWizard* AbstractWizardPage::wizard() const
{
    return m_wizard;
}

int AbstractWizardPage::id() const
{
    return m_id;
}

bool AbstractWizardPage::isComplete() const
{
    return m_isComplete;
}

void AbstractWizardPage::setIsComplete(bool b)
{
    if (m_isComplete != b)
    {
        m_isComplete = b;
        emit completeChanged(m_isComplete);
    }
}

void AbstractWizardPage::addedAsPage(AbstractWizard* wizard, int id)
{
    Q_ASSERT(wizard != nullptr);
    m_wizard = wizard;
    m_id = id;

    for (QString& name : m_fields.keys())
    {
        m_wizard->registerField(name, m_fields[name]);
    }
}

void AbstractWizardPage::onFieldValueChanged(const QVariant&)
{
    for (AbstractWizardField* field : m_fields.values())
    {
        if (field->isRequired() && !field->isFilled())
        {
            setIsComplete(false);
            return;
        }
    }
    setIsComplete(true);
}
