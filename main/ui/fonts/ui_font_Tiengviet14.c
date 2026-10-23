/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --font C:/Users/luan/Documents/Thuc_hanh_IoT/SquareLine/assets/Roboto-VariableFont_wdth,wght.ttf -o C:/Users/luan/Documents/Thuc_hanh_IoT/SquareLine/assets\ui_font_Tiengviet14.c --format lvgl -r 0x20-0x7f --symbols aáàảãạăắằẳẵặâấầẩẫậeéèẻẽẹêếềểễệiíìỉĩịoóòỏõọôốồổỗộơớờởỡợuúùủũụưứừửữựyýỳỷỹỵdđAÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬEÉÈẺẼẸÊẾỀỂỄỆIÍÌỈĨỊOÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢUÚÙỦŨỤƯỨỪỬỮỰYÝỲỶỸỴDĐ --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_TIENGVIET14
#define UI_FONT_TIENGVIET14 1
#endif

#if UI_FONT_TIENGVIET14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0x20,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x14, 0x14, 0x7f, 0x24, 0x24, 0x24, 0xfe,
    0x28, 0x28, 0x28,

    /* U+0024 "$" */
    0x10, 0x43, 0x9f, 0x45, 0x16, 0x4, 0xe, 0x18,
    0x7f, 0x78, 0x41, 0x0,

    /* U+0025 "%" */
    0x60, 0x49, 0x24, 0x92, 0x86, 0x40, 0x40, 0x4c,
    0x29, 0x24, 0x92, 0x40, 0xc0,

    /* U+0026 "&" */
    0x38, 0x44, 0x44, 0x4c, 0x38, 0x70, 0xd2, 0x8a,
    0x8e, 0xce, 0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x5, 0x29, 0x24, 0x92, 0x24, 0x88,

    /* U+0029 ")" */
    0x11, 0x22, 0x49, 0x24, 0xa4, 0xa0,

    /* U+002A "*" */
    0x21, 0x3e, 0x45, 0x6c,

    /* U+002B "+" */
    0x10, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x10,

    /* U+002C "," */
    0x54,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x8, 0x44, 0x21, 0x10, 0x84, 0x42, 0x31, 0x0,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x85, 0x27,
    0x80,

    /* U+0031 "1" */
    0x1f, 0x91, 0x11, 0x11, 0x11, 0x10,

    /* U+0032 "2" */
    0x79, 0x9a, 0x10, 0x20, 0x41, 0x4, 0x18, 0x60,
    0x83, 0xf8,

    /* U+0033 "3" */
    0x7b, 0x18, 0x41, 0xc, 0xe0, 0xc1, 0x87, 0x37,
    0x80,

    /* U+0034 "4" */
    0x4, 0x18, 0x50, 0xa2, 0x44, 0x91, 0x7f, 0x4,
    0x8, 0x10,

    /* U+0035 "5" */
    0x7d, 0x4, 0x10, 0xf9, 0x30, 0x41, 0x87, 0x37,
    0x80,

    /* U+0036 "6" */
    0x39, 0x84, 0x20, 0xbb, 0x38, 0x61, 0x85, 0x37,
    0x80,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x20, 0x81, 0x6, 0x8, 0x30,
    0x40, 0x80,

    /* U+0038 "8" */
    0x7b, 0x38, 0x61, 0xcd, 0xec, 0xe1, 0x87, 0x37,
    0x80,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0x87, 0x37, 0x41, 0x8, 0x67,
    0x0,

    /* U+003A ":" */
    0x81,

    /* U+003B ";" */
    0x87, 0x80,

    /* U+003C "<" */
    0x4, 0x66, 0x30, 0x70, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x81, 0x83, 0x3b, 0x0, 0x0,

    /* U+003F "?" */
    0x76, 0x62, 0x11, 0x88, 0x84, 0x0, 0x8,

    /* U+0040 "@" */
    0xf, 0x6, 0x11, 0x1, 0x27, 0x38, 0x93, 0x22,
    0x64, 0x4c, 0x91, 0x92, 0x32, 0x6b, 0x37, 0x20,
    0x2, 0x0, 0x3c, 0x0,

    /* U+0041 "A" */
    0xc, 0x7, 0x1, 0xc0, 0x58, 0x36, 0xc, 0x82,
    0x31, 0xfc, 0x61, 0x90, 0x24, 0x8,

    /* U+0042 "B" */
    0xf9, 0xa, 0x14, 0x28, 0xdf, 0x21, 0xc1, 0x83,
    0xf, 0xf0,

    /* U+0043 "C" */
    0x3c, 0x8e, 0xc, 0x18, 0x10, 0x20, 0x40, 0x82,
    0x8c, 0xf0,

    /* U+0044 "D" */
    0xf9, 0x1a, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x85,
    0x1b, 0xe0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0x8,
    0x0,

    /* U+0047 "G" */
    0x3c, 0x42, 0xc1, 0x80, 0x80, 0x80, 0x8f, 0x81,
    0xc1, 0x61, 0x3e,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81,
    0x81, 0x81, 0x81,

    /* U+0049 "I" */
    0xff, 0xe0,

    /* U+004A "J" */
    0x4, 0x10, 0x41, 0x4, 0x10, 0x41, 0x87, 0x37,
    0x80,

    /* U+004B "K" */
    0x87, 0x1a, 0x64, 0x8a, 0x1e, 0x34, 0x4c, 0x8d,
    0xa, 0x18,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0xf,
    0xc0,

    /* U+004D "M" */
    0xc0, 0xf0, 0x3c, 0xe, 0x85, 0xa1, 0x6c, 0xd9,
    0x26, 0x49, 0x8c, 0x63, 0x18, 0xc4,

    /* U+004E "N" */
    0x81, 0xc1, 0xe1, 0xa1, 0xb1, 0x99, 0x8d, 0x8d,
    0x87, 0x83, 0x81,

    /* U+004F "O" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0x81,
    0xc3, 0x42, 0x3c,

    /* U+0050 "P" */
    0xfd, 0xa, 0xc, 0x18, 0x30, 0xff, 0x40, 0x81,
    0x2, 0x0,

    /* U+0051 "Q" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0x81,
    0xc3, 0x42, 0x3e, 0x3, 0x0,

    /* U+0052 "R" */
    0xfd, 0xe, 0xc, 0x18, 0x30, 0xbe, 0x46, 0x85,
    0xe, 0x8,

    /* U+0053 "S" */
    0x3c, 0x62, 0x41, 0x40, 0x70, 0x1c, 0x7, 0x1,
    0x41, 0x63, 0x3e,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+0056 "V" */
    0xc1, 0xa0, 0x90, 0x4c, 0x62, 0x21, 0x10, 0xd8,
    0x28, 0x14, 0xe, 0x2, 0x0,

    /* U+0057 "W" */
    0x42, 0x14, 0x63, 0x46, 0x34, 0x52, 0x65, 0x22,
    0xd2, 0x29, 0x62, 0x8c, 0x28, 0xc3, 0xc, 0x10,
    0xc0,

    /* U+0058 "X" */
    0x43, 0x62, 0x26, 0x34, 0x1c, 0x8, 0x1c, 0x34,
    0x26, 0x63, 0x41,

    /* U+0059 "Y" */
    0x83, 0x8d, 0x13, 0x62, 0x87, 0x4, 0x8, 0x10,
    0x20, 0x40,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x82, 0x8, 0x30, 0x41,
    0x3, 0xf8,

    /* U+005B "[" */
    0xea, 0xaa, 0xaa, 0xb0,

    /* U+005C "\\" */
    0xc1, 0x4, 0x8, 0x20, 0x81, 0x4, 0x18, 0x20,
    0x83,

    /* U+005D "]" */
    0xd5, 0x55, 0x55, 0x70,

    /* U+005E "^" */
    0x21, 0x8c, 0xe4, 0xa4,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x44,

    /* U+0061 "a" */
    0x7b, 0x10, 0x5f, 0xc6, 0x18, 0xdd,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0x87, 0x3b,
    0x80,

    /* U+0063 "c" */
    0x79, 0x38, 0x60, 0x82, 0x14, 0xde,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0x85, 0x37,
    0x40,

    /* U+0065 "e" */
    0x39, 0x38, 0x7f, 0x82, 0x4, 0x5e,

    /* U+0066 "f" */
    0x3a, 0x11, 0xe4, 0x21, 0x8, 0x42, 0x10,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x86, 0x14, 0xdd, 0x6, 0x37,
    0x80,

    /* U+0068 "h" */
    0x82, 0x8, 0x2e, 0xc6, 0x18, 0x61, 0x86, 0x18,
    0x40,

    /* U+0069 "i" */
    0x9f, 0xe0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x93, 0x80,

    /* U+006B "k" */
    0x82, 0x8, 0x22, 0x92, 0x8e, 0x38, 0x92, 0x68,
    0xc0,

    /* U+006C "l" */
    0xff, 0xe0,

    /* U+006D "m" */
    0xb9, 0xd8, 0xc6, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0xbe, 0x82, 0x8,
    0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x86, 0x1c, 0xdd, 0x4, 0x10,
    0x40,

    /* U+0072 "r" */
    0xfa, 0x49, 0x24,

    /* U+0073 "s" */
    0x39, 0x14, 0x1c, 0x1c, 0x14, 0x4e,

    /* U+0074 "t" */
    0x4b, 0xa4, 0x92, 0x4c,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdf,

    /* U+0076 "v" */
    0xc4, 0x89, 0x33, 0x42, 0x85, 0xc, 0x8,

    /* U+0077 "w" */
    0xc4, 0x53, 0x14, 0xcd, 0x2a, 0x72, 0x8c, 0xa3,
    0x10, 0xc4,

    /* U+0078 "x" */
    0x44, 0xd8, 0xa1, 0x83, 0x5, 0x1b, 0x22,

    /* U+0079 "y" */
    0xc5, 0x14, 0xda, 0x28, 0xa3, 0x4, 0x10, 0x86,
    0x0,

    /* U+007A "z" */
    0xfc, 0x31, 0x8c, 0x31, 0x8c, 0x3f,

    /* U+007B "{" */
    0x5, 0x24, 0x94, 0x49, 0x24, 0x40,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0x99, 0x24, 0x99, 0x69, 0x25, 0xa0,

    /* U+007E "~" */
    0x71, 0x9b, 0x8e,

    /* U+00C0 "À" */
    0x10, 0x6, 0x0, 0xc0, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+00C1 "Á" */
    0x6, 0x1, 0x0, 0x80, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+00C2 "Â" */
    0x8, 0x5, 0x0, 0x20, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+00C3 "Ã" */
    0x1a, 0x9, 0x80, 0xc0, 0x70, 0x1c, 0x5, 0x83,
    0x60, 0xc8, 0x23, 0x1f, 0xc6, 0x19, 0x2, 0x40,
    0x80,

    /* U+00C8 "È" */
    0x40, 0x82, 0x3f, 0x82, 0x8, 0x20, 0xfa, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00C9 "É" */
    0x18, 0x42, 0x3f, 0x82, 0x8, 0x20, 0xfa, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00CA "Ê" */
    0x20, 0xc4, 0xbf, 0x82, 0x8, 0x20, 0xfa, 0x8,
    0x20, 0x83, 0xf0,

    /* U+00CC "Ì" */
    0xb5, 0x55, 0x55, 0x50,

    /* U+00CD "Í" */
    0x7a, 0xaa, 0xaa, 0xa0,

    /* U+00D2 "Ò" */
    0x20, 0x10, 0x8, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D3 "Ó" */
    0x4, 0x8, 0x10, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D4 "Ô" */
    0x0, 0x18, 0x24, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D5 "Õ" */
    0x3c, 0x0, 0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81,
    0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+00D9 "Ù" */
    0x60, 0x60, 0x44, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+00DA "Ú" */
    0xc, 0x30, 0x44, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+00DD "Ý" */
    0xc, 0x30, 0x44, 0x1c, 0x68, 0x9b, 0x14, 0x38,
    0x20, 0x40, 0x81, 0x2, 0x0,

    /* U+00E0 "à" */
    0x60, 0xc0, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E1 "á" */
    0x8, 0x40, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E2 "â" */
    0x31, 0xa0, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E3 "ã" */
    0x65, 0x60, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+00E8 "è" */
    0x60, 0x80, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+00E9 "é" */
    0x18, 0x40, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+00EA "ê" */
    0x31, 0x20, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+00EC "ì" */
    0x91, 0x55, 0x54,

    /* U+00ED "í" */
    0x50, 0x49, 0x24, 0x92, 0x0,

    /* U+00F2 "ò" */
    0x60, 0x60, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F3 "ó" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F4 "ô" */
    0x30, 0xd0, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F5 "õ" */
    0x74, 0xb8, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0,

    /* U+00F9 "ù" */
    0x60, 0xc0, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0xc0,

    /* U+00FA "ú" */
    0x18, 0x40, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0xc0,

    /* U+00FD "ý" */
    0x8, 0x40, 0x31, 0x45, 0x36, 0x8a, 0x28, 0xc1,
    0x4, 0x21, 0x80,

    /* U+0102 "Ă" */
    0x14, 0x6, 0x0, 0x80, 0x70, 0x1c, 0x5, 0x83,
    0x60, 0xc8, 0x23, 0x1f, 0xc6, 0x19, 0x2, 0x40,
    0x80,

    /* U+0103 "ă" */
    0x48, 0xe0, 0x1e, 0x84, 0x17, 0xf1, 0x86, 0x37,
    0x40,

    /* U+0110 "Đ" */
    0x7c, 0x46, 0x42, 0x41, 0x41, 0xf1, 0x41, 0x41,
    0x42, 0x46, 0x7c,

    /* U+0111 "đ" */
    0x4, 0x3c, 0x13, 0xac, 0xd0, 0xa1, 0x42, 0x84,
    0x99, 0xd0,

    /* U+0128 "Ĩ" */
    0xf8, 0x8, 0x42, 0x10, 0x84, 0x21, 0x8, 0x42,
    0x0,

    /* U+0129 "ĩ" */
    0x4d, 0x80, 0x42, 0x10, 0x84, 0x21, 0x8,

    /* U+0168 "Ũ" */
    0x7c, 0x2, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+0169 "ũ" */
    0x66, 0x60, 0x21, 0x86, 0x18, 0x61, 0x86, 0x37,
    0xc0,

    /* U+01A0 "Ơ" */
    0x0, 0x9e, 0x50, 0xd8, 0x68, 0x14, 0xa, 0x5,
    0x2, 0x81, 0x61, 0x90, 0x87, 0x80,

    /* U+01A1 "ơ" */
    0x2, 0x3a, 0x46, 0x82, 0x82, 0x82, 0x82, 0x44,
    0x38,

    /* U+01AF "Ư" */
    0x82, 0x60, 0x98, 0x3a, 0x8, 0x82, 0x20, 0x88,
    0x22, 0x8, 0x82, 0x11, 0x3, 0x80,

    /* U+01B0 "ư" */
    0x1, 0x85, 0x86, 0x84, 0x84, 0x84, 0x84, 0x8c,
    0x7c,

    /* U+1EA0 "Ạ" */
    0x8, 0x7, 0x1, 0xc0, 0x50, 0x16, 0xc, 0x82,
    0x30, 0xfc, 0x61, 0x10, 0x24, 0x8, 0x0, 0x8,
    0x0,

    /* U+1EA1 "ạ" */
    0x7b, 0x10, 0x5f, 0xc6, 0x18, 0xdd, 0x0, 0x80,

    /* U+1EA2 "Ả" */
    0xc, 0x1, 0x0, 0x80, 0x30, 0x1c, 0x7, 0x1,
    0x60, 0xd8, 0x32, 0x8, 0xc7, 0xf1, 0x86, 0x40,
    0x90, 0x20,

    /* U+1EA3 "ả" */
    0x18, 0x40, 0x0, 0x7b, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+1EA4 "Ấ" */
    0x0, 0x80, 0x21, 0xd0, 0x8c, 0xc, 0x7, 0x1,
    0xc0, 0x58, 0x36, 0xc, 0x82, 0x31, 0xfc, 0x61,
    0x90, 0x24, 0x8,

    /* U+1EA5 "ấ" */
    0x3, 0x2, 0x30, 0x68, 0x0, 0x78, 0xc4, 0x4,
    0x7c, 0xc4, 0x84, 0x8c, 0x74,

    /* U+1EA6 "Ầ" */
    0xc0, 0x10, 0x3, 0xc0, 0x58, 0xc, 0x7, 0x1,
    0xc0, 0x58, 0x36, 0xc, 0x82, 0x31, 0xfc, 0x61,
    0x90, 0x24, 0x8,

    /* U+1EA7 "ầ" */
    0x80, 0xb0, 0xd0, 0x3, 0xc8, 0x40, 0x9f, 0x62,
    0x85, 0x19, 0xd0,

    /* U+1EA8 "Ẩ" */
    0x1, 0x0, 0x47, 0x42, 0x40, 0xc0, 0xe0, 0x70,
    0x2c, 0x36, 0x19, 0x8, 0xcf, 0xe6, 0x12, 0xd,
    0x2,

    /* U+1EA9 "ẩ" */
    0x6, 0x4, 0xf2, 0x40, 0xf, 0x31, 0x2, 0x7d,
    0x8a, 0x14, 0x67, 0x40,

    /* U+1EAA "Ẫ" */
    0x1a, 0x9, 0x0, 0x80, 0xd8, 0xc, 0x7, 0x1,
    0xc0, 0x58, 0x36, 0xc, 0x82, 0x31, 0xfc, 0x61,
    0x90, 0x24, 0x8,

    /* U+1EAB "ẫ" */
    0x29, 0x63, 0x12, 0x1, 0xec, 0x41, 0x7f, 0x18,
    0x63, 0x74,

    /* U+1EAC "Ậ" */
    0x8, 0x5, 0x1, 0x60, 0x20, 0x1c, 0x7, 0x1,
    0x40, 0x58, 0x32, 0x8, 0xc3, 0xf1, 0x84, 0x40,
    0x90, 0x20, 0x0, 0x20,

    /* U+1EAD "ậ" */
    0x31, 0x20, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40, 0x20,

    /* U+1EAE "Ắ" */
    0x4, 0x2, 0x1, 0x20, 0x70, 0xc, 0x7, 0x1,
    0xc0, 0x58, 0x36, 0xc, 0x82, 0x31, 0xfc, 0x61,
    0x90, 0x24, 0x8,

    /* U+1EAF "ắ" */
    0x11, 0x23, 0x80, 0x7a, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+1EB0 "Ằ" */
    0x10, 0x2, 0x1, 0x20, 0x70, 0xc, 0x7, 0x1,
    0xc0, 0x58, 0x36, 0xc, 0x82, 0x31, 0xfc, 0x61,
    0x90, 0x24, 0x8,

    /* U+1EB1 "ằ" */
    0x21, 0x23, 0x80, 0x7a, 0x10, 0x5f, 0xc6, 0x18,
    0xdd,

    /* U+1EB2 "Ẳ" */
    0xc, 0x1, 0x0, 0x80, 0x8, 0x1c, 0x3, 0x1,
    0xc0, 0x70, 0x16, 0xd, 0x83, 0x20, 0x8c, 0x7f,
    0x18, 0x64, 0x9, 0x2,

    /* U+1EB3 "ẳ" */
    0x18, 0x44, 0x8e, 0x1, 0xe8, 0x41, 0x7f, 0x18,
    0x63, 0x74,

    /* U+1EB4 "Ẵ" */
    0x1a, 0x9, 0x80, 0x20, 0x70, 0xc, 0x7, 0x1,
    0xc0, 0x58, 0x36, 0xc, 0x82, 0x31, 0xfc, 0x61,
    0x90, 0x24, 0x8,

    /* U+1EB5 "ẵ" */
    0x29, 0x64, 0x8e, 0x1, 0xe8, 0x41, 0x7f, 0x18,
    0x63, 0x74,

    /* U+1EB6 "Ặ" */
    0x16, 0x7, 0x0, 0x80, 0x70, 0x1c, 0x5, 0x1,
    0x60, 0xc8, 0x23, 0xf, 0xc6, 0x11, 0x2, 0x40,
    0x80, 0x0, 0x80,

    /* U+1EB7 "ặ" */
    0x48, 0xe0, 0x1e, 0xc4, 0x17, 0xf1, 0x86, 0x37,
    0x40, 0x20,

    /* U+1EB8 "Ẹ" */
    0xfd, 0x2, 0x4, 0x8, 0x1f, 0xa0, 0x40, 0x81,
    0x3, 0xf8, 0x1, 0x0,

    /* U+1EB9 "ẹ" */
    0x3c, 0x8e, 0xf, 0xf8, 0x10, 0x10, 0x9e, 0x0,
    0x20,

    /* U+1EBA "Ẻ" */
    0x30, 0x43, 0x0, 0xfe, 0x8, 0x20, 0x83, 0xf8,
    0x20, 0x82, 0xf, 0xc0,

    /* U+1EBB "ẻ" */
    0x38, 0x40, 0x0, 0x39, 0x38, 0x7f, 0x82, 0x4,
    0x5e,

    /* U+1EBC "Ẽ" */
    0x78, 0xf, 0xe0, 0x82, 0x8, 0x3e, 0x82, 0x8,
    0x20, 0xfc,

    /* U+1EBD "ẽ" */
    0x69, 0x60, 0xe, 0x4e, 0x1f, 0xe0, 0x81, 0x17,
    0x80,

    /* U+1EBE "Ế" */
    0x2, 0x49, 0xd6, 0x4f, 0xd0, 0x20, 0x40, 0x81,
    0xf2, 0x4, 0x8, 0x10, 0x3f, 0x0,

    /* U+1EBF "ế" */
    0x2, 0x4, 0xd2, 0x40, 0x7, 0x13, 0x42, 0xfd,
    0x2, 0x2, 0x27, 0x80,

    /* U+1EC0 "Ề" */
    0x81, 0x1, 0x63, 0x27, 0xe8, 0x10, 0x20, 0x40,
    0xf9, 0x2, 0x4, 0x8, 0x1f, 0x80,

    /* U+1EC1 "ề" */
    0x81, 0x81, 0x61, 0x20, 0x3, 0x89, 0xa1, 0x7e,
    0x81, 0x1, 0x13, 0xc0,

    /* U+1EC2 "Ể" */
    0x4, 0x8, 0xd2, 0x4f, 0xd0, 0x20, 0x40, 0x81,
    0xf2, 0x4, 0x8, 0x10, 0x3f, 0x0,

    /* U+1EC3 "ể" */
    0x6, 0x4, 0xd2, 0x40, 0x7, 0x13, 0x42, 0xfd,
    0x2, 0x2, 0x27, 0x80,

    /* U+1EC4 "Ễ" */
    0x69, 0x42, 0x16, 0xfe, 0x8, 0x20, 0x83, 0xe8,
    0x20, 0x82, 0xf, 0xc0,

    /* U+1EC5 "ễ" */
    0x29, 0x63, 0x12, 0x0, 0xe4, 0xe1, 0xfe, 0x8,
    0x11, 0x78,

    /* U+1EC6 "Ệ" */
    0x10, 0x51, 0xa7, 0xe8, 0x10, 0x20, 0x40, 0xfd,
    0x2, 0x4, 0x8, 0x1f, 0xc0, 0x8,

    /* U+1EC7 "ệ" */
    0x10, 0xd8, 0x1, 0xe4, 0x70, 0x7f, 0xc0, 0x80,
    0x84, 0xf0, 0x1, 0x0,

    /* U+1EC8 "Ỉ" */
    0xd8, 0xaa, 0xaa, 0xa8,

    /* U+1EC9 "ỉ" */
    0xe0, 0xaa, 0xaa,

    /* U+1ECA "Ị" */
    0xff, 0xe8,

    /* U+1ECB "ị" */
    0x9f, 0xe8,

    /* U+1ECC "Ọ" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0x81,
    0xc3, 0x42, 0x3c, 0x0, 0x10,

    /* U+1ECD "ọ" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c, 0x0,
    0x20,

    /* U+1ECE "Ỏ" */
    0x18, 0x4, 0x8, 0x0, 0x3c, 0x42, 0xc3, 0x81,
    0x81, 0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+1ECF "ỏ" */
    0x18, 0x20, 0x0, 0x3, 0x88, 0xa0, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+1ED0 "Ố" */
    0x1, 0x19, 0x3e, 0x66, 0x3c, 0x42, 0xc3, 0x81,
    0x81, 0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+1ED1 "ố" */
    0x1, 0x2, 0x3a, 0x6c, 0x0, 0x38, 0x44, 0x82,
    0x82, 0x82, 0x82, 0x44, 0x38,

    /* U+1ED2 "Ồ" */
    0x80, 0x98, 0x7c, 0x66, 0x3c, 0x42, 0xc3, 0x81,
    0x81, 0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+1ED3 "ồ" */
    0x80, 0x40, 0x5c, 0x36, 0x0, 0x1c, 0x22, 0x41,
    0x41, 0x41, 0x41, 0x22, 0x1c,

    /* U+1ED4 "Ổ" */
    0x2, 0x1, 0x1a, 0x24, 0x3c, 0x42, 0xc3, 0x81,
    0x81, 0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+1ED5 "ổ" */
    0x2, 0x4, 0xf2, 0x60, 0x7, 0x11, 0x41, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+1ED6 "Ỗ" */
    0x34, 0x2c, 0x18, 0x24, 0x3c, 0x42, 0xc3, 0x81,
    0x81, 0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c,

    /* U+1ED7 "ỗ" */
    0x24, 0xb0, 0xe3, 0x60, 0x7, 0x11, 0x41, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+1ED8 "Ộ" */
    0x10, 0x28, 0x2c, 0x3c, 0x42, 0xc3, 0x81, 0x81,
    0x81, 0x81, 0x81, 0xc3, 0x42, 0x3c, 0x0, 0x10,

    /* U+1ED9 "ộ" */
    0x10, 0xd0, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x82,
    0x88, 0xe0, 0x1, 0x0,

    /* U+1EDA "Ớ" */
    0x6, 0x6, 0x4, 0x27, 0x94, 0x36, 0x1a, 0x5,
    0x2, 0x81, 0x40, 0xa0, 0x58, 0x64, 0x21, 0xe0,

    /* U+1EDB "ớ" */
    0xc, 0x10, 0x1, 0x3a, 0x46, 0x82, 0x82, 0x82,
    0x82, 0x44, 0x38,

    /* U+1EDC "Ờ" */
    0x20, 0x8, 0x2, 0x27, 0x94, 0x36, 0x1a, 0x5,
    0x2, 0x81, 0x40, 0xa0, 0x58, 0x64, 0x21, 0xe0,

    /* U+1EDD "ờ" */
    0x60, 0x30, 0x1, 0x3a, 0x46, 0x82, 0x82, 0x82,
    0x82, 0x44, 0x38,

    /* U+1EDE "Ở" */
    0x8, 0x2, 0x2, 0x0, 0x13, 0xca, 0x1b, 0xd,
    0x2, 0x81, 0x40, 0xa0, 0x50, 0x2c, 0x32, 0x10,
    0xf0,

    /* U+1EDF "ở" */
    0x18, 0x10, 0x0, 0x2, 0x3a, 0x46, 0x82, 0x82,
    0x82, 0x82, 0x44, 0x38,

    /* U+1EE0 "Ỡ" */
    0x3e, 0x0, 0x4f, 0x28, 0x6c, 0x34, 0xa, 0x5,
    0x2, 0x81, 0x40, 0xb0, 0xc8, 0x43, 0xc0,

    /* U+1EE1 "ỡ" */
    0x74, 0x5c, 0x1, 0x3a, 0x46, 0x82, 0x82, 0x82,
    0x82, 0x44, 0x38,

    /* U+1EE2 "Ợ" */
    0x0, 0x9e, 0x50, 0xd8, 0x68, 0x14, 0xa, 0x5,
    0x2, 0x81, 0x61, 0x90, 0x87, 0x80, 0x0, 0x80,

    /* U+1EE3 "ợ" */
    0x2, 0x3a, 0x46, 0x82, 0x82, 0x82, 0x82, 0x44,
    0x38, 0x0, 0x10,

    /* U+1EE4 "Ụ" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,
    0x88, 0xe0, 0x1, 0x0,

    /* U+1EE5 "ụ" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdf, 0x0, 0x80,

    /* U+1EE6 "Ủ" */
    0x18, 0x10, 0x40, 0x8, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x18, 0x28, 0x8e, 0x0,

    /* U+1EE7 "ủ" */
    0x38, 0xc0, 0x0, 0x86, 0x18, 0x61, 0x86, 0x18,
    0xdf,

    /* U+1EE8 "Ứ" */
    0xc, 0x2, 0x1, 0x2, 0x9, 0x82, 0x60, 0xe8,
    0x22, 0x8, 0x82, 0x20, 0x88, 0x22, 0x8, 0x44,
    0xe, 0x0,

    /* U+1EE9 "ứ" */
    0x18, 0x10, 0x1, 0x85, 0x86, 0x84, 0x84, 0x84,
    0x84, 0x8c, 0x7c,

    /* U+1EEA "Ừ" */
    0x60, 0xc, 0x1, 0x2, 0x9, 0x82, 0x60, 0xe8,
    0x22, 0x8, 0x82, 0x20, 0x88, 0x22, 0x8, 0x44,
    0xe, 0x0,

    /* U+1EEB "ừ" */
    0x60, 0x30, 0x1, 0x85, 0x86, 0x84, 0x84, 0x84,
    0x84, 0x8c, 0x7c,

    /* U+1EEC "Ử" */
    0x18, 0x2, 0x1, 0x0, 0x0, 0x82, 0x60, 0x98,
    0x3a, 0x8, 0x82, 0x20, 0x88, 0x22, 0x8, 0x82,
    0x11, 0x3, 0x80,

    /* U+1EED "ử" */
    0x30, 0x8, 0x10, 0x1, 0x85, 0x86, 0x84, 0x84,
    0x84, 0x84, 0x8c, 0x7c,

    /* U+1EEE "Ữ" */
    0x7c, 0x0, 0x8, 0x26, 0x9, 0x83, 0xa0, 0x88,
    0x22, 0x8, 0x82, 0x20, 0x88, 0x21, 0x10, 0x38,
    0x0,

    /* U+1EEF "ữ" */
    0x64, 0x98, 0x1, 0x85, 0x86, 0x84, 0x84, 0x84,
    0x84, 0x8c, 0x7c,

    /* U+1EF0 "Ự" */
    0x82, 0x60, 0x98, 0x3a, 0x8, 0x82, 0x20, 0x88,
    0x22, 0x8, 0x82, 0x11, 0x3, 0x80, 0x0, 0x10,
    0x0,

    /* U+1EF1 "ự" */
    0x1, 0x85, 0x86, 0x84, 0x84, 0x84, 0x84, 0x8c,
    0x7c, 0x0, 0x20,

    /* U+1EF2 "Ỳ" */
    0x20, 0x60, 0x44, 0x1c, 0x68, 0x9b, 0x14, 0x38,
    0x20, 0x40, 0x81, 0x2, 0x0,

    /* U+1EF3 "ỳ" */
    0x20, 0x40, 0x31, 0x45, 0x36, 0x8a, 0x28, 0xc1,
    0x4, 0x21, 0x80,

    /* U+1EF4 "Ỵ" */
    0x83, 0x8d, 0x13, 0x62, 0x87, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x1, 0x0,

    /* U+1EF5 "ỵ" */
    0xc5, 0x24, 0x9a, 0x38, 0xc3, 0x4, 0x20, 0x8c,
    0x80,

    /* U+1EF6 "Ỷ" */
    0x18, 0x8, 0x10, 0x82, 0xc6, 0x44, 0x6c, 0x28,
    0x38, 0x10, 0x10, 0x10, 0x10, 0x10,

    /* U+1EF7 "ỷ" */
    0x18, 0x40, 0x0, 0xc5, 0x14, 0xda, 0x28, 0xe3,
    0x4, 0x10, 0x86, 0x0,

    /* U+1EF8 "Ỹ" */
    0x24, 0xb2, 0xe, 0x34, 0x4d, 0x8a, 0x1c, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+1EF9 "ỹ" */
    0x25, 0x60, 0x31, 0x45, 0x36, 0x8a, 0x28, 0xc1,
    0x4, 0x21, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 58, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 72, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 126, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 39, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 53, .adv_w = 77, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 59, .adv_w = 78, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 65, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 69, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 77, .adv_w = 44, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 62, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 79, .adv_w = 59, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 92, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 88, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 126, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 54, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 47, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 181, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 187, .adv_w = 123, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 190, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 196, .adv_w = 106, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 201, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 223, .adv_w = 146, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 147, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 61, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 196, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 396, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 145, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 143, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 199, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 59, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 502, .adv_w = 92, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 511, .adv_w = 59, .box_w = 2, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 515, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 519, .adv_w = 101, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 520, .adv_w = 69, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 521, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 117, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 573, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 54, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 54, .box_w = 3, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 590, .adv_w = 114, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 54, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 196, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 634, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 76, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 73, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 168, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 695, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 76, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 707, .adv_w = 55, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 709, .adv_w = 76, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 715, .adv_w = 152, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 718, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 61, .box_w = 2, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 61, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 858, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 898, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 911, .adv_w = 135, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 951, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 960, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 969, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 978, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 55, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 55, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 995, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1015, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1025, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1035, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1053, .adv_w = 106, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1064, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1081, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1090, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1101, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 61, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1120, .adv_w = 55, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1127, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1139, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1148, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1171, .adv_w = 156, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1185, .adv_w = 139, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1194, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1211, .adv_w = 122, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1219, .adv_w = 146, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1237, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1246, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1265, .adv_w = 122, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1278, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1297, .adv_w = 122, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1308, .adv_w = 146, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1325, .adv_w = 122, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1337, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1356, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1366, .adv_w = 146, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1386, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1396, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1415, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1424, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1443, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1452, .adv_w = 146, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1472, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1482, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1501, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1511, .adv_w = 146, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1530, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1540, .adv_w = 127, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1552, .adv_w = 119, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1561, .adv_w = 127, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1573, .adv_w = 119, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1582, .adv_w = 127, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1592, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1601, .adv_w = 127, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1615, .adv_w = 119, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1627, .adv_w = 127, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1641, .adv_w = 119, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1653, .adv_w = 127, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1667, .adv_w = 119, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1679, .adv_w = 127, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1691, .adv_w = 119, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1701, .adv_w = 127, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1715, .adv_w = 119, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1727, .adv_w = 61, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1731, .adv_w = 55, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1734, .adv_w = 61, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1736, .adv_w = 54, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1738, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1751, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1760, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1775, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1786, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1801, .adv_w = 128, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1814, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1829, .adv_w = 128, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1842, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1857, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1869, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1884, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1896, .adv_w = 154, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1912, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1924, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1940, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1951, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1967, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1978, .adv_w = 154, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1995, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2007, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2022, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2033, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2049, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2060, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2072, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2080, .adv_w = 145, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2094, .adv_w = 123, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2103, .adv_w = 156, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2121, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2132, .adv_w = 156, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2150, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2161, .adv_w = 156, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2180, .adv_w = 139, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2192, .adv_w = 156, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2209, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2220, .adv_w = 156, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2237, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2248, .adv_w = 135, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2261, .adv_w = 106, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2272, .adv_w = 135, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2284, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2293, .adv_w = 135, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2307, .adv_w = 106, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2319, .adv_w = 135, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2331, .adv_w = 106, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xc,
    0xd, 0x12, 0x13, 0x14, 0x15, 0x19, 0x1a, 0x1d,
    0x20, 0x21, 0x22, 0x23, 0x28, 0x29, 0x2a, 0x2c,
    0x2d, 0x32, 0x33, 0x34, 0x35, 0x39, 0x3a, 0x3d,
    0x42, 0x43, 0x50, 0x51, 0x68, 0x69, 0xa8, 0xa9,
    0xe0, 0xe1, 0xef, 0xf0
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 192, .range_length = 241, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 44, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 7840, .range_length = 90, .glyph_id_start = 140,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 0, 2, 0, 0, 0, 0,
    2, 3, 0, 0, 0, 4, 0, 4,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 7, 8, 9, 10, 11,
    0, 12, 12, 13, 14, 15, 12, 12,
    9, 16, 17, 18, 0, 19, 13, 20,
    21, 22, 23, 24, 25, 0, 0, 0,
    0, 0, 26, 27, 28, 0, 29, 30,
    0, 31, 0, 0, 32, 0, 31, 31,
    33, 27, 0, 34, 0, 35, 0, 36,
    37, 38, 36, 39, 40, 0, 0, 0,
    6, 6, 6, 6, 10, 10, 10, 12,
    12, 9, 9, 9, 9, 13, 13, 23,
    26, 26, 26, 26, 29, 29, 29, 0,
    0, 33, 33, 33, 33, 0, 0, 36,
    6, 26, 9, 0, 12, 0, 13, 0,
    0, 0, 0, 0, 6, 26, 6, 26,
    6, 26, 6, 26, 6, 26, 6, 26,
    6, 26, 6, 26, 6, 26, 6, 26,
    6, 26, 6, 26, 10, 29, 10, 29,
    10, 29, 10, 29, 10, 29, 10, 29,
    10, 29, 10, 29, 12, 0, 12, 0,
    9, 33, 9, 33, 9, 33, 9, 33,
    9, 33, 9, 33, 9, 33, 0, 0,
    0, 0, 0, 0, 0, 33, 0, 0,
    13, 0, 13, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 23, 36,
    23, 36, 23, 36, 23, 36
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 0, 2, 0, 0, 0, 3,
    2, 0, 4, 5, 0, 6, 7, 6,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    9, 0, 10, 0, 11, 0, 0, 0,
    11, 0, 0, 12, 0, 0, 0, 0,
    11, 0, 11, 0, 13, 14, 15, 16,
    17, 18, 19, 20, 0, 0, 21, 0,
    0, 0, 22, 0, 23, 23, 23, 24,
    23, 0, 0, 0, 0, 0, 25, 25,
    26, 25, 23, 27, 28, 29, 30, 31,
    32, 33, 31, 34, 0, 0, 35, 0,
    10, 10, 10, 10, 0, 0, 0, 0,
    0, 11, 11, 11, 11, 15, 15, 19,
    22, 22, 22, 22, 23, 23, 23, 0,
    0, 26, 26, 26, 26, 30, 30, 31,
    10, 22, 0, 0, 0, 0, 15, 30,
    11, 23, 36, 30, 10, 22, 10, 22,
    10, 22, 10, 22, 10, 22, 10, 22,
    10, 22, 10, 22, 10, 22, 10, 22,
    10, 22, 10, 22, 0, 23, 0, 23,
    0, 23, 0, 23, 0, 23, 0, 23,
    0, 23, 0, 23, 0, 0, 0, 0,
    11, 26, 11, 26, 11, 26, 11, 26,
    11, 26, 11, 26, 11, 26, 11, 23,
    11, 23, 11, 23, 11, 26, 11, 23,
    15, 30, 15, 30, 0, 30, 0, 30,
    0, 30, 0, 30, 0, 30, 19, 31,
    19, 31, 19, 31, 19, 31
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -12, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -19, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -24,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -13, 0, 0,
    0, 0, 0, 0, -7, 0, -1, 0,
    0, -14, -2, -10, -8, 0, -10, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    -2, -1, -5, -4, 0, 1, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, -11, 0, 0,
    0, -2, 0, 0, 0, -3, 0, -2,
    0, -2, -5, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, -2, -2, 0, -2, 0, 0,
    0, -2, -3, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -26, 0, 0,
    0, -19, 0, -29, 0, 2, 0, 0,
    0, 0, 0, 0, 0, -4, -2, 0,
    0, -2, -3, 0, 0, -2, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    0, -3, 0, 0, 0, 2, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -3, -3, 0, 0,
    0, -3, -4, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, -7, 0, 0, -30, -6, -19,
    -16, 0, -26, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, -15, -10,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -35, 0, 0, 0, -15, 0, -22,
    0, 0, 0, 0, 0, -3, 0, -3,
    0, -1, -1, 0, 0, -1, 0, 0,
    2, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, -3,
    -2, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -9, 0, -2, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, -24, -25, 0,
    0, -9, -3, -26, -2, 2, 0, 2,
    2, 0, 2, 0, 0, -12, -11, 0,
    -12, -11, -8, -13, 0, -10, -8, -6,
    -8, -7, 0, 0, 0, 0, 0, 2,
    0, -25, -4, 0, 0, -8, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, -5, -5, 0, 0, -5, -3, 0,
    0, -3, -1, 0, 0, 0, 2, 0,
    0, 0, 0, 2, 0, -13, -7, 0,
    0, -5, 0, 0, 0, 2, 0, 0,
    0, 0, 0, 0, 1, -4, -3, 0,
    0, -3, -2, 0, 0, -2, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, -5, 0, 0, 0, -3, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, -3, 0, 0, -2, 0, 0,
    0, -2, -3, 0, 0, 0, 0, 0,
    0, 0, -3, 2, -5, -23, -6, 0,
    0, -10, -3, -10, -2, 2, -10, 2,
    2, 1, 2, 0, 2, -8, -7, -2,
    -4, -7, -4, -6, -2, -4, -2, 0,
    -3, -3, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, -2, 0, 0,
    0, -2, -3, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    -2, -2, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 2, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    0, -11, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    -2, -2, 0, 0, 0, 2, 0, 0,
    0, -13, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -2, 2, 0, -2, 0, 0,
    5, 0, 2, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    0, -12, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -1, 1, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -14, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 40,
    .right_class_cnt     = 36,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 3,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Tiengviet14 = {
#else
lv_font_t ui_font_Tiengviet14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_TIENGVIET14*/

