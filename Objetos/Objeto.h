//
// Created by jeremy on 21/09/24.
//

#ifndef OBJETO_H
#define OBJETO_H


class Objeto
{
public:
    virtual void interaccion() = 0; //Interaccion del objeto
    virtual char* recurso() = 0; //Ruta imagen

};


#endif //OBJETO_H
