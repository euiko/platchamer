/*
 * Japanese code system utilities < jutil.h >
 *
 * ���ܸ�Υ������ηϤ˴ؤ���桼�ƥ���ƥ�
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
 * (̾��) iskana   --- ���ե�JIS�����ɤΥ���ʸ�������ؿ�
 *        iskanji  --- ���ե�JIS�����ɤδ�����̸����ؿ�
 *        iskanji2 --- ���ե�JIS�����ɤδ������̸����ؿ�
 *        jmstojis --- ���ե�JIS����JIS�ؤΥ������Ѵ�
 *        jistojms --- JIS���饷�ե�JIS�ؤΥ������Ѵ�
 *
 * (����)
 *        MSDOS
 *        #include <jctype.h>
 *        UNIX &
 *        #include <jutil.h>
 *
 *        int iskana(c)
 *        int iskanji(c)
 *        int iskanji2(c)
 *        unsigned short c; �����о�ʸ��
 *
 *        unsigned short jmstojis( c )
 *        unsigned short jistojms( c )
 *        unsigned short c; �����о�ʸ��
 *
 * (����)
 *        ���줾��Borland C++�ʤɤ�MSDOS����ѥ���Υޥ˥奢��򸫤Ʋ�����.
 *
 * (��­)
 *        �������������ܸ�MSDOS�Υ���ѥ�����Ѱդ���Ƥ��륷�ե�JIS
 *        ���ܸ쥳���ɤΥ롼����ΰ�����UNIX�إ��ݡ��Ȥ����ΤǤ�.
 *        ���ܸ쥳���ɤΥ롼��������Ƥ���Ѥ��������ˤ��ۺ�jmskanji-1.0
 *        ��jctype.h�򤳤�jutil.h���ޤ��˥��󥯥롼�ɤ���ɬ�פ�����ޤ�.
 */
/*
 * (̾��) shiftjis --- ���ܸ쥷�ե�JISʸ����
 *
 * (����)
 *        ���ե�JIS��ɽ�����ʸ�����, ASCIIʸ���Υ���ե��å�ʸ���ΰ��
 *        �����ɤ��Ѥ�, ���Х��ȤΥ��ե�JIS�����ɤǳ�Ǽ�����.
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
 * (̾��) isjiss --- ʸ����JIS�����ɤγ��ϸ����ؿ�
 *        isjise --- ʸ����JIS�����ɤν�λ�����ؿ�
 *        
 * (����)
 *        #include <jutil.h>
 *
 *        int isjiss( s )
 *        int isjise( s )
 *        unsigned char *s; ʸ����Υݥ���
 *
 * (����)
 *        ʸ����JIS�����ɤγ���(��λ)�����ɤ��ޤޤ�Ƥ��뤫�ɤ���Ĵ�٤�.
 *        iskanji �� iseuc �Τ褦��ʸ�����Τ�Τ������ǤϤʤ�, 
 *        ����ʸ������Ƭ�ˤ��ʸ����Ǥ��뤳�Ȥ����.
 */
/*
 * (̾��) jis --- ���ܸ�JIS������ʸ����
 *
 * (����) JIS�����ɤ�ɽ�����ʸ�����, ��������ʸ����(^[$B)�Ƚ�λʸ����(^[(J)��
 *        �Ϥޤ줿ʸ���ΰ��, 2�Х��Ȥ�JIS�����ɤǳ�Ǽ�����.
 */
extern char _JISB[2][4];
extern char _JISE[3][4];

#define isjiss(s) \
((strncmp(s,_JISB[0],3)==0)||(strncmp(s,_JISB[1],3)==0))
#define isjise(s) \
((strncmp(s,_JISE[0],3)==0)||(strncmp(s,_JISE[1],3)==0)||(strncmp(s,_JISE[2],3)==0))

/*
 * (̾��) iseuc  --- EUC�δ�����̸����ؿ�
 *        iseuc2 --- EUC�δ������̸����ؿ�
 *        euctojis --- EUC����JIS�ؤΥ������Ѵ�
 *        jistoeuc --- JIS����EUC�ؤΥ������Ѵ�
 *        euctojms --- EUC���饷�ե�JIS�ؤΥ������Ѵ�
 *        jmstoeuc --- ���ե�JIS����EUC�ؤΥ������Ѵ�
 *
 * (����)
 *        #include <jutil.h>
 *
 *        int iseuc(c)
 *        int iseuc2(c)
 *        unsigned short c; �����о�ʸ��
 *
 *        unsigned short euctojis( c )
 *        unsigned short jistoeuc( c )
 *        unsigned short euctojms( c )
 *        unsigned short jmstoeuc( c )
 *        unsigned short c; �����о�ʸ��
 *
 * (����)
 *        EUC���ܸ쥳���ɤθ�����, JIS, ���ե�JIS�Ȥ�����Ѵ���Ԥʤ��ޤ�.
 */
/*
 * (̾��) eucj --- ���ܸ�EUC������ʸ����
 *
 * (����) EUC��ɽ�����ʸ�����, ASCIIʸ����Ⱦ�Ѥ���ʸ���ΰ�Υ����ɤ��Ѥ�, 
 *        ���Х��Ȥ�JIS�����ɤ�0x80��û����������ɤǳ�Ǽ�����.
 */
#define iseuc(c)  (0x8e<=(unsigned char)(c)&&(unsigned char)(c)<=0xfe\
		   &&(unsigned char)(c)!=0x8f&&(unsigned char)(c)!=0xa0)
#define iseuc2(c) (0xa0<=(unsigned char)(c)&&(unsigned char)(c)<=0xfe)

#define euctojis(u) ((u)-0x8080)
#define jistoeuc(u) ((u)+0x8080)
#define euctojms(u) jistojms(euctojis(u))
#define jmstoeuc(u) jistoeuc(jmstojis(u))

/*
 * (̾��) _JCODES --- ���ܸ쥳�������
 *
 * (����)
 *        #include <jutil.h>
 *
 *        enum _JCODES {
 *          JCT_ILGL = -1, // ���꡼�����ʸ��  //
 *          JCT_ANK,       // ASCII���ͥ���ʸ�� //
 *          JCT_SJ,        // ���ե�JISʸ��     //
 *          JCT_JIS,       // JISʸ��           //
 *          JCT_EUC        // EUC���ܸ�ʸ��     //
 *        };
 *
 * (����)
 *        �ص���, ���ܸ�ʸ���������ηϤ�ʬ�ह�뤿�����󷿤Ǥ�.
 */
enum _JCODES { JCT_ILGL = -1, JCT_ANK, JCT_SJ, JCT_JIS, JCT_EUC };

/*
 * (̾��) jcode  --- Ϳ����줿  ʸ����  ���ɤΥ������ηϤ�ɽ����Ƥ��뤫����
 *        jfcode --- Ϳ����줿���ȥ꡼�ब�ɤΥ������ηϤ�ɽ����Ƥ��뤫����
 *
 * (����)
 *        #include <jutil.h>
 *
 *        int jcode( unsigned char *str )
 *        unsigned char *str; ʸ����
 *
 *        int jfcode( fp )
 *        FILE *fp; �ե�����ݥ���
 *
 * (����)
 *        ʸ����, �ե����뤬�ɤΥ������ηϤ����ܸ줬�ޤޤ�Ƥ��뤫�֤��ޤ�.
 *        ���ͤ���� _JCODES �Ǥ�.
 */
extern int jcode( unsigned char *str );
extern int jfcode( FILE *fp );

/*
 * (̾��) sj2jis  --- ʸ����Υ��ե�JIS����JIS���Ѵ��ؿ�
 *        jis2sj  --- ʸ�����JIS���饷�ե�JIS���Ѵ��ؿ�
 *        jis2euc --- ʸ�����JIS����EUC�����ɤ��Ѵ��ؿ�
 *        euc2jis --- ʸ�����EUC����JIS�����ɤ��Ѵ��ؿ�
 *        euc2sj  --- ʸ�����EUC���饷�ե�JIS���Ѵ��ؿ�
 *        sj2euc  --- ʸ����Υ��ե�JIS����EUC���Ѵ��ؿ�
 *        str2sj  --- ʸ����Υ��ե�JIS���Ѵ��ؿ�
 *        str2jis --- ʸ�����JIS�����ɤ��Ѵ��ؿ�
 *        str2euc --- ʸ�����EUC���ܸ���Ѵ��ؿ�
 *
 * (����)
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
 *        unsigned char *src; �Ѵ�����ʸ����
 *        unsigned char *dst; �Ѵ����ʸ����
 *
 * (����)
 *        ������ʸ���󥳡��ɴ��Ѵ��ؿ�(SJ<->JIS, JIS<->EUC, EUC<->SJ)�Ǥ�.
 *        dst �ˤϽ�ʬ���ΰ褬���ݤ���Ƥ��ʤ���Фʤ�ޤ���.
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
 * (̾��) setjcode --- ���������Ϥ���ؤˤ��뤿��Υ����ȴ�������������ؿ�
 *        getjcode --- �����ȴ��������ɤ�����ؿ�
 *
 * (����) setjcode( jcode )
 *        enum _JCODES jcode; �����ȴ���������
 *
 *        enum _JCODES getjcode( void )
 *        ���ͤϥ����ȴ���������
 *
 * (����) �����ȴ��������ɤ���ꤷ, ���Ϥ�ץ���ॽ���������������ɤǤ�
 *        �����Ϥ����ꤵ�줿���������ɤˤ��뤿��Υ롼���󽸤ˤ�����
 *        �����ȴ��������ɤ����, ��������ؿ��Ǥ�.
 *        ����ˤ�ä����椵���Τϰʲ��Υ롼����Ǥ�.
 *
 *        jfputs, jputs --- ���Ϥ˴ؤ���ؿ�
 *        jfgets, jgets --- ���Ϥ˴ؤ���ؿ�
 *
 *        ���ϤǤ�ʸ���󤬲���Υ����ɤǤ⥫���ȴ��������ɤǽ��Ϥ���ޤ�.
 *        ���ϤǤ�����ʸ���󤬲���Υ����ɤǤ⥫���ȴ��������ɤǳ�Ǽ����ޤ�.
 */
extern void setjcode( int c );
extern int getjcode( void );

/*
 * (̾��)
 *        jfputs --- �����ȴ��������ɤǥ��ȥ꡼����Ϥ���ؿ�
 *        jputs  --- �����ȴ��������ɤ�ɸ����Ϥ���ؿ�
 *        jfgets --- �����ȴ��������ɤǥ��ȥ꡼�����Ϥ���ؿ�
 *        jgets  --- �����ȴ��������ɤ�ɸ�����Ϥ���ؿ�
 *
 * (����) 
 *        int jfputs( str, fp )
 *        char *str; ʸ����
 *        FILE *fp;  �ե����륹�ȥ꡼��
 *        �����������Ǥʤ�����, ���Ԥ� EOF
 *
 *        int jputs( src )
 *        char *str; ʸ����
 *        �����������Ǥʤ�����, ���Ԥ� EOF
 *
 *        char *jfgets( str, n, fp )
 *        char *str; ʸ����
 *        size_t n;  �Хåե�������
 *        FILE *fp;  �ե����륹�ȥ꡼��
 *        ��������� str �ؤΥݥ���, ���Ԥ� NULL
 *
 *        char *jgets ( str )
 *        char *str; ʸ����
 *        ��������� str �ؤΥݥ���, ���Ԥ� NULL
 *
 * (����)
 *        ���ϤǤ�ʸ���󤬲���Υ����ɤǤ⥫���ȴ��������ɤǽ��Ϥ���ޤ�.
 *        ���ϤǤ�����ʸ���󤬲���Υ����ɤǤ⥫���ȴ��������ɤǳ�Ǽ����ޤ�.
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
