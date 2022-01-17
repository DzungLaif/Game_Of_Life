/*
 * ILI9225.h
 *
 * Created: 11.08.2016 17:37:57
 */ 
#ifndef LCD_HANDLE_H_
#define LCD_HANDLE_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

// Hardware
#define ILI9225_CS_DDR		DDRC
#define ILI9225_CS_PORT		PORTC
#define ILI9225_CS_BIT		PORTC5

#define ILI9225_RST_DDR		DDRC
#define ILI9225_RST_PORT	PORTC
#define ILI9225_RST_BIT		PORTC4

#define ILI9225_RS_DDR		DDRC
#define ILI9225_RS_PORT		PORTC
#define ILI9225_RS_BIT		PORTC3

#define ILI9225_SDI_DDR		DDRC
#define ILI9225_SDI_PORT	PORTC
#define ILI9225_SDI_BIT		PORTC2

#define ILI9225_CLK_DDR		DDRC
#define ILI9225_CLK_PORT	PORTC
#define ILI9225_CLK_BIT		PORTC1

/* ILI9225 screen size */
#define ILI9225_LCD_WIDTH  176
#define ILI9225_LCD_HEIGHT 220

/* ILI9225 LCD Registers */
#define ILI9225_DRIVER_OUTPUT_CTRL      (0x01u)  // Driver Output Control
#define ILI9225_LCD_AC_DRIVING_CTRL     (0x02u)  // LCD AC Driving Control
#define ILI9225_ENTRY_MODE              (0x03u)  // Entry Mode
#define ILI9225_DISP_CTRL1              (0x07u)  // Display Control 1
#define ILI9225_BLANK_PERIOD_CTRL1      (0x08u)  // Blank Period Control
#define ILI9225_FRAME_CYCLE_CTRL        (0x0Bu)  // Frame Cycle Control
#define ILI9225_INTERFACE_CTRL          (0x0Cu)  // Interface Control
#define ILI9225_OSC_CTRL                (0x0Fu)  // Osc Control
#define ILI9225_POWER_CTRL1             (0x10u)  // Power Control 1
#define ILI9225_POWER_CTRL2             (0x11u)  // Power Control 2
#define ILI9225_POWER_CTRL3             (0x12u)  // Power Control 3
#define ILI9225_POWER_CTRL4             (0x13u)  // Power Control 4
#define ILI9225_POWER_CTRL5             (0x14u)  // Power Control 5
#define ILI9225_VCI_RECYCLING           (0x15u)  // VCI Recycling
#define ILI9225_RAM_ADDR_SET1           (0x20u)  // Horizontal GRAM Address Set
#define ILI9225_RAM_ADDR_SET2           (0x21u)  // Vertical GRAM Address Set
#define ILI9225_GRAM_DATA_REG           (0x22u)  // GRAM Data Register
#define ILI9225_GATE_SCAN_CTRL          (0x30u)  // Gate Scan Control Register
#define ILI9225_VERTICAL_SCROLL_CTRL1   (0x31u)  // Vertical Scroll Control 1 Register
#define ILI9225_VERTICAL_SCROLL_CTRL2   (0x32u)  // Vertical Scroll Control 2 Register
#define ILI9225_VERTICAL_SCROLL_CTRL3   (0x33u)  // Vertical Scroll Control 3 Register
#define ILI9225_PARTIAL_DRIVING_POS1    (0x34u)  // Partial Driving Position 1 Register
#define ILI9225_PARTIAL_DRIVING_POS2    (0x35u)  // Partial Driving Position 2 Register
#define ILI9225_HORIZONTAL_WINDOW_ADDR1 (0x36u)  // Horizontal Address Start Position
#define ILI9225_HORIZONTAL_WINDOW_ADDR2 (0x37u)  // Horizontal Address End Position
#define ILI9225_VERTICAL_WINDOW_ADDR1   (0x38u)  // Vertical Address Start Position
#define ILI9225_VERTICAL_WINDOW_ADDR2   (0x39u)  // Vertical Address End Position
#define ILI9225_GAMMA_CTRL1             (0x50u)  // Gamma Control 1
#define ILI9225_GAMMA_CTRL2             (0x51u)  // Gamma Control 2
#define ILI9225_GAMMA_CTRL3             (0x52u)  // Gamma Control 3
#define ILI9225_GAMMA_CTRL4             (0x53u)  // Gamma Control 4
#define ILI9225_GAMMA_CTRL5             (0x54u)  // Gamma Control 5
#define ILI9225_GAMMA_CTRL6             (0x55u)  // Gamma Control 6
#define ILI9225_GAMMA_CTRL7             (0x56u)  // Gamma Control 7
#define ILI9225_GAMMA_CTRL8             (0x57u)  // Gamma Control 8
#define ILI9225_GAMMA_CTRL9             (0x58u)  // Gamma Control 9
#define ILI9225_GAMMA_CTRL10            (0x59u)  // Gamma Control 10

#define ILI9225C_INVOFF  0x20
#define ILI9225C_INVON   0x21

/* RGB 16-bit color table definition (RG565) */
#define COLOR_BLACK          0x0000      /*   0,   0,   0 */
#define COLOR_WHITE          0xFFFF      /* 255, 255, 255 */
#define COLOR_BLUE           0x001F      /*   0,   0, 255 */
#define COLOR_GREEN          0x07E0      /*   0, 255,   0 */
#define COLOR_RED            0xF800      /* 255,   0,   0 */
#define COLOR_NAVY           0x000F      /*   0,   0, 128 */
#define COLOR_DARKBLUE       0x0011      /*   0,   0, 139 */
#define COLOR_DARKGREEN      0x03E0      /*   0, 128,   0 */
#define COLOR_DARKCYAN       0x03EF      /*   0, 128, 128 */
#define COLOR_CYAN           0x07FF      /*   0, 255, 255 */
#define COLOR_TURQUOISE      0x471A      /*  64, 224, 208 */
#define COLOR_INDIGO         0x4810      /*  75,   0, 130 */
#define COLOR_DARKRED        0x8000      /* 128,   0,   0 */
#define COLOR_OLIVE          0x7BE0      /* 128, 128,   0 */
#define COLOR_GRAY           0x8410      /* 128, 128, 128 */
#define COLOR_GREY           0x8410      /* 128, 128, 128 */
#define COLOR_SKYBLUE        0x867D      /* 135, 206, 235 */
#define COLOR_BLUEVIOLET     0x895C      /* 138,  43, 226 */
#define COLOR_LIGHTGREEN     0x9772      /* 144, 238, 144 */
#define COLOR_DARKVIOLET     0x901A      /* 148,   0, 211 */
#define COLOR_YELLOWGREEN    0x9E66      /* 154, 205,  50 */
#define COLOR_BROWN          0xA145      /* 165,  42,  42 */
#define COLOR_DARKGRAY       0x7BEF      /* 128, 128, 128 */
#define COLOR_DARKGREY       0x7BEF      /* 128, 128, 128 */
#define COLOR_SIENNA         0xA285      /* 160,  82,  45 */
#define COLOR_LIGHTBLUE      0xAEDC      /* 172, 216, 230 */
#define COLOR_GREENYELLOW    0xAFE5      /* 173, 255,  47 */
#define COLOR_SILVER         0xC618      /* 192, 192, 192 */
#define COLOR_LIGHTGRAY      0xC618      /* 192, 192, 192 */
#define COLOR_LIGHTGREY      0xC618      /* 192, 192, 192 */
#define COLOR_LIGHTCYAN      0xE7FF      /* 224, 255, 255 */
#define COLOR_VIOLET         0xEC1D      /* 238, 130, 238 */
#define COLOR_AZUR           0xF7FF      /* 240, 255, 255 */
#define COLOR_BEIGE          0xF7BB      /* 245, 245, 220 */
#define COLOR_MAGENTA        0xF81F      /* 255,   0, 255 */
#define COLOR_TOMATO         0xFB08      /* 255,  99,  71 */
#define COLOR_GOLD           0xFEA0      /* 255, 215,   0 */
#define COLOR_ORANGE         0xFD20      /* 255, 165,   0 */
#define COLOR_SNOW           0xFFDF      /* 255, 250, 250 */
#define COLOR_YELLOW         0xFFE0      /* 255, 255,   0 */

//Port handling
#define ILI9225_RST_HIGH()	do {ILI9225_RST_PORT |= _BV(ILI9225_RST_BIT);} while (0)
#define ILI9225_RST_LOW()	do {ILI9225_RST_PORT &=~_BV(ILI9225_RST_BIT);} while (0)

#define ILI9225_CS_HIGH()	do {ILI9225_CS_PORT	 |= _BV(ILI9225_CS_BIT);} while (0)
#define ILI9225_CS_LOW()	do {ILI9225_CS_PORT  &=~_BV(ILI9225_CS_BIT);} while (0)

#define ILI9225_RS_HIGH()	do {ILI9225_RS_PORT  |= _BV(ILI9225_RS_BIT);} while (0)
#define ILI9225_RS_LOW()	do {ILI9225_RS_PORT  &=~_BV(ILI9225_RS_BIT);} while (0)

#define ILI9225_SDI_HIGH()	do {ILI9225_SDI_PORT  |= _BV(ILI9225_SDI_BIT);} while (0)
#define ILI9225_SDI_LOW()	do {ILI9225_SDI_PORT  &=~_BV(ILI9225_SDI_BIT);} while (0)

#define ILI9225_CLK_HIGH()	do {ILI9225_CLK_PORT  |= _BV(ILI9225_CLK_BIT);} while (0)
#define ILI9225_CLK_LOW()	do {ILI9225_CLK_PORT  &=~_BV(ILI9225_CLK_BIT);} while (0)

/* Font defines */
#define FONT_HEADER_SIZE 4 // 1: pixel width of 1 font character, 2: pixel height,
#define readFontByte(x) pgm_read_byte(&myFont.font[x])

struct _currentFont
{
	uint8_t* font;
	uint8_t width;
	uint8_t height;
	uint8_t offset;
	uint8_t numchars;
	uint8_t nbrows;
	uint8_t monoSp;
};

extern uint8_t Terminal6x8[];
extern uint8_t Terminal11x16[];
extern uint8_t Terminal12x16[];
extern uint8_t Trebuchet_MS16x21[];

void ILI9225_resetWindow(void);
void ILI9225_init(void);
void ILI9225_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void ILI9225_clear(void);
void ILI9225_invert(uint8_t flag);
void ILI9225_setDisplay(uint8_t flag);
void ILI9225_setOrientation(uint8_t orientation);
uint8_t ILI9225_getOrientation(void);
void ILI9225_drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9225_fillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9225_drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void ILI9225_fillCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color);
void ILI9225_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9225_drawPixel(uint16_t x1, uint16_t y1, uint16_t color);
uint16_t ILI9225_maxX();
uint16_t ILI9225_maxY();
uint16_t ILI9225_setColor(uint8_t red8, uint8_t green8, uint8_t blue8);
void TILI9225_splitColor(uint16_t rgb, uint8_t *red, uint8_t *green, uint8_t *blue);
void ILI9225_drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ILI9225_fillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ILI9225_setBackgroundColor(uint16_t color);
void ILI9225_drawBitmap_P(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
void ILI9225_drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
void ILI9225_drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);

uint16_t  ILI9225_drawText(uint16_t x, uint16_t y, char* s, int length, uint16_t color);
uint16_t drawChar(uint16_t x, uint16_t y, uint16_t ch, uint16_t color);
void ILI9225_setFont(uint8_t* font, int monoSp) ;

#endif /* ILI9225_H_ */
