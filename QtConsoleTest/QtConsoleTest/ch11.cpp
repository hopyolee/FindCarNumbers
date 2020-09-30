#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void ch11::threshold(int argc, char** argv)
{
	if (argc < 2)
		s_src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	else
		s_src = imread(argv[1], IMREAD_GRAYSCALE);

	if (s_src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", s_src);

	namedWindow("dst");
	createTrackbar("Threshold", "dst", 0, 255, on_theshold, (void*)&s_src);
	setTrackbarPos("Threshold", "dst", 128);

	waitKey();
	return;
}

void ch11::adaptive()
{
	s_src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	if (s_src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", s_src);

	namedWindow("dst");
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&s_src);
	setTrackbarPos("Block size", "dst", 11);

	waitKey();
	return;
}

void ch11::erode_dilatte()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat bin;
	cv::threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;

	erode(bin, dst1, Mat());
	dilate(bin, dst2, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

void ch11::open_close()
{
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat bin;
	cv::threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}