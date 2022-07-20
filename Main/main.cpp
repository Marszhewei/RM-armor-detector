#include "../include/VideoProcess.h"
#include "../include/SetCam.h"
#include "../include/solvePnP.h"
#include "../include/Port.h"

// #define VIDEO_
#define CAMERA_
// #define PHOTO_
#define DEBUG_


using namespace std;
using namespace cv;

// template <class T>
// void measure(T&& func)  {
//     using namespace std::chrono;
//     auto start = system_clock::now();
//     func();
//     duration<double> diff = system_clock::now - start;
//     cout << "Time:" << diff.count() << "seconds." << endl;
// }

/*
*   main函数主调图像处理函数
*/

int main(int argc, char** argv)
{
    // 设定相机初始参数并show
    //SetCam();

const char * devName = "/dev/ttyUSB0";
Port port;
int fd = port.OpenPort(devName);
port.ConfigurePort(fd);

#ifdef DEBUG_
    try {
        #ifdef VIDEO_
        VideoCapture capture("../../TestVideo/sample.mp4");
        #endif

        #ifdef CAMERA_
        VideoCapture capture(0);
        #endif

        namedWindow("Img", 1);

        if (capture.isOpened()) {
            while(true) {
                Mat srcImg;
                capture >> srcImg;

                if(!srcImg.empty())  {
                    vector<Point2f> points;
                    bool flag = ArmorDetector(srcImg, points);

                    if(flag)    {
                        cout << "左上：" << points[0] << endl;
                        cout << "右上：" << points[1] << endl;
                        cout << "左下：" << points[2] << endl;
                        cout << "右下：" << points[3] << endl;
                        // cout << "中心：" << points[4] << endl

                        solvepnp(points, fd);

                        cout << endl;
                    }
                    
                    imshow("Img", srcImg);
                }

                
                if(waitKey(10) == 27)   {
                    break;
                } 
            }
        }

        destroyAllWindows();         
    }

    catch (...) {
        return -1;
    }

    #endif

    #ifdef PHOTO_

    Mat srcImg = imread("../../TestVideo/test.jpg", 1);
    if(!srcImg.empty())  {
        vector<Point2f> points;
        bool flag = ArmorDetector(srcImg, points);

        if(flag)    {
            cout << "左上：" << points[0] << endl;
            cout << "右上：" << points[1] << endl;
            cout << "左下：" << points[2] << endl;
            cout << "右下：" << points[3] << endl;
            // cout << "中心：" << points[4] << endl

            solvepnp(points);
            cout << endl;
        }
        
        imshow("Img", srcImg);
    }
    waitKey(0);

    #endif

    port.ClosePort(fd);
   
    cout << "finished" << endl;
    return 0;
}