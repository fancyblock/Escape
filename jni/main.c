
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_android.h> /* al_android_set_apk_file_interface */
#include <allegro5/internal/aintern_bitmap.h>
#include <allegro5/allegro_font.h>
#include "engine.h"


#define MAX_TOUCH 10
#define SCREEN_LOGIC_WID    480
#define SCREEN_LOGIC_HEI    320


ALLEGRO_DEBUG_CHANNEL("main")

touch g_touches[MAX_TOUCH];
float g_screenRatioX;
float g_screenRatioY;



static void set_transform(ALLEGRO_DISPLAY *dpy)
{
    ALLEGRO_TRANSFORM t;

    al_identity_transform(&t);
    al_ortho_transform(&t, 0, SCREEN_LOGIC_WID, SCREEN_LOGIC_HEI, 0, -1, 1);
    al_set_projection_transform(dpy, &t);
}


int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *dpy;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;

    (void)argc;
    (void)argv;

    ALLEGRO_DEBUG("init allegro!");
    if (!al_init())
    {
        return 1;
    }

    ALLEGRO_DEBUG("init primitives");
    al_init_primitives_addon();

    ALLEGRO_DEBUG("init image addon");
    al_init_image_addon();

    ALLEGRO_DEBUG("init touch input");
    al_install_touch_input();

    ALLEGRO_DEBUG("init keyboard");
    al_install_keyboard();
    
//    ALLEGRO_DEBUG( "init font" );
//    al_init_font_addon();
//    al_init_ttf_addon();

    ALLEGRO_DEBUG("creating display");
    al_set_new_display_option( ALLEGRO_SUPPORTED_ORIENTATIONS, ALLEGRO_DISPLAY_ORIENTATION_LANDSCAPE, ALLEGRO_REQUIRE );
    al_set_new_display_refresh_rate( 60 );
    dpy = al_create_display( 0, 0 );
    if(!dpy)
    {
        ALLEGRO_ERROR("failed to create display!");
        return 1;
    }
    
    g_screenRatioX = SCREEN_LOGIC_WID / (float)al_get_display_width(dpy);
    g_screenRatioY = SCREEN_LOGIC_HEI / (float)al_get_display_height(dpy);

    /* This is loaded from assets in the apk. */
    al_android_set_apk_file_interface();

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(dpy));
    al_register_event_source(queue, al_get_touch_input_event_source());

    bool running = true;

    int frame = 0;
    double elapsedTime = 0;
    double timeAdj = al_get_time();

    InitialGame();

    while( running )
    {
        // calculate the FPS
        frame++;
        double tt = al_get_time();
        elapsedTime = tt - timeAdj;

        if( elapsedTime >= 3.0 )		// FPS display interval
        {
            ALLEGRO_DEBUG( "[FPS]: %.2f", frame / elapsedTime );

            frame = 0;
            elapsedTime = 0;
            timeAdj = tt;
        }
       
        int i;
        for( i = 0; i < MAX_TOUCH; i++ )
        {
            g_touches[i]._type = EVT_NOTOUCH;
        }

        while( al_get_next_event( queue, &event ) )
        {
            switch (event.type)
            {
                case ALLEGRO_EVENT_TOUCH_BEGIN:
                    g_touches[event.touch.id]._type = EVT_TOUCH;
                    g_touches[event.touch.id]._x = event.touch.x * g_screenRatioX;
                    g_touches[event.touch.id]._y = event.touch.y * g_screenRatioY;
                    break;
                case ALLEGRO_EVENT_TOUCH_END:
                    g_touches[event.touch.id]._type = EVT_UNTOUCH;
                    g_touches[event.touch.id]._x = 0.0;
                    g_touches[event.touch.id]._y = 0.0;
                    break;
                case ALLEGRO_EVENT_TOUCH_MOVE:
                    g_touches[event.touch.id]._type = EVT_MOVE;
                    g_touches[event.touch.id]._x = event.touch.x * g_screenRatioX;
                    g_touches[event.touch.id]._y = event.touch.y * g_screenRatioY;
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    ALLEGRO_DEBUG("display close");
                    running = false;
                    break;
                case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
                    ALLEGRO_DEBUG("halt drawing");
                    ALLEGRO_DEBUG("after set target");
                    al_acknowledge_drawing_halt(dpy);
                    break;
                case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
                    ALLEGRO_DEBUG("resume drawing");
                    al_acknowledge_drawing_resume(dpy);
                    ALLEGRO_DEBUG("done waiting for surface recreated");
                    break;
                case ALLEGRO_EVENT_DISPLAY_RESIZE:
                    ALLEGRO_DEBUG("display resize");
                    al_acknowledge_resize(dpy);
                    ALLEGRO_DEBUG("done resize");
                    set_transform(dpy);
                    break;
                case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
                    set_transform(dpy);
                    break;
            }
        }

        // inject input
        InjectInputs( g_touches );

        double interval = 1.0/60.0;
       
        // logic
        GameLogic(interval);

        // render
        set_transform(dpy);
        al_clear_to_color(al_map_rgb(30, 30, 30));
        GameRender(interval);
        al_flip_display();
    }
    
//    al_shutdown_ttf_addon();
//    al_shutdown_font_addon();

    ALLEGRO_DEBUG("done");
    return 0;
}

/* vim: set sts=3 sw=3 et: */
