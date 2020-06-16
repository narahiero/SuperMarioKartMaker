//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <QScrollArea>

#include "Common/Property.hpp"

class QVBoxLayout;

class PropertyEditorPane final : public QScrollArea
{
    Q_OBJECT

public:

    explicit PropertyEditorPane(QWidget* parent = nullptr);
    ~PropertyEditorPane();

    // add properties

    void addIntProperty(
        const QString& label, Property<int>& property, int min = INT_MIN, int max = INT_MAX,
        int step = 1, const QString& prefix = QString(), const QString& suffix = QString()
    );
    void addShortProperty(
        const QString& label, Property<short>& property, short min = SHRT_MIN, short max = SHRT_MAX,
        short step = 1, const QString& prefix = QString(), const QString& suffix = QString()
    );

    void addDoubleProperty(
        const QString& label, Property<double>& property, double min = -DBL_MAX, double max = DBL_MAX,
        double step = 1.0, const QString& prefix = QString(), const QString& suffix = QString()
    );
    void addFloatProperty(
        const QString& label, Property<float>& property, float min = -FLT_MAX, float max = FLT_MAX,
        float step = 1.f, const QString& prefix = QString(), const QString& suffix = QString()
    );

    void addBoolProperty(const QString& label, Property<bool>& property);

    void addStringProperty(const QString& label, Property<std::string>& property);
    void addFilePathProperty(const QString& label, Property<std::string>& property, bool dir = false);

    // misc controls

    void addSpacing();
    void addSeparator();

private:

    // initializers

    void createWidget();
    void createLayout();

    // fields

    QWidget* m_widget;
    QVBoxLayout* m_layout;
};
