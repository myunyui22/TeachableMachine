# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from flask import Flask, render_template, send_from_directory, request
import os
from flask_socketio import SocketIO
import serial

app = Flask(__name__)
socket_io = SocketIO(app)

max_label_name=0
value=0

arduino = serial.Serial('COM4',115200)

@app.route("/", methods=['GET', 'POST'])
def home():
    return render_template('home.html',subject="Teachable Machine Audio Model")


         
@socket_io.on('message')
def handleMessage(msg):
    print(request.method)   #통신방식 출력. 나같은 경우는 get이 나왔음
    if request.method == 'GET':
        max_label_name, value = msg.split()
        print("max label name : " + max_label_name + "\n")
        print("value : " + value + "\n");
        if (max_label_name=="open_the_front_door"):
            arduino.write(b'f')
            print("f\n")
        if (max_label_name=="close_the_front_door"):
            arduino.write(b'b')
            print("b\n")
        if (max_label_name=="open_the_window"):
            arduino.write(b'o')
            print("o\n")
        if (max_label_name=="close_the_window"):
            arduino.write(b'c')
            print("c\n")
        if (max_label_name=="current_time"):
            arduino.write(b't')
            print("c\n")
        if (max_label_name=="weather"):
            arduino.write(b'w')
            print("w\n")
        if (max_label_name=="led_on"):
            arduino.write(b'n')
            print("n\n")
        if (max_label_name=="led_off"):
            arduino.write(b'l')
            print("l\n")
        if (max_label_name=="curtain_open"):
            arduino.write(b'u')
            print("u\n")
        if (max_label_name=="curtain_close"):
            arduino.write(b'd')
            print("d\n")
        #if (max_label_name != "_background_noise_"):
        #    arduino.write(max_label_name)

#favicon error를 해결하기 위한 코드
@app.route('/favicon.ico') 
def favicon(): 
    return send_from_directory(os.path.join(app.root_path, 'static'), 'favicon.ico', mimetype='image/vnd.microsoft.icon')

    
if __name__ == "__main__":
    app.run()
    