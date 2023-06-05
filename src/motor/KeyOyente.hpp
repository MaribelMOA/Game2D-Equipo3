#pragma once
#include<SDL.h>
class KeyOyente
{
    private:
        KeyOyente();
        bool keys[SDL_NUM_SCANCODES];
    public:
        static KeyOyente& get();
        static void keyPresionado(SDL_Event *e);
        static bool estaPresionado(int key) {return get().keys[key];};
        static bool nadaPresionado();
};