# ball-chaser-robot
This is a ball chasing robot. It is my second project for the Robotics Software Engineering Nanodegree from Udacity.

This project contains two packages: `my_robot` and `ball_chaser`. 

## my_robot package

This package contains a differential robot, a white ball and a world. The differential robot contains two sensors: a camera and a lidar. The white ball is just the object that the robot tries to chase. Both the robot and white ball are housed in the world.

The `world.launch` launches the ball and robot inside the world.

## ball_chaser package

This package contains two nodes: `drive_bot` and `process_image`.

### drive_bot node

This node provides a ball_chaser/command_robot service to drive the robot by controlling its linear x and angular z velocities. 

The service should publishes to the wheel joints and return back the requested velocities.

### process_image node

This node that provides a ball_chaser/command_robot service to drive the robot by controlling its linear x and angular z velocities. 

The service publishes to the wheel joints and return back the requested velocities.

Both nodes are launched using the `ball_chaser.launch` file.
