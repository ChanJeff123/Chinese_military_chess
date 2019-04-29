#!/usr/bin/env python
# -*- coding: UTF-8 -*
import time,pygame,string,sys,os,threading,SimpleMFRC522
import RPi.GPIO as GPIO
import serial
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.5)

def SUANFA():
    #算法
# 比較大小，普通的情况
    if b1==range(1,13) and b2==range(1,13) :
        if b1<10 and b2<10 and b1 < b2:
            b1_win()
        elif b1<10 and b2<10 and b2 < b1:
            b2_win()
        elif b1 == b2:
            no_win()
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
    else:
        pass

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

try:
    while 1:
        ser.write(b"GET TAGS")
        response = str(ser.readline().decode())
        if response.startswith('num:'):
            x=response.strip('num:\n\r')
            a= int(x)
            b1=3
            b2=5
            print a,b1,b2
            if b1==range(1,13) and b2==range(1,13) :
                if b1<10 and b2<10 and b1 < b2:
                    b1_win()
                    print b1
                elif b1<10 and b2<10 and b2 < b1:
                    b2_win()
                elif b1 == b2:
                    no_win()
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
            else:
                pass

except KeyboardInterrupt:
    ser.close()
finally:
    GPIO.cleanup()
