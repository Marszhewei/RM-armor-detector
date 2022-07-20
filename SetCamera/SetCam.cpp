# include "../include/SetCam.h"
# include <iostream>
using namespace std;

/*
*   初始化相机参数
*/

void SetCam()
{
    VideoCapture().set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);     //设置宽度
    VideoCapture().set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);    //设定高度
    VideoCapture().set(cv::CAP_PROP_FPS, FPS);           //FPS
    VideoCapture().set(cv::CAP_PROP_BRIGHTNESS, BRIGHTNESS);     //亮度 
	VideoCapture().set(cv::CAP_PROP_CONTRAST, CONTRAST);      //对比度 
	VideoCapture().set(cv::CAP_PROP_SATURATION, SATURATION);    //饱和度 
	VideoCapture().set(cv::CAP_PROP_HUE, HUE);       //色调 
	VideoCapture().set(cv::CAP_PROP_EXPOSURE, EXPOSURE);      //曝光 


    cout << "\n相机基本参数" << endl;
    cout << "宽度:" << VideoCapture().get(cv::CAP_PROP_FRAME_WIDTH) << endl;
    cout << "高度:" << VideoCapture().get(cv::CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "FPS:" << VideoCapture().get(cv::CAP_PROP_FPS) << endl;
    cout << "亮度:" << VideoCapture().get(cv::CAP_PROP_BRIGHTNESS) << endl;
    cout << "对比度:" << VideoCapture().get(cv::CAP_PROP_CONTRAST) << endl;
    cout << "饱和度:" << VideoCapture().get(cv::CAP_PROP_SATURATION) << endl;
    cout << "色调:" << VideoCapture().get(cv::CAP_PROP_HUE) << endl;
    cout << "曝光:" << VideoCapture().get(cv::CAP_PROP_EXPOSURE) << endl;
}