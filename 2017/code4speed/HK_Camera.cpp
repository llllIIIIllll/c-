
#include <iostream> 
#include "Camera.h"
#include "Channel.h"
#include "PTZControl.h"
#include "ChannelImg.h"
#include "StorgeImgMap.h"

#define CAMERA_NUMBERS 2

// camera struct
struct CameraArgument
{
	std::string inputArgv[3];
	Camera		*camera;
	Channel		*channel;
	ChannelImg	*channelimg;
};

int main(int argc, char **argv)
{
	// ip setting
	std::string ip[CAMERA_NUMBERS] = { "169.254.13.102" , "169.254.13.104"};
	CameraArgument allCam[CAMERA_NUMBERS];
	// output mat
	map<long, cv::Mat> out;
	
	// camera setup
	for (int i = 0; i < CAMERA_NUMBERS; ++i)
	{
		allCam[i].inputArgv[0] = ip[i];
		allCam[i].inputArgv[1] = "admin";
		allCam[i].inputArgv[2] = "infecon123";
		allCam[i].camera = new Camera(allCam[i].inputArgv[0], allCam[i].inputArgv[1], allCam[i].inputArgv[2]);
		if (allCam[i].camera->lUserID == -1)
			return -1;
		allCam[i].channel = new Channel(allCam[i].camera->lUserID, 1);
		allCam[i].channelimg = new ChannelImg();
		allCam[i].channelimg->setlRealPlayHandle(allCam[i].channel->lRealPlayHandle);
		allCam[i].channelimg->setImg(Mat(0, 0, CV_8UC3));
		Channel::storgeImgMap->Imgmaps->insert(make_pair(allCam[i].channel->lRealPlayHandle, allCam[i].channelimg));
	}

	while (true)
	{
		/// get all pictures
		
	
			for (int i = 0; i < CAMERA_NUMBERS; ++i)
			{
				out = Channel::storgeImgMap->getImg(allCam[i].channel->lRealPlayHandle, -1);
				if (out.find(allCam[i].channel->lRealPlayHandle) != out.end())
					imshow("test" + i, out.at(allCam[i].channel->lRealPlayHandle));
				waitKey(1);
			}

		// show picture

		
		

		Sleep(10);
	}

}

