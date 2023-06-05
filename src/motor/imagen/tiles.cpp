#include "tiles.hpp"
#include <iostream>
#include <fstream>

Tile::Tile(TileInfo info)
{
    dst = info.dstRect;
    src = info.srcRect;
    size ={info.width,info.height};
    atlas = info.source;
};