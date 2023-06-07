#include "FSMCamaras.hpp"
#include "../Func_aux.hpp"
#include <iostream>
#include <cmath>

EstadoCamaraMover::EstadoCamaraMover(Coordenadas dir)
{
    direccion = dir;
    strestado = "mover";
};

FSMCamara* EstadoCamaraMover::input_handle(Camara &cam, KeyOyente &keys, MouseOyente& mouse)
{
    if(cam.lock)
    {
        return new EstadoCamaraTransicion();
    }else
        return new EstadoCamaraMover({0,0});
};

void EstadoCamaraMover::on_entrar(Camara &cam){
    vel = cam.velocidad;
};
void EstadoCamaraMover::on_salir(Camara &cam){};
void EstadoCamaraMover::on_update(Camara &cam)
{
    Coordenadas p=cam.get_posicion_mundo();
    p.x =(int)(vel*direccion.x);
    p.y =(int)(vel*direccion.y);
    cam.set_posicion_mundo(p);
};

/*
TRANSICIÓN
*/
EstadoCamaraTransicion::EstadoCamaraTransicion()
{
    frames_actual =0;
    frames_maximo = 45;
    strestado = "transicion";
};

FSMCamara* EstadoCamaraTransicion::input_handle(Camara &cam, KeyOyente &keys, MouseOyente& mouse)
{
    if(!cam.lock){
        return new EstadoCamaraMover({0,0});
    }else if(frames_actual>frames_maximo)
    {
        if(distancia<10)
        {
            return new EstadoCamaraLock(*cam.get_obj_lock());
        }
        return new EstadoCamaraTransicion();
    }
    return NULL;
};

void EstadoCamaraTransicion::on_entrar(Camara &cam)
{
    cam.en_transicion = 1;
    vel = cam.velocidad;
    pos_inicial = cam.get_posicion_mundo();//(0,0) 

    //seguro decir que este estado siempre entra en lock object
    // no es necesario comprobar que lock object no es nulo
    pos_final = cam.get_obj_lock()->get_posicion_mundo(); //o.x,o.y
    
    //convertir en posicion relativo a las coordenads camara
    centro = cam.get_posicion_centro();
    pos_final.x -= centro.x;
    pos_final.y -= centro.y;

    //la diferencia es la cantidad de pixeles que se mueve
    ant_check={0,0};
    //checkar la distancia es pequeña para ajustar los frames
    distancia = std::sqrt(std::pow(centro.x-(pos_final.x+centro.x),2)+std::pow(centro.y-(pos_final.y+centro.y),2));
    //std::cout<<"Distancia > "<<distancia<<"\n";
    float lim = cam.get_obj_lock()->get_avatar()->get_vertices()[3].x - cam.get_obj_lock()->get_avatar()->get_vertices()[0].x;
    if(distancia<lim){
        frames_maximo = 10;
    }
};
void EstadoCamaraTransicion::on_salir(Camara &cam){
    cam.en_transicion=0;
};
void EstadoCamaraTransicion::on_update(Camara &cam)
{
    if(frames_actual>frames_maximo)
        return;

    float t = frames_actual/(float)frames_maximo;
    check= LERP(pos_inicial,pos_final,t);
    //la diferencia es cuantos pixeles avanza por frame
    ant_check.x = check.x-ant_check.x;
    ant_check.y = check.y-ant_check.y;

    Coordenadas objpos = cam.get_obj_lock()->get_posicion_mundo();

    distancia = std::sqrt(std::pow(centro.x-objpos.x,2)+std::pow(centro.y-objpos.y,2));

    cam.set_posicion_mundo(ant_check);
    frames_actual++;
    ant_check = check;
};
/*
LOCK
*/
EstadoCamaraLock::EstadoCamaraLock(Objeto &objlock)
{
    strestado = "lock";
    obj = &objlock;
};

FSMCamara* EstadoCamaraLock::input_handle(Camara &cam, KeyOyente &keys, MouseOyente& mouse)
{   
    if(!cam.lock){
        return new EstadoCamaraMover({0,0});
    }
    return NULL;
};
void EstadoCamaraLock::on_entrar(Camara &cam)
{
    centro = cam.get_posicion_centro();
};
void EstadoCamaraLock::on_salir(Camara &cam){};
void EstadoCamaraLock::on_update(Camara &cam){
    // simplemente la camara obtiene la posición del obj
    Coordenadas pos_mundo = obj->get_posicion_mundo();
    pos_mundo.x -= centro.x;
    pos_mundo.y -= centro.y;
    cam.set_posicion_mundo(pos_mundo);
};