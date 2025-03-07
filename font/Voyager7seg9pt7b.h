const uint8_t Voyager7seg9pt7bBitmaps[] PROGMEM = {
    0x00, 0x03, 0x00, 0xC0, 0x30, 0x7F, 0x9F, 0xE0, 0xC0, 0x30, 0x0C, 0x00, 
    0x00, 0xFC, 0x94, 0x00, 0x01, 0xFF, 0xF8, 0x00, 0x77, 0x70, 0x3F, 0x2F, 
    0x58, 0x6C, 0x3C, 0x1E, 0x0D, 0x03, 0x02, 0xC1, 0xE1, 0xF0, 0xD8, 0x6B, 
    0xD3, 0xF0, 0x00, 0x05, 0xB6, 0xCA, 0x7F, 0x64, 0x00, 0x3F, 0x0F, 0x40, 
    0x60, 0x30, 0x18, 0x0D, 0xFB, 0x7E, 0xC0, 0x60, 0x30, 0x18, 0x0B, 0xC3, 
    0xF0, 0x00, 0x7E, 0x3D, 0x03, 0x03, 0x03, 0x03, 0x7D, 0x3E, 0x03, 0x07, 
    0x06, 0x06, 0x7A, 0xFC, 0x41, 0x63, 0x63, 0xC3, 0xC3, 0x7D, 0x3E, 0x03, 
    0x07, 0x06, 0x06, 0x02, 0x00, 0x3F, 0x2F, 0x18, 0x0C, 0x0C, 0x06, 0x01, 
    0xF8, 0x7E, 0x01, 0x81, 0xC0, 0xC0, 0x63, 0xD3, 0xF0, 0x00, 0x3F, 0x2F, 
    0x18, 0x0C, 0x0C, 0x06, 0x01, 0xF9, 0x7E, 0xC1, 0xE1, 0xF0, 0xD8, 0x6B, 
    0xD3, 0xF0, 0x00, 0x3F, 0x0F, 0x40, 0x60, 0x30, 0x18, 0x0C, 0x02, 0x02, 
    0x01, 0x81, 0xC0, 0xC0, 0x60, 0x10, 0x00, 0x00, 0x3F, 0x2F, 0x58, 0x6C, 
    0x3C, 0x1E, 0x0D, 0xFB, 0x7E, 0xC1, 0xE1, 0xF0, 0xD8, 0x6B, 0xD3, 0xF0, 
    0x00, 0x3F, 0x2F, 0x58, 0x6C, 0x3C, 0x1E, 0x0D, 0xFA, 0x7E, 0x01, 0x81, 
    0xC0, 0xC0, 0x63, 0xD3, 0xF0, 0x00, 0x3F, 0x2F, 0x18, 0x0C, 0x0C, 0x06, 
    0x01, 0xF9, 0x7E, 0xC0, 0x60, 0x30, 0x18, 0x0B, 0xC3, 0xF0, 0x00, 0xFF, 
    0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xFC, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 
    0xC0, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0xE0, 0xF8, 0x3F, 0x0F, 
    0xC3, 0xD8, 0xF6, 0x3C, 0xCF, 0x33, 0xC6, 0xF1, 0xBC, 0x3F, 0x0F, 0xC1, 
    0xF0, 0x70, 0xD9, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF1, 0x99, 
    0x8C, 0xC6, 0x63, 0x31, 0x99, 0xCD, 0xB3, 0x8C, 0x00
};

const GFXglyph Voyager7seg9pt7bGlyphs[] PROGMEM = {
    {     0,  10,  10,  11,    0,  -11 },   // 0x2B '+'
    {    13,   3,   5,  11,    1,   -2 },   // 0x2C ','
    {    16,   7,   4,  11,    1,   -8 },   // 0x2D '-'
    {    20,   4,   4,  11,    1,   -2 },   // 0x2E '.'
    {     0,   0,   0,   0,    0,    0 },   // 0x2F '/'
    {    22,   9,  14,  11,    0,  -13 },   // 0x30 '0'
    {    39,   3,  14,  11,    6,  -13 },   // 0x31 '1'
    {    45,   9,  14,  11,    0,  -13 },   // 0x32 '2'
    {    62,   8,  14,  11,    1,  -13 },   // 0x33 '3'
    {    76,   8,  13,  11,    1,  -12 },   // 0x34 '4'
    {    89,   9,  14,  11,    0,  -13 },   // 0x35 '5'
    {   106,   9,  14,  11,    0,  -13 },   // 0x36 '6'
    {   123,   9,  14,  11,    0,  -13 },   // 0x37 '7'
    {   140,   9,  14,  11,    0,  -13 },   // 0x38 '8'
    {   157,   9,  14,  11,    0,  -13 },   // 0x39 '9'
    {     0,   0,   0,   0,    0,    0 },   // 0x3A ':'
    {     0,   0,   0,   0,    0,    0 },   // 0x3B ';'
    {     0,   0,   0,   0,    0,    0 },   // 0x3C '<'
    {     0,   0,   0,   0,    0,    0 },   // 0x3D '='
    {     0,   0,   0,   0,    0,    0 },   // 0x3E '>'
    {     0,   0,   0,   0,    0,    0 },   // 0x3F '?'
    {     0,   0,   0,   0,    0,    0 },   // 0x40 '@'
    {     0,   0,   0,   0,    0,    0 },   // 0x41 'A'
    {     0,   0,   0,   0,    0,    0 },   // 0x42 'B'
    {     0,   0,   0,   0,    0,    0 },   // 0x43 'C'
    {     0,   0,   0,   0,    0,    0 },   // 0x44 'D'
    {   174,   9,  14,  11,    1,  -13 },   // 0x45 'E'
    {   191,   8,  14,  11,    1,  -13 },   // 0x46 'F'
    {     0,   0,   0,   0,    0,    0 },   // 0x47 'G'
    {     0,   0,   0,   0,    0,    0 },   // 0x48 'H'
    {   205,   4,  14,   9,    1,  -13 },   // 0x49 'I'
    {     0,   0,   0,   0,    0,    0 },   // 0x4A 'J'
    {     0,   0,   0,   0,    0,    0 },   // 0x4B 'K'
    {     0,   0,   0,   0,    0,    0 },   // 0x4C 'L'
    {     0,   0,   0,   0,    0,    0 },   // 0x4D 'M'
    {   212,  10,  14,  11,    1,  -13 },   // 0x4E 'N'
    {     0,   0,   0,   0,    0,    0 },   // 0x4F 'O'
    {     0,   0,   0,   0,    0,    0 },   // 0x50 'P'
    {     0,   0,   0,   0,    0,    0 },   // 0x51 'Q'
    {     0,   0,   0,   0,    0,    0 },   // 0x52 'R'
    {     0,   0,   0,   0,    0,    0 },   // 0x53 'S'
    {     0,   0,   0,   0,    0,    0 },   // 0x54 'T'
    {     0,   0,   0,   0,    0,    0 },   // 0x55 'U'
    {     0,   0,   0,   0,    0,    0 },   // 0x56 'V'
    {     0,   0,   0,   0,    0,    0 },   // 0x57 'W'
    {     0,   0,   0,   0,    0,    0 },   // 0x58 'X'
    {     0,   0,   0,   0,    0,    0 },   // 0x59 'Y'
    {     0,   0,   0,   0,    0,    0 },   // 0x5A 'Z'
    {     0,   0,   0,   0,    0,    0 },   // 0x5B '['
    {     0,   0,   0,   0,    0,    0 },   // 0x5C '\'
    {     0,   0,   0,   0,    0,    0 },   // 0x5D ']'
    {   230,   3,   4,   2,   -1,   -2 },   // 0x5E '^'
    {     0,   0,   0,   0,    0,    0 },   // 0x5F '_'
    {     0,   0,   0,   0,    0,    0 },   // 0x60 '`'
    {   232,   9,  14,  11,    0,  -13 }    // 0x61 'a'
};

const GFXfont Voyager7seg9pt7b PROGMEM = {
    (uint8_t  *)Voyager7seg9pt7bBitmaps,   
    (GFXglyph *)Voyager7seg9pt7bGlyphs, 0x2B, 0x61,     18 };

// Approx. 218 bytes
