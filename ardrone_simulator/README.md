ardrone_simulator on Indigo
=============
This is the 2017 FIRA Air environment

OS: ubuntu 14.04
ROS: indigo
gazebo : 2.2.3

How to install the simulator:

1. Create a workspace for the simulator

    ```
    mkdir -p ~/catkin_ws/src
    cd  ~/catkin_ws
    catkin_make
    source devel/setup.bash
    ```

2. Download dependencies

    ```
    cd ~/catkin_ws/src
    git clone https://github.com/AutonomyLab/ardrone_autonomy.git	# The AR.Drone ROS driver
    git clone https://github.com/HubFire/ardrone_simulator.git
    cd ..
    rosdep install --from-paths src --ignore-src --rosdistro indigo -y
    ```
3. Build the simulator

    ```
    catkin_make
    ```
4. Source the environment

    ```
    source devel/setup.bash
    ```
How to run a simulation:

1. Run a simulation by executing a launch file in cvg_sim_gazebo package:

    ```
    roslaunch cvg_sim_gazebo ardrone_testworld.launch
    ```
