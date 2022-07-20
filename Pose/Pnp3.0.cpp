#include "../include/solvePnP.h"
#include "../include/Port.h"

/*
	Input: vector<Point2f> img
	Output:angle//angle{yaw,pitch,distance}
*/
void solvepnp(vector<Point2f> img, int fd)
{
	Angle angle = AngleSolve(img);//angle solve
	// CompensateOffset(angle);//angle.pitch update
	//CompensateGravity(angle, );//angle.pitch update
	// uint8_t model = 0;		//0代表近距离，1代表远距离
	// if(angle.distance > 3000)	{
	// 	model = 1;
	// }
	bool flag = TestSerial(angle.yaw, angle.pitch, angle.distance, fd);

	if(flag)	{
		cout << "yaw= "<<angle.yaw<<"\npitch= "<<angle.pitch<<"\ndistance= "<<angle.distance<<endl;
	}
}

Angle AngleSolve(vector<Point2f> img)
{	
	//_3D_points
	vector<Point3f> obj = vector<Point3f> {
    	Point3f(-HALF_LENGTH, -HALF_WIDTH, 0),	//tl
    	Point3f(HALF_LENGTH, -HALF_WIDTH, 0),	//tr
   	    Point3f(HALF_LENGTH, HALF_WIDTH, 0),	//br
    	Point3f(-HALF_LENGTH, HALF_WIDTH, 0)	//bl
	};
	
	Mat camera_matrix = (Mat_<float>(3,3)<<1.2668,0,0.9227,0,1.2709,0.5686,0,0,0.0010); //内参矩阵
	Mat dist_coeffs=(Mat_<float>(1,5)<<0.1108,-0.4147,0,0,0); //畸变参数
	MyVec vec; 
	vec.rvec = Mat::zeros(3, 3, CV_64FC1);//init rvec
	vec.tvec = Mat::zeros(3, 1, CV_64FC1);//init tvec	

	 solvePnP(obj, img, camera_matrix, dist_coeffs, vec.rvec, vec.tvec, true, SOLVEPNP_P3P);	
	
	vec.rvec.at<double>(1,0) -= gun_cam_y; //（如果枪管在上面，则需要减去一个正数，这是在进行枪管与摄像头坐标的转换
	Angle angle;
	angle.yaw = (atan(vec.tvec.at<double>(0, 0) / vec.tvec.at<double>(2,0)) * 180 / CV_PI)-90;
	angle.pitch = (atan(-vec.tvec.at<double>(1, 0)) /  vec.tvec.at<double>(2, 0) * 180 / CV_PI)+90;
	angle.distance = sqrt(vec.tvec.at<double>(0, 0)*vec.tvec.at<double>(0, 0)+vec.tvec.at<double>(2, 0)*vec.tvec.at<double>(2, 0)+vec.tvec.at<double>(1, 0)*vec.tvec.at<double>(1, 0));
	//cout << "rvec= "<<vec.rvec<<"\ntvec= "<<vec.tvec<<endl;
	//cout << "yaw= "<<angle.yaw<<"\npitch= "<<angle.pitch<<"\ndistance= "<<angle.distance<<endl;
	return angle;
}

/*void CompensateOffset(Angle angle)//偏移补偿
{
	 float camera_target_height = angle.distance * sin(angle.pitch / 180 * CV_PI);
    	float gun_target_height = camera_target_height + gun_cam_y;
    	float gun_pitch_tan = gun_target_height / (angle.distance * cos(angle.pitch / 180 * CV_PI));
   	 angle.pitch = atan(gun_pitch_tan) / CV_PI * 180;
}*/

/*void CompensateGravity( )//重力补偿
{

}*/