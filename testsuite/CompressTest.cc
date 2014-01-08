/*
 * STX String Functions
 * Copyright (C) 2007-2014 Timo Bingmann <tb@panthema.net>
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stx-string.h>
#include <stdlib.h>

#include "check.h"

#if HAVE_ZLIB

void test_compress()
{
    const unsigned char input_[642] = {
        0x4D,0x69,0x7A,0x58,0x4A,0x4D,0x55,0x73,0x68,0x4A,0x55,0x64,0x71,0x43,0x36,0x31,
        0x33,0x44,0x55,0x33,0x62,0x61,0x49,0x73,0x68,0x69,0x56,0x37,0x35,0x6B,0x6A,0x47,
        0x49,0x59,0x64,0x50,0x69,0x76,0x38,0x44,0x34,0x51,0x68,0x6B,0x53,0x64,0x62,0x4D,
        0x65,0x75,0x44,0x36,0x4B,0x4B,0x6F,0x72,0x71,0x38,0x70,0x6C,0x69,0x4D,0x70,0x71,
        0x69,0x48,0x35,0x47,0x32,0x31,0x4A,0x78,0x48,0x71,0x56,0x59,0x48,0x76,0x69,0x6D,
        0x64,0x6C,0x67,0x6E,0x74,0x49,0x55,0x5A,0x47,0x37,0x39,0x6F,0x4A,0x6F,0x53,0x70,
        0x76,0x4D,0x76,0x6F,0x44,0x33,0x5A,0x4A,0x68,0x73,0x68,0x70,0x62,0x46,0x50,0x34,
        0x6F,0x76,0x68,0x59,0x31,0x30,0x76,0x38,0x76,0x75,0x6B,0x33,0x58,0x31,0x69,0x47,
        0x44,0x55,0x73,0x45,0x4C,0x46,0x4E,0x73,0x79,0x73,0x56,0x4E,0x78,0x6B,0x49,0x61,
        0x54,0x6E,0x77,0x4A,0x62,0x68,0x48,0x4E,0x51,0x70,0x47,0x6C,0x65,0x6D,0x72,0x68,
        0x34,0x61,0x6B,0x46,0x66,0x76,0x79,0x52,0x65,0x4A,0x66,0x50,0x73,0x6C,0x70,0x42,
        0x4D,0x5A,0x4B,0x6F,0x37,0x50,0x7A,0x4C,0x33,0x33,0x77,0x58,0x66,0x64,0x33,0x61,
        0x31,0x62,0x66,0x58,0x4D,0x52,0x6F,0x71,0x5A,0x48,0x34,0x48,0x73,0x68,0x47,0x35,
        0x37,0x50,0x6A,0x32,0x63,0x59,0x44,0x56,0x50,0x78,0x72,0x75,0x51,0x69,0x4B,0x47,
        0x39,0x6F,0x64,0x4C,0x33,0x46,0x30,0x53,0x4E,0x73,0x5A,0x35,0x50,0x65,0x30,0x4B,
        0x74,0x58,0x43,0x4C,0x74,0x44,0x66,0x38,0x30,0x4D,0x74,0x46,0x73,0x31,0x4C,0x72,
        0x64,0x6D,0x30,0x58,0x72,0x6F,0x70,0x34,0x57,0x44,0x30,0x6D,0x68,0x6F,0x75,0x51,
        0x43,0x78,0x5A,0x74,0x79,0x34,0x73,0x6E,0x45,0x5A,0x73,0x77,0x4F,0x31,0x62,0x73,
        0x64,0x53,0x46,0x4B,0x36,0x75,0x44,0x52,0x76,0x33,0x31,0x53,0x66,0x6C,0x67,0x66,
        0x57,0x34,0x50,0x4C,0x79,0x37,0x79,0x31,0x55,0x65,0x6C,0x69,0x56,0x42,0x51,0x79,
        0x52,0x56,0x36,0x4C,0x45,0x39,0x63,0x78,0x30,0x54,0x47,0x57,0x33,0x6B,0x7A,0x50,
        0x65,0x45,0x59,0x52,0x39,0x4B,0x47,0x54,0x6F,0x72,0x32,0x37,0x71,0x47,0x76,0x37,
        0x61,0x71,0x4A,0x63,0x70,0x6C,0x50,0x65,0x35,0x54,0x30,0x77,0x34,0x6E,0x42,0x57,
        0x73,0x61,0x6C,0x72,0x69,0x72,0x39,0x4E,0x58,0x7A,0x4B,0x44,0x35,0x34,0x42,0x54,
        0x6B,0x4B,0x76,0x4E,0x74,0x39,0x72,0x6D,0x53,0x66,0x59,0x4B,0x4A,0x61,0x68,0x31,
        0x79,0x49,0x67,0x57,0x79,0x64,0x68,0x4C,0x53,0x73,0x4D,0x4D,0x6B,0x4E,0x64,0x4B,
        0x56,0x50,0x56,0x46,0x4F,0x44,0x70,0x65,0x69,0x45,0x70,0x70,0x65,0x4B,0x67,0x51,
        0x51,0x42,0x6B,0x43,0x65,0x49,0x4E,0x76,0x79,0x59,0x35,0x59,0x6A,0x59,0x67,0x33,
        0x6E,0x31,0x38,0x7A,0x34,0x6E,0x53,0x62,0x70,0x35,0x47,0x48,0x46,0x6C,0x58,0x54,
        0x6B,0x38,0x57,0x45,0x45,0x68,0x78,0x32,0x35,0x73,0x51,0x64,0x48,0x77,0x57,0x73,
        0x6E,0x53,0x67,0x67,0x35,0x79,0x35,0x6A,0x74,0x42,0x71,0x77,0x6B,0x45,0x46,0x4B,
        0x41,0x5A,0x4E,0x45,0x37,0x41,0x34,0x30,0x72,0x4B,0x54,0x77,0x34,0x70,0x63,0x66,
        0x37,0x38,0x39,0x31,0x75,0x34,0x61,0x62,0x34,0x45,0x4E,0x65,0x49,0x52,0x6E,0x47,
        0x6F,0x30,0x49,0x6C,0x79,0x43,0x61,0x64,0x4B,0x72,0x50,0x43,0x58,0x73,0x69,0x53,
        0x6F,0x66,0x48,0x5A,0x61,0x66,0x79,0x53,0x6B,0x43,0x77,0x71,0x52,0x58,0x78,0x33,
        0x4E,0x35,0x64,0x41,0x36,0x33,0x64,0x45,0x6B,0x72,0x48,0x35,0x58,0x6E,0x4D,0x42,
        0x49,0x54,0x59,0x67,0x78,0x4E,0x79,0x58,0x4E,0x6A,0x44,0x63,0x36,0x79,0x56,0x49,
        0x73,0x79,0x47,0x6D,0x72,0x68,0x71,0x51,0x4F,0x78,0x4A,0x6C,0x61,0x56,0x6C,0x6A,
        0x6E,0x39,0x44,0x61,0x4D,0x32,0x76,0x5A,0x62,0x77,0x7A,0x56,0x6C,0x4C,0x62,0x52,
        0x39,0x68,0x33,0x70,0x46,0x6A,0x33,0x54,0x56,0x43,0x33,0x76,0x57,0x65,0x53,0x39,
        0x62,0x57
    };

    std::string input = ARRAY_AS_STRING(input_);

    std::string compresstest = stx::string::compress(input);

    const unsigned char compressed_[513] = {
        0x78,0xDA,0x0D,0xD1,0x59,0xA2,0x6B,0x30,0x00,0x00,0xD0,0x2D,0xD1,0x50,0x7C,0xD6,
        0x4C,0x70,0x4D,0x35,0xFD,0xD1,0x20,0x86,0x9A,0xD2,0x86,0x74,0xF5,0xEF,0x9D,0x2D,
        0x1C,0x7F,0xF8,0x15,0xAE,0xFF,0x24,0xD8,0x7D,0xA2,0x5D,0xBB,0xF3,0x40,0x7F,0x82,
        0xA6,0x76,0x08,0x1E,0x32,0x49,0x9C,0x46,0xCB,0x29,0x51,0x38,0x50,0x59,0x17,0x22,
        0x3C,0x25,0xA8,0xF1,0xDB,0xAF,0x7E,0x87,0x70,0x3D,0x76,0x79,0x9B,0x07,0x7F,0xDB,
        0x07,0x5B,0xB4,0x6E,0xBC,0x7B,0xD9,0x7B,0x56,0xDA,0x74,0x78,0xA3,0xB9,0x5F,0x3E,
        0xCE,0xB3,0xB2,0x24,0x65,0x75,0xD7,0x64,0xA3,0x3E,0x5D,0x75,0x50,0xB9,0x98,0xE0,
        0xAD,0x31,0x43,0x61,0xA5,0xB8,0xE4,0x39,0x2A,0xD3,0xEF,0x04,0x0A,0x7E,0xB0,0xF4,
        0x27,0x31,0x3C,0x33,0x20,0x8C,0x64,0xC1,0x35,0x39,0x75,0xBA,0x9C,0x6E,0x83,0xED,
        0x20,0xDA,0xAC,0xB9,0x7D,0x1F,0x58,0xA8,0x27,0xB3,0xA3,0x2C,0x6E,0xDD,0x2E,0x24,
        0xF3,0xA6,0xFA,0x15,0x5C,0xA5,0xF0,0xE7,0x01,0x70,0x16,0x1D,0x02,0x35,0xDF,0x74,
        0x85,0x1F,0xAF,0x7B,0x65,0x0B,0x36,0xC1,0x96,0x28,0x85,0xE3,0xED,0x55,0xEA,0x59,
        0x78,0x1D,0xDF,0x68,0x80,0x96,0xB2,0x22,0x0F,0x98,0x5C,0x12,0x90,0x4A,0x0C,0x5B,
        0x0E,0x7E,0x0A,0xCD,0xFB,0xE8,0x9D,0xCC,0xF9,0x1F,0x93,0xF0,0xDE,0x81,0xDE,0x5C,
        0x71,0xAC,0x9B,0x90,0xEB,0xDC,0x1B,0xAF,0xDF,0x48,0xBB,0xAA,0x0F,0x13,0xC8,0x62,
        0x54,0xE4,0xFC,0xE3,0x1B,0x82,0x12,0x13,0xDE,0xBF,0x7A,0x4C,0x01,0x9F,0x74,0x73,
        0xDF,0xE5,0x42,0xE8,0x31,0x89,0xF1,0xCF,0x76,0x1E,0x32,0x35,0x62,0x71,0x76,0xF7,
        0x0C,0xE5,0x75,0x71,0xA9,0x95,0x83,0xE9,0x17,0xB6,0x46,0x19,0x2B,0xD0,0x4A,0xD7,
        0xE3,0x26,0xED,0x16,0x95,0xEA,0xDD,0x7D,0x6D,0x73,0xD8,0x8A,0x29,0x77,0x0A,0x8B,
        0x9A,0x93,0x7A,0x3E,0x86,0x43,0x09,0x8A,0x1F,0xD4,0x45,0x41,0x4D,0x27,0x48,0x83,
        0x8F,0x72,0xBC,0x93,0xAE,0x84,0x6E,0x8D,0x79,0xE6,0xF4,0x39,0x43,0xD8,0x4B,0x88,
        0xEF,0x4F,0x01,0x82,0x59,0x98,0x99,0x7F,0xFA,0xD6,0x0E,0xC6,0xB6,0xB5,0xB0,0x8F,
        0x22,0x75,0xD2,0x5A,0x27,0xA0,0xAC,0x14,0xCB,0xB1,0xEC,0xC1,0xC2,0xCB,0x3F,0x61,
        0x49,0x9A,0x4D,0xB4,0x6C,0x73,0x2E,0xD2,0x49,0xCE,0x0D,0x03,0x5F,0x37,0x91,0x44,
        0xC8,0x3E,0x73,0xB2,0x24,0x7D,0x2F,0x32,0x71,0xFC,0xA8,0xFB,0x39,0x19,0x26,0x7C,
        0x54,0x81,0x21,0x3D,0x04,0xEE,0x80,0xE9,0x29,0x6C,0xAF,0x4E,0x92,0x15,0xFE,0x2B,
        0xD4,0x8D,0x60,0x04,0xAD,0x13,0x2F,0xD6,0xCA,0x39,0x33,0xD3,0x6A,0x04,0x8F,0x50,
        0x2B,0xC8,0x90,0xAC,0x9D,0x5D,0xD5,0x1D,0x4B,0x26,0xED,0xDC,0xE3,0xE2,0x02,0x81,
        0x88,0x1E,0x77,0x80,0x8C,0xE9,0xB0,0xC5,0x62,0xF1,0x55,0x27,0x2D,0xFB,0x2B,0x60,
        0x45,0x30,0xEA,0xAF,0x3B,0xCB,0x1C,0xC2,0xAC,0xFF,0x6B,0x7B,0xF4,0x77,0xB9,0x73,
        0x9D,0xCD,0xE3,0xA2,0xE8,0xB5,0x7F,0xA3,0x55,0x73,0xFE,0xB2,0xD9,0x6B,0x62,0x05,
        0x83,0xCD,0x1C,0x41,0x9A,0x69,0x80,0xE6,0x6D,0xA2,0x34,0xF9,0x3F,0xB7,0x6F,0xDB,
        0xF8
    };

    std::string compressed = ARRAY_AS_STRING(compressed_);

    CHECK( compresstest == compressed );
}

void test_compress_random()
{
    std::string rand1 = stx::string::random_binary(1023);
    std::string rand2 = stx::string::random_alpha(1023);
    std::string rand3 = stx::string::random_alphanumeric(1023);

    CHECK( stx::string::decompress( stx::string::compress(rand1) ) == rand1 );
    CHECK( stx::string::decompress( stx::string::compress(rand2) ) == rand2 );
    CHECK( stx::string::decompress( stx::string::compress(rand3) ) == rand3 );
}

int main()
{
    test_compress();
    test_compress_random();

    return 0;
}

#else

int main()
{
    return 0;
}

#endif // HAVE_ZLIB
