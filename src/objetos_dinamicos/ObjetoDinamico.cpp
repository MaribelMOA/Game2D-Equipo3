#include "ObjetoDinamico.hpp"
#include "../objetos/Figuras.hpp"

Jugador::Jugador(float vida, int x, int y , SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c); 
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoJugadorIDLE();
    piso = {500,500}; // definir el piso en general
};

Jugador::Jugador(std::string path_sprite,float vida, int atk,int x, int y, int w, int h, int sw, int sh, SDL_Color c)
:ObjetoDinamico{}
{
     hp = vida;
    ataque = atk;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoJugadorIDLE();
    piso = {500,500}; // definir el piso en general
    velocidad = 100;
    gemas=0;
    plantas=10;
    sprite = new Sprite(path_sprite,posicion_mundo,w,h,sw,sh);

    game_over = false;
};


std::string Jugador::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Jugador::get_estado()
{
    return estado_actual;
};

void Jugador::set_estado(void* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = (FSMJugador*)estado;
    estado_actual->entrar(*this);
};

void Jugador::update(double dt)
{
    if(game_over==false){
         if(!estado_actual) //nulo
            return;
        checar_colisiones();
        if(en_colision){
            avatar->set_rellenocolor({255,0,0,255});
            
        } 
        else
            avatar->set_rellenocolor(color);

        estado_actual->update(*this,dt);
        
        //reset
        en_colision=false;
    }

   


};

void Jugador::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMJugador* estado = estado_actual->input_handle(*this, input,mouse);
    if(estado)
    {
        set_estado(estado);
    }
};

void Jugador::checar_colisiones()
{
     // MotorFisico2D::get().sat_colision(*this,colisionables);
     if(colision_gemas==true)
     {
         gemas++;
        // printf("gemas: %d\n",gemas);
         colision_gemas=false;
     }
    if(colision_plantas==true)
    {
        plantas++;
       // printf("plantas: %d\n",plantas);
        colision_plantas=false;
    }
    
    
};

Enemigo::Enemigo(float vida, int x, int y , SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c); 
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoTransicion();
    piso = {500,500}; // definir el piso en general
};

Enemigo::Enemigo(std::string path_sprite,float vida, int atk,int x, int y, int w, int h, int sw, int sh, SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    ataque = atk;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoMover({0,0});
    piso = {500,500}; // definir el piso en general
  
    muerto=false;
    start=false;
    game_over = false;


    velocidad=5.f;

    sprite = new Sprite(path_sprite,posicion_mundo,w,h,sw,sh);
};
Enemigo::Enemigo(std::string path_sprite,float vida, int atk,int x, int y, int w, int h, int sw, int sh, SDL_Color c, Jugador* jugador)
:ObjetoDinamico{}
{
    hp = vida;
    ataque = atk;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoMover({0,0});
    piso = {500,500}; // definir el piso en general
    objeto_seguir = jugador;
    jugador_seguir = jugador;
    muerto=false;
    start=false;

    lock_objeto(*jugador);
    game_over = false;


    velocidad=5.f;

    sprite = new Sprite(path_sprite,posicion_mundo,w,h,sw,sh);
};


std::string Enemigo::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Enemigo::get_estado()
{
    return estado_actual;
};

void Enemigo::set_estado(void* estado)
{
    estado_actual->on_salir(*this);
    delete estado_actual;
    estado_actual = (FSMEnemigo*)estado;
    estado_actual->on_entrar(*this);
};

void Enemigo::update(double dt)
{
    if(game_over==false){
          if(!estado_actual) //nulo
            return;
        //checar_colisiones();
        if(en_colision){
            
            avatar->set_rellenocolor({255,0,0,255});
            
        } 
        else
            avatar->set_rellenocolor(color);

        estado_actual->on_update(*this,dt);
        
        //reset
        en_colision=false;
    }
  


};

void Enemigo::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMEnemigo* estado = estado_actual->input_handle(*this,input,mouse);
    if(estado)
    {
        estado_actual->on_salir(*this);
        delete estado_actual;
        estado_actual = estado;
        estado_actual->on_entrar(*this);
    }
};

void Enemigo::lock_objeto(Objeto &obj)
{
    //Alumnos implementarla
    objeto_seguir = &obj;
    lock =1;
    
};

void Enemigo::unluck_objeto()
{
    //Alumnos implementarla
    objeto_seguir = nullptr;
    lock=0;
};
/*Guardian*/
Guardian::Guardian(float vida, int x, int y , SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c); 
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoGuardianIDLE();
    piso = {500,500}; // definir el piso en general
};

Guardian::Guardian(std::string path_sprite,float vida, int atk,int x, int y, int w, int h, int sw, int sh, SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    ataque = atk;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoGuardianIDLE();
    piso = {500,500}; // definir el piso en general

    velocidad=5;
    first_time=0;
    game_over = false;

    sprite = new Sprite(path_sprite,posicion_mundo,w,h,sw,sh);
};


std::string Guardian::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Guardian::get_estado()
{
    return estado_actual;
};

void Guardian::set_estado(void* estado)
{
    estado_actual->on_salir(*this);
    delete estado_actual;
    estado_actual = (FSMGuardian*)estado;
    estado_actual->on_entrar(*this);
};

void Guardian::update(double dt)
{
    if(game_over==false){
        if(!estado_actual) //nulo
        return;
  
        //checar_colisiones();
        if(en_colision){
            
            avatar->set_rellenocolor({255,0,0,255});
            
        } 
        else
            avatar->set_rellenocolor(color);

        estado_actual->on_update(*this,dt);
        
        //reset
        en_colision=false;
    }
    


};

void Guardian::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMGuardian* estado = estado_actual->input_handle(*this,input,mouse);
    if(estado)
    {
        estado_actual->on_salir(*this);
        delete estado_actual;
        estado_actual = estado;
        estado_actual->on_entrar(*this);
    }
};

void Guardian::lock_objeto(Objeto &obj)
{
    //Alumnos implementarla
    objeto_seguir = &obj;
    lock =1;
    
};

void Guardian::unluck_objeto()
{
    //Alumnos implementarla
    objeto_seguir = nullptr;
    lock=0;
};