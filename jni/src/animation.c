//
//  animation.c
//  Escape
//
//  Created by He jia bin on 10/25/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include "animation.h"


ALLEGRO_DEBUG_CHANNEL("[ANIMATION]")


// create an animation
animation* CreateAnimation( int frameCnt, float interval, int wid, int hei )
{
    animation* ani = NULL;
    
    ani = (animation*)malloc( sizeof(animation) );
    ani->frameCnt = frameCnt;
    ani->interval = interval;
    ani->wid = wid;
    ani->hei = hei;
    
    ani->curTime = 0;
    
    return ani;
}


// initial animation
void InitAnimation( animation* ani, int frameCnt, float interval, int wid, int hei )
{
    ani->frameCnt = frameCnt;
    ani->interval = interval;
    ani->wid = wid;
    ani->hei = hei;
    
    ani->curTime = 0;
}


// destroy an animation
void DestroyAnimation( animation* ani )
{
    free( ani );
}


// add frame
void AddFrame( animation* ani, int index, int xoffset, int yoffset )
{
    if( index >= MAX_FRAME )
    {
        return;
    }
    
    ani->frames[index].x = xoffset;
    ani->frames[index].y = yoffset;
}


// draw animation
void DrawAnimation( animation* ani, float xoffset, float yoffset )
{
    int frameIdx = ani->curTime / ani->interval;
    int curIdx = frameIdx % ani->frameCnt;
    
    al_draw_bitmap_region( ani->spritesheet, ani->frames[curIdx].x, ani->frames[curIdx].y, (float)ani->wid, (float)ani->hei, xoffset, yoffset, 0 );

}


// update animation
void UpdateAnimation( animation* ani, float elapsed )
{
    ani->curTime += elapsed;
}

