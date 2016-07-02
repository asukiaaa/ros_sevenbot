#define USE_USBCON
#include <ros.h>
#include <std_msgs/String.h>
#include "SevenBotController.h"

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher publisher("serial_publisher", &str_msg);

SevenBotController sevenbot;

void setup() {
  nh.initNode();
  nh.advertise(publisher);
}

void loop() {
  str_msg.data = sevenbot.get_angle_str().c_str();
  publisher.publish( &str_msg );
  nh.spinOnce();
  //delay(1000);
}
