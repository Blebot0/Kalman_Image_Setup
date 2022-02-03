#include "../include/kalman_implementation/Kalman.hpp"

using namespace kl;

Kalman::Kalman(){
	
	float kernel_data[] = {1, 0, 1, 1, 0, 1, 1, 0, 1};
	kernel = cv::Mat(3, 3, *kernel_data);
}
void Kalman::pred() const{

	cv::Mat predicted_kernel = kernel;

	//variance = variance + process_noise;
}



cv::Mat Kalman::measurement() const{
	// TODO: FIX MEMORY LEAK AND BAD_ALLOC IN THIS FUNCTION	
	// Eigen Tensor to hold the OpenCV kernel Matrix 
	Eigen::Tensor< float, 3, Eigen::RowMajor> kernel_mat;

	// Converting kernel to Eigen container
	cv::cv2eigen(kernel, kernel_mat); 
	
	// Flattening Eigen Vector to apply operations
	Eigen::array<Eigen::DenseIndex, 1> flatten({KERNEL_SIZE * KERNEL_SIZE });
	Eigen::Tensor<float, 1,  Eigen::RowMajor> flatten_mat = kernel_mat.reshape(flatten);

	std::clog << "flatten mat\n" << flatten_mat << flatten_mat.dimensions() << '\n';
		
	// DO ALL THE OPERATIONS REQUIRED
	//
	//
	//
	// Converting Tensor from flat to initial shape
	Eigen::array<int, 3> shapen{3, 3, 1};
	kernel_mat = flatten_mat.reshape(shapen);
	
	std::clog << "Shapen mat\n" << kernel_mat << kernel_mat.dimensions() << '\n';

	// Converting it back to OpenCV Matrix
	cv::eigen2cv(kernel_mat, kernel);

	return kernel;
}
