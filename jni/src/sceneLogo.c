//
//  sceneLogo.c
//  Escape
//
//  Created by He jia bin on 10/22/12.
//  Copyright (c) 2012 CoconutIslandStudio. All rights reserved.
//

#include <stdio.h>
#include "allScenes.h"
#include "engine.h"

ALLEGRO_DEBUG_CHANNEL("[Scene]")


static ALLEGRO_BITMAP* _imgLogo = NULL;
static double _time;


void SceneLogo_onEnter()
{
    ALLEGRO_DEBUG("[EnterScene]: SceneLogo");
    
    _imgLogo = al_load_bitmap( "logo.png" );
    _time = 0;
    
    //TODO  preload sound & other stuff
}


void SceneLogo_onFrame( double interval )
{
    if( _time > 2.5 )
    {
        StartScene( SCENE_MAINMENU );
    }
    
    _time += interval;
}


void SceneLogo_onRender( double interval )
{
    (void)interval;
    
    al_draw_bitmap_region( _imgLogo, 0, 0, 480, 320, 0, 0, 0 );
}


void SceneLogo_onLeave()
{
    al_destroy_bitmap( _imgLogo );
    
    ALLEGRO_DEBUG("[LeaveScene]: SceneLogo");
}


