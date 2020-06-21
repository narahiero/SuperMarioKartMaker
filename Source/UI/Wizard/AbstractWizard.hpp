//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QDialog>
#include <QMap>
#include <QStack>

class QCheckBox;
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QVBoxLayout;

class AbstractWizardField;
class AbstractWizardPage;

class AbstractWizard : public QDialog
{
    Q_OBJECT

    friend class AbstractWizardPage;

public:

    explicit AbstractWizard(QWidget* parent = nullptr);
    ~AbstractWizard();

    // use this instead of exec()
    void run();

    void setPage(int id, AbstractWizardPage* page);

    // reimplementable functions

    virtual void finished();

    // field getters/setters

    AbstractWizardPage* page(int id) const;

    void setStartId(int id);
    int startId() const;

    QVariant field(const QString& name) const;

private:

    // initializers

    void createLayout();
    void createButtons();

    // slots

    void nextPage();
    void prevPage();

    void onCompleteChanged(bool isComplete);

    // functions for AbstractWizardPage

    void registerField(const QString& name, AbstractWizardField* field);

    // fields

    QMap<int, AbstractWizardPage*> m_pages;
    int m_startId;

    AbstractWizardPage* m_curr;
    QStack<int> m_idStack;

    QMap<QString, AbstractWizardField*> m_fields;

    QVBoxLayout* m_layout;

    QHBoxLayout* m_buttonLayout;
    QPushButton* m_nextButton;
    QPushButton* m_backButton;
    QPushButton* m_cancelButton;
};

class AbstractWizardPage : public QWidget
{
    Q_OBJECT

    friend class AbstractWizard;

public:

    explicit AbstractWizardPage(QWidget* parent = nullptr);
    ~AbstractWizardPage();

    void registerField(const QString& name, QLineEdit* lineEdit, bool required = false);
    void registerField(const QString& name, QCheckBox* checkBox, bool required = false);

    // reimplementable functions

    virtual int nextId() const;
    virtual bool finalPage() const;

    // field getters/setters

    AbstractWizard* wizard() const;

    int id() const;

    bool isComplete() const;

signals:

    void completeChanged(bool isComplete);

private:

    void setIsComplete(bool b);

    // slots

    void onFieldValueChanged(const QVariant&);

    // functions for AbstractWizard

    void addedAsPage(AbstractWizard* wizard, int id);

    // fields

    AbstractWizard* m_wizard;
    int m_id;

    QMap<QString, AbstractWizardField*> m_fields;
    bool m_isComplete;
};
