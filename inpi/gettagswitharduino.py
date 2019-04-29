import serial
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.5)

try:
    while 1:
        ser.write(b"GET TAGS")
        response =ser.read(20)
        if response.startswith('num:'):
            a=response.strip('num:\n\r')
            print(a)
except KeyboardInterrupt:
    ser.close()


