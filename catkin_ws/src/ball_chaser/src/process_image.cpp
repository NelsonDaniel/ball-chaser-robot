#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
	// TODO
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
	int white_pixel = 255;
	int left_count = 0;
	int middle_count = 0;
	int right_count = 0;
  	int i = 0;
	for (int height = 0; height < img.height; height++) {
		for (int step = 0; step < img.step; step++) {
          if (img.data[i] == white_pixel) {  
			if (step <= img.step*(1.0/3)) {
				left_count += 1;
			} else if (step <= img.step*(2.0/3)) {
				middle_count += 1;
			} else {
				right_count += 1;
			} 
          }
          
          i++;
		}
	}
	
  
  	ROS_INFO_STREAM("L: "<< left_count << " R: "<<right_count << " M: "<< middle_count);
	if (left_count > right_count && left_count > middle_count) {
		ROS_INFO_STREAM("left");
	} else if (right_count > left_count && right_count > middle_count) {
		ROS_INFO_STREAM("right");
	} else {
		ROS_INFO_STREAM("forward");
	}
}

int main(int argc, char** argv) 
{
	// initialize the process image node and create a handle to it
	ros::init(argc, argv, "process_image");
	ros::NodeHandle n;
	
	// Define a client service capable of requesting services from command_robot
	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chasser/command_robot");
	
	// Subscribe to /camera/rgb/image_raw topic to read 
	// the image data inside the process_image_callback function
	ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
	
	// Handle ROS communications events
	ros::spin();
	
	return 0;
}
