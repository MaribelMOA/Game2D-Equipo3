#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../objetos_estaticos/ObjetoEstatico.hpp"
#include "../../objetos/Objeto.hpp"
#include "../camaras/Camaras.hpp"
#include<vector>

class MotorFisico2D
{
    public:
        static MotorFisico2D& get();
       //static void aabb_colision(ObjetoDinamico& p, std::vector<ObjetoEstatico*> obj); 
        static bool aabb_colision(Figura& A, Figura& B); 
        static bool diag_colision(Figura& A, Figura& B);
        static bool diag_ovelap(Objeto& A, Objeto& B);

        bool diag_ovelap_g(Objeto& A, Objeto& B);
        
        static void sat_colision(ObjetoDinamico&p, std::vector<ObjetoEstatico*> obj);
        static void sortandsweep_colision(std::vector<ObjetoDinamico*> objs);

        static void gravedad(std::vector<ObjetoDinamico*> objs);

        void set_colision(bool c){colisiona=c;};
         bool get_colision(){return colisiona;};
    public:
        static float gforce;
        bool colisiona;
    
    private:
        bool sat(Objeto &A, Objeto& B);
        //bool aabb(Objeto &A, Objeto &B);

    private:
        MotorFisico2D(){};
        static MotorFisico2D* instancia;
       // float gforce{0.09};
        float dtgravedad{0};
    


        
};
