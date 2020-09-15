/* A simple program to show how to set up zdb.
 */
#include <stdio.h>
#include <stdlib.h>

#include "GLWindow.h"

#include <GLView.h>
#include <GLLabel.h>
#include <GLContext.h>
#include "ZDBConsole.h"
#include "interkomm_resources.h"
#include "InternalMidiManager.h"
#include "Interkomm.h"

int User::ID{0};
int Channel::ID{0};
int Role::ID{0};


int main(int argc, char **argv)
{
    printf("Interkommi.\n");
    
    
    GLWindow * window = 0;
    CRect screen_rect = CRectMake(0, 0, 1024, 768);
    
    SetupBlock setup_interkomm = [=] (ZDB * a_zdb) {

        
        
        __unused interkomm_resources * modstep_resource = new interkomm_resources(a_zdb);
        
        GLTextView * splashscreen = new GLTextView(a_zdb);
        splashscreen->font_size_level->setValue(9);
        splashscreen->textAlignment = GLTextAlignmentCenter;
        splashscreen->baseLine = GLBaselineCenter;
        splashscreen->allow_input = false;
        splashscreen->setIsPopupLayer(false);
        splashscreen->fontColor = TALightLightGray();
        splashscreen->backgroundColor = TADarkGray();
        //splashscreen->setImage(zdb->gl->imageWithName("icon_1024X1024.png"));
        splashscreen->setText("loading interkomm.");
        a_zdb->gl->base_context->backgroundColor = TAMidGray();
        GLContext * context = a_zdb->gl->addPopup(splashscreen, true, 0.04, GLColorMakeChar(29, 39, 45, 1), [=]{});

        context->isTouchEnabled = false;
        
        a_zdb->gl->addTimerWithInterval(0.05, 1, [=]{
            
            //load app
            
        
            
            a_zdb->midi->mirroring = true;
            a_zdb->midi->use_local_ports = true;
            
            

            
     
            Interkomm * interkomm = Interkomm::Kit(a_zdb);


            a_zdb->gl->base_context->addSubview(interkomm);
            //interkomm->app_version_label->setText("123");
            
            a_zdb->midi->internal_manager->create_omni_source();
            
            createDirectoryAtPath("/Sessions/");

            //a_zdb->midi->addDelegate(interkomm);
            //a_zdb->midi->usb_bridge->usb_port->block_connect = false;
            
            a_zdb->gl->addTimerWithInterval(15, -1, [=]{
                a_zdb->dispatch->on_background([=]{
                    //sequence->session->autosave();
                });
            });

            createDirectoryAtPath("/States/");
            
            a_zdb->gl->addTimerWithInterval(0.5, 1, [=]{
                
                a_zdb->gl->animateFloat(&context->global_opacity, 0, 3.1337, false, false, false, GLAnimationExp, [=]{
                    
                    splashscreen->removeFromSuperview();
                    
                    delete splashscreen;
                    context->pop_context();

                    if (itemExistsAtPath("/States/interkomm.mls")) {
                        //interkomm->restore_state("/States/interkomm.mls");
                    }
                    else {
                        printf("FAILED TO RESTORE STATE from: %s\n", "States/interkomm.mls");
                    }
                    
                    
                    //1interkomm->restore_state();

                    
                }, 0, context);
            });

        });
        
        
        a_zdb->gl->console->backgroundColor = GLColorWithAlpha(GLBlack(), 0.02);
    };
    
    
    SetupCallback * block = new SetupCallback(setup_interkomm);
    window = new GLWindow(screen_rect, false, argv, argc, block, true, true);

    exit(0);
    
}



