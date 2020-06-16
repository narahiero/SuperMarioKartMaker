//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "Common/Observable.hpp"

Observable::Observable() :
    m_observers{}
{

}

Observable::~Observable() = default;

void Observable::addObserver(Observer* o)
{
    if (o != nullptr)
    {
        m_observers.push_back(o);
    }
}

void Observable::removeObserver(Observer* o)
{
    for (size_t i = 0; i < m_observers.size(); ++i)
    {
        if (m_observers[i] == o)
        {
            m_observers.erase(m_observers.begin() + i);
            --i;
        }
    }
}

void Observable::notifyAll()
{
    for (Observer* o : m_observers)
    {
        o->updated(this);
    }
}
