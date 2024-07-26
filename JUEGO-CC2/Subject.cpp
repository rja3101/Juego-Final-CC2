#include "Subject.h"
#include <algorithm>

void Subject::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update(); // Suponiendo que el método update() es el que deben llamar los observadores
    }
}
