//
//  hexmap.c
//  Escape
//
//  Created by He jia bin on 10/22/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include "hexmap.h"
#include <stdlib.h>
#include <math.h>


#define TILE_WIDTH      27
#define TILE_HEIGHT     33


ALLEGRO_DEBUG_CHANNEL("[HexMap]")


// create hex map ( for now only support one orientation )
hexmap* CreateHexMap( int wid, int hei, float xOffset, float yOffset, int orientation )
{
    hexmap* mapObj = (hexmap*)malloc( sizeof(hexmap) );
    
    mapObj->_wid = wid;
    mapObj->_hei = hei;
    mapObj->_xOffset = xOffset;
    mapObj->_yOffset = yOffset;
    mapObj->_orientation = orientation;
    
    // map data
    mapObj->_mapData = (char*)malloc( wid * hei * sizeof(char) );
    
    // load resource
    mapObj->_imgTiles = al_load_bitmap( "tileset.png" );
    
    return mapObj;
}


// destory map
void DestoryHexMap( hexmap* map )
{
    //TODO
    
    al_destroy_bitmap( map->_imgTiles );
    
    free( map->_mapData );
    free( map );
}


// fill map with the specific type
void FillMap( hexmap* map, char type )
{
    int count = map->_wid * map->_hei;
    int i;
    
    for( i = 0; i < count; i++ )
    {
        map->_mapData[i] = type;
    }
}


// set tile info
void SetTile( hexmap* map, int posX, int posY, char type )
{
    if( posX < 0 && posY < 0 && posX >= map->_wid && posY >= map->_hei )
    {
        return;
    }
    
    int index = posY * map->_wid + posX;
    map->_mapData[index] = type;
}


// set tile
char GetTile( hexmap* map, int posX, int posY )
{
    if( posX < 0 || posY < 0 || posX >= map->_wid || posY >= map->_hei )
    {
        return eTileEmpty;
    }
    
    int index = posY * map->_wid + posX;
    
    return map->_mapData[index];
}


// draw map
void DrawMap( hexmap* map, float xOffset, float yOffset )
{
    DrawAlphaMap( map, xOffset, yOffset, 1.0f );
}


// draw alpha map
void DrawAlphaMap( hexmap* map, float xOffset, float yOffset, float alpha )
{
    int wid = map->_wid;
    int hei = map->_hei;
    
    int i, j;
    int index = 0;
    float posX, posY;
    char type;
    
    float factorX1 = map->_xOffset;
    float factorX2 = map->_xOffset / 2;
    float factorY = map->_yOffset;
    
    int picOffset;
    
    for( j = 0; j < hei; j++ )
    {
        for( i = 0; i < wid; i++ )
        {
            type = map->_mapData[index];
            index++;
            
            if( type == eTileEmpty )
            {
                continue;
            }
            
            // convert coordinate
            posX = factorX1 * i + factorX2 * j;
            posY = factorY * j;
            
            // draw map tile       
            if( type == eTileBlank )
            {
                picOffset = 33;
            }
            if( type == eTileBlock )
            {
                picOffset = 0;
            }
            if( type == eTileObject )
            {
                picOffset = 33;             // the same as eTileBlank
            }
            
            if( type == eTileSpecial )
            {
                picOffset = 132;
            }
            
            al_draw_tinted_bitmap_region( map->_imgTiles, al_map_rgba_f( 1.0f, 1.0f, 1.0f, alpha ), 0, picOffset, TILE_WIDTH, TILE_HEIGHT,
                                         posX + xOffset - TILE_WIDTH/2.0, posY + yOffset - TILE_HEIGHT/2.0, 0 );
        }
    }
}


// draw a single tile
void DrawTile( hexmap* map, int gridX, int gridY, float xOffset, float yOffset, ALLEGRO_COLOR color )
{
    float factorX1 = map->_xOffset;
    float factorX2 = map->_xOffset / 2;
    float factorY = map->_yOffset;
    
    // convert coordinate
    float posX = factorX1 * gridX + factorX2 * gridY;
    float posY = factorY * gridY;
    
    al_draw_tinted_bitmap_region( map->_imgTiles, color,
                                 0, 132, TILE_WIDTH, TILE_HEIGHT,
                                 posX + xOffset - TILE_WIDTH/2.0, posY + yOffset - TILE_HEIGHT/2.0, 0 );
}


// draw specific type tile
void DrawTileType( hexmap* map, int gridX, int gridY, float xOffset, float yOffset, char type, float alpha )
{
    int picOffset = 132;
    
    // draw map tile       
    if( type == eTileBlank )
    {
        picOffset = 33;
    }
    if( type == eTileBlock )
    {
        picOffset = 0;
    }
    if( type == eTileObject )
    {
        picOffset = 33;             // the same as eTileBlank
    }
    
    if( type == eTileSpecial )
    {
        picOffset = 132;
    }
    
    float factorX1 = map->_xOffset;
    float factorX2 = map->_xOffset / 2;
    float factorY = map->_yOffset;
    
    // convert coordinate
    float posX = factorX1 * gridX + factorX2 * gridY;
    float posY = factorY * gridY;
    
    al_draw_tinted_bitmap_region( map->_imgTiles, al_map_rgba_f( 1.0f, 1.0f, 1.0f, alpha ),
                                 0, picOffset, TILE_WIDTH, TILE_HEIGHT,
                                 posX + xOffset - TILE_WIDTH/2.0, posY + yOffset - TILE_HEIGHT/2.0, 0 );
}


// convert from grid coordinate to map coordinate ( center of the hexagon )
void GridToPosition( hexmap* map, int gridX, int gridY, float* posX, float* posY )
{
    float factorX1 = map->_xOffset;
    float factorX2 = map->_xOffset / 2;
    float factorY = map->_yOffset;
    
    *posX = factorX1 * gridX + factorX2 * gridY;
    *posY = factorY * gridY;
}


// convert form map coordinate (center of the hexagon) to grid coordinate
void PositionToGrid( hexmap* map, float posX, float posY, int* gridX, int* gridY )
{
    float factorX1 = map->_xOffset;
    float factorX2 = map->_xOffset / 2;
    float factorY = map->_yOffset;
    
    *gridY = posY / factorY;
    *gridX = ( posX - factorX2 * (*gridY) ) / factorX1;
}


// get neighbors
int GetNeighborGrids( hexmap* map, int posX, int posY, pos* output )
{
    int offsetx[] = { 0, 1, -1, 1, -1, 0 };
    int offsety[] = { -1, -1, 0, 0, 1, 1 };
    
    int neighborPosX;
    int neighborPosY;
    
    int i;
    int count = 0;
    for( i = 0; i < BOARD_COUNT; i++ )
    {
        neighborPosX = posX + offsetx[i];
        neighborPosY = posY + offsety[i];
        
        // if the grid type is not empty , add to the neighbor list
        if( GetTile( map, neighborPosX, neighborPosY ) != eTileEmpty )
        {
            output[count].x = neighborPosX;
            output[count].y = neighborPosY;
            
            count++;
        }
    }
    
    return count;
}


// get adjoin grids
int GetAdjoinGrids( hexmap* map, int posX, int posY, int distance, pos* posPool, int posPoolSize )
{
    if( distance < 1 )
    {
        return 0;
    }
    
    int count = 0;
    
    //TODO
    (void)map;
    (void)posX;
    (void)posY;
    (void)posPool;
    (void)posPoolSize;
    //TODO
    
    return count;
}


// calculate the distance of two grids ( omit grid type )
int CalcDistance( int x1, int y1, int x2, int y2 )
{
    int distance = 0;
    
    float value = ( ( x1 - x2 ) + (float)( y1 - y2 ) * 0.5 ) * ( ( x1 - x2 ) + (float)( y1 - y2 ) * 0.5 );
    value += ( y1 - y2 ) * ( y1 - y2 ) * 0.75;
    
    value = sqrt( value );
    
    distance = (int)( value + 0.5f );
    
    return distance;
}



//---------------------- inner used functions ------------------------







