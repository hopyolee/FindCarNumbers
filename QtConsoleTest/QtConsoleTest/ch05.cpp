#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void ch05::HistogramStretching()
{
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", GetGrayHistImage(CalcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", GetGrayHistImage(CalcGrayHist(dst)));
	waitKey();
	destroyAllWindows();
}

Mat ch05::GetGrayHistImage(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++)
	{
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

Mat ch05::CalcGrayHist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;

	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

void ch05::Contrast1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch05::Contrast2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch05::Brightness4()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, OnBrightness, (void*)&src);
	OnBrightness(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void ch05::Brightness2()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch05::Brightness1()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = src.clone();

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	Mat dst2(src.rows, src2.cols, src2.type());

	for (int j = 0; j < src2.rows; j++)
	{
		for (int i = 0; i < src2.cols; i++)
		{
			int v = src2.at<uchar>(j, i) + 100;
			dst2.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	imshow("dst2", dst2);
	waitKey();
	destroyAllWindows();
}

void ch05::Brightness()
{

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst = src + 100;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}