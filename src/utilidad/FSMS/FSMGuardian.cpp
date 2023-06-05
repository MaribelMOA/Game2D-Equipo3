#include "FSMGuardian.hpp"
#include "../Func_aux.hpp"
#include <iostream>
#include <cmath>


/*
IDLE
*/
EstadoGuardianIDLE::EstadoGuardianIDLE()
{

    //generar un numero rando entre 5 y 15
   // int random = rand() % 10 + 5;
     frames_actual_ani=0;
    frames_maxim_ani=3;
    contador = 0;
    current_tiempo = 0.0;
    idle_tiempo = rand() % 10 + 5;;  // 10 segundos de tiempo de espera
    strestado = "IDLE";
};

FSMGuardian* EstadoGuardianIDLE::input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse)
{

    return NULL;
};
void EstadoGuardianIDLE::on_entrar(Guardian& g)
{
    frames_actual_ani=0;
    frames_maxim_ani=3;
    contador = 0;
    current_tiempo = Tiempo::get_tiempo();
   
};
void EstadoGuardianIDLE::on_salir(Guardian& g)
{

};
void EstadoGuardianIDLE::on_update(Guardian& g,double dt)
{
    contador++;
    double elapsed_tiempo = Tiempo::get_tiempo() - current_tiempo;
    if (elapsed_tiempo > idle_tiempo && g.get_first_time()==1) {
        // El tiempo de espera ha excedido, transicionar al estado de transición
        g.set_estado(new EstadoGuardianTransicion());
    }
    g.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;
    contador++;
   

};

/*
TRANSICIÓN
*/
EstadoGuardianTransicion::EstadoGuardianTransicion()
{
     check = {0, 0};
    ant_check = {0, 0};
    centro = {0, 0};
    distancia = 10.0;
     frames_actual =0;
    frames_maximo = 45;
    frames_actual_ani=0;
    frames_maxim_ani=8;
    strestado = "TRANSICION";
};

FSMGuardian* EstadoGuardianTransicion::input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse)
{


    return NULL;
};

void EstadoGuardianTransicion::on_entrar(Guardian &g)
{
     Objeto* objeto_seguir = g.get_obj_lock();
    if (objeto_seguir) {
        centro = objeto_seguir->get_posicion_mundo();

        int diferenciaX = centro.x - g.get_posicion_mundo().x;
        int diferenciaY = centro.y - g.get_posicion_mundo().y;
        distancia = std::sqrt(diferenciaX * diferenciaX + diferenciaY * diferenciaY);
    }
    //frames para sprite
     frames_actual_ani=0;
    frames_maxim_ani=8;



};
void EstadoGuardianTransicion::on_salir(Guardian &g)
{
    //Alumnos implementa
    g.en_transicion=0;
};
void EstadoGuardianTransicion::on_update(Guardian &g,double dt)
{

    float objetivo_x = g.get_obj_lock()->get_posicion_mundo().x;
    float objetivo_y = g.get_obj_lock()->get_posicion_mundo().y;
    float direccion_x = objetivo_x - g.get_posicion_mundo().x;
    float direccion_y = objetivo_y - g.get_posicion_mundo().y;

    // Calcula la distancia al objetivo
    float distancia = std::sqrt(direccion_x * direccion_x + direccion_y * direccion_y);

    // Normaliza el vector de dirección
    if (distancia > 0) {
        direccion_x /= distancia;
        direccion_y /= distancia;
    }

    // Calcula el desplazamiento en cada eje según la velocidad y el tiempo transcurrido
   // float desplazamiento_x = direccion_x * en.velocidad * dt;
   // float desplazamiento_y = direccion_y * en.velocidad * dt;

    // Calcula el desplazamiento máximo permitido por fotograma
    float max_desplazamiento = g.velocidad * dt;

    // Calcula el desplazamiento en cada eje según el desplazamiento máximo permitido
    float desplazamiento_x = direccion_x * std::min(distancia, max_desplazamiento);
    float desplazamiento_y = direccion_y * std::min(distancia, max_desplazamiento);

    // Actualiza la posición del enemigo
    Coordenadas temp={g.get_posicion_mundo().x + desplazamiento_x, g.get_posicion_mundo().y + desplazamiento_y};
    g.set_posicion_mundo(temp);

    // Verifica si se ha alcanzado la posición objetivo
    if (distancia <= 10) // Puedes ajustar el valor límite según tu necesidad
    {
        // Se ha alcanzado la posición objetivo, cambiar al estado de ataque
        g.set_estado(new EstadoGuardianAttack(*g.get_obj_lock()));
    }else{
        g.set_estado(new EstadoGuardianTransicion());
    }


    g.get_sprite()->play_frame(2,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;

};
/*
LOCK
*/
EstadoGuardianAttack::EstadoGuardianAttack(Objeto &objlock)
{
   centro = {0, 0};
    strestado = "ATTACK";
    obj = &objlock;
     frames_actual_ani=0;
    frames_maxim_ani=8;

};

FSMGuardian* EstadoGuardianAttack::input_handle(Guardian &g, KeyOyente &keys, MouseOyente& mouse)
{   


    return NULL;
};

void EstadoGuardianAttack::on_entrar(Guardian &g)
{
    if (obj) {
        centro = obj->get_posicion_mundo();
        g.lock = true;
           frames_actual_ani=0;
        frames_maxim_ani=8;
    }
    
};
void EstadoGuardianAttack::on_salir(Guardian &g)
{
    //Alumnos implementa
};
void EstadoGuardianAttack::on_update(Guardian &g,double dt)
{
    //Alumnos implementa

     if (obj && g.lock) {
        // Realizar acciones de ataque al objeto
        // Restar HP al objeto, por ejemplo:
        float vida=obj->get_hp();
        obj->set_hp(vida-g.get_ataque());
        // Verificar si el objeto ha sido derrotado
        if (obj->get_hp() <= 0.0) {
            // El objeto ha sido derrotado, transicionar al estado IDLE después de 10 segundos
            printf("El objeto ha sido derrotado\n");
        }
        g.set_estado(new EstadoGuardianIDLE());
        //en.get_estado()->on_entrar(en);  // Reiniciar el estado IDLE
    } 
    g.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }else{
        g.lock = 0;
    }
    frame_dt++;

};