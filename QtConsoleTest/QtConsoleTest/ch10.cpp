#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void ch10::color_inverse()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0];
			p2[1] = 255 - p1[1];
			p2[2] = 255 - p1[2];
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch10::color_grayscale()
{
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch10::color_split()
{
	Mat src = imread("candies.png");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_planes", bgr_planes[0]);
	imshow("G_Planes", bgr_planes[1]);
	imshow("R_Planes", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}

void ch10::color_eq()
{
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);

	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

void ch10::in_range()
{
	s_src = imread("candies.png", IMREAD_COLOR);

	if (s_src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	cvtColor(s_src, s_srcHsv, COLOR_BGR2HSV);

	imshow("src", s_src);

	namedWindow("mask");
	createTrackbar("Lower Hue", "mask", &s_lowerHue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &s_upperHue, 179, on_hue_changed);
	on_hue_changed(0, 0);

	waitKey();
	return;
}