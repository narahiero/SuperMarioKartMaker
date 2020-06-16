//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include "Common/Observable.hpp"

template <class Type>
class Property : public Observable
{

public:

    Property(const Type& value) :
        m_value{value}
    {

    }

    virtual ~Property() = default;

    void set(const Type& value)
    {
        m_value = value;
        notifyAll();
    }

    Type get() const
    {
        return m_value;
    }

private:

    Type m_value;
};

template <class Type>
class PropertyObserver : public Observer
{

public:

    PropertyObserver(Property<Type>& property) :
        m_property{property}
    {
        m_property.addObserver(this);
    }

    virtual ~PropertyObserver()
    {
        m_property.removeObserver(this);
    }

    void updated(Observable* o) final
    {
        if (&m_property == o)
        {
            valueUpdated(static_cast<Property<Type>*>(o)->get());
        }
    }

    virtual void valueUpdated(const Type& value) = 0;

    Property<Type>& observedProperty() const
    {
        return m_property;
    }

private:

    Property<Type>& m_property;
};
