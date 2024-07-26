#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers();

protected:
    std::vector<Observer*> observers;
};

#endif // SUBJECT_H
