//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <vector>

class Observable;

class Observer
{

public:

    virtual void updated(Observable* o) = 0;
};

class Observable
{

public:

    Observable();
    virtual ~Observable();

    void addObserver(Observer* o);
    void removeObserver(Observer* o);
    void notifyAll();

private:

    std::vector<Observer*> m_observers;
};
