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
	self.image = None
        self.imageLock = Lock()
	self.bridge = CvBridge()

        rospy.init_node('ardrone_keyboard_controller')
        self.controller = BasicDroneController()
        self.image_sub = rospy.Subscriber("/ardrone/bottom/image_raw",Image,self.reciveImage)
	self.action = 0 # 0 takeoff status , 1  go foward 
        self.status =-1 # drone status , 0 flying,-1 landed
    def reciveImage(self,data):
	try:
        	cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
		self.processImage(cv_image)
        except CvBridgeError as e:
         	print(e)
    
    #process recived image ,change the drone's action     
    def processImage(self,img):
        #cv2.imwrite('drone.jpg',img)
	cv2.imshow("Image window", img)
	cv2.waitKey(3)
    	self.action=1
        
    def drive(self):
        while not rospy.is_shutdown():
                # sleep 1 second to wait the drone initial
		rate =rospy.Rate(1)
                rate.sleep()
		if self.status ==-1:
			print "send take off"
			self.controller.SendTakeoff()
			self.status =0
		elif self.action ==1:
			print "send go foward"
			self.controller.SetCommand(pitch=1)
                else:
			pass
	self.controller.Land()
            

            

 
if __name__=='__main__':
    auto_drive =AutoDrive()
    auto_drive.drive()
        

