//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/Wizard/SMKM/ProjectWizard.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "Core/Core.hpp"
#include "Core/Project.hpp"

ProjectWizard::ProjectWizard(QWidget* parent) : AbstractWizard(parent)
{
    setWindowTitle("Project Wizard");
    resize(480, 360);

    setPage(Main, new MainPage);

    setStartId(Main);

    setRetVal(Cancelled);
}

ProjectWizard::~ProjectWizard() = default;

void ProjectWizard::finished()
{
    Core::setActiveProject(std::make_shared<Project>(field("name").toString().toStdString()));

    setRetVal(Created);
}

////// MainPage class //////////////////

ProjectWizard::MainPage::MainPage(QWidget* parent) : AbstractWizardPage(parent)
{
    QGridLayout* layout = new QGridLayout;

    QLabel* projectNameL = new QLabel(tr("Project name"));
    QLineEdit* projectName = new QLineEdit;
    layout->addWidget(projectNameL, 0, 0, Qt::AlignRight);
    layout->addWidget(projectName, 0, 1);

    setLayout(layout);

    registerField("name", projectName, true);
}

ProjectWizard::MainPage::~MainPage() = default;

bool ProjectWizard::MainPage::finalPage() const
{
    return true;
}
