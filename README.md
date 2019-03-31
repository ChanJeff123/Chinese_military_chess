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
git clone https://github.com/ChanJeff123/Chinese_military_chess.git
下载好代码放在同一目录下  
把music文件夹里的MP3文件放在/home/pi/music/文件夹下  
需要定制50个含IC芯片的军棋  
对每个芯片卡写处理:  

| 写入 | 代表 | 写入 | 代表 |
| :------: | :------: | :------: | :------: |
| 1 | 红方司令 | 13 | 黄方司令 |
| 2 | 红方军长 | 14 | 黄方军长 |
| 3 | 红方师长 | 15 | 黄方师长 |
| 4 | 红方旅长 | 16 | 黄方旅长 |
| 5 | 红方团长 | 17 | 黄方团长 |
| 6 | 红方营长 | 18 | 黄方营长 |
| 7 | 红方连长 | 19 | 黄方连长 |
| 8 | 红方排长 | 20 | 黄方排长 |
| 9 | 红方工兵 | 21 | 黄方工兵 |
| 10 | 红方地雷 | 22 | 黄方地雷 |
| 11 | 红方炸弹 | 23 | 黄方炸弹 |
| 12 | 红方军旗 | 24 | 黄方军旗 |

>sudo python ezWrite.py

读一下试试，结果是写入的数字
>sudo python ezRead.py

然后就可以直接上核心代码啦！
>sudo python repeatV5.py

Any question connect me.
ccwanyuan2014@163.com
