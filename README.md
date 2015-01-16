HT1632C Library
===============

Spark Core specific library for HT1632C based led dot matrix displays (eg. Sure Electronics)
adapted from Arduino library found at https://code.google.com/p/ht1632c/

In your project include the library header, and instantiate HT1632C class with correct port and pin numbers.

Library Usage
-------------

#include "ht1632c.h"

usage: ht1632c(data, wr, clk, cs, geometry, number);
ht1632c ledMatrix = ht1632c( D0, D1, D2, D3, GEOM_32x16, 2);

Note: pin numbers are Spark Core designations (D0-D7, A0-A7)

With the library there are over 20 fonts included. You cannot fill flash memory compiling all provided fonts, so you must comment some font definitions in ht1632c.h:

```
//#define FONT_4x6     1
//#define FONT_5x7     2
#define FONT_5x8     3
#define FONT_5x7W    4
//#define FONT_6x10    5
//#define FONT_6x12    6
//#define FONT_6x13    7
//#define FONT_6x13B   8
//#define FONT_6x13O   9
//#define FONT_6x9    10
//#define FONT_7x13   11
//#define FONT_7x13B  12
//#define FONT_7x13O  13
//#define FONT_7x14   14
//#define FONT_7x14B  15
#define FONT_8x8    16
//#define FONT_8x13   17
//#define FONT_8x13B  18
//#define FONT_8x13O  19
#define FONT_9x15   20
#define FONT_9x15B  21
#define FONT_8x16   22
#define FONT_8x16B  23
```

Control functions
-----------------

void pwm(byte value);
void sendframe();
void clear();
pwm() sets the display brightness. Input value range is 0-15.

sendframe() writes buffer memory to display. It's required after one or more text of graphic function.

clear() clears buffer memory and display. It doesn't require sendframe().

Text functions
--------------

byte putchar(int x, int y, char c, byte color = GREEN, byte attr = 0);
void hscrolltext(int y, const char *text, byte color, int delaytime, int times = 1, byte dir = LEFT);
void vscrolltext(int x, const char *text, byte color, int delaytime, int times = 1, byte dir = UP);
void setfont(byte userfont);
putchar() puts a character c at x, y coordinates of color color (defaults GREEN) with attributes attr (future use).

hscrolltext() and vscrolltext() does horizontal or vertical scroll of a text text of color color with a delay of delaytime milliseconds, and repeats times times, with direction dir (RIGHT/LEFT or UP/DOWN).

setfont() change font to userfont.

Graphic functions
-----------------

void plot (byte x, byte y, byte color);
byte getpixel (byte x, byte y);
void line(int x0, int y0, int x1, int y1, byte color);
void rect(int x0, int y0, int x1, int y1, byte color);
void circle(int xm, int ym, int r, byte color);
void ellipse(int x0, int y0, int x1, int y1, byte color);
void fill (byte x, byte y, byte color);
void bezier(int x0, int y0, int x1, int y1, int x2, int y2, byte color);
void putbitmap(int x, int y, prog_uint16_t *bitmap, byte w, byte h, byte color);
plot() put a pixel of color color in x, y coordinates.

getpixel() reads the color of the pixel in x, y coordinates.

line() draw a line from x0, y0 to x1, y1 of color color.

rect() draw a rectangle with vertexes in x0, y0 and x1, y1 of color color.

circle() draw a circle with center in xm, ym and radius of r of color color.

ellipse() draw an ellipse inscribed in the rectangle with vertexes in x0, y0 and x1, y1 of color color.

bezier() draw a bezier curve from x0, y0 to x2, y2 with direction x1, y1 of color color.

fill() boundary flood fill of color color starting from x, y.

putbitmap() puts a bitmap of color color, of width w and height h, in the coordinates x, y. Bitmap is supposed to be > 8 pixel wide, stored in flash.

