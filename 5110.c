#include <stdio.h>
#include "arduino.h"
#include "readout.c"
#include "5110.h"

int main(int argc,char **argv){
if(init() != 0){
printf("init failed!\n");
return 1;
}
setup();
while(1) loop();
return 0;
}
