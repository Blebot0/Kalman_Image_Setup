#include <gazebo-10/gazebo/gazebo_client.hh>
#include <gazebo-10/gazebo/transport/transport.hh>
#include <gazebo-10/gazebo/gazebo.hh>
#include <gazebo-10/gazebo/msgs/msgs.hh>
#include <gazebo-10/gazebo/transport/TransportTypes.hh>
#include <gazebo/msgs/image_stamped.pb.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
//// Function is called everytime a message is received.

void camera_callback(ConstImageStampedPtr &msg){
//  // Dump the message contents to stdout.
    //int width, height;
    //char* data;

    //width =  (int) msg->image().width();
    //height = (int) msg->image().height();
    //data = new char[msg->image().data().length() + 1];
    //memcpy(data, msg->image().data().c_str(), msg->image().data().length());
    

    	cv::Mat mRGBAImg = cv::Mat(cv::Size(msg->image().width(),msg->image().height()),CV_8UC3);
	memcpy(mRGBAImg.data,msg->image().data().c_str(),msg->image().data().size());
	cv::imshow("Camera Feed", mRGBAImg);
	cv::waitKey(3);

    //cv::Mat image(height, width, CV_8UC3, data);
    //delete data;
}

int main(int _argc, char **_argv){
//      // Load gazebo
        gazebo::client::setup(_argc, _argv);

//      // Create our node for communication
        gazebo::transport::NodePtr node(new gazebo::transport::Node());
        node->Init();

//                // Listen to Gazebo world_stats topic
        gazebo::transport::SubscriberPtr sub = node->Subscribe("/gazebo/default/distorted_camera/link/camera/image", camera_callback);

//                    // Busy wait loop...replace with your own code as needed.
	while(1){
		gazebo::common::Time::MSleep(10);
	}
        gazebo::client::shutdown();
}
