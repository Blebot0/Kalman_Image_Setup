#ifndef KALMAN_FILTER_HEADER_H
#define KALMAN_FILTER_HEADER_H

#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Eigenvalues>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/Core/util/Constants.h>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>
#include <eigen3/unsupported/Eigen/CXX11/src/util/EmulateArray.h>
#include <eigen3/Eigen/src/Core/util/Meta.h>
#include <eigen3/Eigen/src/Core/util/Constants.h>

#include <iostream>

#include <opencv2/core/hal/interface.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>

#define KERNEL_SIZE 3

namespace kl{

class Kalman{

	private:
	public:
		// init
		// defining a all zero 3 x 3 kernel
		Kalman();

		// OpenCV Kernel to be manipulated 
		cv::Mat kernel;
		
		// uncertainity

		// process noise Q
		static constexpr float process_noise_data[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
		cv::Mat process_noise = cv::Mat(KERNEL_SIZE, KERNEL_SIZE, *process_noise_data);
		float K;

		// prediction update
		void pred() const;

		// measurement update
		cv::Mat measurement() const;
};

}
#endif
