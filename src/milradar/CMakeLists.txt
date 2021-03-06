cmake_minimum_required(VERSION 2.8.3)
project(milradar)

find_package(catkin REQUIRED COMPONENTS
  roscpp std_msgs message_generation
)
find_package(OpenCV REQUIRED)
## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   obj208.msg
   obj408.msg
   obj208_multi.msg
   obj408_multi.msg
 )
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
add_executable(milradar208_12 src/milradar208_12.cpp)
add_executable(milradar208_35 src/milradar208_35.cpp)
add_executable(milradar208_46 src/milradar208_46.cpp)
add_executable(milradar408 src/milradar408.cpp)
add_executable(milradar_display src/milradar_display.cpp)
add_dependencies(milradar408 milradar208_12 milradar208_35 milradar208_46 milradar_display
    ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(milradar_display ${catkin_LIBRARIES})
target_link_libraries(milradar408 ${catkin_LIBRARIES})
target_link_libraries(milradar208_12 ${catkin_LIBRARIES})
target_link_libraries(milradar208_35 ${catkin_LIBRARIES})
target_link_libraries(milradar208_46 ${catkin_LIBRARIES})

target_link_libraries(milradar_display ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
