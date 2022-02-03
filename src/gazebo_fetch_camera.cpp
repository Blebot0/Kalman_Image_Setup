// Name: Keshav Kapur
// Email: keshav29kapur@gmail.com

// Gazebo Libraries 
#include <gazebo/gazebo_client.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <gazebo/msgs/image_stamped.pb.h>

// Standard Libraries
#include <iostream>

// OpenCV Libraries
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <../include/kalman_implementation/Kalman.hpp>

cv::Mat Convolve2D(cv::Mat& image,const cv::Mat& kernel){
	cv::Mat convolved(image);
//	// Default anchor
	cv::Point  anchor = cv::Point(-1, -1);

//	// Same Depth Of Source and Destination Image
	int ddepth = -1;

// 	// Filter 2D src, destination, ddepth, kernel, anchor
	cv::filter2D(image, convolved, ddepth, kernel, anchor, 0, cv::BORDER_DEFAULT);
	
	return convolved;
}

//// Function is called everytime a message is received.
void camera_callback(ConstImageStampedPtr &msg){
	
	kl::Kalman kf;
//	// Setting up OpenCV image container to store the camera feedback
    	cv::Mat mRGBAImg = cv::Mat(cv::Size(msg->image().width(),msg->image().height()),CV_8UC3);
	
//	// Saving Camera Feedback Data to the image container
	memcpy(mRGBAImg.data,msg->image().data().c_str(),msg->image().data().size());
	
	cv::Mat kernel = kf.measurement();
	mRGBAImg = Convolve2D(mRGBAImg, kernel);	

//	// Image Display Video Feedback
	cv::imshow("Camera Feed", mRGBAImg);
	cv::waitKey(1);

}

int main(int _argc, char **_argv){
//      // Load gazebo
        gazebo::client::setup(_argc, _argv);

//      // Create our node for communication
        gazebo::transport::NodePtr node(new gazebo::transport::Node());
        node->Init();
	
	std::clog << "Client Connected!\n";
//      // Listen to Gazebo world_stats topic
        gazebo::transport::SubscriberPtr sub = node->Subscribe("/gazebo/default/distorted_camera/link/camera/image", camera_callback);

//      // Busy wait loop
	while(1){
		gazebo::common::Time::MSleep(10);
	}
//	// Node shutdown
        gazebo::client::shutdown();
}
