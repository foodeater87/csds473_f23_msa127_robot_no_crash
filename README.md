# Lab 4
## Step 1
Clone the repository.

## Step 2
Setup and enter the catkin workspace that you cloned the repository into (catkin_ws should be replaced with the name of your workspace).
`source /opt/ros/noetic/setup.bash`
`cd catkin_ws`
`catkin_make`
`source devel/setup.bash`

## Step 3
Use the following launch commands to run the program:
`roslaunch robot_no_crash robot_launch.launch &`
`roslaunch robot_no_crash nodelaunch.launch &`

## Step 4
Add a robot to the interface:
1. Click the "Create Robot" button in the stdr gui (third button to the right on the row of buttons below "file")
2. Click the "+" symbol next to where it says "Lasers"
3. Click "Add Robot to map"
4. Click a spot on the map to add the robot and use the remote control gui to control the robot. Make sure the text box below "robot steering" in the remote control gui says "/robot0/des_vel"
