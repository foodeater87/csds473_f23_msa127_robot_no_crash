#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>
#include "std_msgs/String.h"
#include <sstream>
#include <geometry_msgs/Twist.h>

ros::Publisher *p_pub;

float wall_dist = 0.5;
geometry_msgs::Twist velmsg;
sensor_msgs::LaserScan LaserData;

void Lidar(const sensor_msgs::LaserScan msg){
  LaserData = msg;
}

void des_vel(const geometry_msgs::Twist msg){
  bool stop = false;
  velmsg = msg;
  float xvel = msg.linear.x;
  int a = LaserData.ranges.size()/2-15;
  int b = LaserData.ranges.size()/2+15;
  if (xvel>0){
    for(int i = a;i<b;i++){
      float dist = LaserData.ranges[i];
      if (dist<wall_dist){
        ROS_INFO("%f",dist);
        stop = true;
        break;
      }
    }
    if (stop){
      velmsg.linear.x = 0;
      velmsg.angular.z = 0.3;
      ROS_WARN("You are about to run into a wall. Please turn.");
    }
  }
  p_pub->publish(velmsg);
}

int main(int argc, char* argv[]){
  ros::init(argc, argv, "control_node");
  ros::NodeHandle n;
  p_pub = new ros::Publisher(n.advertise<geometry_msgs::Twist>("cmd_vel", 1000));
  ros::Subscriber sub2 = n.subscribe<sensor_msgs::LaserScan>("laser_1", 1000, Lidar);
  ros::Subscriber sub1 = n.subscribe<geometry_msgs::Twist>("des_vel", 1000, des_vel);
  ros::Rate loop_rate(10);
	  
  ROS_INFO_ONCE("wall_dist began with: [%2.2f]", wall_dist);
  if (n.getParamCached("wall_dist",wall_dist)){
    ROS_INFO("wall_dist was updated to [%2.2f]", wall_dist);
  }
  
  if (n.getParam("wall_dist", wall_dist))
  {
    ROS_INFO("wall_dist is: [%2.2f]", wall_dist);
  }
  else
  {
    ROS_ERROR("Failed to get param 'wall_dist'");
  }
  /*
  while (ros::ok())
  {
    n.getParamCached("wall_dist", wall_dist);
    ros::spinOnce();
  }
*/
  ros::spin();
}
