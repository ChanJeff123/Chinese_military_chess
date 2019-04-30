#!/usr/bin/env python
#coding: UTF-8
import time
import RPi.GPIO as GPIO
import SimpleMFRC522
import pygame
import string
# Create an object of the class MFRC522
reader = SimpleMFRC522.SimpleMFRC522()
# Welcome message
print("Looking for cards.Press Ctrl-C to stop.")
#create music files
file1=r'/home/pi/Music/win进攻方胜利.mp3'
file2=r'/home/pi/Music/lost防守方胜利.mp3'
file3=r'/home/pi/Music/out双方出局.mp3'
file4=r'/home/pi/Music/error非法操作.mp3'
file5=r'/home/pi/Music/end游戏结束.mp3'
pygame.mixer.init()

def a_win():
	print("Attack side win!进攻方胜")
	track = pygame.mixer.music.load(file1)
	pygame.mixer.music.play()
	time.sleep(5)
	pygame.mixer.music.stop()

def b_win():
	print("Defense side win!防守方胜")
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
	
def error():
	print("error!wrong operation")
	track = pygame.mixer.music.load(file4)
	pygame.mixer.music.play()
	time.sleep(5)
	pygame.mixer.music.stop()
	
def end():
	print("end！game over!进攻方胜")
	track = pygame.mixer.music.load(file5)
	pygame.mixer.music.play()
	time.sleep(5)
	pygame.mixer.music.stop()
	exit ()
# This loop checks for chips. If one is near it will get the UID
try:
    for i in range(1,3):
        if i%2==0:
            id,text = reader.read()
            print("防守: "+str(text))
            b = string.atoi(text)
            time.sleep(1)
        else:
            id,text = reader.read()
            print("进攻: "+str(text))
            a = string.atoi(text)
            time.sleep(1)
#出错的情况
    if a == 10 or a == 12:
        error()
# 获胜的情况
    elif b == 12:
        end()
# 两方都消失的情况
    elif a == 11 or b == 11:
        no_win()
# 对是M（地雷）分情况考虑
    elif b == 10:
        if a == 9:
            a_win()
        elif a == 11:
            no_win()
        else:
            b_win()
# 比較大小，普通的情况
    elif a > 0 and a < 10 and a < b:
        a_win()
    elif a > 0 and a < 10 and a > b:
        b_win()
    elif a == b:
        no_win()
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
# 1 表示司令
# 2 表示军长
# 3 表示师长
# 4 表示旅长
# 5 表示团长
# 6 表示营长
# 7 表示连长
# 8 表示排长
# 9 表示工兵
# 10 表示地雷
# 11 表示炸弹
# 12 表示军旗