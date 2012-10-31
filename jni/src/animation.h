//
//  animation.h
//  Escape
//
//  Created by He jia bin on 10/25/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#ifndef Escape_animation_h
#define Escape_animation_h

#include "engine.h"
#include "common.h"


#define MAX_FRAME   10


// animation struct define
typedef struct
{
    int frameCnt;
    float interval;
    
    int wid;
    int hei;
    
    ALLEGRO_BITMAP* spritesheet;
    pos frames[MAX_FRAME];
    
    double curTime;
    
}animation;



// create an animation
animation* CreateAnimation( int frameCnt, float interval, int wid, int hei );

// initial animation
void InitAnimation( animation* ani, int frameCnt, float interval, int wid, int hei );

// destroy an animation
void DestroyAnimation( animation* ani );

// add frame
void AddFrame( animation* ani, int index, int xoffset, int yoffset );

// draw animation
void DrawAnimation( animation* ani, float xoffset, float yoffset );

// draw alpha animation
void DrawAlphaAnimation( animation* ani, float xoffset, float yoffset, float alpha );

// update animation
void UpdateAnimation( animation* ani, float elapsed );



#endif
