//
//  surrounder.c
//  Escape
//
//  Created by He jia bin on 10/31/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "surrounder.h"


ALLEGRO_DEBUG_CHANNEL("[AI]")


#define MAX_QUEUE_SIZE  200

pos g_queue[MAX_QUEUE_SIZE];
int g_queueHead;
int g_queueTail;


//--------------------- inner functions ------------------------


int GetAllBorderGrids( hexmap* map, pos* grids, int maxSize );
hexmap* AnalysisMap( hexmap* map );


//--------------------------------------------------------------



// calculate the next grid for surround the player
bool GetNextGrid( hexmap* map, pos* posBuf )
{
    srand( time(0) );
    
    //*
    bool find = false;
    while( find == false )
    {
        int randX = rand() % map->_wid;
        int randY = rand() % map->_hei;
        
        if( GetTile( map, randX, randY ) == eTileBlank )
        {
            posBuf->x = randX;
            posBuf->y = randY;
            
            find = true;
        }
    }
    //*/
    
    //TODO 
    
    return true;
}


//--------------------- inner functions ------------------------ 


// return all the border grids
int GetAllBorderGrids( hexmap* map, pos* grids, int maxSize )
{
    int wid = map->_wid;
    int hei = map->_hei;
    int i, j;
    
    int gridCnt = 0;
    for( i = 0; i < wid; i++ )
    {
        for( j = 0; j < hei; j++ )
        {
            if( GetTile( map, i, j ) == eTileBlank )
            {
                if( IsBorder( map, i, j ) == true )
                {
                    grids[gridCnt].x = i;
                    grids[gridCnt].y = j;
                    
                    gridCnt++;
                    
                    if( gridCnt >= maxSize )
                    {
                        return gridCnt;
                    }
                }
            }
        }
    }
    
    return gridCnt;
}


// analysis the game map and return a info map
hexmap* AnalysisMap( hexmap* map )
{
    char b = -2;        // block grid
    char v = -1;        // 
    
    hexmap* infoMap = CreateHexMap( map->_wid, map->_hei, map->_xOffset, map->_yOffset, map->_orientation );
    FillMap( infoMap, v );
    
    int wid = map->_wid;
    int hei = map->_hei;
    int i, j;
    int escaperX, escaperY;
    
    // initial the infoMap 
    char type;
    for( i = 0; i < wid; i++ )
    {
        for( j = 0; j < hei; j++ )
        {
            type = GetTile( map, i, j );
            
            if( type == eTileBlank )
            {
                // don't need to do anything
            }
            else if( type == eTileObject )  // the escaper's grid
            {
                SetTile( infoMap, i, j, 0 );
                escaperX = i;
                escaperY = j;
            }
            else
            {
                SetTile( infoMap, i, j, b );
            }
        }
    }
    
    // calculate the grid distance from escaper
    //TODO 
    
    return infoMap;
}




















