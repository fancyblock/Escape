//
//  hexmap.h
//  Escape
//
//  Created by He jia bin on 10/22/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#ifndef Escape_hexmap_h
#define Escape_hexmap_h


#define FLAT_ORIENTATION    0
#define POINTY_ORIENTATION  1
#define BOARD_COUNT         6

#include "engine.h"
#include "common.h"


// struct hex map
typedef struct
{
    int _wid;
    int _hei;
    float _xOffset;
    float _yOffset;
    int _orientation;
    
    char* _mapData;
    
    ALLEGRO_BITMAP* _imgTiles;
    
}hexmap;


// tile type define
enum
{
    eTileEmpty = 0,
    eTileBlank,
    eTileBlock,
    eTileObject,
    eTileSpecial
};


// for now , only accept POINTY_ORIENTATION orientation as the direction parameter 
hexmap* CreateHexMap( int wid, int hei, float xOffset, float yOffset, int orientation );

// destory the hex map
void DestoryHexMap( hexmap* map );

// fill map with the specific type
void FillMap( hexmap* map, char type );

// set tile info
void SetTile( hexmap* map, int posX, int posY, char type );

// set tile
char GetTile( hexmap* map, int posX, int posY );

// draw map
void DrawMap( hexmap* map, float xOffset, float yOffset );

// draw a single tile
void DrawTile( hexmap* map, int gridX, int gridY, float xOffset, float yOffset, ALLEGRO_COLOR color );

// convert from grid coordinate to map coordinate ( center of the hexagon )
void GridToPosition( hexmap* map, int gridX, int gridY, float* posX, float* posY );

// convert form map coordinate (center of the hexagon) to grid coordinate
void PositionToGrid( hexmap* map, float posX, float posY, int* gridX, int* gridY );

// get neighbors
int GetNeighborGrids( hexmap* map, int posX, int posY, pos* output );

// get adjoin grids
int GetAdjoinGrids( hexmap* map, int posX, int posY, int distance, pos* posPool, int posPoolSize );

// calculate the distance of two grids ( omit grid type )
int CalcDistance( int x1, int y1, int x2, int y2 );


#endif
