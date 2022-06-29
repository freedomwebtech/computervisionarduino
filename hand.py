import cv2
import paho.mqtt.client as mqtt
import time

from cvzone.HandTrackingModule import HandDetector
detector=HandDetector(detectionCon=0.5,maxHands=2)

cap=cv2.VideoCapture(0)
count=0
def forward():
    mqttBroker ="mqtt.fluux.io"
    client = mqtt.Client("raspberry pi 40")
    client.connect(mqttBroker)
    client.publish("test2",(bytes("forward",'utf-8')))     



def back():
    mqttBroker ="mqtt.fluux.io"
    client = mqtt.Client("raspberry pi 401")
    client.connect(mqttBroker)
    client.publish("test2",(bytes("back",'utf-8')))     

def turn():
    mqttBroker ="mqtt.fluux.io"
    client = mqtt.Client("raspberry pi 401")
    client.connect(mqttBroker)
    client.publish("test2",(bytes("turn",'utf-8')))    
    

def stop():
    mqttBroker ="mqtt.fluux.io"
    client = mqtt.Client("raspberry pi 40")
    client.connect(mqttBroker)
    client.publish("test2",(bytes("stop",'utf-8')))     

  
    

while True:
    ret,frame=cap.read()
    count += 1
    if count % 10 != 0:
        continue
    frame=cv2.flip(frame,-1)
#    frame=cv2.resize(frame,(640,480))
    hands,frame=detector.findHands(frame)
    if not hands:
        stop()
    else: 
        hands1=hands[0]
        bbox=hands1["bbox"]
        x,y,w,h=bbox
        fingers1=detector.fingersUp(hands1)
        count = fingers1.count(1)
        print('Count of 1:', count)
        if count==1:
            forward()
            cv2.putText(frame,"FORWARD",(40,50),3,cv2.FONT_HERSHEY_PLAIN,(255,0,255),2)
        elif count==2:
            back()
            cv2.putText(frame,"BACK",(40,50),3,cv2.FONT_HERSHEY_PLAIN,(255,0,255),2)
        elif count==4:
            turn()
            cv2.putText(frame,"TURN",(40,50),3,cv2.FONT_HERSHEY_PLAIN,(255,0,255),2)
        elif count==5:
            stop()
            cv2.putText(frame,"STOP",(40,50),3,cv2.FONT_HERSHEY_PLAIN,(255,0,255),2) 
         

        
   
           
   
        
    frame=cv2.imshow("FRAME",frame)
   
    if cv2.waitKey(1)&0xFF==27:
        break
cap.release()
cv2.destroyAllWindows()