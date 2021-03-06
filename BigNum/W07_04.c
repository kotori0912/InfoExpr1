//========================================================
//   情報環境実験I 第7回 
//    多倍長整数の計算
//    問4(1)(2)
//    15T207伊藤 拓海
//========================================================

#include <stdio.h>
#include <time.h>
#include "BigNumLib.h"

#define _ope 3
//===============================================================
//  本体処理
//===============================================================

int main(void)
{
  //----  局所宣言
  BigNum n0;        // 加減乗算や累乗の結果変数
  BigNum n1, n2;    // 入力変数
  BigNum n3, n4;    // 除算における整商と剰余
  int e;            // 累乗の指数
  clock_t start, end;   // 時間計測
  double t0;    //計測時間の結果
  
  //----  入力処理
  printf("U1 N1[] = ? ??  "); bignum_input(&n1);    // 第1項の入力
  
#if _ope == 2 || _ope == 3
  printf("U2 N2[] = ? ??  "); bignum_input(&n2);    // 第2項の入力
#elif _ope == 0
  printf("E = ?  "); scanf("%d", &e);    // 累乗の指数の入力
#endif

  puts("Please wait !");
  
  start = clock();
  //----  計算処理
  // bignum_add(n1, n2, &n0);    // 加算(2引数)
  // bignum_sub(n1, n2, &n0);    // 減算(2引数)
  //bignum_mlt(n1, n2, &n0);    // 乗算(2引数)
  // n0 = n1; bignum_sq(&n0);    // 二乗(1引数)
  // bignum_pow(n1, e, &n0);    // 累乗(1引数、1指数)
  bignum_div(n1, n2, &n3, &n4);    // 除算(2引数)
  // bignum_sqrt(n1, &n0);       // 平方根(1引数)
  // bignum_plrt(n1, e, &n0);    // 累乗根(1引数、1指数)
  // bignum_gcd(n1, n2, &n0);    // 最大公約数(2引数)
  end = clock();

  //----  出力処理
#if _ope == 3
  printf("N3[] = "); bignum_output(n3);    // 整商の出力
  printf("N4[] = "); bignum_output(n4);    // 剰余の出力
#else
  printf("N0[] = "); bignum_output(n0);    // 結果の出力
#endif

  //----  処理時間の計算
  t0 = (end - start + 0.0) / CLOCKS_PER_SEC;    // 実数値
  
  //---- 計測時間の出力
  printf("\ntime = %.10f\n", t0);
  
  //----  終了処理
  return 0;
}

//========================================================
//     関数定義
//======================================================== 
//--------------------------------------------------------------------
//  多倍長整数の入力
//--------------------------------------------------------------------

Bool bignum_input(BigNum *n)
{
    //----  局所宣言
    int u;    // 多倍長の節数
    int t;    // 一時変数
    int k;    // 反復変数

    //----  初期処理
    bignum_init(n, 0);    // 結果を0に初期化

    //----  節数の入力と確認
    scanf("%d", &u);    // 節数の入力
    if ( u > UNI ) { return FALSE; }    // 節数の超上なら打切

    //----  各節の入力と確認
    for ( k = u-1; k >= 0; k-- ) {    // 上位節から
        scanf("%d", &t);    // 入力値の各格納
        if ( t >= RAD ) { return FALSE; }    // 節値が基数の以上なら打切
        (*n).num[k] = t;    // 構造体の配列メンバに節値を格納
    }

    //----  事後処理
    bignum_chk(n);    // 実際の桁数の計算

    //----  返却処理
    return TRUE;    // 処理が正常に完了
}

//--------------------------------------------------------------------
//  多倍長整数の出力
//--------------------------------------------------------------------

void bignum_output(const BigNum n)
{
    //----  局所宣言
    int k = n.uni-1;    // 最上位節

    //----  0の出力
    if ( k < 0 ) { k = 0; }

    //----  最上位桁の出力(0無)
    printf("%4lld ", n.num[k]);

    //----  下位桁の出力(0付)       // 最上位桁の 0 は出力せず
    while ( --k >= 0 ) {
        printf("%04lld ", n.num[k]);    // 途中桁の0は出力
    }

    //----  出力後の改行
    puts("");
}

//--------------------------------------------------------------------
//  多倍長整数の初期化(単倍長整数の多倍長化)
//--------------------------------------------------------------------

Bool bignum_init(BigNum *b, int a)
{
    //----  局所宣言
    int k;    // 反復変数

    //----  事前処理
    // 初期値の吟味
    if ( a < 0 || a >= RAD ) { return FALSE; }    // 節値として不適なら打切

    //----  初期処理
    b->uni = 1;    // 多倍長の節数(1)
    b->dig = 0;    // 実際の桁数(0)

    //----  計算処理
    // 各節の0による初期化
    for ( k = 0; k < UNI; k++ ) { b->num[k] = 0; }
    if ( a == 0 ) { return TRUE; }    // a＝0から処理完了

    //----  事後処理
    // 初期値の代入
    b->num[0] = a;    // 最下位節に代入
    while ( a > 0 ) {
        b->dig++; a /= TEN;    // 節値を割りながら桁数を加算
    }

    //----  返却処理
    return TRUE;    // 正常に処理完了
}

//--------------------------------------------------------------------
//  多倍長整数の正規化(節数と桁数の格納)
//--------------------------------------------------------------------

void bignum_chk(BigNum *b)
{
    //----  局所宣言
    int t;    // 最上位の節値
    int k;    // 反復変数

    //----  計算処理
    // 節数の確認
    for ( k = UNI-1; k >= 0; k-- ) {
        if ( b->num[k] != 0 ) { break; }    // 最上位節の検知
    }
    // 0の例外処理
    if ( k < 0 ) { k = 0; }
    // 節数の格納
    b->uni = k+1;            // num[k+1]＝0でnum[k]≠0のとき、節数はk+1

    //----  計算処理
    // 節数による桁数の概算
    b->dig = k * LEV;        // num[k-1]〜num[0]は、LEV桁分ある
    t = b->num[k];           // 最上位桁num[k]は、1〜LEV桁しかない
    // 桁数の格納
    while ( t > 0 ) {
        b->dig++; t /= TEN;    // 節値を割りながら桁数を加算
    }
}

//--------------------------------------------------------------------
//  多倍長整数の大小比較
//--------------------------------------------------------------------

int bignum_cmp(BigNum b1, BigNum b2)
{
    //----  局所宣言
    int k;    // 反復変数

    //----  大小判定
    // strcmp()と同様の返却値
    for ( k = UNI-1; k >= 0; k-- ) {                 // 上位節からの比較
        if ( b1.num[k] < b2.num[k] ) { return -1; }    // 途中で正順のとき
        if ( b1.num[k] > b2.num[k] ) { return +1; }    // 途中で逆順のとき
    }

    //----  返却処理
    return 0;    // 完全に相等のとき
}

//--------------------------------------------------------------------
//  多倍長整数の零判定
//--------------------------------------------------------------------

Bool bignum_zero(BigNum b)
{
    return  ( b.dig == 0 );
}

//--------------------------------------------------------------------
//  多倍長整数の近傍判定
//--------------------------------------------------------------------

Bool bignum_near(BigNum b1, BigNum b2, int a)
{
    //----  局所宣言
    BigNum t;

    //----  計算処理
    // |b1-b2|≦aの判定
    if ( bignum_cmp(b1, b2) > 0 ) { t = b1; b1 = b2; b2 = t; }
    bignum_inc(&b1, a);

    //----  返却処理
    return ( bignum_cmp(b2, b1) <= 0 );
}

//--------------------------------------------------------------------
//  多倍長整数の桁移動
//--------------------------------------------------------------------

Bool bignum_shift(BigNum *b, int s)
{
    //----  局所宣言
    Bool flag;    // 処理完了フラグ
    int k;        // 反復変数

    //----  事前処理
    if ( s == 0 ) { return TRUE; }    // 移動なし
    flag = TRUE;    // 桁溢れが発生していない

    //----  計算処理
    // 右移動
    if ( s < 0 ) {
        for ( k = 0; k < UNI; k++ ) {
            if ( k-s < UNI ) { b->num[k] = b->num[k-s]; }
            else { b->num[k] = 0; }
        }
    }

    //----  計算処理
    // 左移動
    if ( s > 0 ) {
        for ( k = UNI-1; k >= 0; k-- ) {
            // 桁溢れの吟味
            if ( k >= UNI-s && b->num[k] != 0 ) { flag = FALSE; }
            if ( k-s >= 0 ) { b->num[k] = b->num[k-s]; }
            else { b->num[k] = 0; }
        }
    }

    //----  事後処理
    bignum_chk(b);    // 節数と桁数の格納

    //----  返却処理
    return flag;    // 処理完了フラグ
}

//--------------------------------------------------------------------
//  多倍長整数の加算
//--------------------------------------------------------------------

Bool bignum_add(BigNum b1, BigNum b2, BigNum *b0)
{
    //----  局所宣言
    int c;    // 節の繰上り
    int v;    // 当該の節値
    int k;    // 反復変数

    //----  初期処理
    bignum_init(b0, 0);    // 和を0に
    c = 0;                 // 繰上りを0に

    //----  計算処理
    for ( k = 0; k < UNI; k++ ) {       // 下位節から
        v = b1.num[k] + b2.num[k] + c;    // 節同士の加算(繰上り付)
        c = v / RAD;                      // 繰上りの計算(整商による)
        b0->num[k] = v % RAD;             // 繰上りの清算(剰余による)
    }

    //----  事後処理
    if ( c != 0 ) { return FALSE; }    // 最上位桁での繰上りの吟味
    bignum_chk(b0);                    // 節数と桁数の格納

    //----  返却処理
    return TRUE;    // 正常に処理完了
}

//--------------------------------------------------------------------
//  多倍長整数の増分(多倍長整数への単倍長整数の加算更新)
//--------------------------------------------------------------------

Bool bignum_inc(BigNum *b, int a)
{
    //----  局所宣言
    int k;    // 反復変数

    //----  和の初期化
    b->num[0] += a;

    //---- 計算処理
    // 繰上りの清算
    for ( k = 0; k < UNI-1; k++ ) {    // 下位節から
        if ( b->num[k] >= RAD ) {
            b->num[k] -= RAD;
            b->num[k+1]++;
        }
    }

    //----  事後処理
    if ( b->num[k] > RAD ) { return FALSE; }    // 最上位桁での繰上りの吟味
    bignum_chk(b);                              // 節数と桁数の格納

    //----  返却処理
    return TRUE;    // 正常に処理完了
}


//--------------------------------------------------------------------
//  多倍長整数の減算
//--------------------------------------------------------------------

Bool bignum_sub(BigNum b1, BigNum b2, BigNum *b0)
{
  //----  局所宣言
  int c;    // 節の繰下り
  int v;    // 当該の節値
  int k;    // 反復変数

  //----  初期処理
  bignum_init(b0, 0);    // 和の初期化
  c = 0;                 // 繰下りを0に

  //----  減算
  for ( k = 0; k < UNI; k++ ) {           // 下位節から
    v = b1.num[k] - b2.num[k] - c;        // 節同士の加算(繰上り付)
    c = 0;                                // 繰下りの初期化
    while ( v < 0 ) { v += RAD; c++; }    // 繰下りの計算(剰余による)
    b0->num[k] = v;                       // 節値の格納
  }

  //----  事後処理
  if ( c != 0 ) { return FALSE; }    // 最上位桁での繰下りの吟味
  bignum_chk(b0);                    // 節数と桁数の格納

  //----  返却処理
  return TRUE;    // 正常に処理完了
}

//--------------------------------------------------------------------
//  多倍長整数の多倍長整数による乗算(畳込法による)
//--------------------------------------------------------------------
Bool bignum_mlt(BigNum b1, BigNum b2, BigNum *b0)
{
    //----  局所宣言
    int c;             // 繰上り
    int k1, k2, k0;    // 反復変数

    //----  初期処理
    bignum_init(b0, 0);    // 積の初期化

    //----  事前処理
    // 計算範囲の吟味
    if ( b1.dig + b2.dig > UNI * LEV ) { return FALSE; }    // 桁溢れ

    //----  計算処理
    // 桁同士の乗算と加算
    for ( k1 = 0; k1 < b1.uni; k1++ ) {
        for ( k2 = 0; k2 < b2.uni; k2++ ) {
            if ( k1 + k2 >= UNI ) { continue; }           // 添字の範囲外
            b0->num[k1+k2] += b1.num[k1] * b2.num[k2];    // 桁ごとの加算
        }
    }

    //----  計算処理
    // 繰上りの清算
    c = 0;
    for ( k0 = 0; k0 < UNI; k0++ ) {                // 下位桁から
        b0->num[k0] += c;                             // 桁同士の加算
        c = b0->num[k0] / RAD; b0->num[k0] %= RAD;    // 繰上りの清算
    }

    //----  事後処理
    bignum_chk(b0);    // 節数と桁数の格納

    //----  返却処理
    return TRUE;    // 正常に処理完了
}

//--------------------------------------------------------------------
//  多倍長整数の倍分(多倍長整数への単倍長整数の乗算更新)
//--------------------------------------------------------------------

Bool bignum_scl(BigNum *b, int a)
{
    //----  局所宣言
    int k;    // 反復変数

    //---- 計算処理
    // 桁ごとの乗算
    for ( k = 0; k < UNI; k++ ) {    // 下位節から
        b->num[k] *= a;
    }
    
    // 繰上りの清算
    for ( k = 0; k < UNI-1; k++ ) {    // 下位節から
        while ( b->num[k] >= RAD ) {
            b->num[k] -= RAD;
            b->num[k+1]++;
        }
    }

    //----  事後処理
    if ( b->num[k] > RAD ) { return FALSE; }    // 最上位桁での繰上りの吟味
    bignum_chk(b);                              // 節数と桁数の格納

    //----  返却処理
    return TRUE;    // 正常に処理完了
}

//--------------------------------------------------------------------
//  多倍長整数の累乗
//--------------------------------------------------------------------

Bool bignum_pow(BigNum b1, int e, BigNum *b0)
{
    //----  返却処理
    return bignum_pow1(b1, e, b0);    // 素朴法による実装
    //return bignum_pow2(b1, e, b0);    // 二分法による実装
    // &(*b0)でb0を実引数に
}

//--------------------------------------------------------------------
//  素朴法による多倍長整数の累乗
//--------------------------------------------------------------------

Bool bignum_pow1(BigNum b1, int e, BigNum *b0)
{
    //----  局所宣言
    // 一時変数
    BigNum bt;

    //----  事前処理
    // 計算範囲の吟味
    if ( e < 0 ) { return FALSE; }
    if ( b1.dig * e > UNI*LEV ) { return FALSE; }
    //----  初期処理
    // 結果*b0を1に初期化
    bignum_init(b0, 1);

    //----  計算処理
    // 素朴法による累乗計算
    while ( e-- > 0 ) {
        bt = *b0;
        bignum_mlt(b1, bt, b0);
    }
    //----  事後処理
    // 節数と桁数の格納
    bignum_chk(b0);
    //----  返却処理
    return TRUE;    // 正常に処理完了
}

//--------------------------------------------------------------------
//  多倍長整数の除算(整商と剰余)
//--------------------------------------------------------------------

Bool bignum_div(BigNum b1, BigNum b2, BigNum *b3, BigNum *b4)
{
    //----  計算処理
    //bignum_div0(b1, b2, &b3->num[0], b4);
    //bignum_div1(b1, b2, &b3->num[0], b4);
    //bignum_div2(b1, b2.num[0], b3, &b4->num[0]);
    bignum_div3(b1, b2, b3, b4);
    // bignum_div4(b1, b2, b3, b4);
    //----  返却処理
    return TRUE;
}

//-----------------------------------------------------------------------
//      多倍長整数の除算  多倍長 ÷ 多倍長 ＝ 単倍長 ‥ 多倍長
//------------------------------------------------------------------------

Bool bignum_div0(BigNum b1, BigNum b2, long long int *a3, BigNum *b4) {
    
  //----  事前処理
  if ( bignum_zero(b2) ) { return FALSE; }  // 計算不可の異常終了
  *b4 = b1;  // 剰余を被除数で初期化 
  *a3 = 0;   // 整商を0に初期化
  
  //----  除算処理
  while ( *a3 < RAD ) { 
    if ( bignum_cmp(*b4, b2) < 0 ) { break; }  // 減算の終了判定
    bignum_sub(*b4, b2, b4);                   // 減算を実行して剰余の更新
    (*a3)++;                                   // 整商の更新
  }
  
  //----  事後処理
  if ( *a3 >= RAD ) { return FALSE; }  // 範囲超過
  
  printf("\ndiv0を呼び出しました\n");
  
  bignum_chk(b4);
  
  return TRUE; 
}

//--------------------------------------------------------------------
//  逐次法による多倍長整数の単倍長整数を整商とする除算(整商と剰余)
//--------------------------------------------------------------------

Bool bignum_div1(BigNum b1, BigNum b2, long long int *a3, BigNum *b4)
{
    BigNum val;     // b2格納
    int m0;    // 中央値格納
    int low, hig;
    BigNum v0;
    
    //----  事前処理
    if ( bignum_zero(b2) ) { return FALSE; }  // 計算不可の異常終了
    low = 0;
    hig = RAD;  // 範囲の初期化
    
    //----  除算処理
    while ( hig - low > 1 ) {
        *a3 = (low+hig)/2;     // 中央値の計算
        m0 = *a3;           // 中央値の格納
        val = b2;             // b2をvalに格納
        bignum_scl(&val, *a3);                // val = val * a3 
        if ( bignum_cmp(b1, val) <= 0 ) { hig = m0; }     // 中央値とvalの比較
        else { low = m0; }
        printf("a3 = %lld\n", *a3);     // デバッグ用
    }
  
    //----  事後処理
    puts("div1を呼び出しました");
    if ( bignum_cmp(b1, val) < 0 ) { (*a3)--; }
    bignum_scl(&b2, *a3); 
    v0 = b2;
    return bignum_sub(b1, v0, b4); 
}

//--------------------------------------------------------------------
//  多倍長整数の半分
//--------------------------------------------------------------------

Bool bignum_half(BigNum *b)
{
    //----  局所宣言
    int r;    // 剰余
    int k;    // 反復変数

    //---- 計算処理
    for ( k = UNI-1; k >= 0; k-- ) {    // 上位節から
        r = b->num[k] & 1;    // 奇偶
        b->num[k] >>= 1;       // 半分
        if ( r == 1 && k >= 1 ) {
            b->num[k-1] += RAD;   // 桁送り
        }
    }

    //----  事後処理
    bignum_chk(b);                              // 節数と桁数の格納

    //----  返却処理
    return TRUE;    // 正常に処理完了
}

//-------------------------------------------------------------------
//  商立法による多倍長整数の多倍長整数による除算(整商と剰余)
//--------------------------------------------------------------------

Bool bignum_div3(BigNum b1, BigNum b2, BigNum *b3, BigNum *b4)
{
	int k;
	int uni;
	long long int a3;
	
    //----  事前処理
    if ( bignum_zero(b2) ) { return FALSE; }    // 計算不可で異常終了
    uni = b1.uni - b2.uni +1;                   // b3->nszに相当
    
    if ( uni <= 0 ) { *b4 = b1; return TRUE; }  // 整商が0なら早期終了
    bignum_init(b3, 0);             // 整商b3を0に初期化
    *b4 = b1; bignum_shift(b4, -uni);  // 剰余b4をb1の上位部分節に初期化
    
    //----  除算処理
    for ( k = uni-1; k >= 0; k-- ) {  // 上位節から
        bignum_shift(b4, 1);            // 左移動(RAD倍)
        bignum_inc(b4, b1.num[k]);     // b1の該当節の加算
        bignum_div1(*b4, b2, &a3, b4);  // 商立の除算(整商が単倍長)
        b3->num[k] = a3;               // 整商の当節の格納
    }
    
    //----  事後処理
    bignum_chk(b3);  // 結果の正規化と吟味
    
    return TRUE;
}

//--------------------------------------------------------------------
//  二分法による多倍長整数の多倍長整数による除算(整商と剰余)
//--------------------------------------------------------------------

Bool bignum_div4(BigNum b1, BigNum b2, BigNum *b3, BigNum *b4)
{
    //----  局所宣言
    BigNum low;    // 下端
    BigNum hig;    // 上端
    BigNum mid;    // 中央
    BigNum val;     // 計算値(除数と仮整商の積)
    BigNum t;      // 一時変数
    int sft;       // 上端の節数
    int cmp;       // 大小比較の結果

    //----  事前処理
    // 除数の吟味(0除算の禁止)
    if ( bignum_zero(b2) == TRUE ) { return FALSE; }

    //----  初期処理
    bignum_init(&low, 0);       // 下端の初期化(0)
    bignum_init(&hig, 1);       // 上端の仮値(1)
    sft = b1.uni-b2.uni+1;   // 上端の節数
    bignum_shift(&hig, sft);    // 上端の初期化(節移動)
    //----  計算処理
    //--  整商の計算
    while ( bignum_near(low, hig, 1) == 0 ) {
        //   上端と下端の中点として中央値をmidに格納
        bignum_add(low, hig, &mid);

        bignum_half(&mid);
        //   中央値midとb2の乗算をvalに格納l
        if ( bignum_mlt(mid, b2, &val) == FALSE ) {
            return FALSE;
        }
        //   b1とvalが等しければ脱出
        cmp = bignum_cmp(val, b1);
        if ( cmp == 0 ) {
            low = mid;
            break;
        }
        //   異なれば上端または下端を更新
        else if ( cmp > 0 ) {
            hig = mid;
        } else {
            low = mid;
        }
    }
    //--  整商の格納と剰余の計算
    // 下端値lowを整商*b3として格納
    *b3 = low;
    // 整商*b3とb2の乗算をvalに格納l
    bignum_mlt(*b3, b2, &val);
    // b1とvalの差を剰余として*b4に格納
    bignum_sub(b1, val, b4);
    //----  事後処理
    bignum_chk(b3);    // 節数の更新
    bignum_chk(b4);

    //----  返却処理
    return TRUE;    // 正常に処理完了
}


