#!/usr/bin/env python

import RPi.GPIO as GPIO
import SimpleMFRC522

reader = SimpleMFRC522.SimpleMFRC522()

try:
        for i in range(100):
            id, text = reader.read()
            print(id)
            print(text)
            i+=1
finally:
        GPIO.cleanup()
