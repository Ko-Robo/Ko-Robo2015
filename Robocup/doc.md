# ロボカップジュニアサッカー
## はじめに
これは、ロボカップジュニアサッカーサッカーに挑戦する学生たちへ向けたプログラム作成のマニュアルです。参考にしていただけると幸いです。また、ここには基本的なことしか書かれていません。色々調べてあなただけのプログラムを創り上げてください。これを読んでいる君たちが上級生になった暁には、自由に改変し、よりよいものにしていってください。

## アルゴリズム

## mbed

## センサ

## 特殊な制御法

## 全体の統括

## コツ

## ソースコード
Lチカ
```c++
#include "mbed.h"

DigitalOut led(LED1);

int main(void) {
    while (1) {
        led = 1;
        wait(0.2);
        led = 0;
        wait(0.2);
    }
}
```

PWM
```c++
#include "mbed.h"

PwmOut led(LED1);

int main(void) {
    while (1) {
        for (float i = 0; i < 1; i += 0.005) {
            led = i;
            wait(0.02);
        }
        for (float i = 1; i > 0; i -= 0.005) {
            led = i;
            wait(0.02);
        }
    }
}
```

超音波
```c++
#include "mbed.h"
#include "hcsr04.h"

HCSR04 ultrasonic(p5, p6);
Serial pc(USBTX, USBRX);

int main(void) {
    while (1) {
        long distance = ultrasonic.distance();
        pc.printf("distance : %d\r\n", distance);
        wait(0.1);
    }
}
```

コンパス
```c++
// みかん
```

パソコンに出力
```c++
#include "mbed.h"

Serial pc(USBTX, USBRX);

int main(void) {
    pc.printf("test for pc.printf()\r\n");
    while (1)
        ;
}
```

LCD
```c++
#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(p10, p12, p15, p16, p29, p30);

int main(void) {
    lcd.printf("Hello World!\r\n");
}
```

I2C(master)
```c++
#include "mbed.h"

I2C i2cmaster(p9, p10);
DigitalOut led(p5);

int main(void) {
    char data[1] = {0};
    char address = 0xA0;
    i2cmaster.frequency(2000);

    while (1) {
        i2cmaster.read(address | 1, data, 1, true);
        led = data[0];
    }
}
```

I2C(slave)
```c++
#include "mbed.h"

I2CSlave i2cslave(p9, p10);
Serial pc(USBTX, USBRX);

int main(void) {
    int slaveflg;
    char data = 0x01;
    char addr = 0xA0;
    i2cslave.address(addr);

    while (1) {
        slaveflg = i2cslave.receive();
        switch (slaveflg) {
            case I2CSlave::ReadAddressed:
                i2cslave.write(data);
                break;
            default:
                pc.printf("Error!!\r\n");
                break;
        }
    }
}
```

PWM
```c++
#include "mbed.h"

PwmOut led(LED1);

int main(void) {
    while (1) {
        for (float i = 0; i < 1; i += 0.005) {
            led = i;
            wait(0.02);
        }
        for (float i = 1; i > 0; i -= 0.005) {
            led = i;
            wait(0.02);
        }
    }
}
```

PID
```c++
// みかん
```

## 参考文献
[mbed 日本語リファレンス](https://developer.mbed.org/users/okini3939/notebook/ref_jp/)
