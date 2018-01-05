B.E.R.T.H.A. Version 2 in action:  


Description:
Version 2.0 of my personal robo-project, B.E.R.T.H.A. (Acronym still doesn't represent anything yet.) She is a plank of wood with 4 motors attached to her. Unlike B.E.R.T.H.A. v1, v2 is controlled via an RF transmitter and reciever.   


Software:
Controller.ino (Custom Script)

Hardware:
Arduino Uno R3 
FlySky FS-I6 Transmitter
FlySky FA-IA6 Reciever
L298N Motor Driver
4xAA battery pack
8.4v battery pack (Salvaged from airsoft rifle)
4x12V motors w/gearbox (500rpm)
Plank of wood (frame)
  

Controller.ino:
This script reads in serial values from the reciever, determines what position the joystick is is based on those numbers, and then moves the motors the appropriate directions.



Improvements:
-Need to organize Controller.ino into seperate functions, perhaps create a header file? How to do this with Arduino?
-Find a better way to make circuits other than with a breadboard. If one of the ground wires comes out, something's going to get fried!
-Motors didn't have quite as much torque as I would have liked. She works very well on smooth surfaces, but occasionally gets bogged down in grass.
