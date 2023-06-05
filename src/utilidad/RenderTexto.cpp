#include "RenderTexto.hpp"
#include<iostream>
RenderTexto* RenderTexto::instancia=0;
bool RenderTexto::inicio = false;

RenderTexto::RenderTexto()
{
    if(!instancia && TTF_Init()==-1)
    {    
        std::cout<<"Error: "<<TTF_GetError()<<"\n";
        exit(EXIT_FAILURE);
    }
    inicio=true;
    //por el momento usaremos onuva como default font
    font_default = TTF_OpenFont("assets/fonts/onuava.ttf",20);
    if(font_default == NULL)
    {
        std::cout<<"Error: "<<TTF_GetError()<<"\n";
        exit(EXIT_FAILURE);
    }

}

RenderTexto::~RenderTexto()
{
    //limpiamos
    SDL_DestroyTexture(font_texture);
    TTF_CloseFont(font_default);
};




RenderTexto& RenderTexto::get()
{
    if(!instancia)
        instancia = new RenderTexto();
    return *instancia;
};

void RenderTexto::render_texto(SDL_Renderer *ren, int x, int y, std::string texto, int fontsize, SDL_Color color, std::string font)
{
    //Agregar el font
    std::string ff = "assets/fonts/"+font+".ttf";
    TTF_Font* fontTipo = TTF_OpenFont(ff.c_str(),fontsize);
    //revisamos que si localizamos el font
    if(fontTipo == NULL)
    {
        printf("No se encontro el FONT: %s\n",TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //creamos una superficie donde pintar
    //Optimización precargar y alocar las superficies
    
    SDL_Surface *surf_texto = TTF_RenderText_Blended(
        fontTipo,
        texto.c_str(),
        color);
    //La convertimos en textura
    SDL_Texture *textexto = SDL_CreateTextureFromSurface(
        ren,
        surf_texto);
    //lo pintamos en un cuadro que se mostrara en el canvas
    SDL_Rect rectexto;
    rectexto.x = x;
    rectexto.y = y;
    rectexto.w = surf_texto->w;
    rectexto.h = surf_texto->h;

    //mandarlo a mostrar al canvas
    SDL_RenderCopy(ren,textexto,NULL,&rectexto);
    

    //Liberamos la memoria
    TTF_CloseFont(fontTipo);
    SDL_DestroyTexture(textexto);
    SDL_FreeSurface(surf_texto);
};

void RenderTexto::render_texto(SDL_Renderer *ren, int x, int y, std::string texto, int w, int h,SDL_Color color)
{
    //pixeles
    get().font_surface = TTF_RenderText_Blended(get().font_default,texto.c_str(),color);

    //textura
    get().font_texture = SDL_CreateTextureFromSurface(ren,get().font_surface);

    //liberamos superficie
    SDL_FreeSurface(get().font_surface);

    //rectangulo
    get().font_rect.x =x;
    get().font_rect.y=y;
    get().font_rect.w=w;
    get().font_rect.h=h;

    SDL_RenderCopy(ren,get().font_texture,NULL,&get().font_rect);
    if(get().font_texture!=nullptr)
        SDL_DestroyTexture(get().font_texture);
};

