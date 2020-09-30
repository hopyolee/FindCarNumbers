#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void ch04::UsefulFunc()
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (img.empty())
	{
		cerr << "image load failed" << endl;
		return;
	}

	cout << "Sum : " << (int)sum(img)[0] << endl;
	cout << "Sum[1] : " << (int)sum(img)[1] << endl;
	cout << "Sum[2] : " << (int)sum(img)[2] << endl;
	cout << "Sum[3] : " << (int)sum(img)[3] << endl;
	cout << "Mean : " << (int)mean(img)[0] << endl;

	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal : " << minVal << " at" << minPos << endl;
	cout << "maxVal : " << maxVal << " at" << maxPos << endl;

	Mat src = Mat_<float>({ 1, 5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });
	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);

	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;

	cout << "cvRound(2.5) " << cvRound(2.5) << endl;
	cout << "cvRound(2.51) " << cvRound(2.51) << endl;
}

void ch04::TimeInverse()
{
	Mat src = imread("C:\\Users\\henry\\OneDrive\\Documents\\My Documents\\STUDY\\OpenCV\\Computer_Vision_and_Machine_Learning_With_OpenCV4\\ch04\\utils\\lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());
	TickMeter tm;
	tm.start();

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}
	tm.stop();
	cout << "Image inverse took " << tm.getTimeMilli() << "ms" << endl;
}

void ch04::MaskCopyTo()
{
	Mat src = imread("C:\\Users\\henry\\OneDrive\\Documents\\My Documents\\STUDY\\OpenCV\\Computer_Vision_and_Machine_Learning_With_OpenCV4\\ch04\\utils\\airplane.bmp");
	Mat mask = imread("C:\\Users\\henry\\OneDrive\\Documents\\My Documents\\STUDY\\OpenCV\\Computer_Vision_and_Machine_Learning_With_OpenCV4\\ch04\\utils\\mask_plane.bmp");
	Mat dst = imread("C:\\Users\\henry\\OneDrive\\Documents\\My Documents\\STUDY\\OpenCV\\Computer_Vision_and_Machine_Learning_With_OpenCV4\\ch04\\utils\\field.bmp");
	Mat dstorigin = dst.clone();

	if (src.empty() || mask.empty() || dst.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("dstorigin", dstorigin);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void ch04::MaskSetTo()
{
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("C:\\Users\\henry\\OneDrive\\Documents\\My Documents\\STUDY\\OpenCV\\Computer_Vision_and_Machine_Learning_With_OpenCV4\\ch04\\utils\\mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void ch04::ReadData()
{
	FileStorage fs(filename, FileStorage::READ);

	if (!fs.isOpened())
	{
		cerr << "File open failed" << endl;
		return;
	}

	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();

	cout << "name" << name << endl;
	cout << "age" << age << endl;
	cout << "point" << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;
	cout << "data:\n" << mat1 << endl;
}

void ch04::WriteData()
{
	FileStorage fs(filename, FileStorage::WRITE);

	if (!fs.isOpened())
	{
		cerr << "File open failed" << endl;
		return;
	}

	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;

	fs.release();
}

void ch04::Trackbar()
{
	Mat img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");
	createTrackbar("level", "image", 0, 16, On_level_change, (void*)&img);
	imshow("image", img);
	waitKey();

	return;
}

void ch04::Mouse()
{
	img = imread("lenna.bmp");

	if (img.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	namedWindow("img");
	setMouseCallback("img", On_mouse1);

	imshow("img", img);
	waitKey();

	return;
}

void ch04::KeyBorad()
{
	Mat img = imread("lenna.bmp");

	if (img.empty())
	{
		cerr << "Image load failed" << endl;
		return;
	}

	namedWindow("img");
	imshow("img", img);

	while (true)
	{
		int keycode = waitKey();

		if (keycode == 'i' || keycode == 'I')
		{
			img = ~img;
			imshow("img", img);
		}

		else if (keycode == 27 || keycode == 'q' || keycode == 'Q')
		{
			break;
		}
	}

	destroyWindow("img");

	return;
}

void ch04::DrawText2()
{
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();

	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(255, 0, 0), 1);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void ch04::DrawText1()
{
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));

	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 150), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));

	imshow("img", img);
	waitKey();

	destroyAllWindows();

}

void ch04::DrawPolys()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);

	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);

	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), -1, LINE_AA);
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	vector<Point> pts;
	pts.push_back((Point(250, 250))); pts.push_back((Point(300, 250)));
	pts.push_back((Point(300, 300))); pts.push_back((Point(350, 300)));
	pts.push_back((Point(350, 350))); pts.push_back((Point(250, 350)));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void ch04::Drawlines()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(0, 0, 255), 1, LINE_8, 0, 0.05);

	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

void ch04::Carmera_in_video_out()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cerr << "Camera open failed" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cvRound(cap.get(CAP_PROP_FPS));

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened())
	{
		cout << "File open failed" << endl;
		return;
	}

	Mat frame, inversed;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		outputVideo << inversed;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
}

void ch04::Video_in()
{
	VideoCapture cap("C:\\Users\\henry\\OneDrive\\Documents\\My Documents\\STUDY\\OpenCV\\Computer_Vision_and_Machine_Learning_With_OpenCV4\\ch04\\video\\stopwatch.avi");

	if (!cap.isOpened())
	{
		cerr << "Video open failed" << endl;
		return;
	}

	cout << "Frame Width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	cout << "Frame Height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	cout << "Frame count : " << cvRound(CAP_PROP_FRAME_COUNT);

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS : " << fps << endl;

	int delay = cvRound(1000 / fps);

	Mat frame, inversed;

	while (true)
	{
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}

	destroyAllWindows();
}

void ch04::Carmera_in()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width :" << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height :" << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;

	while (true)
	{
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();
}