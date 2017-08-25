#!/usr/bin/env python
import roslib; roslib.load_manifest('ardrone_fira')
import rospy
from drone_controller import BasicDroneController
from ardrone_autonomy.msg import Navdata
from threading import Lock
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
import cv2

class AutoDrive(object):
    def __init__(self):
        self.rotZ=0
        self.Zlock = Lock()
        
	self.image = None
        self.imageLock = Lock()
	self.bridge = CvBridge()

        rospy.init_node('ardrone_keyboard_controller')
        self.controller = BasicDroneController()
        self.subNavdata = rospy.Subscriber('/ardrone/navdata',Navdata,self.receiveNavdata) 
        self.image_sub = rospy.Subscriber("/ardrone/bottom/image_raw",Image,self.reciveImage)
	self.action = 0 # 0 takeoff status , 1  go foward 

    def reciveImage(self,data):
	try:
        	cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
		self.processImage(cv_image)
        except CvBridgeError as e:
         	print(e)
    
    #process recived image ,change the drone's action     
    def processImage(self,img):
        cv2.imwrite('./drone.jpg',img)
    	self.action=1
    



      
    def turnLeft(self):
        #self.Zlock.acquire()
        self.controller.SetCommand(pitch=0)
        while (self.rotZ<=179):
            self.controller.SetCommand(yaw_velocity=1)
        self.controller.SetCommand(yaw_velocity=0)
        #self.Zlock.release()


    def receiveNavdata(self,navdata):
        self.Zlock.acquire()
        self.rotZ=navdata.rotZ
        print self.rotZ
        self.Zlock.release()

    def drive(self):
        start_time =rospy.get_rostime()
        while not rospy.is_shutdown():
            curent = rospy.get_rostime()
            if (curent - start_time) <  rospy.Duration(1,0):
                self.controller.SendTakeoff()
                self.status =0

            elif (curent - start_time) <  rospy.Duration(22,0):
                self.controller.SetCommand(pitch=1)
                self.status =1

            elif (curent - start_time) <  rospy.Duration(23,0):
                self.controller.SetCommand(pitch=0)
                self.status =2

            elif (curent - start_time) <  rospy.Duration(24,0):
                #self.controller.SetCommand(yaw_velocity=2) 
                self.turnLeft()
                self.status =3 
                rate =rospy.Rate(1)
            elif (curent - start_time) <  rospy.Duration(40.5,0):
                self.controller.SetCommand(pitch=1)  
                self.status =4
            else:
                 self.controller.SetCommand(pitch=0)
                 self.controller.SendLand()

            

 
if __name__=='__main__':
    auto_drive =AutoDrive()
    auto_drive.drive()
        

