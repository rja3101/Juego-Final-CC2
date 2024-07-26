#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void update() = 0; // Metodo puro virtual para ser implementado por los observadores
};

#endif // OBSERVER_H
