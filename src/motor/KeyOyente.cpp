#include "KeyOyente.hpp"
KeyOyente::KeyOyente()
{
    //inicializar ninguna tecla presionada
    for(auto i=0;i<SDL_NUM_SCANCODES;++i)
        keys[i]=false;
};
KeyOyente& KeyOyente::get()
{
    static KeyOyente instancia;
    return instancia;
};
void KeyOyente::keyPresionado(SDL_Event *e)
{
    if(e->type==SDL_KEYDOWN)
    {
        get().keys[e->key.keysym.scancode] = true;
    }
    if(e->type==SDL_KEYUP)
    {
        get().keys[e->key.keysym.scancode] = false;
    }
};

bool KeyOyente::nadaPresionado()
{
    int s=0;
    for(int i=0;i<SDL_NUM_SCANCODES;++i)
        s+=get().keys[i];
    
    return (s==0);
};