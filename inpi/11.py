#!/usr/bin/env python
# -*- coding: UTF-8 -*
import time,pygame,string,sys,os,threading,SimpleMFRC522
import RPi.GPIO as GPIO
import serial
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.5)

reader = SimpleMFRC522.SimpleMFRC522()
# Welcome message
print("Looking for cards.Press Ctrl-C to stop.")
#create music files
fileRW=r'/home/pi/Music/红方胜利.mp3'
fileYW=r'/home/pi/Music/黄方胜利.mp3'
fileNONE=r'/home/pi/Music/out双方出局.mp3'
file4=r'/home/pi/Music/error非法操作.mp3'
file5=r'/home/pi/Music/游戏结束黄方胜利.mp3'
file6=r'/home/pi/Music/游戏结束红方胜利.mp3'

def restart_program():
    python = sys.executable
    os.execl(python,python,* sys.argv)

def Music(X):
    pygame.mixer.init()
    track = pygame.mixer.music.load(X)
    pygame.mixer.music.play()
    time.sleep(2)
    pygame.mixer.music.stop()

def Yled():
    led=13
    GPIO.setup(led,GPIO.OUT)
    GPIO.output(led,True)
    time.sleep(1)
    GPIO.output(led,False)

def Rled():
    led=11
    GPIO.setup(led,GPIO.OUT)
    GPIO.output(led,True)
    time.sleep(1)
    GPIO.output(led,False)

def b1_win():
    threading.Thread(target=Rled).start()
    threading.Thread(target=Music(fileRW)).start()
    print("red side win!红方胜")

def b2_win():
    threading.Thread(target=Yled).start()
    threading.Thread(target=Music(fileYW)).start()
    print("yellow side win!黄方胜")

def no_win():
    threading.Thread(target=Yled).start()
    threading.Thread(target=Rled).start()
    threading.Thread(target=Music(fileNONE)).start()
    print("双方出局 all out!")

def Arduino_one():
    ser.write(b"GET TAGS")
    response =ser.read(20)
    if response.startswith('num:'):
        x=response.strip('num:\n\r')
        a = string.atoi(x)
        print("Arduino_one:",a)
        return a;

def OG_one():
    id,text = reader.read()
    print("OG_one:"+str(text))
    a = string.atoi(text)
    return a;


'''
1 表示红方司令    13 表示黄方司令
2 表示红方军长    14 表示黄方军长
3 表示红方师长    15 表示黄方师长
4 表示红方旅长    16 表示黄方旅长
5 表示红方团长    17 表示黄方团长
6 表示红方营长    18 表示黄方营长
7 表示红方连长    19 表示黄方连长 
8 表示红方排长    20 表示黄方排长
9 表示红方工兵    21 表示黄方工兵 
10 表示红方地雷   22 表示黄方地雷
11 表示红方炸弹   23 表示黄方炸弹 
12 表示红方军旗   24 表示黄方军旗 
'''
#main 核心代码区
try:
    ser.write(b"GET TAGS")
    response =ser.read(20)
    if response.startswith('num:'):
        x=response.strip('num:\n\r')
        a = string.atoi(x)
        print(a)

    # for i in range(2):
    #     if i ==0:
    #         a=Arduino_one()
    #         if a < 13:
    #             b1=a#b1红方
    #         elif a>=13 and a < 25:
    #             b2=a-12#b2黄方
    #     else:
    #         a=OG_one()
    #         if a < 13:
    #             b1=a#b1红方
    #         elif a>=13 and a < 25:
    #             b2=a-12#b2黄方
# #算法
# # 比較大小，普通的情况
#     if b1<10 and b2<10 and b1 < b2:
#         b1_win()
#     elif b1<10 and b2<10 and b2 < b1:
#         b2_win()
#     elif b1 == b2:
#         no_win()
#     # 出错情况
#     # if b1 == 10 or b2 == 12:
#     # 	error()
#     # 获胜的情况
#     elif b1 == 12:
#         b2_win()
#     elif b2 == 12:
#         b1_win()
#     # 两方都消失的情况
#     elif b1 == 11 or b2 == 11:
#         no_win()
#     # 对是M（地雷）分情况考虑
#     elif b1 == 10:
#         if b2 == 9:
#             b2_win()
#         elif b2 == 11:
#             no_win()
#         else:
#             b1_win()
#     elif b2 == 10:
#         if b1 == 9:
#             b1_win()
#         elif b1 == 11:
#             no_win()
#         else:
#             b2_win()
    GPIO.cleanup()
    restart_program()
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()

