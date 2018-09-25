#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Point.h"



class MapMarker {
 public:
  MapMarker () { }
  MapMarker (ros::NodeHandle n);
  ~MapMarker () { }
  void MarkerCallback(const geometry_msgs::Point &position);

 private:
  ros::NodeHandle n;
  // ros::Subscriber marker_sub;
  ros::Publisher marker_pub;
//   double count;

};

MapMarker::MapMarker(ros::NodeHandle n) {  
  marker_pub = n.advertise<visualization_msgs::Marker>("localization_marker", 1000);
//   count = 0.0;
}


void MapMarker::MarkerCallback(const geometry_msgs::Point &position) {

  visualization_msgs::Marker p;  

  p.header.frame_id = "/test_frame";
  p.header.stamp = ros::Time::now();
  p.ns = "position_point";
  p.action = visualization_msgs::Marker::ADD;
  p.pose.orientation.w = 1.0;
  p.id = 0;
  p.type = visualization_msgs::Marker::POINTS;

  p.scale.x = 0.5;
  p.scale.y = 0.5;

  p.color.r = 1.0;
  p.color.a = 1.0;

  geometry_msgs::Point tmp_p;
  tmp_p.x = position.x;
  tmp_p.y = position.y;
  tmp_p.z = 0.2;

  p.points.push_back(tmp_p);
  marker_pub.publish(p);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "localization_marker");
  ros::NodeHandle n;

  MapMarker show(n);
  ros::Subscriber marker_sub = n.subscribe("global_position", 1000, &MapMarker::MarkerCallback, &show);
  ros::spin();  
  
  return 0;
}
