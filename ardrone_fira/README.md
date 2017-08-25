ardrone fira air demo on Indigo
=============
This is the 2017 FIRA Air drone competion demo 

OS: ubuntu 14.04
ROS: indigo
gazebo : 2.2.3


Download and make project

    ```
    cd  ~/catkin_ws/src
    git clone https://github.com/HubFire/ardrone_fira.git
    cd  ~/catkin_ws/
    catkin_make
    source devel/setup.bash
    ```

Run demo:

    ```
    roslaunch ardrone_fira ardrone_fira.launch
    ```
