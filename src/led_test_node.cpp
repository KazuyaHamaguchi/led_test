#include <ros/ros.h>		//ROSに必要な関数を取り込むため必須！
#include <pigpiod_if2.h>	//ラズパイのピンにアクセスするためのライブラリ「PIGPIO」関数を取り込む

int main(int argc, char **argv)	//int main(void)だとROSの関数が使えない
{
        ros::init(argc, argv, "led_test_node");	//ノード名の初期化「ros::init(argc, argv, "起動時に指定するノード名");」(必須！)
	ros::NodeHandle nh;	//ROSシステムとの通信のためのノードハンドルを宣言（必須！）
	int pi = pigpio_start(0, 0);	//PIGPIOを使うときは必ず宣言
	set_mode(pi, 22, PI_OUTPUT);	//GPIOピンの設定「set_mode(pi, "ピン番号", "PI_OUTPUTかPI_INPUT");」
	while(ros::ok())	//ctrl + Cが押されるまで繰り返す
	{
		gpio_write(pi, 22, 1);	//22ピンをHIGHにする「gpio_write(pi, "ピン番号", 1か0);」
		ROS_INFO("LED ON");	//C言語でいうprintf「ROS_INFO("~");　""内の文字を出力」
		time_sleep(1);		//delay関数「time_sleep("秒");」
		gpio_write(pi, 22, 0);	//22ピンをLOWにする「gpio_write(pi, "ピン番号", 1か0);」
		ROS_INFO("LED OFF");
		time_sleep(1);
	}
	pigpio_stop(pi);	//PIGPIOデーモンとの接続を終了しライブラリが使用するリソースを解放(PIGPIOを使うときは必ず宣言)
	return 0;	
}
