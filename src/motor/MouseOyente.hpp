#pragma once
#include <SDL.h>
class MouseOyente
{
    private:
        MouseOyente();
        int scrollX;
        int scrollY;
        int xPos;
        int yPos;
        int lastX;
        int lastY;
        bool mouse_boton[3];
        bool esta_arrastrando;
        bool esta_moviendo;
    
    public:
        static MouseOyente& get();
        static void evento_movimiento(SDL_Event* e);
        static void evento_presionado(SDL_Event* e);
        static void evento_scroll(SDL_Event* e);

        static int getX(){return get().xPos;};
        static int getY(){return get().yPos;};
        static int getDX(){return get().lastX-get().xPos;};
        static int getDY(){return get().lastY-get().yPos;};
        static int getScrollX(){return get().scrollX;};
        static int getScrollY(){return get().scrollY;};
        static bool esArrastrado(){return get().esta_arrastrando;};
        static bool seMueve(){return get().esta_moviendo;};
};