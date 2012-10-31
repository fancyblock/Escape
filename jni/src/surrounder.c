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



// calculate the next grid for surround the player
bool GetNextGrid( hexmap* map, pos* posBuf )
{
    srand( time(0) );
    
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
    
    return true;
}

