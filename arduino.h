#include <unistd.h>
#include <stdio.h>
#include "gpio_lib.c"
#define MSBFIRST 1
#define LSBFIRST 0

void serial_println_char(char text);
void serial_println_int(int inp);
void serial_println(char *text);
void serial_print(char *text);
void serial_begin(int btl);
void setup();
void loop();
struct srl {
void ( *println_int ) (int inp);
void ( *println_char ) (char text);
void ( *println ) (char *text);
void ( *print ) (char *text);
void ( *begin ) (int btl);
} Serial = {serial_println_int,serial_println_char,serial_println,serial_print,serial_begin};
void serial_begin(int btl){
}
void serial_println_int(int inp){
printf("%d \n",inp);
}
void serial_println_char(char text){
printf("%c \n",text);
}
void serial_println(char *text){
printf("%s \n",text);
}
void serial_print(char *text){
printf("%s",text);
}
int pinMode(int pin,int mode){
return sunxi_gpio_set_cfgpin(SUNXI_GPD(pin),mode);
}
int digitalWrite(int pin,int value){
return sunxi_gpio_output(SUNXI_GPD(pin),value);
}
int digitalRead(int pin){
return sunxi_gpio_input(SUNXI_GPD(pin));
}
void shiftOut(int myDataPin, int myClockPin,int wfst, int myDataOut) {
    
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low
  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  //for each bit in the byte myDataOut
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState=1;
    }
    else {	
      pinState=0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
  //stop shifting
  digitalWrite(myClockPin, 0);
}
int delay(int msec){
usleep(msec*1000);
}
int init(){
    if(SETUP_OK!=sunxi_gpio_init()){
        printf("Failed to initialize GPIO\n");
        return 1;
    }else{
        return 0;
    }
}


