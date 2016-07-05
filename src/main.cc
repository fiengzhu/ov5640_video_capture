/*
 * Copyright 2014 Jacob Aslund <jacob@itbuster.dk>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ov_video_capture.h"
#include <time.h>

using namespace std;

int main() {
	
	// Create Ov5640 capture device with 320x240 @ 30 fps format
	//jafp::OvVideoCapture capture(jafp::OvVideoCapture::OV_MODE_1920_1080_15);
        jafp::OvVideoCapture capture(jafp::OvVideoCapture::OV_MODE_2592_1944_15);
	//jafp::OvVideoCapture capture(jafp::OvVideoCapture::OV_MODE_640_480_30);
	
	if (!capture.open()) {
		perror("open");
		return -1;
	}

	cv::Mat frame, frameSM;
	frameSM.create(1944/2, 2592/2, CV_8UC3);

	std::cout << "open successful" << std::endl;

	// Capture 30 frames
	for (int i = 0; i < 2; i++) {
		clock_t t0 = clock();
		capture.read(frame);
		clock_t t1 = clock();

		//cv::cv::Size(0, 0);
		//cv::resize(frame, frameSM, frameSM.size());
		//cv::pyrDown(frame, frameSM, frameSM.size());

		std::stringstream str;
		str << "frames/frame_" << i << ".bmp";
		cv::imwrite(str.str(), frame);
		clock_t t2 = clock();

		float e1 = (float)(t1 - t0) / CLOCKS_PER_SEC;
		float e2 = (float)(t2 - t0) / CLOCKS_PER_SEC;
	
		std::cout << "frame " << i << ", time: " << e1 << ',' << e2 << std::endl;
	}
	
	capture.release();

	return 0;
}
