#include "atlas.hpp"
#include <iostream>
#include <fstream>
#define GEMAS 1
#define PLANTAS 2
#define ARTEFACTO 3
#define ATTACK_ZONE 4
#define PISO 5
#define MURO 6

Atlas::Atlas(std::string atlas)
{
    info.archivo_ids = atlas;
    
};

Atlas::~Atlas()
{
    info.mapa_ids.clear();
};

bool Atlas::cargar_textura(SDL_Renderer *r)
{
    atlas_sheet = IMG_LoadTexture(r,info.archivo_atlas.c_str());
    if(!atlas_sheet)
    {
        std::cout<<SDL_GetError()<<"\n";
        return false;
    }
    return true;
};
void Atlas::generar_mapa(SDL_Renderer *r,int idflip,int notidobjfisicos)
{
    std::ifstream archivo;
    archivo.open(info.archivo_ids.c_str());
    if(!archivo.is_open())
    {
        std::cout<<"El archivo "<<info.archivo_ids<<" no se pudo abrir por:\n"<<SDL_GetError();
        exit(EXIT_FAILURE);
    }


    //cargar la cantidad de tiles y su tamaño
    int renglon,columna;
    archivo >> info.archivo_atlas;
    printf("Archivo del atlas: %s\n",info.archivo_atlas.c_str());
    if(!cargar_textura(r))
    {
        exit(EXIT_FAILURE);
    }
    archivo >> renglon >> columna;
    info.renglones = renglon;
    info.columnas = columna;
    printf("Mundo tiene %d ancho y %d alto\n",renglon, columna);
    
    archivo >> info.tile_width >> info.tile_height;
    printf("Tamaño de los tiles (%dx%d)\n",info.tile_width,info.tile_height);

    archivo >> info.num_tiles_ancho >> info.num_tiles_alto;
    printf("Atlas tiles ancho=%d\nAtlas tiles alto=%d\n",info.num_tiles_ancho,info.num_tiles_alto);

    archivo >>info.atlas_width >> info.atlas_height;
    printf("Atlas width=%d\nAtlas height=%d\n",info.atlas_width,info.atlas_height);
    int id;
     std::vector<Plataformas*> p;
    // inicializar la matriz
    //inicializar la matriz de ids en 0;
    for(int i=0;i<columna;++i)
    {
        std::vector<int> temp;
        for(int j=0;j<renglon;++j)
        {
            temp.push_back(0);
        }
        info.mapa_ids.push_back(temp);
    }
    //llenar matriz_ids
    for(int i=0;i<columna;++i)
    {
        printf("[ ");
        for(int j=0;j<renglon;++j)
        {
            archivo>>info.mapa_ids[i][j];
            printf("%d,",info.mapa_ids[i][j]);
            
            TileInfo tile
            {
                SDL_RendererFlip::SDL_FLIP_NONE,                            //flip
                0.0,                                                        //angulo
                {(info.mapa_ids[i][j]%info.num_tiles_ancho)*info.tile_width,
                (info.mapa_ids[i][j]/info.num_tiles_ancho)*info.tile_height,info.tile_width,info.tile_height},//srcRect
                {j*info.tile_width,i*info.tile_height,info.tile_width,info.tile_height},//dstRect
                atlas_sheet,//source
                {j*info.tile_width,i*info.tile_height},//pos
                info.tile_width,//width
                info.tile_height//height
            };
           
            bool tiene_colision = false; 
           if(info.mapa_ids[i][j]==9 ){
                id=GEMAS;
                tileGema=tile;
            }
            else  if(info.mapa_ids[i][j]==10 ){
               id=PLANTAS;
                tilePlanta=tile;
            }
            else  if(info.mapa_ids[i][j]==1 ){
                id=PISO;
                tilein=tile;
                posicionesPiso.push_back({j*info.tile_width,i*info.tile_height});
            }else if(info.mapa_ids[i][j]==14 ){
                id=ATTACK_ZONE;
                tileBlanco=tile;
               // tilein=tile;
            }
            else if(info.mapa_ids[i][j]==13 ){
                id=ARTEFACTO;
                tileArtefacto=tile;
            }else
            {
                id=MURO;
            }
           
          
           // objetos_fisicos.push_back(new Plataformas(j*t_width,i*t_height,t_width,t_height,{0,0,0,255}));
            //(info.mapa_ids[i][j]==notidobjfisicos) ? false : true;
            objetos_fisicos.push_back(new Plataformas(tile,tiene_colision,id));
            //guradar todos los tileinfo en un vector que no se repitan los ids
           
               
            
        }
        printf("]\n");
    }
   // gemas.push_back(new Gema(9*info.tile_width,2*info.tile_height,info.tile_width,info.tile_height));

    //platafomas apunta  al direccion de p
   // (&plataformas)=p;

    /*constexpr int x=31,y=8;
    constexpr int id=26;
    constexpr int an=32, ren=12;

    constexpr int px= (id%an)*64;
    constexpr int py= ((id/an))*64;*/

    printf("Objetos -> %d\n",(int)objetos_fisicos.size());
    //cerrar archivo
    archivo.close();

};
