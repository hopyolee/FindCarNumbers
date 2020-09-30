#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void using_tesseract::find_carnumber()
{
	Mat img = imread("LPTest06.jpg", IMREAD_GRAYSCALE);
	Mat bin;
	char* outText;

	//tesseract 
	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "Hangul")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	//opencv
	for (int i = 0; i < 10; i++)
	{
		if (img.empty()) {
			cerr << "Image load failed" << endl;
			return;
		}
	}

	//이진화 및 열기 연산
	threshold(img, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	//erode(bin2, bin2, Mat());
	morphologyEx(bin, bin, MORPH_OPEN, Mat());

	//roi 설정
	Mat mask(bin.rows, bin.cols, bin.type(), Scalar(0));
	rectangle(mask, Rect(30, 10, bin.cols - 55, bin.rows - 15), 
		Scalar(255), -1);
	Mat ROI_image;
	bitwise_and(bin, mask, ROI_image);

	//이미지 출력
	imshow("img", img);
	imshow("bin", bin);
	imshow("roi", ROI_image);


	//tesseract
	//input image with leptonica library
	api->SetImage((uchar*)ROI_image.data, ROI_image.size().width,
		ROI_image.size().height, ROI_image.channels(), ROI_image.step1());
	// Get OCR result
	outText = api->GetUTF8Text();

	//printf("OCR output:\n%s", outText);
	outText = UTF8ToANSI(outText);
	std::cout << outText << std::endl;

	// Destroy used object and release memory
	api->End();

	delete api;
	delete[] outText;
	//pixDestroy(&image);

	return;
}

void using_tesseract::find_lable()
{
	Mat img = imread("LPTest06.jpg", IMREAD_GRAYSCALE);
	Mat bin1;
	Mat bin2;
	

	//opencv
	for (int i = 0; i < 10; i++)
	{
		if (img.empty()) {
			cerr << "Image load failed" << endl;
			return;
		}
	}

	Canny(img, bin1, 100, 500, 3);	

	vector<vector<Point>> contours;
	findContours(bin1, contours, RETR_LIST, CHAIN_APPROX_NONE);

	//이진화 및 열기 연산
	threshold(img, bin2, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	//erode(bin2, bin2, Mat());
	morphologyEx(bin2, bin2, MORPH_OPEN, Mat());

	cvtColor(img, img, COLOR_GRAY2BGR);

	double theta = 0.0;
	Point dxy1 = contours[0].at(0);
	Point dxy2 = contours[0].at(50);

	int dx1 = dxy1.x;
	int dy1 = dxy1.y;
	int dx2 = dxy2.x;
	int dy2 = dxy2.y;

	double dx = (double)dx2 - (double)dx1;
	double dy = (double)dy2 - (double)dy1;


	theta = atan2(dx, dy);

	Point2f cp(bin1.cols / 2.f, bin1.rows / 2.f);
	Mat M = getRotationMatrix2D(cp, -theta, 1);

	warpAffine(img, img, M, Size());
	warpAffine(bin2, bin2, M, Size());

	findContours(bin2, contours, RETR_LIST, CHAIN_APPROX_NONE);

	for (vector<Point> pts : contours) {
		if ((contourArea(pts) < 150) || (contourArea(pts) > 600))
			continue;

		setLabel(img, pts, Scalar(0, 0, 255));
		cout << contourArea(pts) << endl;
	}

	cout << dx1 <<", " << dy1 << endl;
	cout << dx2 <<", " << dy2 << endl;
	cout << theta << endl;


	//이미지 출력
	imshow("img", img);
	imshow("bin1", bin1);
	imshow("bin2", bin2);
}

void using_tesseract::find_carnumberver2()
{
	Mat img = imread("bmw.jpg", IMREAD_GRAYSCALE);
	Mat bin1, bin2, M, bin3, bin4, bin5;
	vector<vector<Point>> contours1, contours2, contours3;
	vector<Rect> bounding_temp1, bounding_temp2, bounding_temp3, real_bounding;
	Rect temp_rect;
	Point2f cp(bin1.cols / 2.f, bin1.rows / 2.f);
	Point dp[2];
	double ratio, theta = 0.0;
	float radian = 0.0f;
	int count = 0;
	char* outText;

	//tesseract 
	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with Hangul, without specifying tessdata path
	if (api->Init(NULL, "Hangul")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	//opencv
	if (img.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	bin2 = img.clone();
	bin3 = Mat::zeros(img.size(), CV_8UC3);
	
	//회전각 임의 변경
	//M = getRotationMatrix2D(cp, -3, 1);
	//warpAffine(img, img, M, Size());

	Canny(img, bin1, 100, 500, 3);
	
	findContours(bin1, contours1, RETR_LIST, CHAIN_APPROX_SIMPLE);

	//이진화 및 열기 연산
	//threshold(img, bin2, 0, 255, THRESH_BINARY_INV | THRESH_TRIANGLE);
	adaptiveThreshold(img, bin2, 255, ADAPTIVE_THRESH_GAUSSIAN_C,
		THRESH_BINARY_INV, 51, 0);

	//morphologyEx(bin2, bin2, MORPH_OPEN, Mat());
	//dilate(bin2, bin2, Mat());
	//erode(bin2, bin2, Mat());

	cvtColor(img, img, COLOR_GRAY2BGR);

	for (int i = 0; i < contours1.size(); i++) {
		if ((contourArea(contours1[i]) < 100) || (contourArea(contours1[i]) > 700))
			continue;

		setLabel(img, contours1[i], Scalar(0, 255, 255));
		contours2.push_back(contours1[i]);	
	}

	vector<Rect> bounding_rect1(contours2.size());

	for (int i = 0; i < contours2.size(); i++) {
		bounding_rect1[i] = boundingRect(contours2[i]);
	}

	for (int i = 0; i < bounding_rect1.size(); i++) {
		ratio = ((double)bounding_rect1[i].height / (double)bounding_rect1[i].width);
		if ((ratio < 3.5) && (ratio > 1.2)){
			rectangle(img, bounding_rect1[i], Scalar(255, 0, 0));
			bounding_temp1.push_back(bounding_rect1[i]);
			contours3.push_back(contours2[i]);			
		}
	}
	
	for (int i = 0; i < bounding_temp1.size(); i++) {
		for (int j = 0; j < (bounding_temp1.size() - i - 1); j++) {
			if (bounding_temp1[j].x > bounding_temp1[j + 1].x) {
				temp_rect = bounding_temp1[j];
				bounding_temp1[j] = bounding_temp1[j + 1];
				bounding_temp1[j + 1] = temp_rect;
			}
		}
	}

	for (int i = 0; i < contours3.size(); i++) {
		drawContours(bin3, contours3, i, Scalar(255, 255, 255));
	}

	cv::imshow("bin1", bin1);

	for (int i = 0; i < bounding_temp1.size(); i++) {
		if (i + 1 > bounding_temp1.size() - 1) {
			bounding_temp2.push_back(bounding_temp1[i]);
		}
		else{
			if (bounding_temp1[i].tl() == bounding_temp1[i + 1].tl()) {
				continue;
			}
			else {
				bounding_temp2.push_back(bounding_temp1[i]);
			}
		}
	}

	for (int i = 0; i < bounding_temp2.size(); i++) {
		if (i + 1 > bounding_temp2.size() - 1) {
			if (bounding_temp2[i].tl().x - bounding_temp2[i - 1].tl().x > 10 &&
				bounding_temp2[i].tl().x - bounding_temp2[i - 1].tl().x < 40 &&
				bounding_temp2[i].tl().y - bounding_temp2[i - 1].tl().y < 10)
				real_bounding.push_back(bounding_temp2[i]);

			else
				break;
		}
		else {
			if (i - 1 > 0) {
				if ((bounding_temp2[i + 1].tl().x - bounding_temp2[i].tl().x > 10 &&
					bounding_temp2[i + 1].tl().x - bounding_temp2[i].tl().x < 40 &&
					bounding_temp2[i + 1].tl().y - bounding_temp2[i].tl().y < 10) ||
					(bounding_temp2[i].tl().x - bounding_temp2[i - 1].tl().x > 10 &&
						bounding_temp2[i].tl().x - bounding_temp2[i - 1].tl().x < 40 &&
						bounding_temp2[i].tl().y - bounding_temp2[i - 1].tl().y < 10)) {
					real_bounding.push_back(bounding_temp2[i]);
				}
				else {
					if (bounding_temp2[i].tl().x - bounding_temp2[i - 1].tl().x > 10 &&
						bounding_temp2[i].tl().x - bounding_temp2[i - 1].tl().x < 40 &&
						bounding_temp2[i].tl().y - bounding_temp2[i - 1].tl().y < 10)
						real_bounding.push_back(bounding_temp2[i]);
				}
			}
			else {
				if (bounding_temp2[i + 1].tl().x - bounding_temp2[i].tl().x > 10 &&
					bounding_temp2[i + 1].tl().x - bounding_temp2[i].tl().x < 40 &&
					bounding_temp2[i + 1].tl().y - bounding_temp2[i].tl().y < 10) {
					real_bounding.push_back(bounding_temp2[i]);
				}
			}
		}
	}

	

	dp[0] = real_bounding[0].tl();
	dp[1] = real_bounding[real_bounding.size() - 1].tl();

	//zero-base를 원점 기준으로 변환

	int dx1 = dp[0].x;
	int dy1 = -dp[0].y;
	int dx2 = dp[1].x;
	int dy2 = -dp[1].y;

	double dx = (double)dx2 - (double)dx1;
	double dy = (double)dy2 - (double)dy1;

	
	drawMarker(img, dp[0], Scalar(0, 0, 255));
	drawMarker(img, dp[1], Scalar(0, 0, 255));
	drawMarker(img, real_bounding[real_bounding.size() - 1].br(),
		Scalar(0, 0, 255));
	
	radian = atan2(dy, dx);
	theta = radian * (180 / 3.141592);

	M = getRotationMatrix2D(cp, -theta, 1);

	Mat mask(bin2.rows, bin2.cols, bin2.type(), Scalar(0));

	warpAffine(img, img, M, Size());
	warpAffine(bin2, bin2, M, Size());
	
	//roi 설정 좌표 cp 기준점을 원점으로 회전변환 식 (좌표축의 회전이동)
	float x1 = real_bounding[0].tl().x;
	float y1 = real_bounding[0].tl().y;
	float x2 = real_bounding[real_bounding.size() - 1].br().x;
	float y2 = real_bounding[real_bounding.size() - 1].br().y;

	float rx1 = ((x1-cp.x) * cos(-radian)) + ((y1-cp.y) * sin(-radian));
	float ry1 = -((x1-cp.x) * sin(-radian)) + ((y1-cp.y) * cos(-radian));
	float rx2 = ((x2-cp.x) * cos(-radian)) + ((y2-cp.y) * sin(-radian));
	float ry2 = -((x2-cp.x) * sin(-radian)) + ((y2-cp.y) * cos(-radian));

	rectangle(mask, Point(rx1, ry1), Point(rx2, ry2), Scalar(255), -1);

	Mat ROI_image;
	
	bitwise_and(bin2, mask, ROI_image);
	bitwise_not(ROI_image, ROI_image);

	//Roi tl, br 위치 표시
	//drawMarker(ROI_image, Point(rx1, ry1), Scalar(0));
	//drawMarker(ROI_image, Point(rx2, ry2), Scalar(0));

	

	//tesseract
	//input image with leptonica library
	api->SetImage((uchar*)ROI_image.data, ROI_image.size().width,
		ROI_image.size().height, ROI_image.channels(), ROI_image.step1());
	// Get OCR result
	outText = api->GetUTF8Text();

	outText = UTF8ToANSI(outText);
	cout << "차량번호: " << outText << endl;
	cout << "dxy1좌표 : " << Point(bounding_temp1[1].tl()) << endl;
	cout << "dxy2좌표 : " << Point(bounding_temp1[bounding_temp1.size()-3].tl()) << endl;
	cout << "theta: " << theta << endl;
	cout << "rxy1좌표 : " << Point(rx1, ry1) << endl;
	for (int i = 0; i < bounding_temp1.size(); i++) {
		cout << "temp1의" << i << ": " << 
			Point(bounding_temp1[i].tl()) <<", " << 
			Point(bounding_temp1[i].br()) << endl;
	} 

	for (int i = 0; i < bounding_temp2.size(); i++) {
		cout << "temp2의" << i << ": " <<
			Point(bounding_temp2[i].tl()) << ", " <<
			Point(bounding_temp2[i].br()) << endl;
	}

	for (int i = 0; i < real_bounding.size(); i++) {
		cout << "real의" << i << ": " <<
			Point(real_bounding[i].tl()) << ", " <<
			Point(real_bounding[i].br()) << endl;
		drawMarker(bin3, real_bounding[i].tl(),
			Scalar(0, 128, 255));
		drawMarker(bin3, real_bounding[i].br(),
			Scalar(0, 0, 255));
	}
	cout << "대각선길이 : " <<
		sqrt(pow(real_bounding[real_bounding.size() - 1].tl().x -
			real_bounding[real_bounding.size() - 1].br().x, 2) +
			pow(real_bounding[real_bounding.size() - 1].tl().y -
				real_bounding[real_bounding.size() - 1].br().y, 2)) <<endl;
	//이미지 출력
	imshow("img", img);
	imshow("bin1", bin1);
	imshow("roi", ROI_image);
	imshow("bin3", bin3);
	//imshow("bin5", bin5);

	// Destroy used object and release memory
	api->End();
	delete api;
	delete[] outText;

	return;
}