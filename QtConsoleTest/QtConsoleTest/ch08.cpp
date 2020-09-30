#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void ch08::AffineTransform()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch08::AffineTranslation()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat M = Mat_<double>({ 2,3 }, { 1, 0, 150, 0, 1, 100 });
	
	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch08::AffineShear()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	double mx = 0.3;
	Mat M = Mat_<double>({ 2, 3 }, { 1, mx, 0, 0, 1, 0 });

	Mat dst;
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch08::AffinePoint()
{
	vector<Point2f> src = { Point2f(100,20), Point2f(200, 50) };
	vector<Point2f> dst;
	Mat M = Mat_<double>({ 2,3 }, { 1, 0, 150, 0, 1, 100 });

	transform(src, dst, M);

	cout << dst << endl;
}

void ch08::AffineScale()
{
	Mat src = imread("rose.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	resize(src, dst2, Size(1920, 1280));
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400)));
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();
	destroyAllWindows();
}

void ch08::AffineRotation()
{
	Mat src = imread("tekapo.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows /  2.f);
	Mat M = getRotationMatrix2D(cp, 20, 1);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch08::AffineFlip()
{
	Mat src = imread("eastsea.bmp");

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	int flipcode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++)
	{
		flip(src, dst, flipcode[i]);

		String desc = format("flipCode: %d", flipcode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
		destroyAllWindows();
	}
}

void ch08::Perspective()
{
	cnt = 0;
	s_src = imread("card.bmp");

	if (s_src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	namedWindow("s_src");
	setMouseCallback("s_src", On_mouse2);

	imshow("s_src", s_src);
	waitKey();

	return;
}