

/*
 * BMP image as 4bpp (16 colour index) data
 */

#include <stdint.h>
#include "Animation.h"

const uint16_t m_lids_halfeyes_pal[] = {
0,65535,38918,62943,950,1375,26207,2440,48893,59358,38905,34615,30260,40922,51196,21485
};

const uint8_t m_lids_halfeyes[] = {
104,40,
170,170,170,170,170,170,173,218,170,170,170,170,170,170,170,170,170,170,218,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,221,170,170,170,170,170,170,170,170,170,170,173,171,170,170,170,170,170,170,170,170,170,170,173,218,170,170,170,170,170,170,170,170,170,170,170,170,171,186,170,170,170,170,170,170,170,170,170,170,170,170,221,170,170,170,170,170,170,170,170,170,170,170,170,170,186,170,170,170,170,
170,170,170,170,170,221,170,170,170,170,170,170,170,170,170,170,170,170,170,173,187,170,170,170,170,170,170,170,170,170,170,170,173,218,170,170,170,170,170,170,170,170,170,170,170,170,170,219,186,170,170,170,170,170,170,170,173,218,170,170,170,170,170,170,170,170,170,170,170,170,170,170,219,186,170,170,170,170,170,170,170,170,170,170,221,170,170,170,170,170,170,170,170,170,170,170,170,170,170,173,187,170,170,170,
170,170,170,170,221,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,187,170,170,170,170,170,170,170,170,170,173,218,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,171,186,170,170,170,170,170,173,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,219,186,170,170,170,170,170,170,170,170,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,187,170,170,
170,170,170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,30,187,170,170,170,170,170,170,170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,235,186,170,170,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,219,186,170,170,170,170,170,170,174,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,187,170,
170,170,173,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,155,186,170,170,170,170,170,170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,187,170,170,170,174,17,17,17,17,17,17,17,17,17,25,17,17,17,17,17,17,17,17,17,24,203,170,170,170,170,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,140,186,
170,170,209,17,17,17,17,17,17,17,17,25,17,17,17,17,17,17,17,17,17,17,17,203,170,170,170,170,170,173,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,27,186,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,140,186,170,170,170,170,174,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,203,
170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,186,170,170,170,170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,203,170,173,17,17,17,17,17,17,17,17,145,17,17,17,17,17,17,17,17,17,17,17,17,28,203,170,170,170,170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,188,
170,174,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,27,203,170,170,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,188,170,174,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,203,170,170,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,140,
170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,203,186,170,170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,204,186,170,170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,
170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,204,186,170,170,173,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,204,186,170,170,173,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,28,
170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,204,186,170,170,173,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,204,186,170,170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,
170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,204,186,170,170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,204,186,170,170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,140,
170,174,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,204,186,170,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,140,170,173,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,28,203,186,170,170,170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,188,
170,170,145,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,156,203,170,170,170,170,169,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,25,204,170,170,225,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,140,203,170,170,170,170,174,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,204,
170,170,209,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,204,203,170,170,170,170,173,17,17,17,17,17,17,17,145,17,17,17,17,17,17,17,17,17,17,17,17,28,204,170,170,173,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,219,204,186,170,170,170,170,170,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,140,203,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,188,204,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,187,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,204,204,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,187,204,204,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,188,204,203,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,171,204,204,186,170,170,170,170,170,170,170,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,188,204,203,170,170,170,170,170,170,170,170,171,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,188,204,203,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,188,204,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,171,203,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,186,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,

};