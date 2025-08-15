#include "power.h"
void idle_loop(){
    while(1){
        asm volatile("hlt");
    }
}
