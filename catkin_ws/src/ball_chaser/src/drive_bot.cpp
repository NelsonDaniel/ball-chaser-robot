#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"


// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// This callback function executes whenever a drive_bot service is requested and 
// publishes the requested linear x and angular velocities to the robot wheel joints
// After publising the requested velocities, a message feedback is returned with 
// the requested wheel velocities
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res) {
	ROS_INFO("DriveToTargetRequest received - linear_x:%1.2f, angular_z:%1.2f", (float)req.linear_x, (float)req.angular_z);
	
	
	return true;
}


int main(int argc, char** argv) 
{
	// Initialize a ROS node
	ros::init(argc, argv, "drive_bot");
	
	// Create a ROS NodeHangle object
	ros::NodeHandle n;
	
	// Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue of size 10
	motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	
	// TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
	ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
	
	// TODO: Delete the loop, move the code to the inside of the callback function and make neccessary changes to publish the requested velocities instead of constant values
	
	
	//while (ros::ok()) {
		// Create a motor_command object of type geometry_msgs::Twist
	//	geometry_msgs::Twist motor_command;
		// Set wheel velocities, forward [0.5, 0.0]
	//	motor_command.linear.x = 0.5;
	//	motor_angular.z = 0.0
		//Publish angles to drive the robot
	//	motor_command_publisher.publish(motor_command)	
	//}
	
	// TODO: Handle ROS communication events
	ros::spin();
	
	return 0;
}
