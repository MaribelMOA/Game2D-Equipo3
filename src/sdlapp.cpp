#include "sdlapp.hpp"
#include "utilidad/Tiempo.hpp"
#include "motor/KeyOyente.hpp"
#include "motor/MouseOyente.hpp"
#include <SDL_ttf.h>
#include "utilidad/RenderTexto.hpp"
#include "motor/fisica/MotorFisico.hpp"
#include "utilidad/Func_aux.hpp"
#include <cmath>

//#define RECTANGULOS
//#define TRIANGULOS
//#define CIRCULOS
#define GEMAS 1
#define PLANTAS 2
#define ARTEFACTO 3
#define ATTACK_ZONE 4
#define PISO 5
#define MURO 6

SDLApp* SDLApp::instancia = 0;

SDLApp::SDLApp()
{
    vnt = nullptr;
    vntsurf = nullptr;
    render = nullptr;
    ensamble= nullptr;
    bg_color.r = 255; //rojo
    bg_color.g = 255; //verde
    bg_color.b = 255; //azul
    bg_color.a = 255; //alpha

    esta_corriendo = true;
    WIDTH=1024;
    HEIGHT=720;
    maxFPS=60;
    fps=0;

    
};

//Como solo queremos una instancia del esta clase, entonces se hace una clase singleton
SDLApp& SDLApp::get()
{
    if(!instancia)
        instancia = new SDLApp();
    return *instancia;
};

bool SDLApp::on_init()
{
    //revisar que SDL inicio bien
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){return false;};
    //crear la ventana
    get().vnt = SDL_CreateWindow(
        "Juego",                // Titulo de la ventana
        SDL_WINDOWPOS_UNDEFINED,// posicion X de la pantalla
        SDL_WINDOWPOS_UNDEFINED,// posicion Y de la pantalla
        get().WIDTH,            // ancho de la ventana
        get().HEIGHT,           // alto de la ventana
        SDL_WINDOW_OPENGL);     // que use OPENGL
    
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    //revisar que se creo bien la ventana
    if(get().vnt == NULL)
    {
        printf("No se creo la ventana por: %s",SDL_GetError());
        return false;
    }
    //la forma de procesar en GPU
    SDL_SetHint(SDL_HINT_RENDER_BATCHING,"opengl");
    //creamos el 'canvas'
    get().render = SDL_CreateRenderer(
        get().vnt,                  // la ventana
        -1,                         // driver
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  // flags driver
    //revisamos si se creo correctamente
    if(get().render == NULL)
    {
        printf("No se creo el renderer por: %s",SDL_GetError());
        return false; 
    }
    // si se creo correcto lo agregamos al Pipeline

    get().ensamble = new Pipeline(*get().render);
       // guardarMapa("assets/sprites/mundo/ids/FinalAtlas_ids.txt");

       //
       current_tiempo = Tiempo::get_tiempo();
       idle_tiempo=10;
  //08 tiles
    mapa = new Atlas("assets/sprites/mundo/ids/FinalAtlas_ids.txt");
    mapa->generar_mapa(get().render,2,0);
    posicionesPiso=mapa->get_posicionesPiso();
    atack_on = false;
    start = false;
    game_over=false;
    //03
    
    //07
   //generar 3 posisciones random no rpetidas de posicionesPiso
   Coordenadas posJugador, posEnemigo, posGuardian;
    int random1, random2, random3;
    random1 = rand() % posicionesPiso.size();
    random2 = rand() % posicionesPiso.size();
    random3 = rand() % posicionesPiso.size();
    while(random1 == random2 || random1 == random3 || random2 == random3)
    {
        random1 = rand() % posicionesPiso.size();
        random2 = rand() % posicionesPiso.size();
        random3 = rand() % posicionesPiso.size();
    }
    posJugador = posicionesPiso[random1];
    posEnemigo = posicionesPiso[random2];
    posGuardian = posicionesPiso[random3];

    //07 Generar Jugador
    player = new Jugador("assets/sprites/heroe/myHero.png",100,3,posJugador.x,posJugador.y,135,93,100,70,{255,0,255,255});
            //80,1,300,400,135,93,100,70,{255,0,255,255});
   get().ensamble->cargar_texturas(player->get_sprite());
   player->set_plantas(10);

    //Generar Enemigo
   // enemigo=new Enemigo("assets/sprites/heroe/monster.png",80,1,posEnemigo.x,posEnemigo.y,100,87,100,100,{255,0,255,255},player);//80,1,300,300,100,87,100,100,{255,0,255,255}, player);
 enemigo=new Enemigo("assets/sprites/heroe/monster.png",50,1,posEnemigo.x,posEnemigo.y,100,87,100,100,{255,0,255,255});//80,1,300,300,100,87,100,100,{255,0,255,255}, player);
    
  //Generar Guardian
   guardian=new Guardian("assets/sprites/heroe/buho3.png",15,1,posGuardian.x,posGuardian.y,60,50,100,100,{255,0,255,255});
   get().ensamble->cargar_texturas(enemigo->get_sprite());
    get().ensamble->cargar_texturas(guardian->get_sprite());

    //PINTAR GEMAS, plantas, artefacto y atacckzones
    plataformas = mapa->get_objetos_fisicos();
    allTiles.push_back(mapa->get_tileGema());
    allTiles.push_back(mapa->get_tilePlanta());
    allTiles.push_back(mapa->get_tileArtefacto());
    allTiles.push_back(mapa->get_tileBlanco());
    allTiles.push_back(mapa->get_tilein());
    for(auto &p:plataformas){
        int id = p->get_ID();
         if(id==ARTEFACTO && guardian->get_first_time()==0){
            p->set_tile(new Tile(allTiles[PISO-1]));
            p->set_ID(PISO);
        }
    }




    int numGemas = 0,numPlantas = 0,numBlancos=0;
    bool existeArtefacto = false;
    for(auto &p:plataformas){
        int id = p->get_ID();
      
        if(id==PISO && rand()%100<50){
            //HAY UN 20 PORCIETNO DE PROB DE QUE HAYA UNA GEMA
            if(rand()%100<5 && numGemas<=30){
                p->set_tile(new Tile(allTiles[GEMAS-1]));
                p->set_ID(GEMAS);
                numGemas++;
            } 
            if(rand()%100<5 && numPlantas<=30){
                p->set_tile(new Tile(allTiles[PLANTAS-1]));
                p->set_ID(PLANTAS);
                numPlantas++;
            }
            //HAY UN 20 PORCIETNO DE PROB DE QUE HAYA UN ARTEFACTO
            if(rand()%100<5 && existeArtefacto==false){
                p->set_tile(new Tile(allTiles[ARTEFACTO-1]));
                p->set_ID(ARTEFACTO);
                existeArtefacto=true;
            } //HAY UN 20 PORCIETNO DE PROB DE QUE HAYA UN BLANCO
            if(rand()%100<5 && numBlancos<10){
                p->set_tile(new Tile(allTiles[ATTACK_ZONE-1]));
                p->set_ID(ATTACK_ZONE);
                numBlancos++;
            }
            
        }
    }

    
 
    // muros=mapa->get_plataformas();
   
    /*tilein = mapa->get_tilein();
    tileArtefacto = mapa->get_tileArtefacto();
    tileBlanco = mapa->get_tileBlanco();*/
  
    //06_Camaras

    get().camara_principal = new Camara(0,0,get().WIDTH,get().HEIGHT,*get().render);
    //get().camara_principal = new Camara(0,0,get().WIDTH,get().HEIGHT,enemigo,*get().render);
     //camara_principal->lock_objeto(*player);

    for(int i=0;i<plataformas.size();i++)
    {
        //agregar todos los objetos en una lista para la camara
        objetos.push_back(plataformas[i]);
    }
  

    
    
    objetos.push_back(player);
    objetos.push_back(enemigo);
    objetos.push_back(guardian);
    //Crear una plataforma ne medio de la pantalla

    
    printf("Se crearon los test exitosamente\n");

    //agregamos el color del background del frame
    SDL_SetRenderDrawColor(
        get().render,       // canvas
        get().bg_color.r,   // rojo
        get().bg_color.g,   // verde
        get().bg_color.b,   // azul
        SDL_ALPHA_TRANSPARENT);// como usar el alpha

    return true;
};

void SDLApp::on_evento(SDL_Event* evento)
{
    if(evento->type==SDL_QUIT)
    {
        get().esta_corriendo = false;
    }
    //eventos del mouse
    MouseOyente::get().evento_movimiento(evento);
    MouseOyente::get().evento_presionado(evento);
    MouseOyente::get().evento_scroll(evento);
    // que esta presionado
    KeyOyente::get().keyPresionado(evento);
    
};

void SDLApp::on_fisicaupdate(double dt)
{
    
    //Camara Lock UnLock
   
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_L))
    {
        start = true;
        camara_principal->start = true;
        enemigo->start = true;
        camara_principal->lock_objeto(*player);
        enemigo->lock_objeto(*player);
        guardian->lock_objeto(*player);
    }

    player->input_handle(KeyOyente::get(),MouseOyente::get());
 

    double elapsed_tiempo = Tiempo::get_tiempo() - current_tiempo;
    if (elapsed_tiempo > idle_tiempo) {
        if(atack_on==false)
        {
            atack_on = true;
           
        }
        else
        {
            atack_on = false;
        }
         player->set_attack_on(atack_on);
        current_tiempo = Tiempo::get_tiempo();
    }
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_J) && atack_on==true)
    {
        if(player->get_plantas()>0){
            enemigo->set_hp(enemigo->get_hp()-player->get_ataque());
            player->set_plantas(player->get_plantas()-1);
          //  printf("HP-enemigo: %2.f\n",enemigo->get_hp());
        }
        
    }
   for(auto &p:plataformas)
    {  
       // p->update(dt);
        int id=p->get_ID();
        if(id==ATTACK_ZONE){
            if(atack_on==true && start==true){
                p->set_tile(new Tile(allTiles[ATTACK_ZONE-1]));
                
            }else{
                p->set_tile(new Tile(allTiles[PISO-1]));
            }
        }
        if(id==MURO ){
            MotorFisico2D::get().diag_ovelap_g(*player,*p);
            player->en_colision=false;
        }
           
        if(id==GEMAS && start==true){
           MotorFisico2D::get().diag_ovelap_g(*player,*p);
           if(player->en_colision==true){
                p->set_tile(new Tile(allTiles[PISO-1]));
                p->set_ID(PISO);
                player->en_colision=false;
                player->set_hp(player->get_hp()+2);
                
                player->set_colision_gemas(true);
            }
        }
        if(id==PLANTAS && start==true){
           MotorFisico2D::get().diag_ovelap_g(*player,*p);
           if(player->en_colision==true){
                p->set_tile(new Tile(allTiles[PISO-1]));
                p->set_ID(PISO);
                player->en_colision=false;
                player->set_colision_plantas(true);
                player->set_plantas(player->get_plantas()+1);
            }
        }
        if(id==ARTEFACTO && guardian->get_first_time()==0){
            p->set_tile(new Tile(allTiles[PISO-1]));
            
        }else if(id==ARTEFACTO && guardian->get_first_time()==1){
            p->set_tile(new Tile(allTiles[ARTEFACTO-1]));
            MotorFisico2D::get().diag_ovelap_g(*player,*p);
            if(player->en_colision==true){
                p->set_tile(new Tile(allTiles[PISO-1]));
                player->set_colision_artefacto(true);
                player->set_hp(player->get_hp()+25);
                player->game_over=true;
                enemigo->game_over=true;
                guardian->game_over=true;
                camara_principal->game_over=true;
                game_over=true;
               
            }
        }
     
      
    }
    //inicio->update(dt);
    for(auto &p:objetos)
    {  
        p->update(dt);
    }

    
        //gems->update(&objetos);
    player->update(dt);
  //  printf("Coordenadas player: (%d,%d)\n",player->get_posicion_mundo().x,player->get_posicion_mundo().y);
    enemigo->update(dt);
    //imprimir esaod del enemgio
    std::string estado=enemigo->get_strEstado();
  // printf("EsTADO enemigo :%s\n",estado.c_str());
   // printf("Coordenadas enemigo: (%d,%d)\n",enemigo->get_posicion_mundo().x,enemigo->get_posicion_mundo().y);
  //  if(game_over==false){
            MotorFisico2D::get().diag_ovelap_e(*player,*enemigo);
        if(player->en_colision==true){
            player->set_hp(player->get_hp()-enemigo->get_ataque());
            
            player->en_colision=false;
        }
    //  printf("HP-enemigo: %2.f\n",player->get_hp());
        guardian->update(dt);
        MotorFisico2D::get().diag_ovelap_g(*player,*guardian);
        if(player->en_colision==true){
            guardian->set_first_time(1);
            player->set_hp(player->get_hp()-guardian->get_ataque());
            player->en_colision=false;
        }
    //}
    
    if(player->get_hp()<=0){
       // printf("GAME OVER\n");
        game_over  = true;
         player->game_over=true;
        enemigo->game_over=true;
        guardian->game_over=true;
        camara_principal->game_over=true;
    }
    if(enemigo->get_hp()<=0){
       // printf("ENEMIGO MUERTO\n");
        enemigo->set_muerto(true);
    }
    

    
    /*CAMARA al final para actualizar la proyeción de los objetos*/
    camara_principal->input_handle(KeyOyente::get(),MouseOyente::get());
    camara_principal->update();
    camara_principal->proyectar(objetos);
    //printf("Update Fisica\n");

    
    
};

void SDLApp::on_frameupdate(double dt)
{
    // limpiar frame
    SDL_RenderClear(get().render);

    //posicion del mouse
    int mx = MouseOyente::get().getX();
    int my = MouseOyente::get().getY();
    std::string pm = "mouse("+std::to_string(mx)+","+std::to_string(my)+")";
    Coordenadas cp = camara_principal->get_posicion_centro();
    Coordenadas mcp = camara_principal->get_posicion_mundo();
    std::string cm = "camara("+std::to_string(cp.x)+","+std::to_string(cp.y)+")";
    std::string cmm = "camara("+std::to_string(mcp.x)+","+std::to_string(mcp.y)+")";

    RenderTexto::get().render_texto(get().render,815,630,pm,100,30,SDL_Color{0,0,0,255});
    RenderTexto::get().render_texto(get().render,815,580,cmm,100,30,SDL_Color{0,0,0,255});
    RenderTexto::get().render_texto(get().render,815,530,cm,100,30,SDL_Color{0,0,0,255});
    //fps
    RenderTexto::get().render_texto(get().render,get().WIDTH-200,30,
        std::to_string((int)(dt/get().msfrecuencia))+" fps",
        100,30,SDL_Color{0,135,62});

    //Renderizar todo a través de la camara
    camara_principal->renderizar(objetos);
   // camara_principal->render_cross();
    std::string vidaJugador="Vida: "+std::to_string((int)player->get_hp());
    std::string gemasJugador="Gemas: "+std::to_string((int)player->get_gemas());
    std::string plantasJugador="Plantas: "+std::to_string((int)player->get_plantas());
    std::string ataqueJugador="Fuerza de Ataque: "+std::to_string((int)player->get_ataque());
    std::string vidaEnemigo="Vida: "+std::to_string((int)enemigo->get_hp());
    std::string ataqueEnemigo="Fuerza de Ataque: "+std::to_string((int)enemigo->get_ataque());
    std::string ataqueGuardian="Fuerza de Ataque: "+std::to_string((int)guardian->get_ataque());
   // RenderTexto::get().render_texto(get().render,50,630,player->get_strEstado(),120,30,SDL_Color{0,0,0,255});
   if(start==true){
        RenderTexto::get().render_texto(get().render,50,50,"JUGADOR",200,50,SDL_Color{255,0,0,255});
        RenderTexto::get().render_texto(get().render,50,90,vidaJugador,200,50,SDL_Color{255,0,0,255});
        RenderTexto::get().render_texto(get().render,50,130,gemasJugador,200,50,SDL_Color{255,0,0,255});
        RenderTexto::get().render_texto(get().render,50,170,plantasJugador,200,50,SDL_Color{255,0,0,255});
        RenderTexto::get().render_texto(get().render,50,200,ataqueJugador,200,50,SDL_Color{255,0,0,255});

        RenderTexto::get().render_texto(get().render,400,50,"ENEMIGO",150,30,SDL_Color{0,255,0,255});
        RenderTexto::get().render_texto(get().render,400,100,vidaEnemigo,150,30,SDL_Color{0,255,0,255});
        RenderTexto::get().render_texto(get().render,400,150,ataqueEnemigo,150,30,SDL_Color{0,255,0,255});

        RenderTexto::get().render_texto(get().render,700,50,"GUARDIAN",160,50,SDL_Color{0,0,255,255});
        RenderTexto::get().render_texto(get().render,700,100,ataqueGuardian,160,50,SDL_Color{0,0,255,255});

        if(atack_on==true && player->get_colision_artefacto()==false && game_over==false && enemigo->get_muerto()==false){
            RenderTexto::get().render_texto(get().render,400,300,"ATTACK NOW",150,40,SDL_Color{255,255,0,255});
        }
        if(player->get_hp()<=0 && game_over==true){
            RenderTexto::get().render_texto(get().render,400,350,"GAME OVER",150,70,SDL_Color{255,0,255,255});
            enemigo->set_muerto(true);
            game_over=true;
             if(game_over==true){
            RenderTexto::get().render_texto(get().render,350,450,"PRESS L TO RESTART THE GAME",350,70,SDL_Color{255,0,255,255});
                if(KeyOyente::get().estaPresionado(SDL_SCANCODE_L))
                {
                    restart();
                }
             }
        }
        if(player->get_colision_artefacto()==true){
            RenderTexto::get().render_texto(get().render,400,430,"YOU WIN",150,40,SDL_Color{255,0,255,255});
            enemigo->set_muerto(true);
            game_over=true;
             if(game_over==true){
            RenderTexto::get().render_texto(get().render,400,350,"PRESS L TO RESTART THE GAME",350,70,SDL_Color{255,0,255,255});
                if(KeyOyente::get().estaPresionado(SDL_SCANCODE_L))
                {
                    restart();
                }
             }
        }
   }
    
    if(start==false){
        RenderTexto::get().render_texto(get().render,400,300,"PRESS L TO START",200,90,SDL_Color{255,255,0,255});
        
    }
   

    //Actualizar
    SDL_RenderPresent(get().render);

    //resetear color del frame
    SDL_SetRenderDrawColor(
        get().render,
        get().bg_color.r,
        get().bg_color.g,
        get().bg_color.b,
        SDL_ALPHA_TRANSPARENT);
};

void SDLApp::on_limpiar()
{
    SDL_DestroyRenderer(get().render);
    SDL_FreeSurface(get().vntsurf);
    SDL_DestroyWindow(get().vnt);

    for(auto &p:plataformas)
    {
        delete p;
    }
    plataformas.clear();
    delete ensamble;
    delete player;
    delete enemigo;
    SDL_Quit();
};

int SDLApp::on_correr()
{
    //revisar que todo se inicializo bien
    if(get().on_init()==false){return -1;}

    SDL_Event eventos;
    double dt=0;
    double frecuencia = 1/get().maxFPS; // 1 frame a 60fps
    get().msfrecuencia = frecuencia*1000;

    while(get().estaCorriendo())
    {
        //double start = SDL_GetTicks();
        double inicio = Tiempo::get_tiempo();

        //printf("%lf <> %d\n",Tiempo::get_tiempo(),SDL_GetTicks());
        //captura eventos
        while(SDL_PollEvent(&eventos))
        {
            get().on_evento(&eventos);
        }

        //actualizamos si inicia o hay una diferencia de tiempo
        
        get().on_fisicaupdate(dt);
        get().on_frameupdate(dt);

        //calculamos el tiempo del frame
        dt = (Tiempo::get_tiempo() - inicio)/frecuencia*1000;
        
        inicio=dt; //el nuevo frame inicia en este tiempo
        //printf("<%d>[%lf][%d]\n",get().fps,dt,(int)Tiempo::get_tiempo());
        if(dt<get().msfrecuencia)
        {
            SDL_Delay(floor(get().msfrecuencia-dt));
        }
        //get().fps++;
    }
    //liberamos memoria
    get().on_limpiar();
    return 0;
};

void SDLApp::restart()
{
   // get().on_limpiar();
    get().on_init();
    get().on_correr();
};



