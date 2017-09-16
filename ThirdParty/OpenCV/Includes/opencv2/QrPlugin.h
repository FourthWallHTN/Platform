#pragma once  

#define DLL_EXPORT __declspec(dllexport)	//shortens __declspec(dllexport) to DLL_EXPORT

#include <opencv2\opencv.hpp>
#include <iostream>
#include <cmath>

#ifdef __cplusplus		//if C++ is used convert it to C to prevent C++'s name mangling of method names
extern "C"
{
#endif

	bool DLL_EXPORT detect(cv::Mat& image);

#ifdef __cplusplus	
}
#endif
