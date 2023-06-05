#include "MouseOyente.hpp"
MouseOyente::MouseOyente()
{
    scrollX=0;
    scrollY=0;
    xPos=0;
    yPos=0;
    lastX=0;
    lastY=0;
    for(auto i=0;i<3;++i)
        mouse_boton[i]=false;
};
MouseOyente& MouseOyente::get()
{
    static MouseOyente instancia;
    return instancia;
};
void MouseOyente::evento_movimiento(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION)
    {
        get().lastX = get().xPos;
        get().lastY = get().yPos;
        get().xPos = e->motion.x;
        get().yPos = e->motion.y;
        get().esta_moviendo = true;
        get().esta_arrastrando = get().mouse_boton[0] | get().mouse_boton[1] | get().mouse_boton[2];
    }
    else
    {
        get().esta_moviendo=false;
    }
};

void MouseOyente::evento_presionado(SDL_Event*e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        switch (e->button.button)
        {
        case SDL_BUTTON_LEFT:
            get().mouse_boton[SDL_BUTTON_LEFT-1]=true;
            break;
        case SDL_BUTTON_RIGHT:
            get().mouse_boton[SDL_BUTTON_RIGHT-1]=true;
            break;
        default:
            get().mouse_boton[SDL_BUTTON_MIDDLE-1]=true;
            break;
        }
    }
    if(e->type == SDL_MOUSEBUTTONUP)
    {
        switch (e->button.button)
        {
        case SDL_BUTTON_LEFT:
            get().mouse_boton[SDL_BUTTON_LEFT-1]=false;
            break;
        case SDL_BUTTON_RIGHT:
            get().mouse_boton[SDL_BUTTON_RIGHT-1]=false;
            break;
        default:
            get().mouse_boton[SDL_BUTTON_MIDDLE-1]=false;
            break;
        }
        get().esta_arrastrando=false;
    }
};

void MouseOyente::evento_scroll(SDL_Event *e)
{
    if(e->type == SDL_MOUSEWHEEL)
    {
        get().scrollX = e->wheel.x;
        get().scrollY = e->wheel.y;
    }
};