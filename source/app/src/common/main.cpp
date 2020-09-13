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


int main(int argc, char **argv)
{
    printf("Interkommi.\n");
    
    
    GLWindow * window = 0;
    CRect screen_rect = CRectMake(0, 0, 1024, 768);
    
    SetupBlock setup_studiomux = [=] (ZDB * a_zdb) {

        
        
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
            
            

            
     
            
            Interkomm * studiomux = Interkomm::Kit(a_zdb);

            a_zdb->gl->base_context->addSubview(studiomux);
            //studiomux->app_version_label->setText("123");
            
            a_zdb->midi->internal_manager->create_omni_source();
            
            createDirectoryAtPath("/Sessions/");

            //a_zdb->midi->addDelegate(studiomux);
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

                    if (itemExistsAtPath("/States/studiomux.mls")) {
                        //studiomux->restore_state("/States/studiomux.mls");
                    }
                    else {
                        printf("FAILED TO RESTORE STATE from: %s\n", "States/studiomux.mls");
                    }
                    
                    
                    //1studiomux->restore_state();

                    
                }, 0, context);
            });

        });
        
        
        a_zdb->gl->console->backgroundColor = GLColorWithAlpha(GLBlack(), 0.02);
    };
    
    bool use_ab_on_ios = true;
    bool use_iaa_on_ios = true;
    string api_key = "H4sIAAAAAAAAA63Ty07DMBAF0F+pZh01aZ5V/oAVC5YNqvIwENE4kR8ooeq/46JBgKnsIM0uuteZs7pnYPPUiwXKKIBG8+7EjrweGJQgle76cdAzBKDF6SjbF/a72NbXj0bLsgqr0DybRqEklIczqGW6Pq21eDY5Xnz4+nFzr9VmZ4qOyVb0k+pHfrOXusFLkvHIBEPN9VPdKi2YMOk7E6NJ35iQnyeSS7DKjj12bNs7Ojvx2Iltx3R26rFT207o7MxjZ7ad0tm5x85tO6OzC49d2HZOZ+899t62i3/ajZhv2XfcOW+sv+W/6k8xWie6Ro01seiaMtbEomvAWBOLrtliTSy6xoo1seiaKNbEomuYWK8XHwPoO5NWIYayCl/ZUoVxEUVw+QBramcc5AcAAA==:fJjhY24mt5beP+fviBtxh5bsTTWT0ojDGo8bgLW9aWLVsov42/k08YwjEdXAC9/e1FOSkNmp51CRLeM/1fEm/yzyD4nd8gEYMLgSd38Ha1JJcCbOh2P1y5jCfTZrT5lo";
    
    SetupCallback * block = new SetupCallback(setup_studiomux);
    
    window = new GLWindow(screen_rect, false, argv, argc, block, true, true, true, api_key, false);
        
    exit(0);
    
}



