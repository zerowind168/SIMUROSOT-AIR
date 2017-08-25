# SIMUROSOT-AIR
=============
This is the 2017 FIRA SIMUROSOT Air environment

#### OS: ubuntu 14.04
#### ROS: indigo
#### Gazebo : 2.2.3

:exclamation:You must not install the OS on a(any) Virtual Machine, otherwise, there will be a lot of Bug waitting for you.:exclamation:
## 1. Install the ROS & Gazebo:<br>
You can go to: http://wiki.ros.org/indigo/Installation/Ubuntu
for how to download the ROS Indigo version.<br>
Here we copy some of the proceed below:<br>

1. Setup your sources.list
    ```
    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
    ```
2. Setup your keys
    ```
    sudo apt-key adv --OS: indigokeyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
    ```
3. Installation
    ```
    sudo apt-get update
    sudo apt-get install ros-indigo-desktop-full
    ```
4. Initialize rosdep
    ```
    sudo rosdep init
    rosdep update
    ```
5. Environment setup
    ```
    echo "source /opt/ros/indigo/setup.bash" >> ~/.bashrc
    source ~/.bashrc
    ```
6. Getting rosinstall
    ```
    sudo apt-get install python-rosinstall
    ```
#### Note： :exclamation:Some users can not find the namespace of the model when starting gazebo, the reason may be a network problems. The solution is to manually download the .gazebo file and copy it to the home directory and we provide the .gazebo file. :exclamation:

## 2. Install the simulator:

1. Create a workspace for the simulator

    ```
    mkdir -p ~/catkin_ws/src
    cd  ~/catkin_ws
    catkin_make
    source devel/setup.bash
    ```
2. Download the project
   
   Copy the ardrone_simulator file to the ~/catkin_ws/src/ directory.
   
2. Download dependencies

    ```
    cd ~/catkin_ws/src
    git clone https://github.com/AutonomyLab/ardrone_autonomy.git	# The AR.Drone ROS driver
    cd ..
    rosdep install --from-paths src --ignore-src --rosdistro indigo -y
    sudo apt-get install libjsoncpp-dev libjsoncpp0 # Library for reading and writing JSON 
    ```
3. Build the simulator

    ```
    catkin_make
    ```
4. Source the environment

    ```
    source devel/setup.bash
    ```
5. Copy the model.json file

    Copy the model.json file to the home directory.</br>
    
    The model.json file is used to dynamically configure the location and number of the road, QR code, obstructions, towers and residential buildings of the simulation environment.
   
## 3. Run a simulation:

1. Run a simulation by executing a launch file in cvg_sim_gazebo package:

    ```
    roslaunch cvg_sim_gazebo ardrone_testworld.launch
    ```
    
If you see the figure as follow, you are success. 
![image](https://github.com/zerowind168/SIMUROSOT-AIR/blob/master/robot-simulation.jpg)

## 4. Run ardrone fira air demo on Indigo

1. Download and make project

    Copy the ardrone_fira file to the ~/catkin_ws/src/ directory.
    
    ```
    cd ~/catkin_ws/
    catkin_make
    source devel/setup.bash
    ```
2. Run the demo
    ```
    roslaunch ardrone_fira ardrone_fira.launch
    ```

If you see the figure as follow, you are success. 
![image](https://github.com/zerowind168/SIMUROSOT-AIR/blob/master/robot-airdemo.jpg)
