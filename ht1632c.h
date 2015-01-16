/*
 * ht1632c.h
 * defintions for Holtek ht1632c LED driver.
 */

#ifndef ht1632c_h
#define ht1632c_h

#include "application.h"


/* Leaflab Maple specific definitions */

typedef uint8_t prog_uint8_t;
typedef uint16_t prog_uint16_t;
uint8_t inline pgm_read_byte_near(uint8_t *ptr) { return (uint8_t)*ptr; }
uint16_t inline pgm_read_word_near(uint16_t *ptr) { return (uint16_t)*ptr; }
#define pinLO(_pin)	(PIN_MAP[_pin].gpio_peripheral->BRR = PIN_MAP[_pin].gpio_pin)
#define pinHI(_pin)	(PIN_MAP[_pin].gpio_peripheral->BSRR = PIN_MAP[_pin].gpio_pin)
#define pinTOGGLE(_pin)	(PIN_MAP[_pin].gpio_peripheral->ODR ^= PIN_MAP[_pin].gpio_pin)
#define PROGMEM
#define inline inline __attribute__((always_inline))

/*
 * commands written to the chip consist of a 3 bit "ID", followed by
 * either 9 bits of "Command code" or 7 bits of address + 4 bits of data.
 */
#define HT1632_ID_CMD        4	/* ID = 100 - Commands */
#define HT1632_ID_RD         6	/* ID = 110 - Read RAM */
#define HT1632_ID_WR         5	/* ID = 101 - Write RAM */

#define HT1632_CMD_SYSDIS 0x00	/* CMD= 0000-0000-x Turn off oscil */
#define HT1632_CMD_SYSON  0x01	/* CMD= 0000-0001-x Enable system oscil */
#define HT1632_CMD_LEDOFF 0x02	/* CMD= 0000-0010-x LED duty cycle gen off */
#define HT1632_CMD_LEDON  0x03	/* CMD= 0000-0011-x LEDs ON */
#define HT1632_CMD_BLOFF  0x08	/* CMD= 0000-1000-x Blink ON */
#define HT1632_CMD_BLON   0x09	/* CMD= 0000-1001-x Blink Off */
#define HT1632_CMD_SLVMD  0x10	/* CMD= 0001-00xx-x Slave Mode */
#define HT1632_CMD_MSTMD  0x14	/* CMD= 0001-01xx-x Master Mode */
#define HT1632_CMD_RCCLK  0x18	/* CMD= 0001-10xx-x Use on-chip clock */
#define HT1632_CMD_EXTCLK 0x1C	/* CMD= 0001-11xx-x Use external clock */
#define HT1632_CMD_COMS00 0x20	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS01 0x24	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS10 0x28	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS11 0x2C	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_PWM    0xA0	/* CMD= 101x-PPPP-x PWM duty cycle */

#define HT1632_ID_LEN     (1 << 2)  /* IDs are 3 bits */
#define HT1632_CMD_LEN    (1 << 7)  /* CMDs are 8 bits */
#define HT1632_DATA_LEN   (1 << 7)  /* Data are 4*2 bits */
#define HT1632_ADDR_LEN   (1 << 6)  /* Address are 7 bits */

#define HT1632_CS_NONE       0  /* None of ht1632c selected */
#define HT1632_CS_ALL       32 /* All of ht1632c selected */

#define GEOM_32x16	    32	/* 32x16 */
#define GEOM_24x16	    24	/* 24x16 */
#define GEOM_32x8	     8	/* 32x8 */

#define BLACK        0
#define GREEN        1
#define RED          2
#define ORANGE       3
#define RANDOMCOLOR  4
#define MULTICOLOR   8
#define BLINK       16

#define BOLD         1
#define UNDERLINE    2
#define ITALIC       4
#define PROPORTIONAL 8

#define LEFT         0
#define RIGHT        1
#define UP           0
#define DOWN         1

#define FONT_4x6     1
#define FONT_5x7     2
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
#define FONT_8x13   17
#define FONT_8x13B  18
//#define FONT_8x13O  19
//#define FONT_9x15   20
//#define FONT_9x15B  21
#define FONT_8x16   22
#define FONT_8x16B  23

//#define FONT_8x13BK 118

/* USE_NLFB experimental feature: use nonlinear framebuffer addressing, faster then linear addressing */
#define USE_NLFB 


class ht1632c : public Print {

#ifdef putchar
#undef putchar
#endif

public:
    ht1632c(const uint8_t data, const uint8_t wr, const uint8_t clk, const uint8_t cs, const uint8_t geometry, const uint8_t number);

    void pwm(uint8_t value);
    void sendframe();
    void clear();
    void plot(uint8_t x, uint8_t y, uint8_t color);
    uint8_t getpixel(uint8_t x, uint8_t y);
    uint8_t putchar(int x, int y, char c, uint8_t color = GREEN, uint8_t attr = 0, uint8_t bgcolor = BLACK);
    void putbitmap(int x, int y, prog_uint16_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
    void hscrolltext(int y, char *text, uint8_t color, int delaytime, int times = 1, uint8_t dir = LEFT, uint8_t attr = 0, uint8_t bgcolor = BLACK);
    void vscrolltext(int x, char *text, uint8_t color, int delaytime, int times = 1, uint8_t dir = UP, uint8_t attr = 0, uint8_t bgcolor = BLACK);
    void setfont(uint8_t userfont);
    void line(int x0, int y0, int x1, int y1, uint8_t color);
    void rect(int x0, int y0, int x1, int y1, uint8_t color);
    void circle(int xm, int ym, int r, uint8_t color);
    void ellipse(int x0, int y0, int x1, int y1, uint8_t color);
    void fill(uint8_t x, uint8_t y, uint8_t color);
    void bezier(int x0, int y0, int x1, int y1, int x2, int y2, uint8_t color);
    void profile();

    virtual size_t write(uint8_t chr);
    virtual size_t write(const char *str);

    uint8_t x_max;
    uint8_t y_max;
    int fps;

private:
    void _sendcmd(uint8_t cs, uint8_t command);
    void _setup(uint8_t number);
    void _update_fb(uint8_t *ptr, uint8_t target, uint8_t pixel);

    void _set(uint8_t pin);
    void _toggle(uint8_t pin);
    void _reset(uint8_t vpinal);
    void _pulse(uint8_t num, uint8_t pin);

    void _writebits (uint8_t bits, uint8_t msb);
    void _chipselect(uint8_t cs);

    void _fill_r(uint8_t x, uint8_t y, uint8_t color);
    void _fill_l(uint8_t x, uint8_t y, uint8_t color);

    static uint8_t *g_fb;
    static uint8_t *r_fb;
    uint16_t fb_size;
    uint8_t cs_max;
    boolean bicolor;
    prog_uint8_t *font;
    prog_uint16_t *wfont;
    uint8_t font_width;
    uint8_t font_height;
    uint8_t x_cur;
    uint8_t y_cur;

    static uint8_t _data;
    static uint8_t _wr;
    static uint8_t _clk;
    static uint8_t _cs;
};

#endif
