/*
 * Japanese code system utilities < jutil.h >
 *
 * 日本語のコード体系に関するユーティリティ
 *
 * Copyright (c) 1992-94 Tokyo Denki University, Taiji Yamada
 */
#ifndef _JUTIL_H_
#define _JUTIL_H_

#define s2code(s) (((unsigned short)((unsigned char)(s[0])*0x100U\
				    +(unsigned char)(s[1]))))
#define codec1(c) ((unsigned char)(((c)>>8))&0x00ff)
#define codec2(c) ((unsigned char)((c)&0x00ff))

#ifndef __JCTYPE_H
/*
 * (名前) iskana   --- シフトJISコードのカナ文字検査関数
 *        iskanji  --- シフトJISコードの漢字上位検査関数
 *        iskanji2 --- シフトJISコードの漢字下位検査関数
 *        jmstojis --- シフトJISからJISへのコード変換
 *        jistojms --- JISからシフトJISへのコード変換
 *
 * (形式)
 *        MSDOS
 *        #include <jctype.h>
 *        UNIX &
 *        #include <jutil.h>
 *
 *        int iskana(c)
 *        int iskanji(c)
 *        int iskanji2(c)
 *        unsigned short c; 検査対象文字
 *
 *        unsigned short jmstojis( c )
 *        unsigned short jistojms( c )
 *        unsigned short c; 検査対象文字
 *
 * (説明)
 *        それぞれBorland C++などのMSDOSコンパイラのマニュアルを見て下さい.
 *
 * (補足)
 *        これらは本来日本語MSDOSのコンパイラに用意されているシフトJIS
 *        日本語コードのルーチンの一部をUNIXへサポートするものです.
 *        日本語コードのルーチンの全てを使用したい場合には拙作jmskanji-1.0
 *        のjctype.hをこのjutil.hよりまえにインクルードする必要があります.
 */
/*
 * (名前) shiftjis --- 日本語シフトJIS文字列
 *
 * (説明)
 *        シフトJISで表される文字列は, ASCII文字のグラフィック文字領域の
 *        コードを用い, ２バイトのシフトJISコードで格納される.
 */
#define _KNJ_M  ((char)0x01) /* Non-punctuation of Kana-set */
#define _KNJ_P  ((char)0x02) /* Punctuation of Kana-set */
#define _KNJ_1  ((char)0x04) /* Legal 1st byte of double byte stream */
#define _KNJ_2  ((char)0x08) /* Legal 2nd btye of double byte stream */

#define iskana(c)   ((_jctype+1)[(unsigned char)(c)]&(_KNJ_M|_KNJ_P))
#define iskanji(c)  ((_jctype+1)[(unsigned char)(c)]&_KNJ_1)
#define iskanji2(c) ((_jctype+1)[(unsigned char)(c)]&_KNJ_2)

extern char _jctype[257];

extern unsigned short jmstojis( unsigned short c );

extern unsigned short jistojms( unsigned short c );

#endif

/*
 * (名前) isjiss --- 文字列がJISコードの開始検査関数
 *        isjise --- 文字列がJISコードの終了検査関数
 *        
 * (形式)
 *        #include <jutil.h>
 *
 *        int isjiss( s )
 *        int isjise( s )
 *        unsigned char *s; 文字列のポインタ
 *
 * (説明)
 *        文字列がJISコードの開始(終了)コードか含まれているかどうか調べる.
 *        iskanji や iseuc のように文字そのものが引数ではなく, 
 *        その文字を先頭にもつ文字列であることに注意.
 */
/*
 * (名前) jis --- 日本語JISコード文字列
 *
 * (解説) JISコードで表される文字列は, 漢字開始文字列(^[$B)と終了文字列(^[(J)で
 *        囲まれた文字領域に, 2バイトのJISコードで格納される.
 */
extern char _JISB[2][4];
extern char _JISE[3][4];

#define isjiss(s) \
((strncmp(s,_JISB[0],3)==0)||(strncmp(s,_JISB[1],3)==0))
#define isjise(s) \
((strncmp(s,_JISE[0],3)==0)||(strncmp(s,_JISE[1],3)==0)||(strncmp(s,_JISE[2],3)==0))

/*
 * (名前) iseuc  --- EUCの漢字上位検査関数
 *        iseuc2 --- EUCの漢字下位検査関数
 *        euctojis --- EUCからJISへのコード変換
 *        jistoeuc --- JISからEUCへのコード変換
 *        euctojms --- EUCからシフトJISへのコード変換
 *        jmstoeuc --- シフトJISからEUCへのコード変換
 *
 * (形式)
 *        #include <jutil.h>
 *
 *        int iseuc(c)
 *        int iseuc2(c)
 *        unsigned short c; 検査対象文字
 *
 *        unsigned short euctojis( c )
 *        unsigned short jistoeuc( c )
 *        unsigned short euctojms( c )
 *        unsigned short jmstoeuc( c )
 *        unsigned short c; 検査対象文字
 *
 * (説明)
 *        EUC日本語コードの検査と, JIS, シフトJISとの相互変換を行ないます.
 */
/*
 * (名前) eucj --- 日本語EUCコード文字列
 *
 * (説明) EUCで表される文字列は, ASCII文字の半角かな文字領域のコードを用い, 
 *        ２バイトのJISコードに0x80を加算したコードで格納される.
 */
#define iseuc(c)  (0x8e<=(unsigned char)(c)&&(unsigned char)(c)<=0xfe\
		   &&(unsigned char)(c)!=0x8f&&(unsigned char)(c)!=0xa0)
#define iseuc2(c) (0xa0<=(unsigned char)(c)&&(unsigned char)(c)<=0xfe)

#define euctojis(u) ((u)-0x8080)
#define jistoeuc(u) ((u)+0x8080)
#define euctojms(u) jistojms(euctojis(u))
#define jmstoeuc(u) jistoeuc(jmstojis(u))

/*
 * (名前) _JCODES --- 日本語コード列挙型
 *
 * (形式)
 *        #include <jutil.h>
 *
 *        enum _JCODES {
 *          JCT_ILGL = -1, // イリーガルな文字  //
 *          JCT_ANK,       // ASCII数値カナ文字 //
 *          JCT_SJ,        // シフトJIS文字     //
 *          JCT_JIS,       // JIS文字           //
 *          JCT_EUC        // EUC日本語文字     //
 *        };
 *
 * (説明)
 *        便宜上, 日本語文字コード体系を分類するための列挙型です.
 */
enum _JCODES { JCT_ILGL = -1, JCT_ANK, JCT_SJ, JCT_JIS, JCT_EUC };

/*
 * (名前) jcode  --- 与えられた  文字列  がどのコード体系で表されているか検査
 *        jfcode --- 与えられたストリームがどのコード体系で表されているか検査
 *
 * (形式)
 *        #include <jutil.h>
 *
 *        int jcode( unsigned char *str )
 *        unsigned char *str; 文字列
 *
 *        int jfcode( fp )
 *        FILE *fp; ファイルポインタ
 *
 * (説明)
 *        文字列, ファイルがどのコード体系の日本語が含まれているか返します.
 *        返値は列挙型 _JCODES です.
 */
extern int jcode( unsigned char *str );
extern int jfcode( FILE *fp );

/*
 * (名前) sj2jis  --- 文字列のシフトJISからJISへ変換関数
 *        jis2sj  --- 文字列のJISからシフトJISへ変換関数
 *        jis2euc --- 文字列のJISからEUCコードへ変換関数
 *        euc2jis --- 文字列のEUCからJISコードへ変換関数
 *        euc2sj  --- 文字列のEUCからシフトJISへ変換関数
 *        sj2euc  --- 文字列のシフトJISからEUCへ変換関数
 *        str2sj  --- 文字列のシフトJISへ変換関数
 *        str2jis --- 文字列のJISコードへ変換関数
 *        str2euc --- 文字列のEUC日本語へ変換関数
 *
 * (形式)
 *        #include <jutil.h>
 *
 *        sj2jis ( src, dst )
 *        jis2sj ( src, dst )
 *        jis2euc( src, dst )
 *        euc2jis( src, dst )
 *        euc2sj ( src, dst )
 *        sj2euc ( src, dst )
 *        str2sj ( src, dst )
 *        str2jis( src, dst )
 *        str2euc( src, dst )
 *        unsigned char *src; 変換元の文字列
 *        unsigned char *dst; 変換先の文字列
 *
 * (説明)
 *        これらは文字列コード間変換関数(SJ<->JIS, JIS<->EUC, EUC<->SJ)です.
 *        dst には十分な領域が確保されていなければなりません.
 */
extern void sj2jis ( unsigned char *src, unsigned char *dst );
extern void jis2sj ( unsigned char *src, unsigned char *dst );
extern void jis2euc( unsigned char *src, unsigned char *dst );
extern void euc2jis( unsigned char *src, unsigned char *dst );
extern void euc2sj ( unsigned char *src, unsigned char *dst );
extern void sj2euc ( unsigned char *src, unsigned char *dst );
extern void str2sj ( unsigned char *src, unsigned char *dst );
extern void str2jis( unsigned char *src, unsigned char *dst );
extern void str2euc( unsigned char *src, unsigned char *dst );

/*
 * (名前) setjcode --- 漢字入出力を簡便にするためのカレント漢字コード設定関数
 *        getjcode --- カレント漢字コードを取得関数
 *
 * (形式) setjcode( jcode )
 *        enum _JCODES jcode; カレント漢字コード
 *
 *        enum _JCODES getjcode( void )
 *        返値はカレント漢字コード
 *
 * (説明) カレント漢字コードを指定し, 入力やプログラムソースが漢字コードでも
 *        入出力が固定された漢字コードにするためのルーチン集における
 *        カレント漢字コードを指定, 取得する関数です.
 *        これによって制御されるのは以下のルーチンです.
 *
 *        jfputs, jputs --- 出力に関する関数
 *        jfgets, jgets --- 入力に関する関数
 *
 *        出力では文字列が何れのコードでもカレント漢字コードで出力されます.
 *        入力では入力文字列が何れのコードでもカレント漢字コードで格納されます.
 */
extern void setjcode( int c );
extern int getjcode( void );

/*
 * (名前)
 *        jfputs --- カレント漢字コードでストリーム出力する関数
 *        jputs  --- カレント漢字コードで標準出力する関数
 *        jfgets --- カレント漢字コードでストリーム入力する関数
 *        jgets  --- カレント漢字コードで標準入力する関数
 *
 * (形式) 
 *        int jfputs( str, fp )
 *        char *str; 文字列
 *        FILE *fp;  ファイルストリーム
 *        成功すれば負でない整数, 失敗は EOF
 *
 *        int jputs( src )
 *        char *str; 文字列
 *        成功すれば負でない整数, 失敗は EOF
 *
 *        char *jfgets( str, n, fp )
 *        char *str; 文字列
 *        size_t n;  バッファサイズ
 *        FILE *fp;  ファイルストリーム
 *        成功すれば str へのポインタ, 失敗は NULL
 *
 *        char *jgets ( str )
 *        char *str; 文字列
 *        成功すれば str へのポインタ, 失敗は NULL
 *
 * (説明)
 *        出力では文字列が何れのコードでもカレント漢字コードで出力されます.
 *        入力では入力文字列が何れのコードでもカレント漢字コードで格納されます.
 */
extern int sjfputs( unsigned char *src, FILE *fp );
extern int sjputs ( unsigned char *str );
extern int jisfputs( unsigned char *src, FILE *fp );
extern int jisputs ( unsigned char *str );
extern int eucfputs( unsigned char *src, FILE *fp );
extern int eucputs ( unsigned char *str );
extern int jfputs( unsigned char *str, FILE *fp );
extern int jputs ( unsigned char *str );
extern char *jfgets( unsigned char *str, size_t n, FILE *fp );
extern char *jgets ( unsigned char *str );

#endif
