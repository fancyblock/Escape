//
//  escaper.c
//  Escape
//
//  Created by He jia bin on 10/24/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include "escaper.h"


#define ANI_INTERVAL    0.2
#define ANI_WID         14
#define ANI_HEI         20
#define ANI_FRAME       3


ALLEGRO_DEBUG_CHANNEL("[ESCAPER]")


// create an escaper
escaper* CreateEscaper()
{
    escaper* obj = NULL;
    
    obj = (escaper*)malloc( sizeof(escaper) );
    obj->_xPos = 0;
    obj->_yPos = 0;
    obj->_status = eEscapeStateIdle;
    obj->_map = NULL;
    
    // create animations
    InitAnimation( &(obj->_anis[eDirUp]), ANI_FRAME, ANI_INTERVAL, ANI_WID, ANI_HEI );
    InitAnimation( &(obj->_anis[eDirDown]), ANI_FRAME, ANI_INTERVAL, ANI_WID, ANI_HEI );
    InitAnimation( &(obj->_anis[eDirLeft]), ANI_FRAME, ANI_INTERVAL, ANI_WID, ANI_HEI );
    InitAnimation( &(obj->_anis[eDirRight]), ANI_FRAME, ANI_INTERVAL, ANI_WID, ANI_HEI );
    
    // load texture
    obj->_spritesheet = al_load_bitmap( "rsgirl.png" );
    
    obj->_anis[eDirUp].spritesheet = obj->_spritesheet;
    obj->_anis[eDirDown].spritesheet = obj->_spritesheet;
    obj->_anis[eDirLeft].spritesheet = obj->_spritesheet;
    obj->_anis[eDirRight].spritesheet = obj->_spritesheet;
    
    // add frames 
    AddFrame( &obj->_anis[eDirUp], 0, 4, 4 );
    AddFrame( &obj->_anis[eDirUp], 1, 22, 4 );
    AddFrame( &obj->_anis[eDirUp], 2, 40, 4 );
    
    AddFrame( &obj->_anis[eDirDown], 0, 4, 29 );
    AddFrame( &obj->_anis[eDirDown], 1, 22, 29 );
    AddFrame( &obj->_anis[eDirDown], 2, 40, 29 );
    
    AddFrame( &obj->_anis[eDirLeft], 0, 60, 4 );
    AddFrame( &obj->_anis[eDirLeft], 1, 77, 4 );
    AddFrame( &obj->_anis[eDirLeft], 2, 94, 4 );
    
    AddFrame( &obj->_anis[eDirRight], 0, 60, 29 );
    AddFrame( &obj->_anis[eDirRight], 1, 77, 29 );
    AddFrame( &obj->_anis[eDirRight], 2, 94, 29 );
    
    obj->_dir = eDirDown;
    
    return obj;
}


// destory escaper
void DestoryEscaper( escaper* obj )
{
    al_destroy_bitmap( obj->_spritesheet );
    
    free( obj );
}


// add to map
bool AddEscapeToMap( escaper* obj, hexmap* map, int x, int y )
{
    obj->_map = map;
    obj->_xPos = x;
    obj->_yPos = y;
    
    return true;
}


// set status
bool SetStatus( escaper* obj, int status )
{
    if( status == eEscapeStateMoving )
    {
        return false;
    }
    
    obj->_status = status;
    
    return true;
}


// update the escape
void UpdateEscaper( escaper* obj, float elapsed )
{
    // update animation
    // animation frame update
    if( obj->_status == eEscapeStateMoving || obj->_status == eEscapeStateWaittingMove )
    {
        UpdateAnimation( &obj->_anis[obj->_dir], elapsed );
    }
    // stop at the 2th frame ( idle frame )
    else if( obj->_status == eEscapeStateIdle )
    {
        obj->_anis[obj->_dir].curTime = obj->_anis[obj->_dir].interval;
    }
    
    // update position
    if( obj->_status == eEscapeStateMoving )
    {
        obj->_movingTime += elapsed;
        
        if( obj->_movingTime >= GRID_MOVE_TIME )
        {
            obj->_status = eEscapeStateIdle;
            obj->_xPos = obj->_xDest;
            obj->_yPos = obj->_yDest;
        }
    }
    
    //TODO 
    
}


// draw the escape
void DrawEscaper( escaper* obj, float offsetx, float offsety )
{
    float xpos;
    float ypos;
    
    GridToPosition( obj->_map, obj->_xPos, obj->_yPos, &xpos, &ypos );
    
    if( obj->_status == eEscapeStateMoving )
    {
        float destX;
        float destY;

        GridToPosition( obj->_map, obj->_xDest, obj->_yDest, &destX, &destY );
        
        xpos += ( destX - xpos ) * obj->_movingTime / GRID_MOVE_TIME;
        ypos += ( destY - ypos ) * obj->_movingTime / GRID_MOVE_TIME;
    }
    
    xpos -= ( ANI_WID / 2.0 );
    ypos -= ( ANI_HEI / 2.0 );
    
    DrawAnimation( &obj->_anis[obj->_dir], xpos + offsetx, ypos + offsety );
    
    //TODO 
    
}


// move to
void MoveEscapeTo( escaper* obj, int gridX, int gridY )
{
    // set the dest position
    obj->_xDest = gridX;
    obj->_yDest = gridY;
    obj->_movingTime = 0.0f;
    
    // rotate the character
    if( obj->_yPos == gridY )
    {
        // left, right direction
        if( gridX > obj->_xPos )
        {
            obj->_dir = eDirRight;
        }
        else
        {
            obj->_dir = eDirLeft;
        }
    }
    else
    {
        // up, down direction
        if( gridY > obj->_yPos )
        {
            obj->_dir = eDirDown;
        }
        else
        {
            obj->_dir = eDirUp;
        }
    }
    
    // set status
    obj->_status = eEscapeStateMoving;
    
}

























