#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "nav_msgs/Path.h"

class PathMarker {
 public:
  PathMarker(ros::NodeHandle n) {
    path_pub = n.advertise<visualization_msgs::Marker>("path_marker", 100);
  };
  ~PathMarker() {}
  void ShowPathCallback(const nav_msgs::Path& planned_path);

 private:
  ros::Publisher path_pub;	
};

void PathMarker::ShowPathCallback(const nav_msgs::Path& planned_path) {
  visualization_msgs::Marker path;

  path.header.frame_id = "/test_frame";
  path.header.stamp = ros::Time::now();
  path.ns = "path_point";
  path.action = visualization_msgs::Marker::ADD;
  path.pose.orientation.w = 1.0;
  path.id = 1;
  path.type = visualization_msgs::Marker::LINE_STRIP;
  
  path.scale.x = 0.1;
  
  path.color.g = 1.0;
  path.color.a = 1.0;

  geometry_msgs::Point path_point;
  for (size_t i = 0; i < planned_path.poses.size(); i++) {
    path_point.x = planned_path.poses[i].pose.position.x;
    path_point.y = planned_path.poses[i].pose.position.y;
    path_point.z = 0.2;
    path.points.push_back(path_point);
  }
  
  path_pub.publish(path);  
}

int main(int argc, char** argv) {
  
  ros::init(argc, argv, "path_marker");
  ros::NodeHandle n;
  PathMarker show(n);
  ros::Subscriber marker_sub = n.subscribe("global_path", 1000, &PathMarker::ShowPathCallback, &show);
  ros::spin();
  
  return 0;
}
