#pragma once
#include<QtCore/QCoreApplication>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<QDebug>
#include<tesseract/baseapi.h>
#include<leptonica/allheaders.h>
#include<wtypes.h>
#include<OleAuto.h>

using namespace std;
using namespace cv;

static String filename = "mydata.json";
static Mat img;
static Point ptOld;
static void On_mouse1(int event, int x, int y, int flag, void*);
static void On_mouse2(int event, int x, int y, int flags, void* userdata);
static void On_level_change(int pos, void* userdata);
static void OnBrightness(int pos, void* userdata);
static void on_hue_changed(int, void*);
static void on_theshold(int pos, void* userdata);
static void on_trackbar(int pos, void* userdata);
static char* UTF8ToANSI(char* pszCode);
static void setLabel(Mat img, vector<Point> pts, Scalar color);
static Point theta_point(vector<Point> pts);
static String name = "Jane";
static int age = 10;
static Point pt1(100, 200);
static vector<int> scores = { 80, 90, 50 };
static Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);
static int cnt, s_lowerHue = 40, s_upperHue = 80;
static Mat s_src, s_srcHsv, s_mask;
static Point2f srcQuad[4], dstQuad[4];

class ch03
{
public:
	void virtual MatOp1();
	void virtual MatOp2();
	void virtual MatOp3();
	void virtual MatOp4();
	void virtual MatOp5();
	void virtual MatOp6();
	void virtual MatOp7();
};

class ch04
{
public:
	void virtual Carmera_in();
	void virtual Video_in();
	void virtual Carmera_in_video_out();
	void virtual Drawlines();
	void virtual DrawPolys();
	void virtual DrawText1();
	void virtual DrawText2();
	void virtual KeyBorad();
	void virtual Mouse();
	void virtual Trackbar();
	void virtual WriteData();
	void virtual ReadData();
	void virtual MaskSetTo();
	void virtual MaskCopyTo();
	void virtual TimeInverse();
	void virtual UsefulFunc();
};

class ch05
{
public:
	void virtual Brightness();
	void virtual Brightness1();
	void virtual Brightness2();
	void virtual Brightness4();

	void virtual Contrast1();
	void virtual Contrast2();

	Mat virtual CalcGrayHist(const Mat&img);
	Mat virtual GetGrayHistImage(const Mat& hist);
	void virtual HistogramStretching();
};

class ch06
{
public:
	void virtual Arithmetic();
	void virtual Logical();
};

class ch07
{
public:
	void virtual FilterEmbossing();
	void virtual BlurringMean();
	void virtual BlurringGaussian();
	void virtual UnsharpMask();
	void virtual NoiseGaussian();
	void virtual FilterBilateral();
	void virtual FilterMedian();
};

class ch08
{
public:
	void virtual AffineTransform();
	void virtual AffineTranslation();
	void virtual AffineShear();
	void virtual AffinePoint();
	void virtual AffineScale();
	void virtual AffineRotation();
	void virtual AffineFlip();
	void virtual Perspective();
};

class ch09
{
public:
	void virtual Edges();
	void virtual CannyEdge();
	void virtual HoughLines1();
	void virtual hough_line_segments();
	void virtual hough_circles();
};

class ch10
{
public :
	void virtual color_inverse();
	void virtual color_grayscale();
	void virtual color_split();
	void virtual color_eq();
	void virtual in_range();
};

class ch11
{
public :
	void virtual threshold(int argc, char** argv);
	void virtual adaptive();
	void virtual erode_dilatte();
	void virtual open_close();
};

class ch13
{
public :
	void virtual template_matching();


private :
	struct carnumber
	{
		int number[7] = { 0, };
		int temp = 0;
		Point temploc;
		Point numloc[7] = { 0, };

	};

};

class using_tesseract
{
public :
	void virtual find_carnumber();
	void virtual find_lable();
	void virtual find_carnumberver2();
};