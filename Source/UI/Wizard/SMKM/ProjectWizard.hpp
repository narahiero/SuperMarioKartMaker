//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include "UI/Wizard/AbstractWizard.hpp"

class ProjectWizard final : public AbstractWizard
{
    Q_OBJECT

public:

    enum Result
    {
        Cancelled = 0,
        Created = 1
    };

    enum PageId
    {
        Main
    };

    explicit ProjectWizard(QWidget* parent = nullptr);
    ~ProjectWizard();

    // reimplemented functions

    void finished() override;

private:

    class MainPage final : public AbstractWizardPage
    {
    
    public:

        explicit MainPage(QWidget* parent = nullptr);
        ~MainPage();

        // reimplemented functions

        bool finalPage() const;
    };
};
