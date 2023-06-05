#include "ObjetoEstatico.hpp"

Plataformas::Plataformas(int x, int y, int w, int h, SDL_Color color)
:ObjetoEstatico{} //llamar constructor padre
{
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,w,h,color);
    avatar->set_rellenocolor(color);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,w+5,h+5,{0,255,0,255});
    tiene_fisica=false;
    en_colision=false;
};
Plataformas::Plataformas(TileInfo tiles, bool colision,int ID)
{
    avatar=nullptr;
    sprite = nullptr;
    posicion_mundo = tiles.pos;
    col_box = new Rectangulo(posicion_mundo.x-(tiles.width/2),posicion_mundo.y-(tiles.height/2),tiles.width,tiles.height,{0,255,0,255});
    tiene_fisica=colision;
    en_colision=false;
    tilein = tiles;
    tile = new Tile(tiles);
    ID_tile = ID;
    
};

void Plataformas::update(double dt)
{

};
