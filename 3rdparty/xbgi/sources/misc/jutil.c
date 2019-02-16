/*
 * Japanese code system utilities < jutil.c >
 *
 * 日本語のコード体系に関するユーティリティ
 *
 * Copyright (c) 1992-94 Tokyo Denki University, Taiji Yamada
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <jutil.h>

#ifndef __JCTYPE_H

#define ___  0
#define _1_  _KNJ_1 /* Legal 1st byte of double byte code */
#define __2  _KNJ_2 /* Legal 2nd byte of double byte code */
#define _M_  _KNJ_M /* Non-puntuation in Kana-set */
#define _P_  _KNJ_P /* Punctuation of Kana-set */
#define _12 (_1_|__2)
#define _M2 (_M_|__2)
#define _P2 (_P_|__2)

char _jctype[257] = {
/*-1*/  ___,
/*0x*/  ___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,
/*1x*/  ___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,
/*2x*/  ___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,
/*3x*/  ___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,___,
/*4x*/  __2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,
/*5x*/  __2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,
/*6x*/  __2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,
/*7x*/  __2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,__2,___,
/*8x*/  __2,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,
/*9x*/  _12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,
/*Ax*/  __2,_P2,_P2,_P2,_P2,_P2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,
/*Bx*/  _M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,
/*Cx*/  _M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,
/*Dx*/  _M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,_M2,
/*Ex*/  _12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,
/*Fx*/  _12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,_12,___,___,___
};

unsigned short jmstojis( unsigned short c )
{
  int c1, c2;

  c2 = (unsigned char)c;
  c1 = c >> 8;
  if (c1 < 0xf0 && iskanji(c1) && iskanji2(c2)) {
    if (c1 >= 0xe0)
      c1 -= 0x40;
    c1 -= 0x70;
    c1 <<= 1;
    if (c2 < 0x9f) {
      c1 --;
      c2 -= 0x1f;
      if (c2 >= (0x80-0x1f))
        c2 --;
    } else {
      c2 -= 0x7e;
    }
    return ((c1 << 8) | c2);
  }
  return 0;
}

unsigned short jistojms( unsigned short c )
{
  int c1, c2;

  c2 = (unsigned char)c;
  c1 = c >> 8;
  if (c1 >= 0x21 && c1 <= 0x7e && c2 >= 0x21 && c2 <= 0x7e) {
    if (c1 & 0x01) {
      c2 += 0x1f;
      if (c2 >= 0x7f)
        c2 ++;
    } else {
      c2 += 0x7e;
    }
    c1 += 0xe1;
    c1 >>= 1;
    if (c1 >= 0xa0)
      c1 += 0x40;
    return ((c1 << 8) | c2);
  }
  return 0;
}

static unsigned short han_to_zen_ascii_table[0x5f] = {
  0x8140, 0x8149, 0x8168, 0x8194, 0x8190, 0x8193, 0x8195, 0x8166,
  0x8169, 0x816a, 0x8196, 0x817b, 0x8143, 0x817c, 0x8144, 0x815e,
  0x824f, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256,
  0x8257, 0x8258, 0x8146, 0x8147, 0x8183, 0x8181, 0x8184, 0x8148,
  0x8197, 0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266,
  0x8267, 0x8268, 0x8269, 0x826a, 0x826b, 0x826c, 0x826d, 0x826e,
  0x826f, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276,
  0x8277, 0x8278, 0x8279, 0x816d, 0x818f, 0x816e, 0x814f, 0x8151,
  0x8165, 0x8281, 0x8282, 0x8283, 0x8284, 0x8285, 0x8286, 0x8287,
  0x8288, 0x8289, 0x828a, 0x828b, 0x828c, 0x828d, 0x828e, 0x828f,
  0x8290, 0x8291, 0x8292, 0x8293, 0x8294, 0x8295, 0x8296, 0x8297,
  0x8298, 0x8299, 0x829a, 0x816f, 0x8162, 0x8170, 0x8150
};

static unsigned short han_to_zen_kana_table[0x40] = {
  0x8140, 0x8142, 0x8175, 0x8176, 0x8141, 0x8145, 0x8392, 0x8340,
  0x8342, 0x8344, 0x8346, 0x8348, 0x8383, 0x8385, 0x8387, 0x8362,
  0x815b, 0x8341, 0x8343, 0x8345, 0x8347, 0x8349, 0x834a, 0x834c,
  0x834e, 0x8350, 0x8352, 0x8354, 0x8356, 0x8358, 0x835a, 0x835c,
  0x835e, 0x8360, 0x8363, 0x8365, 0x8367, 0x8369, 0x836a, 0x836b,
  0x836c, 0x836d, 0x836e, 0x8371, 0x8374, 0x8377, 0x837a, 0x837d,
  0x837e, 0x8380, 0x8381, 0x8382, 0x8384, 0x8386, 0x8388, 0x8389,
  0x838a, 0x838b, 0x838c, 0x838d, 0x838f, 0x8393, 0x814a, 0x814b
};

#if 0 /* zentohan, reserved future */
static unsigned char zen_to_han_kana_table[0x8396-0x8340+1] = {
  0xa7, 0xb1, 0xa8, 0xb2, 0xa9, 0xb3, 0xaa, 0xb4,
  0xab, 0xb5, 0xb6, 0xb6, 0xb7, 0xb7, 0xb8, 0xb8,
  0xb9, 0xb9, 0xba, 0xba, 0xbb, 0xbb, 0xbc, 0xbc,
  0xbd, 0xbd, 0xbe, 0xbe, 0xbf, 0xbf, 0xc0, 0xc0,
  0xc1, 0xc1, 0xaf, 0xc2, 0xc2, 0xc3, 0xc3, 0xc4,
  0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xca,
  0xca, 0xcb, 0xcb, 0xcb, 0xcc, 0xcc, 0xcc, 0xcd,
  0xcd, 0xcd, 0xce, 0xce, 0xce, 0xcf, 0xd0, 0,
  0xd1, 0xd2, 0xd3, 0xac, 0xd4, 0xad, 0xd5, 0xae,
  0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdc,
  0xb2, 0xb4, 0xa6, 0xdd, 0xb3, 0xb6, 0xb9
};

#define ZTOH_SYMBOLS 9

static unsigned short zen_to_han_symbol_table_1[ZTOH_SYMBOLS] = {
  0x8142, 0x8175, 0x8176, 0x8141, 0x8145, 0x815b, 0x814a, 0x814b
};

static unsigned char zen_to_han_symbol_table_2[ZTOH_SYMBOLS] = {
  0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xb0, 0xde, 0xdf
};
#endif

#define ISKANA(c) ((c) >= 0xa1 && (c) <= 0xdf)
#define JISHIRA(c) ((c) >= 0x829f && (c) <= 0x82f1)
#define JISKANA(c) ((c) >= 0x8340 && (c) <= 0x8396 && (c) != 0x837f)
#define JTOKANA(c) ((c) <= 0x82dd ? (c) + 0xa1 : (c) + 0xa2)

static unsigned short hantozen(unsigned short c)
{
  if (c >= 0x20 && c <= 0x7e) {
    return han_to_zen_ascii_table[c - 0x20];
  } else if (ISKANA(c)) {
    return han_to_zen_kana_table[c - 0xa0];
  }
  return c;
}
#if 0 /* zentohan, reserved future */
static unsigned short zentohan(unsigned short c)
{
  int i;
  unsigned short *p;

  if (JISKANA(c)) {
    return zen_to_han_kana_table[c - 0x8340];
  } else if (JISHIRA(c)) {
    c = JTOKANA(c);
    return zen_to_han_kana_table[c - 0x8340];
  } else if (c <= 0x8396) {
    for (i = 0x20, p = han_to_zen_ascii_table; i <= 0x7e; i++, p++) {
      if (*p == c) {
        return i;
      }
    }
    for (i = 0; i < ZTOH_SYMBOLS; i++) {
      if (zen_to_han_symbol_table_1[i] == c) {
        return zen_to_han_symbol_table_2[i];
      }
    }
  }
  return c;
}
#endif
#endif

char _JISB[2][4] = {
  {0x1b,'$','B','\0'},
  {0x1b,'$','@','\0'}
};
char _JISE[3][4] = {
  {0x1b,'(','J','\0'},
  {0x1b,'(','B','\0'},
  {0x1b,'(','H','\0'}
};

static unsigned char *whereisjiss( unsigned char *line )
{
  unsigned char *ptr;

  if ( (ptr=strstr(line,_JISB[0])) == NULL ){
    if ( (ptr=strstr(line,_JISB[1])) == NULL ){
      return NULL;
    }else{
      return ptr;
    }
  }else{
    return ptr;
  }
}
static unsigned char *whereisjise( unsigned char *line )
{
  unsigned char *ptr;

  if ( (ptr=strstr(line,_JISE[0])) == NULL ){
    if ( (ptr=strstr(line,_JISE[1])) == NULL ){
      if ( (ptr=strstr(line,_JISE[2])) == NULL ){
	return NULL;
      }else{
	return ptr;
      }
    }else{
      return ptr;
    }
  }else{
    return ptr;
  }
}

int jcode( unsigned char *str )
{
  unsigned char *ptr;

  /* JCT_JIS */
  if ( whereisjiss( str ) != NULL || whereisjise( str ) != NULL )
    return JCT_JIS;
  /* JCT_ANK */
  ptr = str;
  while ( *ptr != '\0' ){
#if 0 /* THIS IS OLD VERSION 1.2 */
    if ( !iscntrl(*ptr) && !isprint(*ptr) )
      break;
#else
    if ( !isascii(*ptr) || !(iscntrl(*ptr)||isprint(*ptr)) )
      break;
#endif
    ptr++;
  }
  if ( *ptr == '\0' ) return JCT_ANK;
  /* JCT_EUC */
  ptr = str;
  while ( *ptr != '\0' ){
    if ( iseuc(*ptr) ){
      if ( iseuc2(*(ptr+1)) ){
        ptr += 2;
      }else{
        break;
      }
#if 0 /* THIS IS OLD VERSION 1.2 */
    }else if ( iscntrl(*ptr) || isprint(*ptr) ){
      ptr++;
#else
    }else if ( isascii(*ptr) && (iscntrl(*ptr)||isprint(*ptr)) ){
      ptr++;
#endif
    }else{
      break;
    }
  }
  if ( *ptr == '\0' ) return JCT_EUC;
  /* JCT_SJ */
  ptr = str;
  while ( *ptr != '\0' ){
    if ( iskanji(*ptr) ){
      if ( iskanji2(*(ptr+1)) ){
        ptr += 2;
      }else{
        break;
      }
#if 0 /* THIS IS OLD VERSION 1.2 */
    }else if ( iscntrl(*ptr) || isprint(*ptr) || iskana(*ptr) ){
      ptr++;
#else
    }else if ( (isascii(*ptr)&&(iscntrl(*ptr)||isprint(*ptr))) || iskana(*ptr) ) {
      ptr++;
#endif
    }else{
      break;
    }
  }
  /*if ( *ptr == '\0' )*/ return JCT_SJ;
  /*return JCT_ILGL;*/
}

int jfcode( FILE *fp )
{
  int code, codes[] = { 0, 0, 0, 0 };
  long fpos = 0;
  unsigned char buf[2048];

  if ( fp != stdin ) fpos = ftell( fp );
  while ( fgets(buf,2048,fp) != NULL ){
     code = jcode( buf );
     if ( code == JCT_JIS ){
       if ( fp != stdin ) fseek( fp, fpos, 0 );
       return JCT_JIS;
     }else if ( code != JCT_ILGL ){
       codes[code]++;
     }
  }
  if ( fp != stdin ) fseek( fp, fpos, 0 );
  if ( codes[JCT_SJ] == 0 && codes[JCT_EUC] == 0 ) return JCT_ANK;
  if ( codes[JCT_SJ] < codes[JCT_EUC] ) return JCT_EUC;
  return JCT_SJ;
}

static unsigned short kanatozen( unsigned short c )
{
  static unsigned short kana_to_zen_table[63] = {
    /* 。「」、・*/ 0x8142, 0x8175, 0x8176, 0x8141, 0x8145,
    /*ヲ*/          0x8392,
    /*ァィゥェォ*/  0x8340, 0x8342, 0x8344, 0x8346, 0x8348,
    /*ャュョッー*/  0x8383, 0x8385, 0x8387, 0x8362, 0x815b,
    /*アイウエオ*/  0x8341, 0x8343, 0x8345, 0x8347, 0x8349,
    /*カキクケコ*/  0x834a, 0x834c, 0x834e, 0x8350, 0x8352,
    /*サシスセソ*/  0x8354, 0x8356, 0x8358, 0x835a, 0x835c,
    /*タチツテト*/  0x835e, 0x8360, 0x8363, 0x8365, 0x8367,
    /*ナニヌネノ*/  0x8369, 0x836a, 0x836b, 0x836c, 0x836d,
    /*ハヒフヘホ*/  0x836e, 0x8371, 0x8374, 0x8377, 0x837a,
    /*マミムメモ*/  0x837d, 0x837e, 0x8380, 0x8381, 0x8382,
    /*ヤユヨラリ*/  0x8384, 0x8386, 0x8388, 0x8389, 0x838a,
    /*ルレロワン*/  0x838b, 0x838c, 0x838d, 0x838f, 0x8393,
    /*゛°*/        0x814a, 0x818b,
  };

  if ( 0xa1 <= (unsigned char)c && (unsigned char)c <= 0xdf )
    return kana_to_zen_table[(int)((unsigned char)c-0xa1)];
  return hantozen( c );
}

static unsigned short kana2zen( unsigned char *ptr, int *ptr_step )
{
  static unsigned short kana_2_zen_table[2][30] = {
    { /* 濁点 */
      /* アイウエオ */ 0x0000, 0x0000, 0x8394, 0x0000, 0x0000,
      /* カキクケコ */ 0x834b, 0x834d, 0x834f, 0x8351, 0x8353,
      /* サシスセソ */ 0x8355, 0x8357, 0x8359, 0x835b, 0x835d,
      /* タチツテト */ 0x835f, 0x8361, 0x8364, 0x8366, 0x8368,
      /* ナニヌネノ */ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      /* ハヒフヘホ */ 0x836f, 0x8372, 0x8375, 0x8378, 0x837b
    },
    { /* 半濁点 */
      /* アイウエオ */ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      /* カキクケコ */ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      /* サシスセソ */ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      /* タチツテト */ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      /* ナニヌネノ */ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
      /* ハヒフヘホ */ 0x8370, 0x8373, 0x8376, 0x8379, 0x837c
    },
  };

  if ( (0xde==*(ptr+1)||0xdf == *(ptr+1)) && (0xb1<=*ptr&&*ptr<=0xce) 
      &&(kana_2_zen_table[*(ptr+1)-0xde][*ptr-0xb1]) ){
    *ptr_step = 2;
    return kana_2_zen_table[*(ptr+1)-0xde][*ptr-0xb1];
  }
  *ptr_step = 1;
  return kanatozen(*ptr);
}

void sj2jis( unsigned char *src, unsigned char *dst )
{
  unsigned short jisc;
  int code, c;

  code = JCT_ANK;
  while ( *src != '\0' ){
    if ( !iskana(*src) && !(iskanji(*src)&&iskanji2(*(src+1))) ){
      if ( code == JCT_SJ ){
        *dst++ = _JISE[0][0];
        *dst++ = _JISE[0][1];
        *dst++ = _JISE[0][2];
      }
      code = JCT_ANK;
      *dst++ = *src++;
    }else{
      if ( code == JCT_ANK ){
        *dst++ = _JISB[0][0];
        *dst++ = _JISB[0][1];
        *dst++ = _JISB[0][2];
      }
      code = JCT_SJ;
      if ( !iskana(*src) ){
        jisc = jmstojis( s2code(src) );
        src += 2;
      }else{
        jisc = jmstojis( kana2zen(src,&c) );
        src += c;
      }
      *dst++ = codec1(jisc);
      *dst++ = codec2(jisc);
    }
  }
  if ( code == JCT_SJ ){
    *dst++ = _JISE[0][0];
    *dst++ = _JISE[0][1];
    *dst++ = _JISE[0][2];
  }
  *dst = '\0';
}

void jis2sj( unsigned char *src, unsigned char *dst )
{
  unsigned short sjis;
  int code;

  code = JCT_ANK;
  if ( whereisjiss( src ) > whereisjise( src ) )
    code = JCT_JIS;
  while ( *src != '\0' ){
    if ( isjise(src) ){
      code = JCT_ANK;
      src += 3;
    }else if ( isjiss(src) ){
      code = JCT_JIS;
      src += 3;
    }else{
      if ( code == JCT_ANK ){
        *dst++ = *src++;
      }else{
        sjis = jistojms( s2code(src) );
        *dst++ = codec1(sjis);
        *dst++ = codec2(sjis);
        src += 2;
      }
    }
  }
  *dst = '\0';
}

void jis2euc( unsigned char *src, unsigned char *dst )
{
  unsigned short eucc;
  int code;

  code = JCT_ANK;
  if ( whereisjiss( src ) > whereisjise( src ) )
    code = JCT_JIS;
  while ( *src != '\0' ){
    if ( isjise(src) ){
      code = JCT_ANK;
      src += 3;
    }else if ( isjiss(src) ){
      code = JCT_JIS;
      src += 3;
    }else{
      if ( code==JCT_ANK ){
        *dst++ = *src++;
      }else{
        eucc = jistoeuc( s2code(src) );
        *dst++ = codec1(eucc);
        *dst++ = codec2(eucc);
        src += 2;
      }
    }
  }
  *dst = '\0';
}

void euc2jis( unsigned char *src, unsigned char *dst )
{
  unsigned short jisc;
  int code;

  code = JCT_ANK;
  while ( *src != '\0' ){
    if ( !(iseuc(*src)&&iseuc2(*(src+1))) ){
      if ( code == JCT_EUC ){
        *dst++ = _JISE[0][0];
        *dst++ = _JISE[0][1];
        *dst++ = _JISE[0][2];
      }
      code = JCT_ANK;
      *dst++ = *src++;
    }else{
      if ( code == JCT_ANK ){
        *dst++ = _JISB[0][0];
        *dst++ = _JISB[0][1];
        *dst++ = _JISB[0][2];
      }
      code = JCT_EUC;
      jisc = euctojis( s2code(src) );
      *dst++ = codec1(jisc);
      *dst++ = codec2(jisc);
      src += 2;
    }
  }
  if ( code == JCT_EUC ){
    *dst++ = _JISE[0][0];
    *dst++ = _JISE[0][1];
    *dst++ = _JISE[0][2];
  }
  *dst = '\0';
}

void euc2sj( unsigned char *src, unsigned char *dst )
{
  unsigned short sjis;

  while ( *src != '\0' ){
    if ( !iseuc( *src ) || !iseuc2( *(src+1) ) ){
      *dst++ = *src++;
    }else{
      sjis = euctojms( s2code(src) );
      *dst++ = codec1(sjis);
      *dst++ = codec2(sjis);
      src += 2;
    }
  }
  *dst = '\0';
}

void sj2euc( unsigned char *src, unsigned char *dst )
{
  unsigned short eucc;
  int c;

  while ( *src != '\0' ){
    if ( !iskana(*src) && !(iskanji(*src)&&iskanji2(*(src+1))) ){
      *dst++ = *src++;
    }else{
      if ( !iskana(*src) ){
        eucc = jmstoeuc( s2code(src) );
        src += 2;
      }else{
        eucc = jmstoeuc( kana2zen(src,&c) );
        src += c;
      }
      *dst++ = codec1(eucc);
      *dst++ = codec2(eucc);
    }
  }
  *dst = '\0';
}

void str2sj( unsigned char *src, unsigned char *dst )
{
  int code = jcode(src);

  switch ( code ){
  case JCT_ANK:
  case JCT_SJ:  strcpy( dst, src ); break;
  case JCT_JIS: jis2sj( src, dst ); break;
  case JCT_EUC: euc2sj( src, dst ); break;
  }
}

void str2jis( unsigned char *src, unsigned char *dst )
{
  int code = jcode(src);

  switch ( code ){
  case JCT_ANK:
  case JCT_JIS: strcpy ( dst, src ); break;
  case JCT_SJ:  sj2jis ( src, dst ); break;
  case JCT_EUC: euc2jis( src, dst ); break;
  }
}

void str2euc( unsigned char *src, unsigned char *dst )
{
  int code = jcode(src);

  switch ( code ){
  case JCT_ANK:
  case JCT_EUC: strcpy ( dst, src ); break;
  case JCT_SJ:  sj2euc ( src, dst ); break;
  case JCT_JIS: jis2euc( src, dst ); break;
  }
}

#ifdef __MSDOS__
static int _JCODE = JCT_SJ;
#else
static int _JCODE = JCT_EUC;
#endif

void setjcode( int c )
{
  _JCODE = c;
}

int getjcode( void )
{
  return _JCODE;
}

int sjfputs( unsigned char *src, FILE *fp )
{
  unsigned short sjis, jisc, eucc;
  int code, c;

  code = JCT_ANK;
  while ( *src != '\0' ){
    if ( !iskana(*src) && !(iskanji(*src)&&iskanji2(*(src+1))) ){
      if ( code == JCT_SJ ){
        switch ( _JCODE ){
        case JCT_JIS:
          fprintf( fp, "%s", _JISE[0] );
          break;
        }
      }
      code = JCT_ANK;
      fprintf( fp, "%c", *src++ );
    }else{
      if ( code == JCT_ANK ){
        switch ( _JCODE ){
        case JCT_JIS:
          fprintf( fp, "%s", _JISB[0] );
          break;
        }
      }
      code = JCT_SJ;
      if ( !iskana(*src) ){
        sjis = s2code(src);
        src += 2;
      }else{
        sjis = kana2zen(src,&c);
        src += c;
      }
      switch ( _JCODE ){
      case JCT_SJ:
        fprintf( fp, "%c%c", codec1(sjis), codec2(sjis) );
        break;
      case JCT_JIS:
        jisc = jmstojis( sjis );
        fprintf( fp, "%c%c", codec1(jisc), codec2(jisc) );
        break;
      case JCT_EUC:
        jisc = jmstojis( sjis );
        eucc = jistoeuc( jisc );
        fprintf( fp, "%c%c", codec1(eucc), codec2(eucc) );
      }
    }
  }
  if ( code == JCT_SJ ){
    switch ( _JCODE ){
    case JCT_JIS:
      fprintf( fp, "%s", _JISE[0] );
      break;
    }
  }
  return 1;
}

int sjputs( unsigned char *str )
{
  return sjfputs( str, stdout );
}

int jisfputs( unsigned char *src, FILE *fp )
{
  unsigned short sjis, jisc, eucc;
  int code;

  code = JCT_ANK;
  if ( strstr( src, _JISB[0] ) > strstr( src, _JISE[0] ) ){
    code = JCT_JIS;
    switch ( _JCODE ){
    case JCT_JIS:
      fprintf( fp, "%s", _JISB[0] );
      break;
    }
  }
  while ( *src != '\0' ){
    if ( isjise(src) ){
      code = JCT_ANK;
      src += 3;
      switch ( _JCODE ){
      case JCT_JIS:
        fprintf( fp, "%s", _JISE[0] );
        break;
      }
    }else if ( isjiss(src) ){
      code = JCT_JIS;
      src += 3;
      switch ( _JCODE ){
      case JCT_JIS:
        fprintf( fp, "%s", _JISB[0] );
        break;
      }
    }else{
      if ( code == JCT_ANK ){
        fprintf( fp, "%c", *src++ );
      }else{
        jisc = s2code(src);
        src += 2;
        switch ( _JCODE ){
        case JCT_SJ:
          sjis = jistojms( jisc );
          fprintf( fp, "%c%c", codec1(sjis), codec2(sjis) );
          break;
        case JCT_JIS:
          fprintf( fp, "%c%c", codec1(jisc), codec2(jisc) );
          break;
        case JCT_EUC:
          eucc = jistoeuc( jisc );
          fprintf( fp, "%c%c", codec1(eucc), codec2(eucc) );
        }
      }
    }
  }
  if ( code == JCT_JIS ){
    switch ( _JCODE ){
    case JCT_JIS:
      fprintf( fp, "%s", _JISE[0] );
      break;
    }
  }
  return 1;
}

int jisputs( unsigned char *str )
{
  return jisfputs( str, stdout );
}

int eucfputs( unsigned char *src, FILE *fp )
{
  unsigned short sjis, jisc, eucc;
  int code;

  code = JCT_ANK;
  while ( *src != '\0' ){
    if ( !iseuc( *src ) || !iseuc2( *(src+1) ) ){
      if ( code == JCT_EUC ){
        switch ( _JCODE ){
        case JCT_JIS:
          fprintf( fp, "%s", _JISE[0] );
          break;
        }
      }
      code = JCT_ANK;
      fprintf( fp, "%c", *src++ );
    }else{
      if ( code == JCT_ANK ){
        switch ( _JCODE ){
        case JCT_JIS:
          fprintf( fp, "%s", _JISB[0] );
          break;
        }
      }
      code = JCT_EUC;
      eucc = s2code(src);
      src += 2;
      switch ( _JCODE ){
      case JCT_SJ:
        jisc = euctojis( eucc );
        sjis = jistojms( jisc );
        fprintf( fp, "%c%c", codec1(sjis), codec2(sjis) );
        break;
      case JCT_JIS:
        jisc = euctojis( eucc );
        fprintf( fp, "%c%c", codec1(jisc), codec2(jisc) );
        break;
      case JCT_EUC:
        fprintf( fp, "%c%c", codec1(eucc), codec2(eucc) );
        break;
      }
    }
  }
  if ( code == JCT_EUC ){
    switch ( _JCODE ){
    case JCT_JIS:
      fprintf( fp, "%s", _JISE[0] );
      break;
    }
  }
  return 1;
}
int eucputs( unsigned char *str )
{
  return eucfputs( str, stdout );
}

int jfputs( unsigned char *str, FILE *fp )
{
  int code;
  
  code = jcode(str);
  switch ( code ){
  case JCT_SJ:  return sjfputs ( str, fp );
  case JCT_JIS: return jisfputs( str, fp );
  case JCT_EUC: return eucfputs( str, fp );
  }
  return fputs( str, fp );
}

int jputs( unsigned char *str )
{
  return jfputs( str, stdout );
}

char *jfgets( unsigned char *str, size_t n, FILE *fp )
{
  int code;
  char *ret;
  unsigned char *dum;
  
  ret = fgets( str, n, fp );
  code = jcode(str);
  if ( code == JCT_ANK || _JCODE == code ){
    return ret;
  }
  dum = (unsigned char*)malloc( (strlen(str)+1)*sizeof(char) );
  strcpy( dum, str );
  switch ( _JCODE ){
  case JCT_SJ:  str2sj ( dum, str ); break;
  case JCT_JIS: str2jis( dum, str ); break;
  case JCT_EUC: str2euc( dum, str ); break;
  }
  free( dum );
  return ret;
}

char *jgets( unsigned char *str )
{
  int code;
  char *ret;
  unsigned char *dum;
  
  ret = gets( str );
  code = jcode(str);
  if ( code == JCT_ANK || _JCODE == code ){
    return ret;
  }
  dum = (unsigned char*)malloc( (strlen(str)+1)*sizeof(char) );
  strcpy( dum, str );
  switch ( _JCODE ){
  case JCT_SJ:  str2sj ( dum, str ); break;
  case JCT_JIS: str2jis( dum, str ); break;
  case JCT_EUC: str2euc( dum, str ); break;
  }
  free( dum );
  return ret;
}
