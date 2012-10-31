//
//  escaper.h
//  Escape
//
//  Created by He jia bin on 10/24/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#ifndef Escape_escaper_h
#define Escape_escaper_h

#include "engine.h"
#include "common.h"
#include "hexmap.h"
#include "animation.h"

#define DIRECTION_CNT   4
#define WALK_DISTANCE   1
#define GRID_MOVE_TIME  0.6f


// character direction enum
enum 
{
    eDirUp = 0,
    eDirDown = 1,
    eDirLeft = 2,
    eDirRight = 3
};


// state of the escaper
enum 
{
    eEscapeStateIdle = 0,
    eEscapeStateWaittingMove,
    eEscapeStateMoving
};


// escaper struct
typedef struct
{
    int _xPos;
    int _yPos;
    int _status;
    
    int _xDest;
    int _yDest;
    float _movingTime;
    
    hexmap* _map;
    ALLEGRO_BITMAP* _spritesheet;
    animation _anis[DIRECTION_CNT];     // for direction animations
    
    int _dir;
    
}escaper;


// create an escaper
escaper* CreateEscaper();

// destory escaper
void DestoryEscaper( escaper* obj );

// add to map
bool AddEscapeToMap( escaper* obj, hexmap* map, int x, int y );

// set status
bool SetStatus( escaper* obj, int status );

// update the escape
void UpdateEscaper( escaper* obj, float elapsed );

// draw the escape
void DrawEscaper( escaper* obj, float offsetx, float offsety );

// draw alpha escape
void DrawAlphaEscaper( escaper* obj, float offsetx, float offsety, float alpha );

// move to
void MoveEscapeTo( escaper* obj, int gridX, int gridY );


#endif
