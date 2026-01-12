import serial
import time

# Deschide conexiunea serială
arduino = serial.Serial(port='COM7', baudrate=9600, timeout=1)  # Schimbă 'COM3' cu portul Arduino

while True:
    # Obține ora curentă a sistemului
    current_time = time.strftime("%H:%M:%S")
    arduino.write((current_time + '\n').encode())  # Trimite ora către Arduino
    print(f"Timp trimis: {current_time}")
    time.sleep(10)  # Trimite timpul o dată pe minut
    



