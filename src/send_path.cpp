#include "ros/ros.h"
#include "nav_msgs/Path.h"



int main(int argc, char** argv) {
  ros::init(argc, argv, "send_path");
  ros::NodeHandle n;
  ros::Publisher path_send = n.advertise<nav_msgs::Path>("global_path", 100);
  
  nav_msgs::Path path;
  double x, y;
  x = 0.0;
  y = 0.0;
  ros::Rate r(20);
  
  while(ros::ok()){
    x = 0.0;
    y = 0.0;
    for(size_t i = 0; i < 5; i++) {
      geometry_msgs::PoseStamped pose_stamp;
      pose_stamp.pose.position.x = x;
      pose_stamp.pose.position.y = y;
      path.poses.push_back(pose_stamp);
      x += cos(i);
      y += sin(i);      
    }
    path_send.publish(path);
    ros::spinOnce();
    r.sleep(); 
  }
}
