#pragma once
#include "../../utilidad/Estructuras.hpp"
#include "../../objetos_estaticos/ObjetoEstatico.hpp"
#include<string>
#include<SDL.h>

class Atlas
{
    public:
        Atlas(std::string atlas);
        ~Atlas();
        bool cargar_textura(SDL_Renderer *r);
        void generar_mapa(SDL_Renderer *r,int idflip,int notidobjfisicos);
        std::vector<ObjetoEstatico*> get_objetos_fisicos() const{return objetos_fisicos;};
        AtlasInfo get_info() const{return info;};
        void set_info(AtlasInfo i){info=i;};
        void set_plataformas(std::vector<Plataformas*> p){plataformas=p;};
        std::vector<Plataformas*> get_plataformas() const{return plataformas;};

        void set_tilein(TileInfo t){tilein=t;};
        TileInfo get_tilein() const{return tilein;};

        void set_tileArtefacto(TileInfo t){tileArtefacto=t;};
        TileInfo get_tileArtefacto() const{return tileArtefacto;};

        void set_tileBlanco(TileInfo t){tileBlanco=t;};
        TileInfo get_tileBlanco() const{return tileBlanco;};

        void set_tileGema(TileInfo t){tileGema=t;};
        TileInfo get_tileGema() const{return tileGema;};

        void set_tilePlanta(TileInfo t){tilePlanta=t;};
        TileInfo get_tilePlanta() const{return tilePlanta;};



        void set_posicionesPiso(std::vector<Coordenadas> p){posicionesPiso=p;};
        std::vector<Coordenadas> get_posicionesPiso() const{return posicionesPiso;};

       
    private:
         AtlasInfo info;
        std::vector<ObjetoEstatico*> objetos_fisicos;
        SDL_Texture *atlas_sheet;
        std::vector<Plataformas*> plataformas;
        TileInfo tilein,tileArtefacto,tileBlanco,tileGema,tilePlanta;
        std::vector<Coordenadas> posicionesPiso;
        
};