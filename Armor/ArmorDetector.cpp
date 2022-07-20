#include <math.h>
#include "../include/VideoProcess.h"

// #define HSV_
#define BGR_
// #define DEBUG_

/*
*   本函数主要用于求解装甲板像素坐标
*/

Mat DilateFunc(Mat& tempImg);

bool ArmorDetector(Mat& srcImg, vector<Point2f>& points)
{
    /*
    *   hsv处理方法
    */

    #ifdef HSV_

    int LowH =60, HighH = 120;
    int LowS=120, HighS = 255;
    int LowV =245, HighV =255;

    //转为hsv图像
    Mat hsvImg;
    cvtColor(srcImg,hsvImg,COLOR_BGR2HSV);

    vector<Mat> hsvSplit;

    split(hsvImg,hsvSplit);
    equalizeHist(hsvSplit[2],hsvSplit[2]);
    merge(hsvSplit,hsvImg);

    //膨胀操作
    Mat binImg;
    inRange(hsvImg,Scalar(LowH,LowS,LowV),Scalar(HighH,HighS,HighV),binImg);
    binImg = DilateFunc(binImg);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));
    morphologyEx(binImg, binImg, MORPH_CLOSE, kernel);
    Mat dilate_element = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(binImg, binImg, dilate_element);


    #endif


    #ifdef BGR_

    //通道分离
    vector<Mat> bgr;
    split(srcImg,bgr);

    //获取b-r图像
    Mat brImg = bgr.at(0)-bgr.at(2);
    Mat binImg;
    //二值化
    threshold(brImg, binImg, 100, 255, THRESH_BINARY);

    //闭操作后再膨胀
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));
    morphologyEx(binImg, binImg, MORPH_CLOSE, kernel);
    Mat dilate_element = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(binImg, binImg, dilate_element);


    #endif


    //寻找轮廓
    vector<vector<Point>> contours;  
    vector<Vec4i> hierarchy;
    findContours(binImg,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(-1, -1));
    
    //如果未找到灯条或仅找到一个灯条，直接终止，继续处理下一帧
    //防止发生内存泄露
    if(contours.size() <= 1)    {
        cout << "No target found!" << endl;
        return false;
    }

    
    vector<vector<Point>> contours_ploy(contours.size());
    vector<Rect> ploy_rects(contours.size());
        
    for(size_t i = 0; i < contours.size(); i++)
    {
        // 多边形拟合
        approxPolyDP(Mat(contours[i]), contours_ploy[i], 3, true);
        ploy_rects[i] = boundingRect(contours_ploy[i]);
    }

    //找符合一定宽高比的灯条并框选
    vector<Rect> rects;
    for(int i = 0; i < contours.size(); i++) {
        // rectangle(srcImg, ploy_rects[i], Scalar(0, 255, 0), 2, 8);

        #ifdef DEBUG_
        cout << "tl:" << ploy_rects[i].tl() << endl;
        cout << "br:" << ploy_rects[i].br() << endl;
        cout << "area:" << ploy_rects[i].area() << endl;
        cout << "width:" << ploy_rects[i].width << endl;
        cout << "height:" << ploy_rects[i].height << endl;
        #endif


        double ratio = 1.0 * ploy_rects[i].height / ploy_rects[i].width;

        if(ratio >= 1.2 && ratio <= 3.0)  {
            rects.push_back(ploy_rects[i]);
        }
    }

    // //如果仅找到小于两个合适的灯条，不予处理，直接进行下一帧
    if(rects.size() <= 1)       {
        cout << "There are no proper two light bars" << endl;
        return false;
    }

    for(size_t i = 0; i < rects.size(); i++)    {
        rectangle(srcImg, rects[i], Scalar(0, 255, 0), 2, 8);
    }
    
    Rect rect;
    size_t flag = 1;
    for(size_t i = 0; i < rects.size()-1; i++)    {
        for(size_t j = i+1; j < rects.size(); j++)  {
            rect = rects[i] | rects[j]; 
             cout <<  1.0*rect.width / rect.height << endl;
            if(1.0*rect.width / rect.height >= 1.4 && 1.0*rect.width / rect.height <= 4.0)  {
                flag = 0;
                break;
            }
        }
        if(!flag)   break;
    }

    if(flag)    {
        cout << "There are no matching armor plates." << endl;
        return false;
    }

    //绘制矩形框
    // Rect rect = rects[0] | rects[1];
    rectangle(srcImg, rect, Scalar(0, 0, 255), 2, 8);


    //获取打击区域四个顶点坐标
    Point2f topLeft = rect.tl();
    Point2f topRight;
    topRight.x = topLeft.x + rect.width;
    topRight.y = topLeft.y;
    Point2f bottomRight = rect.br();
    Point2f bottomLeft;
    bottomLeft.y = bottomRight.y;
    bottomLeft.x = bottomRight.x - rect.width;

    /*
    *   获取装甲板中心位置
    */
    // Point2f center;
    // center.x = topLeft.x + (rect.width / 2.0);
    // center.y = bottomLeft.y + (rect.height / 2.0);

    //将左边存在vector中（顺序为：左上，右上，左下，右下）
    points.push_back(topLeft);
    points.push_back(topRight);
    points.push_back(bottomLeft);
    points.push_back(bottomRight);
    // points.push_back(center);


    return true;
}


/*
*   hsv处理后效果不好，多次膨胀后才能勉强识别
*/

Mat DilateFunc(Mat& tempImg)
{
    Mat dstImg;
    Mat dilate_element = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(tempImg, dstImg, dilate_element);
    dilate(dstImg, dstImg, dilate_element);
    return dstImg;
}