cmake_minimum_required(VERSION 2.8.3)
project(sevenbot_pkg)

find_package(catkin REQUIRED COMPONENTS
  urdf
  roscpp
  rosserial_msgs
  topic_tools
  std_msgs
)
find_package(Boost REQUIRED COMPONENTS
  system
  thread
)

catkin_package(
  INCLUDE_DIRS include ${Bootst_INCLUDE_DIRS}
  CATKIN_DEPENDS urdf roscpp rosserial_msgs topic_tools std_msgs sensor_msgs
)

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

add_executable(sevenbot_state_publisher src/sevenbot_state_publisher.cpp)
target_link_libraries(sevenbot_state_publisher ${catkin_LIBRARIES})

add_executable(serial_node_state_publisher src/serial_node_state_publisher.cpp)
target_link_libraries(serial_node_state_publisher ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_serial_node src/serial_node.cpp)
target_link_libraries(${PROJECT_NAME}_serial_node ${catkin_LIBRARIES})
set_target_properties(${PROJECT_NAME}_serial_node PROPERTIES OUTPUT_NAME serial_node PREFIX "")
add_dependencies(${PROJECT_NAME}_serial_node rosserial_msgs_gencpp)
