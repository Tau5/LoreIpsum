#include "Manager.h"


namespace ecs {

// reserva suficiente (?) memoria para evitar el redimensionamiento
// del vector de entidades
Manager::Manager() : ents_()
{
    ents_.reserve(100);
}

//borra todas las entidades
Manager::~Manager()
{
    for (auto e : ents_) {
        delete e;
    }
}


//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la �ltima iteraci�n
void Manager::refresh()
{
    ents_.erase(
        //Para cada elemento de ents_, remove_if llama a la funci�n
        //(lambda expression) para decider si borrarlo o no, aprovechamos
        //para liberar la memoria tambi�n
        std::remove_if(ents_.begin(), ents_.end(), [this](Entity* e) {
            if (isAlive(e)) {
                return false;
            }
            else {
                delete e;
                return true;
            }
            }),
        ents_.end());
}

}