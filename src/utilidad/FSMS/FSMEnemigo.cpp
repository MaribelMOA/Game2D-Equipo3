#include "FSMEnemigo.hpp"
#include "../Func_aux.hpp"
#include "../Estructuras.hpp"
#include <iostream>
#include <cmath>


EstadoEnemigoMover::EstadoEnemigoMover(Coordenadas dir)
{
    frames_actual_ani=0;
    frames_maxim_ani=5;
    direccion = dir;
    strestado = "mover";
      contador = 0;
    current_tiempo = 0.0;
    idle_tiempo = 5;  // 10 segundos de tiempo de espera
};

FSMEnemigo* EstadoEnemigoMover::input_handle(Enemigo &en, KeyOyente &keys, MouseOyente& mouse)
{
    
    if(en.lock==1 && en.start==true && en.get_muerto()==false)
    {
        en.set_estado(new EstadoEnemigoTransicion());
    }else return new EstadoEnemigoMover({0,0});
};

void EstadoEnemigoMover::on_entrar(Enemigo &en)
{
    //Alumnos implementa
    vel = en.velocidad;
    frames_actual_ani=0;
    frames_maxim_ani=5;
      contador = 0;
    current_tiempo = Tiempo::get_tiempo();
    
};
void EstadoEnemigoMover::on_salir(Enemigo &en)
{
    //Alumnos implementa
};
void EstadoEnemigoMover::on_update(Enemigo &en, double dt)
{
     if(en.lock==1 && en.start==true && en.get_muerto()==false)
    {
        double elapsed_tiempo = Tiempo::get_tiempo() - current_tiempo;
        if (elapsed_tiempo > idle_tiempo && en.get_muerto()==false) {
            // El tiempo de espera ha excedido, transicionar al estado de transición
            en.set_estado(new EstadoEnemigoTransicion());
        }
    }
    en.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
   
};

// Implementación de EstadoEnemigoTransicion
EstadoEnemigoTransicion::EstadoEnemigoTransicion() {
    // Inicializar variables del estado de transición
    check = {0, 0};
   /* ant_check = {0, 0};
    centro = {0, 0};
    distancia = 10.0;*/
    
    frames_actual =0;
    frames_maximo = 100;
    frames_actual_ani=0;
    frames_maxim_ani=5;
    strestado = "TRANSICION";
}

FSMEnemigo* EstadoEnemigoTransicion::input_handle(Enemigo& en, KeyOyente& keys, MouseOyente& mouse) {
    // No hay transiciones en el estado de transición
    if(!en.lock){
        return new EstadoEnemigoMover({0,0});
    }


    return NULL;
}

void EstadoEnemigoTransicion::on_entrar(Enemigo& en) {
    // Calcular el centro y la distancia al objeto a seguir
 
    en.en_transicion = 1;

    vel = en.velocidad;
    frames_actual_ani=0;
    frames_maxim_ani=5;
    float lim = en.get_obj_lock()->get_avatar()->get_vertices()[3].x - en.get_obj_lock()->get_avatar()->get_vertices()[0].x;
    if(distancia<lim)
    {
        //std::cout<<"LIM "<<lim<<"\n";
        frames_maximo = 10;
    }
}

void EstadoEnemigoTransicion::on_salir(Enemigo& en) {
    // No se realiza ninguna acción al salir del estado de transición
    en.en_transicion = 0;
}

void EstadoEnemigoTransicion::on_update(Enemigo& en, double dt) {
      // printf(  "Enemigo en transicion\n");
    if(frames_actual>frames_maximo)
        return;
    pos_inicial = en.get_posicion_mundo();//(0,0) 

    //seguro decir que este estado siempre entra en lock object
    // no es necesario comprobar que lock object no es nulo
    pos_final = en.get_obj_lock()->get_posicion_mundo(); //o.x,o.y
    float t = frames_actual/(float)frames_maximo;
    check= LERP(pos_inicial,pos_final,t);
    //la diferencia es cuantos pixeles avanza por frame
    ant_check.x = check.x-ant_check.x;
    ant_check.y = check.y-ant_check.y;

    Coordenadas objpos = en.get_obj_lock()->get_posicion_mundo();

    distancia = std::sqrt(std::pow(centro.x-objpos.x,2)+std::pow(centro.y-objpos.y,2));
    //std::cout<<"Distancia > "<<distancia<<"\n";

   // en.set_posicion_mundo(ant_check);
   // printf("Enemigo en transicion\n");
   printf("Check: %d,%d\n",check.x,check.y);
   printf("Pos final: %d,%d\n",pos_final.x,pos_final.y);
    en.set_posicion_mundo(check);
    // if(check.x==pos_final.x && check.y==pos_final.y && en.get_muerto()==false)
     //if(distancia<10 && en.get_muerto()==false)
     if(check.x==pos_final.x && check.y==pos_final.y && en.get_muerto()==false)
         en.set_estado(new EstadoEnemigoAttack(*en.get_obj_lock()));
    //if(cam.get_monstruo()->get_muerto()==false) cam.get_monstruo()->set_posicion_mundo(temp);
    frames_actual++;
    //DEBUGLINEA(check,pos_final)
    //DEBUGCOOR(ant_check);

    //guardamos la posición anterior
    ant_check = check;

    en.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}

// Implementación de EstadoEnemigoAttack
EstadoEnemigoAttack::EstadoEnemigoAttack(Objeto& objlock) : obj(&objlock), locked(false) {
    // Inicializar variables del estado de ataque
   // centro = {0, 0};
    strestado = "ATTACK";
    obj = &objlock;
     frames_actual_ani=0;
    frames_maxim_ani=5;
     contador = 0;
    current_tiempo = 0.0;
    idle_tiempo = 3;  // 10 segundos de tiempo de espera
}

FSMEnemigo* EstadoEnemigoAttack::input_handle(Enemigo& en, KeyOyente& keys, MouseOyente& mouse) {
    // No hay transiciones en el estado de ataque
    if(!en.lock || en.get_muerto()==true)
   
    {
        return new EstadoEnemigoMover({0,0});
    }

    return NULL;
}

void EstadoEnemigoAttack::on_entrar(Enemigo& en) {
    // Guardar la posición del objeto a seguir y establecer la bandera de bloqueo en verdadero
    centro = en.get_posicion_mundo();
    frames_actual_ani=0;
    frames_maxim_ani=5;
         contador = 0;
    current_tiempo = Tiempo::get_tiempo();
}

void EstadoEnemigoAttack::on_salir(Enemigo& en) {
    // No se realiza ninguna acción al salir del estado de ataque
    
}

void EstadoEnemigoAttack::on_update(Enemigo& en, double dt) {
    // Verificar si el objeto a seguir sigue existiendo
    printf("Enemigo en ataque\n");
     double elapsed_tiempo = Tiempo::get_tiempo() - current_tiempo;
    if (elapsed_tiempo > idle_tiempo && en.get_muerto()==false) {
        // El tiempo de espera ha excedido, transicionar al estado de transición
        en.set_estado(new EstadoEnemigoTransicion());
    }
   /* Coordenadas pos_mundo = obj->get_posicion_mundo();
    pos_mundo.x -= centro.x;
    pos_mundo.y -= centro.y;
    en.set_posicion_mundo(pos_mundo);*/
    en.get_sprite()->play_frame(2,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
}
