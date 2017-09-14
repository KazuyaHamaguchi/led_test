#include "ros/ros.h"
#include <pigpiod_if2.h>

int main(int argc, char **argv)
{
	int pi = pigpio_start(0, 0);
	ros::init(argc, argv, "led_test_node");
	set_mode(pi, 22, PI_OUTPUT);
	while(1)
	{
		gpio_write(pi, 22, 1);
		ROS_INFO("LED ON");
		time_sleep(1);
		gpio_write(pi, 22, 0);
		ROS_INFO("LED OFF");
		time_sleep(1);
	}
	pigpio_stop(pi);
	return 0;	
}
