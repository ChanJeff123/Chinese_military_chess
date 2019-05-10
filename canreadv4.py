#!/usr/bin/env python
# -*- coding: UTF-8 -*
import time,pygame,string,sys,os,threading,SimpleMFRC522
import RPi.GPIO as GPIO
import serial
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.5)

GPIO.setmode(GPIO.BOARD)
reader = SimpleMFRC522.SimpleMFRC522()
# Welcome message
# print("Looking for cards.Press Ctrl-C to stop.")
#create music files
fileRW=r'/home/pi/Music/红方胜利.mp3'
fileYW=r'/home/pi/Music/黄方胜利.mp3'
fileBW=r'/home/pi/Music/蓝方胜利.mp3'
fileGW=r'/home/pi/Music/绿方胜利.mp3'
fileNONE=r'/home/pi/Music/out双方出局.mp3'
fileTips=r'/home/pi/Music/tips.mp3'

def Music(X):
    pygame.mixer.init()
    track = pygame.mixer.music.load(X)
    pygame.mixer.music.play()
    time.sleep(2)
    pygame.mixer.music.stop()
def restart_program():
    python = sys.executable
    os.execl(python,python,* sys.argv)
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
def Bled():
    led=13
    GPIO.setup(led,GPIO.OUT)
    GPIO.output(led,True)
    time.sleep(1)
    GPIO.output(led,False)
def Gled():
    led=11
    GPIO.setup(led,GPIO.OUT)
    GPIO.output(led,True)
    time.sleep(1)
    GPIO.output(led,False)

def b1_win():
    threading.Thread(target=Rled).start()
    threading.Thread(target=Music(fileRW)).start()
    print("RED side win!红方胜")

def b2_win():
    threading.Thread(target=Yled).start()
    threading.Thread(target=Music(fileYW)).start()
    print("YELLOW side win!黄方胜")

def b3_win():
    threading.Thread(target=Bled).start()
    threading.Thread(target=Music(fileBW)).start()
    print("BLUE side win!蓝方胜")

def b4_win():
    threading.Thread(target=Gled).start()
    threading.Thread(target=Music(fileGW)).start()
    print("GREEN side win!绿方胜")

def no_win():
    threading.Thread(target=Yled).start()
    threading.Thread(target=Rled).start()
    threading.Thread(target=Music(fileNONE)).start()
    print("双方出局 all out!")

def Arduino_one():
    global b1
    global b2
    global b3
    global b4
    global i
    ser.write(b"GET TAGS")
    response = str(ser.readline().decode())
    if response.startswith('num:'):
        x=response.strip('num:\n\r')
        a= int(x)
        print "Arduino_one:",a
        threading.Thread(target=Rled).start()
        threading.Thread(target=Music(fileTips)).start()
        if a < 13:
            b1=a#b1红方
        elif a>=13 and a < 25:
            b2=a-12#b2黄方
        elif a>=25 and a < 37:
            b3=a-24#b3蓝方
        elif a>=37 and a < 49:
            b4=a-36#b4绿方
        print ((a,b1) if(b1>0) else (a,b2))
        i+=1
        print "i=",i
        print "b1=",b1,"b2=",b2,"b3=",b3,"b4=",b4,"a=",a

def OG_one():
    global b1
    global b2
    global b3
    global b4
    global i
    id,text = reader.read()
    print("OG_one:"+str(text))
    a = string.atoi(text)
    if a < 13:
        b1=a#b1红方
    elif a>=13 and a < 25:
        b2=a-12#b2黄方
    elif a>=25 and a < 37:
        b3=a-24#b3蓝方
    elif a>=37 and a < 49:
        b4=a-36#b4绿方
    print ((a,b2) if(b2>0) else (a,b1))
    threading.Thread(target=Yled).start()
    threading.Thread(target=Music(fileTips)).start()
    i+=1
    print "b1=",b1,"b2=",b2,"b3=",b3,"b4=",b4,"a=",a
    print "i=",i
    return i

def SUANFA():
    #算法
# 比較大小，普通的情况
# 红黄比
    if b1!=0 and b2!=0:
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
#红蓝比
    if b1!=0 and b3!=0:
        if b1<10 and b3<10 and b1 < b3:
            b1_win()
        elif b1<10 and b3<10 and b3 < b1:
            b3_win()
        elif b1 == b3:
            no_win()
        # 获胜的情况
        elif b1 == 12:
            b3_win()
        elif b3 == 12:
            b1_win()
        # 两方都消失的情况
        elif b1 == 11 or b3 == 11:
            no_win()
        # 对是M（地雷）分情况考虑
        elif b1 == 10:
            if b3 == 9:
                b3_win()
            elif b3 == 11:
                no_win()
            else:
                b1_win()
        elif b3 == 10:
            if b1 == 9:
                b1_win()
            elif b1 == 11:
                no_win()
            else:
                b3_win()
#红绿比
    if b1!=0 and b4!=0:
        if b1<10 and b4<10 and b1 < b4:
            b1_win()
        elif b1<10 and b4<10 and b4 < b1:
            b4_win()
        elif b1 == b4:
            no_win()
        # 获胜的情况
        elif b1 == 12:
            b4_win()
        elif b4 == 12:
            b1_win()
        # 两方都消失的情况
        elif b1 == 11 or b4 == 11:
            no_win()
        # 对是M（地雷）分情况考虑
        elif b1 == 10:
            if b4 == 9:
                b4_win()
            elif b4 == 11:
                no_win()
            else:
                b1_win()
        elif b4 == 10:
            if b1 == 9:
                b1_win()
            elif b1 == 11:
                no_win()
            else:
                b4_win()
#黄蓝比
    if b2!=0 and b3!=0:
        if b2<10 and b3<10 and b2 < b3:
            b2_win()
        elif b2<10 and b3<10 and b3 < b2:
            b3_win()
        elif b2 == b3:
            no_win()
        # 获胜的情况
        elif b2 == 12:
            b3_win()
        elif b3 == 12:
            b2_win()
        # 两方都消失的情况
        elif b2 == 11 or b3 == 11:
            no_win()
        # 对是M（地雷）分情况考虑
        elif b2 == 10:
            if b3 == 9:
                b3_win()
            elif b3 == 11:
                no_win()
            else:
                b2_win()
        elif b3 == 10:
            if b2 == 9:
                b2_win()
            elif b2 == 11:
                no_win()
            else:
                b3_win()
#黄绿比
    if b2!=0 and b4!=0:
        if b2<10 and b4<10 and b2 < b4:
            b2_win()
        elif b2<10 and b4<10 and b4 < b2:
            b4_win()
        elif b2 == b4:
            no_win()
        # 获胜的情况
        elif b2 == 12:
            b4_win()
        elif b4 == 12:
            b2_win()
        # 两方都消失的情况
        elif b2 == 11 or b4 == 11:
            no_win()
        # 对是M（地雷）分情况考虑
        elif b2 == 10:
            if b4 == 9:
                b4_win()
            elif b4 == 11:
                no_win()
            else:
                b2_win()
        elif b4 == 10:
            if b2 == 9:
                b2_win()
            elif b2 == 11:
                no_win()
            else:
                b4_win()
#蓝绿比
    if b3!=0 and b4!=0:
        if b3<10 and b4<10 and b3 < b4:
            b3_win()
        elif b3<10 and b4<10 and b4 < b3:
            b4_win()
        elif b3 == b4:
            no_win()
        # 获胜的情况
        elif b3 == 12:
            b4_win()
        elif b4 == 12:
            b3_win()
        # 两方都消失的情况
        elif b3 == 11 or b4 == 11:
            no_win()
        # 对是M（地雷）分情况考虑
        elif b3 == 10:
            if b4 == 9:
                b4_win()
            elif b4 == 11:
                no_win()
            else:
                b3_win()
        elif b4 == 10:
            if b3 == 9:
                b3_win()
            elif b3 == 11:
                no_win()
            else:
                b4_win()
    GPIO.cleanup()
    restart_program()

try:
    i=0
    b1=0
    b2=0
    b3=0
    b4=0
    Arduino_one()
    while i==1:
        # Arduino_one()
        OG_one()
    else:
        SUANFA()
        time.sleep(1)

except KeyboardInterrupt:
    ser.close()
finally:
    GPIO.cleanup()
    restart_program()
