#!/usr/bin/env python

# reference
# http://interimadd.com/2016/02/12/ros%E3%81%A7%E8%A4%87%E6%95%B0%E3%81%AEtopic%E3%82%92subscirbe%E3%81%97%E3%81%9F%E6%83%85%E5%A0%B1%E3%82%92%E5%87%A6%E7%90%86%E3%81%97%E3%81%A6publish%E3%81%99%E3%82%8B%E3%83%8E%E3%83%BC%E3%83%89/

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import JointState
import math

class SerialNodeStateMonitor:
  degrees = []
  radians = []

  def __init__(self):
    rospy.init_node('serial_node_state_monitor');
    self.pub = rospy.Publisher('/joint_states', JointState, queue_size=10)
    self.joint_state = JointState()
    # self.joint_state.name = ['j1', 'j2', 'j3', 'j4', 'j5', 'j6']
    self.joint_state.name = ['j1', 'j2', 'j2m', 'j3', 'j4', 'j5', 'j6']

  def start_subscribe(self):
    rospy.Subscriber("/sevenbot_arduino_master", String, self.callback)

  def callback(self, input_str):
    # remove first info because it is angle_type
    self.degrees = input_str.data.split(',')[1:]
    self.radians = [ (int(degree) - 90) * math.pi / 180 for degree in self.degrees ]
    radians_with_mimic = self.radians
    radians_with_mimic.insert(2, -self.radians[1])
    self.joint_state.position = radians_with_mimic

  def start_publish(self):
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
      self.joint_state.header.stamp = rospy.get_rostime()
      self.pub.publish(self.joint_state)
      print self.joint_state
      print self.degrees
      rate.sleep()

if __name__ == '__main__':
  node_monitor = SerialNodeStateMonitor()
  node_monitor.start_subscribe()
  node_monitor.start_publish()
