/*
 * Coloring interface in graffit library < coloring.h >
 *
 * Various Definitions of Color for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 2000 Taiji Yamada, AIHARA Electrical Engineering Co., Ltd.
 */
#ifndef _COLORING_H_
#define _COLORING_H_
#include <graphics.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   カラー定義(Coloring)パッケージ

   これはBGIに与えられているパレットに対して、グラデーションカラーなどを
   定義するためのルーチン集です。例えば4次元グラフィックスを描画する時に、
   4次元目をグラデーションカラーに割り当てるためなどに使用できるでしょう。

   このパッケージでは以下の列挙型を基本色としてアクセスします。

   enum COLORS {
     BLACK     = 0, DARKGRAY     =  8,
     BLUE      = 1, LIGHTBLUE    =  9,
     GREEN     = 2, LIGHTGREEN   = 10,
     CYAN      = 3, LIGHTCYAN    = 11,
     RED       = 4, LIGHTRED     = 12,
     MAGENTA   = 5, LIGHTMAGENTA = 13,
     BROWN     = 6, YELLOW       = 14,
     LIGHTGRAY = 7, WHITE        = 15,
   };

   カラー定義のルーチンには以下の関数が用意されています。

   ・RGB直線グラデーション
   coloring(開始番号, 終了番号)

   ・2色直線グラデーション
   coloring2(開始番号, 終了番号, 基本色1, 基本色2)

   ・3色平面グラデーション
   coloring3(開始番号, 終了番号, 基本色1, 基本色2, 基本色3)

   ・N色串型グラデーション
   coloringN(開始番号, 終了番号, 基本色数, *基本色配列)

   開始番号と終了番号はパレット番号であり、0 から getmaxcolor() で返される
   カラー数の範囲内で指定できます。基本色には列挙型 COLORS を指定します。
   これらは、いずれもカラーリングが行われた色数を返します。
   ただし、カラーリングに失敗した場合には 0 を返します。
   パレットの開始番号と終了番号が同一であってはなりません。

   カラー定義のルーチンによって定義されたカラーを指定するには、
   直接、パレット番号を指定する以外に、
   浮動小数点による仮想的なカラー軸を指定し、
   浮動小数点によってアクセスするための関数が用意されています。

   ・直線グラデーション用
   co_coloring(開始番号, 終了番号, double r1, double r2)
   int getcolor_(double r)
   setcolor_(double r)

   ・直線グラデーション用、底が 10 のログスケーリング
   co_coloring(開始番号, 終了番号, double r1, double r2)
   int getlog10color_(double r)
   setlog10color_(double r)

   (注) BGI では連続するパレット番号に既定色が割り当てられており、
   BLACK, BLUE, GREEN,... という配色が enum 型 COLORS で宣言されている。
   このヘッダファイルの目的はパレットの RGB 値を直接操作し、好みの色表
   現を行うことであるので enum 型 COLORS で宣言されている BLUE, RED な
   どの値は当然意味をなさなくなる。しかし、前景色、背景色に関してはパ
   レット操作を行わないのが通例であろう。オリジナルの BGI では主に 16 
   色を前提に設計されているが、機種モードによっては 2,4,8 色などの色数
   を扱うこともある。また、拙作 X11 用 BGI では任意数のパレットを扱う
   ことが可能である。XBGI では BGI のパレット定義の慣例として、パレッ
   ト番号 0 に黒、パレット番号 getmaxcolor() に白が割り当てられている。
   この慣例を生かすことを考慮すると、上記の関数の推奨的な使い方は, 0 
   と getmaxcolor() を除く連続したパレット番号に対してRGB定義を行うこ
   とである。

   (例) coloring(1, getmaxcolor()-1);

   もし 16 色モードなら 1 から 15 までがユーザーが利用するグラデーショ
   ンとなり 0(=BLACK) と getmaxcolor(=WHITE) は保存される。
 */

enum coloring_kinds {
  COLORING_CMY, /*0.5*/
  COLORING_MRYWGCB,
  /*COLORING_RGB,*/
  COLORING_RGB, /*0.7*/
  /*COLORING_RGBK,*/ /*0.8*/
  COLORING_RGBK, /*0.9*/
  /*COLORING_RGBW,*/ /*0.9*/
  COLORING_RYGCB,
  /*COLORING_RYGCB,*/ /*0.9*/
  COLORING_RYGCBK,
  COLORING_RYGCBM,
  /*COLORING_RYGCMB,*/ /*-1*/
  /*COLORING_RYGCMB,*/
  /*COLORING_RYGKCBM,*/
  COLORING_WMRYGCBK,
  /*COLORING_WRGB,*/
  /*COLORING_WRGB,*/ /*0.8*/
  COLORING_WRGB, /*0.9*/
  COLORING_WRYGCBK,
  COLORING_WYGCBMRK,
  COLORING_YMC, /*0.5*/
  COLORING_YRMKBCG,
  N_COLORING,
};
extern char *coloring_kind_name[];

struct coloringtype_ {
  int p1, p2;
  double r1, r2;
  enum coloring_kinds coloringkind;
};

/*
   [名前]
   coloring2c --- 2色直線グラデーション
   coloring3c --- 3色直線グラデーション
   coloring4c --- 4色直線グラデーション
   coloring5c --- 5色直線グラデーション
   coloring6c --- 6色直線グラデーション
   coloring7c --- 7色直線グラデーション
   coloring8c --- 8色直線グラデーション

   [形式]
   coloring2c(p1, p2, c1, c2, c)
   coloring3c(p1, p2, c1, c2, c3, c)
   coloring4c(p1, p2, c1, c2, c3, c4, c)
   coloring5c(p1, p2, c1, c2, c3, c4, c5, c)
   coloring6c(p1, p2, c1, c2, c3, c4, c5, c6, c)
   coloring7c(p1, p2, c1, c2, c3, c4, c5, c6, c7, c)
   coloring8c(p1, p2, c1, c2, c3, c4, c5, c6, c7, c8, c)
   int p1, p2;     パレット番号p1からp2まで
   int c1, c2; 2色の基本色
   int c1, c2, c3; 3色の基本色
   int c1, c2, c3, c4; 4色の基本色
   int c1, c2, c3, c4, c5; 5色の基本色
   int c1, c2, c3, c4, c5, c6; 6色の基本色
   int c1, c2, c3, c4, c5, c6, c7; 7色の基本色
   int c1, c2, c3, c4, c5, c6, c7, c8; 8色の基本色
   double c;       混合率

   [説明]
   指定されたN(=3)色を基本として、
   c1 -> c2 -> c3 -> ... となるようなグラデーションカラーを定義します。
   c は混色率で大きければよく混ぜます。
   c の推奨値はN=3のときは0.7|0.5、N=4のときは0.9、N=5..8のときは1です。
 */
extern int coloring2c(int p1, int p2, int c1, int c2, double c);
extern int coloring3c(int p1, int p2, int c1, int c2, int c3, double c);
extern int coloring4c(int p1, int p2, int c1, int c2, int c3, int c4, double c);
extern int coloring5c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, double c);
extern int coloring6c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, int c6, double c);
extern int coloring7c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, int c6, int c7, double c);
extern int coloring8c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8, double c);

/*
   [名前]
   coloring --- RGB直線グラデーション

   [形式]
   coloring(p1, p2)
   int p1, p2; パレット番号p1からp2まで

   [説明]
   RGB(赤、緑、青)を基本として、
   赤 -> 緑 -> 青 となるようなグラデーションカラーを定義します。

   setcoloringtype(kind)
   int kind;

   にenum coloring_kindsで定義される定数を指定することにより、
   さまざまなグラデーションカラーのバリエーションを選べます。
 */
extern void setcoloringtype(int kind);
extern int coloring(int p1, int p2);

/*
   [名前]
   coloring2 --- 2色直線グラデーション

   [形式]
   coloring2(p1, p2, c1, c2)
   int p1, p2; パレット番号p1からp2まで
   int c1, c2; 2色の基本色
 *
   [説明]
   指定された2色を基本として直線のグラデーションを定義します。
 */
extern int coloring2(int p1, int p2, int c1, int c2);

/*
   [名前]
   co_coloring     --- 実数を直線グラデーションのパレット番号に対応
   getcolor_       --- 指定された実数が対応するパレットを返す
   setcolor_       --- 指定された実数が対応するパレットで前景色をセット
   getlog10color_  --- 指定された実数が対応するパレットを返す(対数)
   setlog10color_  --- 指定された実数が対応するパレットで前景色をセット(対数)

   [形式]
   co_coloring(int p1, int p2, double r1, double r2)
   int getcolor_(double r)
   setcolor_(double r)
   int getlog10color_(double r)
   setlog10color_(double r)
   int p1, p2;    パレット番号p1からp2まで
   double r1, r2; 対応される実数領域r1からr2まで
   double r;      実数領域内のある一点

   [説明]
   これらは、実数を直線グラデーションのパレット番号にアクセスするために
   使用します。例えば、以下のように使用します。

   coloring(0, getmaxcolor());              RGBグラデーションを定義
   co_coloring(0, getmaxcolor(), 0.0, 1.0); カラーを実数[0,1]に写像
   c = getcolor_(0.1);                      0.1に対応するパレットを取得
   putpixel(100, 100, c);                   座標(100,100)に点を描画
   setcolor_(0.5);                          0.5に対応するパレットを前景色に
   line(100, 100, 200, 200);                その色で線を描画

   また、対数スケーリングの場合は以下のようにします。

   coloring(0, getmaxcolor());              RGBグラデーションを定義
   co_coloring(0, getmaxcolor(), 0.001, 10.0); カラーを実数[0.001,10.0]に写像
   c = getlog10color_(1.0);                 1.0に対応するパレットを取得
   putpixel(100, 100, c);                   座標(100,100)に点を描画
   setlog10color_(0.5);                     0.5に対応するパレットを前景色に
   line(100, 100, 200, 200);                その色で線を描画

 */
extern void co_coloring(int p1, int p2, double r1, double r2);
extern int getcolor_(double r);
extern void setcolor_(double r);

extern int getlog10color_(double r);
extern void setlog10color_(double r);

/*
   [名前]
   coloring3 --- 3色平面グラデーション

   [形式]
   coloring3(p1, p2, c1, c2, c3)
   int p1, p2;     パレット番号p1からp2まで
   int c1, c2, c3; 3色の基本色

   [説明]
   指定された3色を基本として平面のグラデーションを定義します。
 */
extern int coloring3(int p1, int p2, int c1, int c2, int c3);

/*
   [名前]
   coloringN --- N色串型グラデーション

   [形式]
   coloringN(p1, p2, n, C)
   int p1, p2; パレット番号p1からp2まで
   int n;      基本色の数
   int *C;     基本色の配列

   [説明]
   指定されたN色を基本として串型のグラデーションを定義します。
 */
extern int coloringN(int p1, int p2, int n, int *C);

/*
   [名前]
   swap_colors --- 2色p1とp2を入れ替えるルーチン

   [形式]
   swap_colors(p1, p2)
   int p1; パレット番号1
   int p2; パレット番号2

   [説明]
   2色p1とp2を入れ替えます。
 */
extern void swap_colors(int p1, int p2);

/*
   [名前]
   rotate_colors --- p2-p1間のパレットを回転するルーチン

   [形式]
   rotate_colors(p1, p2)
   int p1; パレット番号1
   int p2; パレット番号2

   [説明]
   p2-p1間のパレットを回転します。
 */
extern void rotate_colors(int p1, int p2);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _COLORING_H_ */



