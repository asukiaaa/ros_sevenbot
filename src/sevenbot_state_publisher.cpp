#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

double degree_to_radian(double degree);

int main(int argc, char** argv) {
  ros::init(argc, argv, "sevenbot_state_publisher");
  ros::NodeHandle node;
  ros::Publisher joint_pub = node.advertise<sensor_msgs::JointState>("/joint_states", 10);
  ros::Rate rate(1); // 1Hz
  sensor_msgs::JointState joint_state;

  // redundant
  joint_state.name.push_back("j1");
  joint_state.name.push_back("j2");
  joint_state.name.push_back("j2m");
  joint_state.name.push_back("j3");
  joint_state.name.push_back("j4");
  joint_state.name.push_back("j5");
  joint_state.name.push_back("j6");

  joint_state.position.resize( joint_state.name.size() );

  while( ros::ok() ) {
    for ( int i=0; i<joint_state.name.size(); i++ ) {
      if ( i == 2 ) {
        // j2m
        // do nothing
      } else {
        joint_state.position[i] = degree_to_radian(30.0);
      }
    }

    joint_state.header.stamp = ros::Time::now();
    joint_pub.publish(joint_state);
    ros::spinOnce();

    // std::cout << joint_state << std::endl;
    rate.sleep();
  }
  return 0;
}

double degree_to_radian(double degree) {
  return ( degree * M_PI ) / 180;
}
