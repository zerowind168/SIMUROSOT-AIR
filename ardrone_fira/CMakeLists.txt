cmake_minimum_required(VERSION 2.8)
project(ardrone_fira)

find_package(catkin REQUIRED)
catkin_package()

#catkin_python_setup()


install(PROGRAMS src/drone_controller.py  
	         src/drive_demo.py
                 src/auto_driver.py
                 src/drone_status.py
                 
        DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)
