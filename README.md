# ros_sevenbot

A package to control sevenbot from ROS.

ROS: http://wiki.ros.org/

# Setup

## ROS

I expect that you have already created workspace for ros.

### setup rosserial_arduino

rosserial_arduino: http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

```sh
cd ~/catkin_ws/src
git clone https://github.com/ros-drivers/rosserial.git
cd ~/catkin_ws
catkin_make
catkin_make install
```

### download this repository
```sh
cd ~/catkin_ws/src
git clone git@github.com:asukiaaa/ros_sevenbot.git
cd ~/catkin_ws
catkin_make
```

## Arduino
I expect that you have already installed Arduino and its package for DUE.

### Set dependent libraries for arduino

- KPowerServoController
- SevenBotController
- rosserial_arduino

```sh
cd ~/Arduino/libraries
git clone git@github.com:asukiaaa/KPowerServoController.git
git clone git@github.com:asukiaaa/SevenBotController.git
# catkin_make install may be needed before the following command
source ~/catkin_ws/install/setup.bash
rosrun rosserial_arduino make_libraries.py ./
```

### Set symlink for sketch.
```sh
cd ~/Arduino
ln -s ~/catkin_ws/src/ros_sevenbot/arduino_sketch sevenbot_with_ros
```

# useage

## Upload program to Arduino
Compile and upload a publisher program to Arduino DUE in sevenbot.

Use this file.
```
~/Arduino/sevenbot_with_ros/serial_publisher/serial_publisher.ino
```

Note: A package "Arduino SAM Boards" is needed for IDE to deal Arduino DUE. Install it via boadmanager before uploading sketch.

## Launch
```
cd ~/catkin_ws
roslaunch ros_sevenbot arduino_pub.launch
```

# References
- http://ros-robot.blogspot.jp/2009/12/python.html
- http://interimadd.com/2016/02/12/ros%E3%81%A7%E8%A4%87%E6%95%B0%E3%81%AEtopic%E3%82%92subscirbe%E3%81%97%E3%81%9F%E6%83%85%E5%A0%B1%E3%82%92%E5%87%A6%E7%90%86%E3%81%97%E3%81%A6publish%E3%81%99%E3%82%8B%E3%83%8E%E3%83%BC%E3%83%89/
- http://www.rt-shop.jp/blog/archives/6968
