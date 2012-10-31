//
//  sceneIngame.c
//  Escape
//
//  Created by He jia bin on 10/22/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "allScenes.h"
#include "engine.h"
#include "hexmap.h"
#include "escaper.h"


ALLEGRO_DEBUG_CHANNEL("[Scene]")


#define MAP_WIDTH           21
#define MAP_HEIGHT          11
#define HEXAGON_XOFFSET     28
#define HEXAGON_YOFFSET     27

#define MAP_OFFSET_X        -105    //30
#define MAP_OFFSET_Y        23

#define INIT_POS_X          10
#define INIT_POS_Y          5


#define STATE_FADEIN        0
#define STATE_PLAYER_TURN   1
#define STATE_ENEMY_TURN    2
#define STATE_SUCCESS       3
#define STATE_FAIL          4
#define STATE_WAIT          5



//---------------------------- game var -------------------------------


static int g_gameState = 0;

static hexmap* g_map = NULL;
static escaper* g_escaper = NULL;

static int g_curX = -1;
static int g_curY = -1;

static pos g_neighborGrids[BOARD_COUNT];      // in hexgeon map, the max neighbor count is 6 
static int g_neighborCount;

static float g_counter = 0.0f;


//------------------------- scene functions ---------------------------

void gotoState( int state );
void createMap();
void drawGrid( char type, float x, float y );
void updateFadeInGame( float elapsed );
void drawFadeInGame();
void updatePlayerTurn( float elapsed );
void drawPlayerTurn();
void updateEnemyTurn( float elapsed );
void drawEnemyTurn();

//----------------------- game functions declare ----------------------


void SceneIngame_onEnter()
{
    ALLEGRO_DEBUG("[EnterScene]: SceneIngame");
    
    // create map
    createMap();
    // create escaper
    g_escaper = CreateEscaper();
    // add escaper to map
    AddEscapeToMap( g_escaper, g_map, INIT_POS_X, INIT_POS_Y );           // initial position
    
    //TODO 
    
    gotoState( STATE_FADEIN );
    
}


void SceneIngame_onFrame( double interval )
{
    if( g_gameState == STATE_FADEIN )
    {
        updateFadeInGame( interval );
    }
    else if( g_gameState == STATE_PLAYER_TURN )
    {
        updatePlayerTurn( interval );
    }
    else if( g_gameState == STATE_ENEMY_TURN )
    {
        updateEnemyTurn( interval );
    }
    
    //TODO 
    
}


void SceneIngame_onRender( double interval )
{
    (void)interval;
    
    if( g_gameState == STATE_FADEIN )
    {
        drawFadeInGame();
    }
    else if( g_gameState == STATE_PLAYER_TURN )
    {
        drawPlayerTurn();
    }
    else if( g_gameState == STATE_ENEMY_TURN )
    {
        drawEnemyTurn();
    }
    
    //TODO 

}


void SceneIngame_onLeave()
{
    // destory map
    DestoryHexMap( g_map );
    // destory escaper
    DestoryEscaper( g_escaper );
    
    ALLEGRO_DEBUG("[LeaveScene]: SceneMainmenu");
}


//-------------------------- game functions ---------------------------


void gotoState( int state )
{
    g_gameState = state;
    g_counter = 0.0f;
    
    //TODO
}


void createMap()
{
    // create map
    g_map = CreateHexMap( MAP_WIDTH, MAP_HEIGHT, HEXAGON_XOFFSET, HEXAGON_YOFFSET, POINTY_ORIENTATION );
    
    FillMap( g_map, eTileEmpty );
    
    // set the necessary grid ( cut two trangles at the left top & right bottom )
    int i, j;
    int offset = 5;
    for( i = 0; i < MAP_HEIGHT; i++ )
    {
        for( j = 0; j < MAP_WIDTH - 5; j++ )            // real width is 11
        {
            SetTile( g_map, j + offset, i, eTileBlank );
        }
        
        if( i % 2 == 0 )
        {
            offset--;
        }
    }
    
    // ( generate some random obstacle )
    srand( time(0) );
    int obstacleCnt = rand() % 10 + 14;
    int miniDis = 3;
    
    int randX;
    int randY;
    while( obstacleCnt > 0 )
    {
        randX = rand() % MAP_WIDTH;
        randY = rand() % MAP_HEIGHT;
        
        if( GetTile( g_map, randX, randY ) == eTileBlank )
        {
            if( CalcDistance( randX, randY, INIT_POS_X, INIT_POS_Y ) > miniDis )
            {
                SetTile( g_map, randX, randY, eTileBlock );
                
                obstacleCnt--;
            }
        }
        
    }
    
}


// update fade in game
void updateFadeInGame( float elapsed )
{
    (void)elapsed;
    
    //TODO 
}


// draw fade in game
void drawFadeInGame()
{
    //TODO 
}


// update player turn
void updatePlayerTurn( float elapsed )
{
    int i;
    
    touch* curTouch = GetTouchEvent();
    
    // get the grid which be touch currently
    if( curTouch->_type == EVT_TOUCH || curTouch->_type == EVT_MOVE )
    {
        PositionToGrid( g_map, curTouch->_x + HEXAGON_XOFFSET/2.0 - MAP_OFFSET_X,
                       curTouch->_y + HEXAGON_YOFFSET/2.0 - MAP_OFFSET_Y,
                       &g_curX, &g_curY );
    }
    // do the action when untouch the current grid
    if( curTouch->_type == EVT_UNTOUCH )
    {
        // waitting select
        if( g_escaper->_status == eEscapeStateIdle )
        {
            if( g_curX == g_escaper->_xPos && g_curY == g_escaper->_yPos )
            {
                SetStatus( g_escaper, eEscapeStateWaittingMove );
                
                // get neighbor grids
                g_neighborCount = GetNeighborGrids( g_map, g_curX, g_curY, g_neighborGrids );
                
            }
        }
        // waitting move 
        else if( g_escaper->_status == eEscapeStateWaittingMove )
        {
            int destIdx = -1;
            
            for( i = 0; i < g_neighborCount; i++ )
            {
                // only blank grid can pass 
                if( GetTile( g_map, g_neighborGrids[i].x, g_neighborGrids[i].y ) != eTileBlank )
                {
                    continue;
                }
                
                if( g_neighborGrids[i].x == g_curX && g_neighborGrids[i].y == g_curY )
                {
                    destIdx = i;
                    break;
                }
            }
            
            // go to destination grid
            if( destIdx >= 0 )
            {
                MoveEscapeTo( g_escaper, g_curX, g_curY );
            }
            // cancel the move status
            else
            {
                SetStatus( g_escaper, eEscapeStateIdle );
            }
            
        }
        
        g_curX = -1;
        g_curY = -1;
        
    }
    
    // update escaper
    UpdateEscaper( g_escaper, elapsed );
}


// draw player turn
void drawPlayerTurn()
{
    int i;
    
    // draw map
    DrawMap( g_map, MAP_OFFSET_X, MAP_OFFSET_Y );
    
    // draw escaper's pending grid
    if( g_escaper->_status == eEscapeStateWaittingMove )
    {
        for( i = 0; i < g_neighborCount; i++ )
        {
            // draw blank grid, only blank grid can pass
            if( GetTile( g_map, g_neighborGrids[i].x, g_neighborGrids[i].y ) == eTileBlank )
            {
                DrawTile( g_map, g_neighborGrids[i].x, g_neighborGrids[i].y, MAP_OFFSET_X, MAP_OFFSET_Y, al_map_rgba_f( 0.2, 1.0, 0, 0.7 ) );
            }
        }
    }
    
    // draw escaper
    DrawEscaper( g_escaper, MAP_OFFSET_X, MAP_OFFSET_Y );
    
    // draw hint spot
    if( g_curX >= 0 && g_curY >= 0 )
    {
        DrawTile( g_map, g_curX, g_curY, MAP_OFFSET_X, MAP_OFFSET_Y, al_map_rgba_f( 1.0, 0, 0, 0.5 ) );
    }
}


// update enemy turn
void updateEnemyTurn( float elapsed )
{
    (void)elapsed;
    
    //TODO 
}


// draw enemy turn
void drawEnemyTurn()
{
    //TODO 
}

















