#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;
float last_lin_x = 0.0;
float last_ang_z = 0.0;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;
	
	if (!client.call(srv)) {
		ROS_ERROR("Falled to call DriveToTarget service");
	}
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
	
	float current_lin_x = 0.0;
	float current_ang_z = 0.0;
	if (left_count == 0 && middle_count == 0 && right_count == 0) {
		ROS_INFO_STREAM("STOP");
		current_lin_x = 0.0;
		current_ang_z = 0.0;
	} else if (left_count > right_count && left_count > middle_count) {
		ROS_INFO_STREAM("LEFT");
		current_lin_x = 0.0;
		current_ang_z = 0.5;
	} else if (right_count > left_count && right_count > middle_count) {
		ROS_INFO_STREAM("RIGHT");
		current_lin_x = 0.0;
		current_ang_z = -0.5;
	} else {
		ROS_INFO_STREAM("FORWARD");
		current_lin_x = 0.5;
		current_ang_z = 0.0;
	}
	
	
	if (current_lin_x != last_lin_x || current_ang_z != last_ang_z) { 
	    drive_robot(current_lin_x, current_ang_z);
	    last_lin_x = current_lin_x;
        last_ang_z = current_ang_z;
	}
}

int main(int argc, char** argv) 
{
	// initialize the process image node and create a handle to it
	ros::init(argc, argv, "process_image");
	ros::NodeHandle n;
	
	// Define a client service capable of requesting services from command_robot
	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
	
	// Subscribe to /camera/rgb/image_raw topic to read 
	// the image data inside the process_image_callback function
	ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
	
	// Handle ROS communications events
	ros::spin();
	
	return 0;
}
