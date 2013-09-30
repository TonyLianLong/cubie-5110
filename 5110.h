#include <stdlib.h>
// The pins to use on the arduino
#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3
#define PIN_LED 9

// COnfiguration for the LCD
#define LCD_C     LOW
#define LCD_D     HIGH
#define LCD_CMD   0
 
// Size of the LCD
#define LCD_X     84
#define LCD_Y     48
int scrollPosition = -10;
 
int ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c &yen;
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
,{0x00, 0x06, 0x09, 0x09, 0x06} // 7f →
};
int replace(char intext){
    switch((int)intext){
        case 'A':
            return 0xdc;
            break;
        case 'B':
            return 0xdd;
            break;
        case 'C':
            return 0xde;
            break;
        case 'D':
            return 0xdf;
            break;
        case 'E':
            return 0xe0;
            break;
        case 'F':
            return 0xe1;
            break;
        case 'G':
            return 0xe2;
            break;
        case 'H':
            return 0xe3;
            break;
        case 'I':
            return 0xe4;
            break;
        case 'J':
            return 0xe5;
            break;
        case 'K':
            return 0xe6;
            break;
        case 'L':
            return 0xe7;
            break;
        case 'M':
            return 0xe8;
            break;
        case 'N':
            return 0xe9;
            break;
        case 'O':
            return 0xea;
            break;
        case 'P':
            return 0xeb;
            break;
        case 'Q':
            return 0xec;
            break;
        case 'R':
            return 0xed;
            break;
        case 'S':
            return 0xee;
            break;
        case 'T':
            return 0xef;
            break;
        case 'U':
            return 0xf0;
            break;
        case 'V':
            return 0xf1;
            break;
        case 'W':
            return 0xf2;
            break;
        case 'X':
            return 0xf3;
            break;
        case 'Y':
            return 0xf4;
            break;
        case 'Z':
            return 0xf5;
            break;
        case 'a':
            return 0xfc;
            break;
        case 'b':
            return 0xfd;
            break;
        case 'c':
            return 0xfe;
            break;
        case 'd':
            return 0xff;
            break;
        case 'e':
            return 0x100;
            break;
        case 'f':
            return 0x101;
            break;
        case 'g':
            return 0x102;
            break;
        case 'h':
            return 0x103;
            break;
        case 'i':
            return 0x104;
            break;
        case 'j':
            return 0x105;
            break;
        case 'k':
            return 0x106;
            break;
        case 'l':
            return 0x107;
            break;
        case 'm':
            return 0x108;
            break;
        case 'n':
            return 0x109;
            break;
        case 'o':
            return 0x10a;
            break;
        case 'p':
            return 0x10b;
            break;
        case 'q':
            return 0x10c;
            break;
        case 'r':
            return 0x10d;
            break;
        case 's':
            return 0x10e;
            break;
        case 't':
            return 0x10f;
            break;
        case 'u':
            return 0x110;
            break;
        case 'v':
            return 0x111;
            break;
        case 'w':
            return 0x112;
            break;
        case 'x':
            return 0x113;
            break;
        case 'y':
            return 0x114;
            break;
        case 'z':
            return 0x115;
            break;
        case ' ':
            return 0x0;
            break;
        case ',':
            return 0xc7;
            break;
        case '.':
            return 0xc9;
            break;
        case '\'':
            return 0xc2;
            break;
        case '\"':
            return 0xbd;
            break;
        default:
            return 0x54;
            //it's □,May ■ ? (55)
        break;
    }
    return 0;
}
void LcdWrite(int dc, int data)
{
    digitalWrite(PIN_DC, dc);
    digitalWrite(PIN_SCE, LOW);
    shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
    digitalWrite(PIN_SCE, HIGH);
}
void LcdCharacter(char character)
{
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}
void LcdFCharacter(char character)
{
  LcdWrite(LCD_D, 0xff);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, 0xff-ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0xff);
}
 
void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}
 
void LcdInitialise(void)
{
  pinMode(PIN_SCE,   OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC,    OUTPUT);
  pinMode(PIN_SDIN,  OUTPUT);
  pinMode(PIN_SCLK,  OUTPUT);
 
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
 
  LcdWrite(LCD_CMD, 0x21);  // LCD Extended Commands.
  LcdWrite(LCD_CMD, 0xBf);  // Set LCD Vop (Contrast). //B1
  LcdWrite(LCD_CMD, 0x04);  // Set Temp coefficent. //0x04
  LcdWrite(LCD_CMD, 0x14);  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_CMD, 0x0C);  // LCD in normal mode. 0x0d for inverse
  LcdWrite(LCD_C, 0x20);
  LcdWrite(LCD_C, 0x0C);
}
/**
 * gotoXY routine to position cursor
 * x - range: 0 to 84
 * y - range: 0 to 5
 */
void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.
}
void LcdPrint(char *characters,int x,int y)
{
    gotoXY(x*7,y);
    while (*characters)
    {
        LcdCharacter(*characters++);
    }
}

void LcdFPrint(char *characters,int x,int y)
{
    gotoXY(x*7,y);
    while (*characters)
    {
        LcdFCharacter(*characters++);
    }
}
int LcdShow(int showdata[],int x,int y){
    gotoXY(x,y);
    for (int index = 0; index < 16; index++)
    {
        LcdWrite(LCD_D, showdata[index*2+1]);
    }
    gotoXY(x,y+1);
    for (int index = 0; index < 16; index++)
    {
        LcdWrite(LCD_D, showdata[index*2]);
    }
}
int LcdFShow(int showdata[],int x,int y){
    gotoXY(x,y);
    for (int index = 0; index < 16; index++)
    {
        LcdWrite(LCD_D, 0xff-showdata[index*2+1]);
    }
    gotoXY(x,y+1);
    for (int index = 0; index < 16; index++)
    {
        LcdWrite(LCD_D, 0xff-showdata[index*2]);
    }
}
void drawBox(void)
{
  int j;
  for(j = 0; j < 84; j++) // top
  {
    gotoXY(j, 0);
    LcdWrite(1, 0x01);
  }
 
  for(j = 0; j < 84; j++) //Bottom
  {
    gotoXY(j, 5);
    LcdWrite(1, 0x80);
  }
 
  for(j = 0; j < 6; j++) // Right
  {
    gotoXY(83, j);
    LcdWrite(1, 0xff);
  }
 
  for(j = 0; j < 6; j++) // Left
  {
    gotoXY(0, j);
    LcdWrite(1, 0xff);
  }
}
void drawHLine(unsigned int length,unsigned int rl,int point){
  int i,j,k;
  if(point >= 0){
    for(i = 0;i<length;i++){
      if(rl){
        LcdWrite(1, 0x08);
      }else{
        if(i == (int)(point/7)){
          for(j = 0; j < point%7; j++){
            LcdWrite(1, 0x08);
          }
          LcdWrite(1, 0x18);
          LcdWrite(1, 0x3C);
          LcdWrite(1, 0x18);
          for(k=7-j-3,j=0; j < k; j++){
            LcdWrite(1, 0x08);
          }
        }else{
          for(j = 0; j < 7; j++){
            LcdWrite(1, 0x08);
          }
        }
      }
    }
  }else{
    for(i = 0;i<length;i++){
      if(rl){
        LcdWrite(1, 0x08);
      }else{
        for(j = 0; j < 7; j++){
          LcdWrite(1, 0x08);
        }
      }
    }
  }
}
int LcdPrintFull(char text[],int x,int y)
{
    printf("Start print length:%d\n",strlen(text));
    for(int i=0;i<strlen(text);i++){
        if((text[i] >> 7) & 1){
            //is it CN?
            if(8*(x+2) >= 84)x=0,y+=2;
            int inint[33] = {};
            read16(text[i],text[i+1],text[i+2],inint);
            printf("text2:%d\n",inint[2]);
            LcdShow(inint,8*x,y);
            //Why x*8? bec 8 is a non CN char,16 is a CN char,and we need to use x+=2 to show CN char
            i+=2;
            x+=2;
        }else{
            /*if(8*(x+1) >= 84)x = 0,y+=2;
            printf("Non CN: %c %d",text[i],(text[i] >> 7));
            //gotoXY(8*x,y+1);
            short cht;
            for(int index=0;index < 8;index++){
                if(index <2 || index >6){
                    gotoXY(8*x+index*2,y);
                    LcdWrite(LCD_D,0x00);
                    LcdWrite(LCD_D,0x00);
                    printf("gotox[j]:%d\n",8*x+index*2);
                    gotoXY(8*x+index*2,y+1);
                    LcdWrite(LCD_D,0x00);
                    LcdWrite(LCD_D,0x00);
                    continue;
                }
                for(int j=0;j < 2;j++){
                gotoXY(8*x+index*2+j,y);
                    printf("gotox:%d\n",8*x+index*2+j);
                cht =
                (((ASCII[text[i] - 0x20][index] >> 3)&1) << 7)+
                (((ASCII[text[i] - 0x20][index] >> 3)&1) << 6)+
                (((ASCII[text[i] - 0x20][index] >> 2)&1) << 5)+
                (((ASCII[text[i] - 0x20][index] >> 2)&1) << 4)+
                (((ASCII[text[i] - 0x20][index] >> 1)&1) << 3)+
                (((ASCII[text[i] - 0x20][index] >> 1)&1) << 2)+
                (((ASCII[text[i] - 0x20][index] >> 0)&1) << 1)+
                (((ASCII[text[i] - 0x20][index] >> 0)&1) << 0);
                printf("char[1]:%x\n",cht);
                LcdWrite(LCD_D, cht);
                gotoXY(8*x+index*2+j,y+1);
                cht =
                (((ASCII[text[i] - 0x20][index] >> 7)&1) << 7)+
                (((ASCII[text[i] - 0x20][index] >> 7)&1) << 6)+
                (((ASCII[text[i] - 0x20][index] >> 6)&1) << 5)+
                (((ASCII[text[i] - 0x20][index] >> 6)&1) << 4)+
                (((ASCII[text[i] - 0x20][index] >> 5)&1) << 3)+
                (((ASCII[text[i] - 0x20][index] >> 5)&1) << 2)+
                (((ASCII[text[i] - 0x20][index] >> 4)&1) << 1)+
                (((ASCII[text[i] - 0x20][index] >> 4)&1) << 0);
                printf("char[2]:%x\n",cht);
                LcdWrite(LCD_D, cht);
                }
            }*/
            // It's too old AND it doesn't work(and bad by this)!
            //LcdCharacter(text[i]);
            if(8*(x+2) >= 84)x=0,y+=2;
            int inint[33] = {};
            read16_index(replace(text[i]),inint);
            printf("text2:%d\n",inint[2]);
            LcdShow(inint,8*x,y);
            //Why x*8? bec 8 is a non CN char,16 is a CN char,and we need to use x+=2 to show CN char
            x+=2;
        }
    }
    return 0;
}
int LcdFPrintFull(char text[],int x,int y)
{
    printf("Start print length:%d\n",strlen(text));
    for(int i=0;i<strlen(text);i++){
        if((text[i] >> 7) & 1){
            //is it CN?
            if(8*(x+2) >= 84)x=0,y+=2;
            int inint[33] = {};
            read16(text[i],text[i+1],text[i+2],inint);
            printf("text2:%d\n",inint[2]);
            LcdFShow(inint,8*x,y);
            //Why x*8? bec 8 is a non CN char,16 is a CN char,and we need to use x+=2 to show CN char
            i+=2;
            x+=2;
        }else{
            /*if(8*(x+1) >= 84)x = 0,y+=2;
             printf("Non CN: %c %d",text[i],(text[i] >> 7));
             //gotoXY(8*x,y+1);
             short cht;
             for(int index=0;index < 8;index++){
             if(index <2 || index >6){
             gotoXY(8*x+index*2,y);
             LcdWrite(LCD_D,0x00);
             LcdWrite(LCD_D,0x00);
             printf("gotox[j]:%d\n",8*x+index*2);
             gotoXY(8*x+index*2,y+1);
             LcdWrite(LCD_D,0x00);
             LcdWrite(LCD_D,0x00);
             continue;
             }
             for(int j=0;j < 2;j++){
             gotoXY(8*x+index*2+j,y);
             printf("gotox:%d\n",8*x+index*2+j);
             cht =
             (((ASCII[text[i] - 0x20][index] >> 3)&1) << 7)+
             (((ASCII[text[i] - 0x20][index] >> 3)&1) << 6)+
             (((ASCII[text[i] - 0x20][index] >> 2)&1) << 5)+
             (((ASCII[text[i] - 0x20][index] >> 2)&1) << 4)+
             (((ASCII[text[i] - 0x20][index] >> 1)&1) << 3)+
             (((ASCII[text[i] - 0x20][index] >> 1)&1) << 2)+
             (((ASCII[text[i] - 0x20][index] >> 0)&1) << 1)+
             (((ASCII[text[i] - 0x20][index] >> 0)&1) << 0);
             printf("char[1]:%x\n",cht);
             LcdWrite(LCD_D, cht);
             gotoXY(8*x+index*2+j,y+1);
             cht =
             (((ASCII[text[i] - 0x20][index] >> 7)&1) << 7)+
             (((ASCII[text[i] - 0x20][index] >> 7)&1) << 6)+
             (((ASCII[text[i] - 0x20][index] >> 6)&1) << 5)+
             (((ASCII[text[i] - 0x20][index] >> 6)&1) << 4)+
             (((ASCII[text[i] - 0x20][index] >> 5)&1) << 3)+
             (((ASCII[text[i] - 0x20][index] >> 5)&1) << 2)+
             (((ASCII[text[i] - 0x20][index] >> 4)&1) << 1)+
             (((ASCII[text[i] - 0x20][index] >> 4)&1) << 0);
             printf("char[2]:%x\n",cht);
             LcdWrite(LCD_D, cht);
             }
             }*/
            //LcdCharacter(text[i]);
            if(8*(x+2) >= 84)x=0,y+=2;
            int inint[33] = {};
            read16_index(replace(text[i]),inint);
            printf("text2:%d\n",inint[2]);
            LcdFShow(inint,8*x,y);
            //Why x*8? bec 8 is a non CN char,16 is a CN char,and we need to use x+=2 to show CN char
            x+=2;
        }
    }
    return 0;
}
void Scroll(char *message)
{
  for (int i = scrollPosition; i < scrollPosition + 11; i++)
  {
    if ((i >= (sizeof(message)/sizeof(char))) || (i < 0))
    {
      LcdCharacter(' ');
    }
    else
    {
      LcdCharacter(message[i]);
    }
  }
  scrollPosition++;
  if ((scrollPosition >= (sizeof(message)/sizeof(char))) && (scrollPosition > 0))
  {
    scrollPosition = -10;
  }
}
 
void setup(void)
{
  Serial.begin(9600);
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED,HIGH);
  Serial.println("Start!");
  LcdInitialise();
  LcdClear();
  LcdPrintFull("呼吸呼吸",0,0);
  LcdPrint("abc",0,2);
}
char dt[100] = {};
unsigned long long i = 0;
void loop(void)
{
  /*Serial.print("I sent:");
  Serial.println_int(i);
  gotoXY(0,0);
  sprintf(dt,"%d",i);
  LcdPrint(dt);
  i++;
  delay(100);*/
}
