cmake_minimum_required(VERSION 2.8.3)
project(ultradar)

find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation serial
)
find_package(OpenCV REQUIRED)
## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES serial
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)
add_executable(ultradar_com src/ultradar_com.cpp)
add_dependencies(ultradar_com
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ultradar_com ${catkin_LIBRARIES})
target_link_libraries(ultradar_com ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
