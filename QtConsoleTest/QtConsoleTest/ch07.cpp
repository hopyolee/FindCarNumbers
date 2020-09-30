#include "QtConsoleTest.h"

void ch07::FilterEmbossing()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch07::BlurringMean()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;

	for (int ksize = 3; ksize <= 7; ksize += 2)
	{
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void ch07::BlurringGaussian()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;

	for (int sigma = 1; sigma <= 5; sigma++)
	{
		GaussianBlur(src, dst, Size(), (double)sigma);

		String text = format("sigma = %d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

void ch07::UnsharpMask()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	for (int sigma = 1; sigma <= 5; sigma++)
	{
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		String desc = format("sigma : %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void ch07::NoiseGaussian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	for (int stddev = 10; stddev <= 30; stddev += 10)
	{
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev : %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	destroyAllWindows();
}

void ch07::FilterBilateral()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();


	imshow("src", src);

}

void ch07::FilterMedian()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	int num = (int)(src.total() * 0.1);

	for (int i = 0; i < num; i++)
	{
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.at<uchar>(y, x) = (i % 2) * 255;
	}

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);

	Mat dst2;
	medianBlur(src, dst2, 3);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}