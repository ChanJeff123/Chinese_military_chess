#!/usr/bin/env python
# -*- coding: UTF-8 -*
import time
import string
import RPi.GPIO as GPIO
import SimpleMFRC522
import pygame

reader = SimpleMFRC522.SimpleMFRC522()
# Welcome message
print("Looking for cards.Press Ctrl-C to stop.")

#create music files
file1=r'/home/pi/Music/红方胜利.mp3'
file2=r'/home/pi/Music/蓝方胜利.mp3'
file3=r'/home/pi/Music/out双方出局.mp3'
file4=r'/home/pi/Music/error非法操作.mp3'
file5=r'/home/pi/Music/游戏结束蓝方胜利.mp3'
file6=r'/home/pi/Music/游戏结束蓝方胜利.mp3'
pygame.mixer.init()
'''
1 表示红方司令    13 表示蓝方司令
2 表示红方军长    14 表示蓝方军长
3 表示红方师长    15 表示蓝方师长
4 表示红方旅长    16 表示蓝方旅长
5 表示红方团长    17 表示蓝方团长
6 表示红方营长    18 表示蓝方营长
7 表示红方连长    19 表示蓝方连长 
8 表示红方排长    20 表示蓝方排长
9 表示红方工兵    21 表示蓝方工兵 
10 表示红方地雷   22 表示蓝方地雷
11 表示红方炸弹   23 表示蓝方炸弹 
12 表示红方军旗   24 表示蓝方军旗 
'''
def b1_win():
	print("red side win!红方胜")
	track = pygame.mixer.music.load(file1)
	pygame.mixer.music.play()
	time.sleep(5)
	pygame.mixer.music.stop()

def b2_win():
	print("blue side win!蓝方胜")
	track = pygame.mixer.music.load(file2)
	pygame.mixer.music.play()
	time.sleep(5)
	pygame.mixer.music.stop()

def no_win():	
	print("all out!")
	track = pygame.mixer.music.load(file3)
	pygame.mixer.music.play()
	time.sleep(5)
	pygame.mixer.music.stop()

try:
    for i in range(1,3):
        if i==1:
            id,text = reader.read()
            print("fristNumber:"+str(text))
            a = string.atoi(text)
            if a < 13:
                b1=a#b1红方
            elif a>=13 and a < 25:
                b2=a-12#b2蓝方
            time.sleep(1)
        else:
            id,text = reader.read()
            print("secondNumber:"+str(text))
            a = string.atoi(text)
            a = string.atoi(text)
            if a < 13:
                b1=a#b1红方
            elif a>=13 and a < 25:
                b2=a-12#b2蓝方
            time.sleep(1)
#算法
# 比較大小，普通的情况
    if b1<10 and b2<10 and b1 < b2:
        b1_win()
    elif b1<10 and b2<10 and b2 < b1:
        b2_win()
    elif b1 == b2:
        no_win()
    # 出错情况
    # if b1 == 10 or b2 == 12:
    # 	error()
    # 获胜的情况
    elif b1 == 12:
        b2_win()
    elif b2 == 12:
        b1_win()
    # 两方都消失的情况
    elif b1 == 11 or b2 == 11:
        no_win()
    # 对是M（地雷）分情况考虑
    elif b1 == 10:
        if b2 == 9:
            b2_win()
        elif b2 == 11:
            no_win()
        else:
            b1_win()
    elif b2 == 10:
        if b1 == 9:
            b1_win()
        elif b1 == 11:
            no_win()
        else:
            b2_win()
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
