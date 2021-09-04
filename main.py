import time
import serial
import keyboard  # using module keyboard
from serial.tools import list_ports
from datetime import datetime
PORT_NO = 'COM3'

if __name__ == '__main__':
    ports = serial.tools.list_ports.comports()
    for port, desc, hwid in sorted(ports):
            print("Found open {}: {} [{}]".format(port, desc, hwid))
            PORT_NO=port
    try:
        ser = serial.Serial(PORT_NO, 9600, timeout=0)
        last_datetime = datetime.now()
        #wait for ready
        read =''
        while read == '':
            read = ser.readline()
            #print(read)
        tex = ''

        while tex != 'q':
            current_datetime = datetime.now()
            if last_datetime.second != current_datetime.second:
            # hours
                if current_datetime.hour < 10:
                    hour_str = str(current_datetime.hour)
                else:
                    hour_str = str(current_datetime.hour)
            # minutes
                if current_datetime.minute < 10:
                    minute_str = '0' + str(current_datetime.minute)
                else:
                    minute_str = str(current_datetime.minute)
            # seconds
                if current_datetime.second < 10:
                    seconds_str = '0' + str(current_datetime.second)
                else:
                    seconds_str = str(current_datetime.second)
            #create string to post
                time_string = hour_str + ':' + minute_str + ':' + seconds_str
                print(time_string)
                try:
                    ser.write(str.encode(time_string))
                except:
                    print('cant send time')
                last_datetime = current_datetime
            else:
                time.sleep(0.1)

            if keyboard.is_pressed('q'):  # if key 'q' is pressed
                print('You Pressed q Key! Exiting')
                ser.close()
                tex = 'q'
    except:
        print('Can\'t open port')
