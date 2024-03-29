#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include<iostream>  
#include<string>  
using namespace std;
using namespace cv;
//bgr图像  
Mat bgr;
//HSV图像  
Mat hsv;
//色相  
int hmin = 0;//h分量提取下限
int hmax = 180;//h分量提取上限
int h_Max = 180; //h分量可取的最大值
//饱和度  
int smin = 0;//s分量提取下限
int smax = 255;//s分量提取上限
int s_Max = 255;//s分量可取的最大值
//亮度  
int vmin = 0;//v分量提取下限
int vmax = 255;//v分量提取上限
int v_Max = 255;//v分量可取的最大值
//显示原图的窗口  
string windowName = "src";
//输出图像的显示窗口  
string dstName = "dst";
//输出图像  
Mat dst;
//回调函数  
void callBack(int, void*)
{
	//输出图像分配内存  
	dst = Mat::zeros(bgr.size(), bgr.type());
	//遮罩  
	Mat mask;
	//inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
	inRange(hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
	//只保留  
	for (int r = 0; r < bgr.rows; r++)
	{
		for (int c = 0; c < bgr.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255)
			{
				dst.at<Vec3b>(r, c)[0] = bgr.at<Vec3b>(r, c)[0];
				dst.at<Vec3b>(r, c)[1] = bgr.at<Vec3b>(r, c)[1];
				dst.at<Vec3b>(r, c)[2] = bgr.at<Vec3b>(r, c)[2];
			}
		}
	}
	imshow("mask", mask);
	//输出图像  
	imshow("dst", dst);
}
int main1()
{
	//输入图像  
	Mat srcImage = imread("C:\\Users\\Administrator\\Desktop\\0001.jpg");
	if (!srcImage.data){
		cout << "falied to read" << endl;
		system("pause");
		return -1;
	}
	imshow(windowName, srcImage);
	bgr = srcImage;
	//颜色空间转换  
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	//定义输出图像的显示窗口  
	namedWindow(dstName, CV_WINDOW_AUTOSIZE);
	//调节色相 H  
	createTrackbar("hmin", dstName, &hmin, h_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, h_Max, callBack);
	//调节饱和度 S  
	createTrackbar("smin", dstName, &smin, s_Max, callBack);
	createTrackbar("smax", dstName, &smax, s_Max, callBack);
	//调节亮度 V  
	createTrackbar("vmin", dstName, &vmin, v_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, v_Max, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}
