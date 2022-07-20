/*
*	PnP空间解算头文件
*	
*/

# include <bits/stdc++.h>
# include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define HALF_LENGTH 74//装甲板实际大小
#define HALF_WIDTH 69.5
#define gun_cam_y 46.5

typedef struct
{
	Mat rvec;
	Mat tvec;
}MyVec;

typedef struct
{
	double yaw;
	double pitch;
	double distance;
}Angle;

void solvepnp(vector<Point2f> img, int fd);
Angle AngleSolve(vector<Point2f> img);
void CompensateOffset(Angle angle);
//void CompensateGravity(Angle angle,double bullet_speed);
