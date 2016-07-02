#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

double degree_to_radian(double degree);
std::vector<std::string> split(const std::string& s, char delim);
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string> &elems);

// reference
// http://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/
class SerialNodeStateMonitor {
public:
  SerialNodeStateMonitor(int argc, char* argv[]) {

    joint_state.name.push_back("j1");
    joint_state.name.push_back("j2");
    joint_state.name.push_back("j2m");
    joint_state.name.push_back("j3");
    joint_state.name.push_back("j4");
    joint_state.name.push_back("j5");
    joint_state.name.push_back("j6");

    joint_state.position.resize( joint_state.name.size() );
    for ( int i=0; i<joint_state.name.size(); i++ ) {
      joint_state.position.push_back(0);
    }
  }

  void callback(const std_msgs::StringConstPtr& input) {
    std::cout << input->data << std::endl;
    convert_input_str_to_joint_state(input->data, joint_state);
  }

  void start_subscribing() {
    serial_sub = node.subscribe("/sevenbot_arduino_master", 10, &SerialNodeStateMonitor::callback, this);
  }

  void start_publishing() {
    joint_pub = node.advertise<sensor_msgs::JointState>("/joint_states", 10);
    ros::Rate rate(2); // 2Hz

    while ( ros::ok() ) {
      std::cout << joint_state << std::endl;
      joint_state.header.stamp = ros::Time::now();
      joint_pub.publish(joint_state);
      rate.sleep();
    }
  }

private:
  ros::NodeHandle node;
  ros::Publisher joint_pub;
  ros::Subscriber serial_sub;
  sensor_msgs::JointState joint_state;
  std::vector<std::string> input_words;

  void convert_input_str_to_joint_state(const std::string& input_str, sensor_msgs::JointState& output_joint_state) {
    split(input_str, ',', input_words);

    // remove angle_type info
    input_words.erase( input_words.begin() );

    for( int i=0, j=0; i<input_words.size(); i++, j++ ) {
      output_joint_state.position[j] = degree_to_radian( atoi(input_words[i].c_str()) - 90 );
      if ( i == 2 ) { // j2m
        j++;
        output_joint_state.position[j] = - degree_to_radian( atoi(input_words[i].c_str()) - 90 );
        continue;
      }
    }
  }

};

//
// main
//
int main(int argc, char** argv) {
  ros::init(argc, argv, "serial_node_state_publisher");
  SerialNodeStateMonitor node_state_monitor(argc, argv);
  node_state_monitor.start_subscribing();
  //node_state_monitor.start_publishing();

  return 0;
}

//
// functions
//
double degree_to_radian(double degree) {
  return ( degree * M_PI ) / 180;
}

std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while ( getline( ss, item, delim) ) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}
