#include <gtk/gtk.h>
#include <iterator>
#include <string>
#include <sstream>
#include <algorithm>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include<dlib/opencv/cv_image_abstract.h>
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<vector>
#include<opencv2/photo.hpp>
#include<opencv2/photo.hpp>
#include <fstream>
using namespace cv;
using namespace dlib;
using namespace std;

std::vector<string> &split(const string &str, char delim, std::vector<string> &elems, bool skip_empty = true) {
	istringstream iss(str);
	for (string item; getline(iss, item, delim);)
		if (skip_empty && item.empty()) continue;
		else elems.push_back(item);
		return elems;
}
char* select_file()
{
	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new("SelectFile", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		return filename;
	}
	gtk_widget_destroy(dialog);
}

// 定义直线参数结构体
struct LinePara
{
	float k;
	float b;

};

// 获取直线参数
void getLinePara(float& x1, float& y1, float& x2, float& y2, LinePara & LP)
{
	int m = 0;

	// 计算分子
	m = x2 - x1;

	if (0 == m)
	{
		LP.k = 10000.0;
		LP.b = y1 - LP.k * x1;
	}
	else
	{
		LP.k = (y2 - y1) / (x2 - x1);
		LP.b = y1 - LP.k * x1;
	}


}

// 获取交点
bool getCross(float & x1, float &y1, float & x2, float & y2, float & x3, float &y3, float & x4, float & y4, Point2f & pt){

	LinePara para1, para2;
	getLinePara(x1, y1, x2, y2, para1);
	getLinePara(x3, y3, x4, y4, para2);

	// 判断是否平行
	if (abs(para1.k - para2.k) > 0.5)
	{
		pt.x = (para2.b - para1.b) / (para1.k - para2.k);
		pt.y = para1.k * pt.x + para1.b;

		return true;

	}
	else
	{
		return false;
	}

}

struct correspondens{
	std::vector<int> index;
};



/*
//用dlib检测人脸特征点
*/
void faceLandmarkDetection(dlib::array2d<unsigned char>& img, shape_predictor sp, std::vector<Point2f>& landmark)
{
	dlib::frontal_face_detector detector = get_frontal_face_detector();

	std::vector<dlib::rectangle> dets = detector(img);

	full_object_detection shape = sp(img, dets[0]);
	//cout << "特征点检测完毕" << endl;
	for (int i = 0; i < shape.num_parts(); ++i)
	{
		float x = shape.part(i).x();
		float y = shape.part(i).y();
		landmark.push_back(Point2f(x, y));
	}

	cout << "特征点检测完毕" << endl;
}








// Apply affine transform calculated using srcTri and dstTri to src
void applyAffineTransform(Mat &warpImage, Mat &src, std::vector<Point2f> &srcTri, std::vector<Point2f> &dstTri)
{
	// Given a pair of triangles, find the affine transform.
	Mat warpMat = getAffineTransform(srcTri, dstTri);

	// Apply the Affine Transform just found to the src image
	warpAffine(src, warpImage, warpMat, warpImage.size(), cv::INTER_LINEAR, BORDER_REFLECT_101);
}




/*
//morp a triangle in the one image to another image.
*/


void warpTriangle(Mat &img1, Mat &img2, std::vector<Point2f> &t1, std::vector<Point2f> &t2)
{

	Rect r1 = boundingRect(t1);
	Rect r2 = boundingRect(t2);

	// Offset points by left top corner of the respective rectangles
	std::vector<Point2f> t1Rect, t2Rect;
	std::vector<Point> t2RectInt;
	for (int i = 0; i < 3; i++)
	{

		t1Rect.push_back(Point2f(t1[i].x - r1.x, t1[i].y - r1.y));
		t2Rect.push_back(Point2f(t2[i].x - r2.x, t2[i].y - r2.y));
		t2RectInt.push_back(Point(t2[i].x - r2.x, t2[i].y - r2.y)); // for fillConvexPoly
	}

	// Get mask by filling triangle
	Mat mask = Mat::zeros(r2.height, r2.width, CV_32FC3);//制作一个mask
	fillConvexPoly(mask, t2RectInt, Scalar(1.0, 1.0, 1.0), 16, 0);

	// Apply warpImage to small rectangular patches
	Mat img1Rect;
	img1(r1).copyTo(img1Rect);//将img1三角形所在的方形复制到img1Rect

	Mat img2Rect = Mat::zeros(r2.height, r2.width, img1Rect.type());

	applyAffineTransform(img2Rect, img1Rect, t1Rect, t2Rect);//将img1Rect仿射到img2Rect

	multiply(img2Rect, mask, img2Rect); //将img2三角形所在的方形复制到img2Rect
	multiply(img2(r2), Scalar(1.0, 1.0, 1.0) - mask, img2(r2));
	img2(r2) = img2(r2) + img2Rect;

}

/*********************************************************************************************************/
//图片旋转操作
void imrotate(Mat& img, Mat& newIm, double angle){
	int len = max(img.cols, img.rows);
	Point2f pt(len / 2., len / 2.);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(img, newIm, r, Size(len, len));

}
/**************************************************************************************************************/
//求两个向量的夹角

float AngleBetween(Point2f vector1, Point2f vector2)
{
	float theta = atan2(vector1.x, vector1.y) - atan2(vector2.x, vector2.y);
	if (theta > CV_PI)
		theta -= 2 * CV_PI;
	if (theta < -CV_PI)
		theta += 2 * CV_PI;

	theta = theta * 180.0 / CV_PI;
	return theta;
}
/************************************************************************************************************/









int main()
{

	ifstream myfile("names.txt");
	string temp;
	if (!myfile.is_open())
	{
			cout << "未成功打开文件" << endl;
	}
	getline(myfile,temp);
	// cout<<temp<<endl;
	myfile.close();
	cout<<temp<<endl;
	std::vector<string> result0;
  split(temp, ' ', result0);
	int hh=0;
	while(hh<4)
	{
		cout<<result0[hh]<<endl;
		++hh;
	}

		// VideoCapture  capture(0);
		// Mat frame;
		// if (!capture.isOpened())
		// {
		// 	cout << "摄像头打开失败！" << endl;
		// 	return -1;
		// }
		// char key;
		int Num = 0;
		//
		//
		int count = 0;
		/*namedWindow("【视频】", 1);
		namedWindow("【图片】", 1);*/
		// while (1)
		// {
		// 	string filename = "../photos/" + to_string(Num) + ".jpg";
		// 	key = waitKey(50);
		// 	capture >> frame;
		// 	imshow("【请摆出造型！】", frame);
		//
		// 	if (key == 27)
		// 		break;//按ESC键退出程序
		// 	if (key == 32)//按空格键进行拍照
		// 	{
		// 		cout << "拍照成功！" << endl;
		// 		imwrite(filename, frame);//图片保存到本工程目录中
		// 		imshow("【已经获取的造型】", frame);
		//
		// 		// Num++;
		// 	}// while (1)
		// {
		// 	string filename = "../photos/" + to_string(Num) + ".jpg";
		// 	key = waitKey(50);
		// 	capture >> frame;
		// 	imshow("【请摆出造型！】", frame);
		//
		// 	if (key == 27)
		// 		break;//按ESC键退出程序
		// 	if (key == 32)//按空格键进行拍照
		// 	{
		// 		cout << "拍照成功！" << endl;
		// 		imwrite(filename, frame);//图片保存到本工程目录中
		// 		imshow("【已经获取的造型】", frame);
		//
		// 		// Num++;
		// 	}
		// }
		// }

	shape_predictor sp;
	deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
	cout << "加载模型完毕" << endl;
	string Str1, Str2;
	int flag = 0;
	// cout << "请输入模特图像:" << endl;
	// cin >> Str2;
	// Str2 = select_file();
	// std::vector<string> result0;
	// std::vector<string> result1;
	// split(Str2, '/', result0);  选择文件
	// string middle_name = result0[result0.size() - 1];
	// split(middle_name, '.', result1);
	// Str2 = result1[0];
	// cout << Str2 << endl;
	string modphotos[5];
	modphotos[0]="刘德华";
	modphotos[1]="克林顿";
	modphotos[2]="黄渤";
  int cishu=0;
	while(cishu<4)
	{

		cout<<"finished"<<endl;
		Str2=result0[cishu];
	string Imgname1, Imgname2;
	// Imgname1 = "../photos/" + to_string(--Num) + ".jpg";
	// string n="init";
	// Imgname1 = "../photos/" + to_string(Num) + ".jpg";
	Imgname1 = "../photos/init.jpg";
	Str1="my";
	Imgname2 = "../photos/" + Str2 + ".jpg";
		//----------------- step 1. load the input two images. ----------------------------------
		dlib::array2d<unsigned char> imgDlib1, imgDlib2, imgDlib_;
		dlib::load_image(imgDlib1, Imgname1);
		dlib::load_image(imgDlib2, Imgname2);

		Mat imgCV1 = imread(Imgname1);
		Mat imgCV2 = imread(Imgname2);
		if (!imgCV1.data || !imgCV2.data)
		{
			printf("No image data \n");
			return -1;
		}
		else
			cout << "image readed by opencv" << endl;




		//---------------------- step 2. detect face landmarks -----------------------------------
		//对图片做旋转缩放
		std::vector<Point2f> points1, points2, points,pre_points2;
		ifstream fin;
		faceLandmarkDetection(imgDlib1, sp, points1);
		faceLandmarkDetection(imgDlib2, sp, points2);

		Point2f vector1, vector2;
		vector1 = points1[42] - points1[39];
		vector2 = points2[42] - points2[39];
		imrotate(imgCV1, imgCV1, AngleBetween(vector2, vector1));

		float num_, num_1, times1, times2;
		num_ = sqrt(pow((points2[16] - points2[0]).x, 2) + pow((points2[16] - points2[0]).y, 2));
		num_1 = sqrt(pow((points1[16] - points1[0]).x, 2) + pow((points1[16] - points1[0]).y, 2));
		times1 = num_ / num_1;
		num_ = sqrt(pow((points2[57] - points2[27]).x, 2) + pow((points2[57] - points2[27]).y, 2));
		num_1 = sqrt(pow((points1[57] - points1[27]).x, 2) + pow((points1[57] - points1[27]).y, 2));
		times2 = num_ / num_1;
		float a, b;
		a = imgCV1.cols*times1;
		b = imgCV1.rows*times1;
		resize(imgCV1, imgCV1, Size(a, b), 0, 0, CV_INTER_LINEAR);



		//对旋转后的图像imgCV1检测特征点
		string imgCV1_filename = "../photos/" + Str2 + "_.jpg";
		imwrite(imgCV1_filename, imgCV1);
		dlib::load_image(imgDlib_, imgCV1_filename);
		points1.clear();
		faceLandmarkDetection(imgDlib_, sp, points1);
		points = points1;

		//增加points2和points的特征点
		float Num_temp=1.2;
		float Num1x, Num1y, Num2x, Num2y;
		Num1x = points[17].x - Num_temp*(points[37].x - points[19].x);
		Num1y = points[17].y - Num_temp* (points[37].y - points[19].y);
		Num2x = points[26].x - Num_temp*(points[44].x - points[24].x);
		Num2y = points[26].y - Num_temp*(points[44].y - points[24].y);
		points.push_back((points[17] + points[26]) / 2.0);
		points.push_back(Point2f(Num1x, Num1y));
		points.push_back(Point2f(Num2x, Num2y));
		Num1x = points2[17].x - Num_temp*(points2[37].x - points2[19].x);
		Num1y = points2[17].y - Num_temp*(points2[37].y - points2[19].y);
		Num2x = points2[26].x - Num_temp*(points2[44].x - points2[24].x);
		Num2y = points2[26].y - Num_temp*(points2[44].y - points2[24].y);
		points2.push_back((points2[17] + points2[26]) / 2.0);
		points2.push_back(Point2f(Num1x, Num1y));
		points2.push_back(Point2f(Num2x, Num2y));
		points2.push_back(Point2f(0, 0));
		points2.push_back(Point2f(imgCV2.cols - 1, 0));
		points2.push_back(Point2f(imgCV2.cols - 1, imgCV2.rows - 1));
		points2.push_back(Point2f(0, imgCV2.rows-1));


		pre_points2 = points2;
		Mat temp_out = imgCV2.clone();
		temp_out.convertTo(temp_out, CV_32F);
		imgCV2.convertTo(imgCV2,CV_32F);
		for (int i = 1; i <= 16; i++)
		{
			points2[i] = points2[0] + (points1[i] - points1[0]);
		}
		/*for (int i = 0; i < points2.size(); i++) {
			circle(imgCV2, cvPoint(points2[i].x, points2[i].y), 2, cv::Scalar(0, 0, 255), -1);
		}*/



		fin.open("不变脸型_tri.txt");
		int x1, y1, z1;
		while (fin >> x1 >> y1 >> z1)
		{
			std::vector<Point2f> t1, t2;

			t1.push_back(pre_points2[x1]);
			t2.push_back(points2[x1]);

			t1.push_back(pre_points2[y1]);
			t2.push_back(points2[y1]);

			t1.push_back(pre_points2[z1]);
			t2.push_back(points2[z1]);

			warpTriangle(temp_out,imgCV2 , t1, t2);//将imgCV2变换到以temp_out为底的图片
		}

		fin.close();
		// imshow(" ", imgCV2 / 255.0);
		// waitKey();
		//---------------------step 3. find convex hull -------------------------------------------
		Mat imgCV1Warped = imgCV2.clone();//复制imgCV2
		imgCV1.convertTo(imgCV1, CV_32F);




		//-----------------------step 4.  triangulation -------------------------------------




		fin.open("tri2.txt");
		int x, y, z;
		while (fin >> x >> y >> z)
		{
			std::vector<Point2f> t1, t2;

			t1.push_back(points[x]);
			t2.push_back(points2[x]);

			t1.push_back(points[y]);
			t2.push_back(points2[y]);

			t1.push_back(points[z]);
			t2.push_back(points2[z]);

			warpTriangle(imgCV1, imgCV1Warped, t1, t2);//将imgCV1变换到以imgCV1Warped为底的图片
		}

		fin.close();
		//------------------------step 5. clone seamlessly -----------------------------------------------

		//calculate mask
		std::vector<Point> hull8U;
		hull8U.push_back(points2[0] - (points2[0] - points2[30]) / 20.0);
		hull8U.push_back(points2[4] - (points2[4] - points2[30]) / 20.0);
		hull8U.push_back(points2[8] - (points2[8] - points2[30]) / 20.0);
		hull8U.push_back(points2[12] - (points2[12] - points2[30]) / 20.0);
		hull8U.push_back(points2[16] - (points2[16] - points2[30]) / 20.0);
		hull8U.push_back(points2[70]);
		hull8U.push_back(points2[69]);



		Mat mask = Mat::zeros(imgCV2.size(), CV_8UC3);

		fillConvexPoly(mask, &hull8U[0], hull8U.size(), Scalar(255, 255, 255));

		Rect r = boundingRect(hull8U);
		Point center = (r.tl() + r.br()) / 2;

		Mat output;
		imgCV2.convertTo(imgCV2, CV_8UC3);
		imgCV1Warped.convertTo(imgCV1Warped, CV_8UC3);
		seamlessClone(imgCV1Warped, imgCV2, mask, center, output, NORMAL_CLONE);

		string filename = "../photos/results/" + to_string(cishu) + ".jpg";

		imwrite(filename, output);
		cishu++;
		imshow("换脸_脸型不变", output);

		// waitKey(0);

		// destroyAllWindows();
	}

	return 0;
}
