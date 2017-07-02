This is a nokia 5110 screen driver for Cubieboard(or Cubietruck,or other devices).
It can show you Chinese,not just English.
By TLL and it use sunduino[2] library,it also use aguegu's Bitmapfont library(https://github.com/aguegu/BitmapFont).

Sunduino[2] is a part or Sunduino(Sunxi arduino),it means we can copy the codes on arduino and paste it on your sunxi device(like Cubie),Then try a little modify,OK,then you can run it on your sunxi device!
This code is from arduino and I modify it,you can see "setup()" and "loop()" on "5110.h".
Good software helps I study.

OK,Let me tell you what can you do:
LcdPrint  print EN string
LcdPrintFull  print Full string like CN
LcdInitialise  Init
LcdClear  clear,you know
Scroll  print scroll string
[Is it wrong?!Tell me!!]
LcdFPrintFull  print Full string by black bg and white text
drawHLine  draw Line and a point
drawBox  draw a box
LcdFPrint  print EN string by black bg and white text
LcdShow  show full data by … (I don't know how to say that,although I wrote this)
LcdFShow  like LcdShow,but you know what "F" means(F is a Chinese Pinyin "Fan"'s first char)
gotoXY  go to where you want to go
LcdCharacter  show a char in EN
LcdFCharacter  like LcdCharacter
LcdWrite  write a 256 byte data direct
replace  replace half EN char to Full EN char in GB2312 [use Lcd(F)Print to print EN will use it]
