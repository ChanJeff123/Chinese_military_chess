# Chinese_military_chess
auto chess judge in raspberry pi 3b+.Use mfrc522
==========
本项目适用于MFRC522模块基于树莓派的读写操作

先安装树莓派3B+的SPI接口支持库
------------------------------
事前update树莓派的库
>sudo apt-get update && sudo apt-get upgrade

这里的支持库分别是“Py-spidev”和“SPI-Py”，安装“Py-spidev”可以使用命令来安装：
>sudo apt-get install python-spidev  
>python3-spidev

这样“Py-spidev”就可以同时支持Python 2和Python 3了。虽然使用“py-spidev”可以驱动Python中的SPI接口，但是项目中我们使用了“SPI-Py”，可以通过以下命令来完成安装“SPI-Py”:
>cd ~  
>git clone https://github.com/lthiery/SPI-Py.git  
>cd SPI-Py  
>sudo python setup.py install  
>sudo python3 setup.py install

同样的“SPI-Py”也可以同时支持Python2和Python3了。

硬件接线图
----
看下树莓派引脚功能
>gpio readall

![raspi](https://github.com/ChanJeff123/Chinese_military_chess/blob/master/pic/rc522_rfid_raspberry_pi.png)

实现过程
----
>git clone https://github.com/ChanJeff123/Chinese_military_chess.git

下载好代码放在同一目录下  
把music文件夹里的MP3文件放在/home/pi/music/文件夹下  
需要定制50个含IC芯片的军棋  
对每个芯片卡写处理:  

| 写入  |   代表   | 写入  |   代表   |
| :---: | :------: | :---: | :------: |
|   1   | 红方司令 |  13   | 黄方司令 |
|   2   | 红方军长 |  14   | 黄方军长 |
|   3   | 红方师长 |  15   | 黄方师长 |
|   4   | 红方旅长 |  16   | 黄方旅长 |
|   5   | 红方团长 |  17   | 黄方团长 |
|   6   | 红方营长 |  18   | 黄方营长 |
|   7   | 红方连长 |  19   | 黄方连长 |
|   8   | 红方排长 |  20   | 黄方排长 |
|   9   | 红方工兵 |  21   | 黄方工兵 |
|  10   | 红方地雷 |  22   | 黄方地雷 |
|  11   | 红方炸弹 |  23   | 黄方炸弹 |
|  12   | 红方军旗 |  24   | 黄方军旗 |
四国军棋以此类推。

>python ezWrite.py

读一下试试，结果是写入的数字
>python ezRead.py

然后就可以直接上核心代码啦！
>python repeatV5.py  

四国军棋可以  

>python canreadv4.py  
# 添加ARDUINO和nodemcu接线和代码  
RFID与Arduino Uno的连线  
SDA------------------------Digital 10  
SCK------------------------Digital 13  
MOSI----------------------Digital 11  
MISO----------------------Digital 12  
IRQ------------------------N/A  
GND-----------------------GND  
RST------------------------Digital 9  

![arduino522](https://github.com/ChanJeff123/Chinese_military_chess/blob/master/pic/arduino.png)  
arduino部分添加ws2812 rgb彩灯，用FASTLED库。WS2812 data接arduino-nano引脚5  
核心代码ARDUIN.INO  
这里可能出现的问题不一定每个arduino都可以用很奇怪，所以我在NODEMCU代码里直接用RFID522的库  
**NODEMCU部分**  
![nodemcu引脚](https://github.com/ChanJeff123/Chinese_military_chess/blob/master/pic/NODEMCU%E5%BC%95%E8%84%9A.png)  
先看NODEMCU的引脚与arduino有点不同默认是GPIO编号所以代码里的引脚说明要注意  
6/7/8/9/10可以之家参照D6,D7...  
这里的WS2812接D8【虽然我买的是5V的2812但是这里依然可以用nodemcu的3V口】  
![nodemcu-522引脚](https://github.com/ChanJeff123/Chinese_military_chess/blob/master/pic/NODEMCU-RC522.png)  
![nodemcu-522引脚](https://raw.githubusercontent.com/ChanJeff123/Chinese_military_chess/master/pic/nodemcu.png)  

代码在arduino ide里进行编译，核心代码8266junqi.ino  

Any question connect me.  
ccwanyuan2014@163.com
