概要
====

Q.board の FreeIMU ライブラリです。  


### FreeIMU ライブラリについて

- 6/9軸センサーを利用したオープンソースのフレームワークです
 http://www.varesano.net/
- センサーの姿勢情報（回転）が取得できます  
- 各センサーの生データを取得することができます
- 元のレポジトリは以下です。  
 http://bazaar.launchpad.net/~fabio-varesano/freeimu/trunk/files  


インストール方法
================

1. QBoard_FreeIMU.zip をダウンロードします
2. Arduino を起動して、メニュー > スケッチ > Include Library > Add .ZIP Library... を選択します
3. 先ほどダウンロードした QBoard_FreeIME.zip を選択すると Arduino にインストールされます


簡単な使い方
============
1. Arduino を起動して新規スケッチを開きます
2. メニュー > スケッチ > Include Library > QBoard_FreeIMU を選択します
3. メニュー > スケッチ > Include Library > SPI を選択します
4. スケッチを書きます  
 例. Q.board の加速度センサーを取得してシリアルに出力する方法  

    `````````````````````````````````````
    #include <SPI.h>
    #include <QBoard_FreeIMU.h>
    
    FreeIMU imu = FreeIMU();
    float fvalues[9];
    
    void setup() {
        imu.init(true);
    }
    
    void loop() {
        MPU9250 *pimu = &imu.accgyromagn;
        imu.getValues(fvalues);
        Serial.println(fvalues[0]);
        Serial.println(fvalues[1]);
        Serial.println(fvalues[2]);
	delay(1000);
    }
    `````````````````````````````````````
5. Q.board を USB ケーブルでPCにつなぎます
6. Q.board 用 Arudino を起動します
7. メニュー > ツール > ポート > /dev/cu.usbmodemXXX を選択します
8. メニュー > ツール > ボード > Koozyt Dash (Native USB POrt) を選択します
9. メニュー > ファイル > マイコンボードに書き込む を選択するとファームウェアを書き込みます
10. 書き込み後 メニュー > ツール > シリアルモニタ を選択します  
 シリアルモニタウィンドウが表示します。一秒間に一回加速度値が取得出来ていれば成功です！




クラス説明
==========

Q.board では主に FreeIMU, MPU9250 クラスを利用しています。  
MPU9250 はセンサー Invensense MPU9250 を制御するための低レベルな実装です。  
FreeIMU クラスは、MPU9250 から取得した値を使用してクォータニオンの計算などを行います。  

### FreeIMU クラス

ヘッダーファイル FreeIMU/FreeIMU.h  
クォータニオンを取得したい場合は getQ(float * q) 関数を使います。  
センサー値の生データを取得したい場合は getRawValues(float *values) メンバを使います。  

ヘッダーファイルから目的の関数を探してみてください。


### MPU9250 クラス

ヘッダーファイル MPU9250/MPU9250.h  
Q.board 上の9軸センサー Invense MPU9250 を制御するクラスです。  
直接使用することはほぼないと思いますがセンサー上で実装されている Low Pass Filter の値を変更したいなど細かい制御が可能です。

MPU9250 のレジスタマップ
http://www.invensense.com/mems/gyro/documents/RM-MPU-9250A-00.pdf  
このレジスタマップに書かれている制御をこのクラスでおこなっています。  
