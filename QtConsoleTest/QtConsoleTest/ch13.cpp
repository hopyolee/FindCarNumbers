#include "QtConsoleTest.h"
#include "staticFunction.cpp"

void ch13::template_matching()
{
	Mat img = imread("LPTest03.jpg", IMREAD_GRAYSCALE);
	Mat* templ = new Mat[10];
	Mat* res = new Mat[10];
	carnumber* test1 = new carnumber;
	int numloc_num = 0;
	int lastnum = 0;
	Mat bin;

	//opencv
	String paths[10] = {
		"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg0.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg1.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg2.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg3.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg4.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg5.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg6.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg7.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg8.jpg", 
	"C:\\Users\\henry\\source\\repos\\QtConsoleTest\\QtConsoleTest\\templateImg\\templateimg9.jpg", };

	for (int i = 0; i < 10; i++)
	{
		templ[i] = imread(paths[i], IMREAD_GRAYSCALE);
	}

	for (int i = 0; i < 10; i++)
	{
		if (img.empty() || templ[i].empty()) {
			cerr << "Image load failed" << endl;
			return;
		}
	}
	
	//이진화 및 열기 연산
	threshold(img, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	for (int i = 0; i < 10; i++) {
		threshold(templ[i], templ[i], 0, 255, THRESH_BINARY | THRESH_OTSU);
	}

	morphologyEx(bin, bin, MORPH_OPEN, Mat());

	for (int i = 0; i < 10; i++) {
		morphologyEx(templ[i], templ[i], MORPH_OPEN, Mat());
	}

	Point2f cp(bin.cols / 2.f, bin.rows / 2.f);
	Mat M = getRotationMatrix2D(cp, -1, 1);

	warpAffine(bin, bin, M, Size());
	
	//템플릿 매칭 및 숫자별 유사도 설정
	for (int i = 0; i < 10; i++) {
		matchTemplate(bin, templ[i], res[i], TM_CCOEFF_NORMED);

		for (int m = 0; m < res[i].rows; m++) {
			for (int n = 0; n < res[i].cols; n++) {
				if (res[i].at<float>(m, n) > 0.85) {

					if (i == 0) {
						if (res[i].at<float>(m, n) > 0.95) {
							float a = res[i].at<float>(m, n);
							cout << "highv: " << a << endl;
							cout << i << endl;
							test1->numloc[numloc_num].x = n;
							test1->numloc[numloc_num].y = m;
							test1->number[lastnum] = i;
							lastnum++;
							numloc_num++;
						}
					}

					else if (i == 1) {
						if (res[i].at<float>(m, n) > 0.99) {
							float a = res[i].at<float>(m, n);
							cout << "highv: " << a << endl;
							cout << i << endl;
							test1->numloc[numloc_num].x = n;
							test1->numloc[numloc_num].y = m;
							test1->number[lastnum] = i;
							lastnum++;
							numloc_num++;
						}
					}

					else if (i == 4) {
						if (res[i].at<float>(m, n) > 0.90) {
							float a = res[i].at<float>(m, n);
							cout << "highv: " << a << endl;
							cout << i << endl;
							test1->numloc[numloc_num].x = n;
							test1->numloc[numloc_num].y = m;
							test1->number[lastnum] = i;
							lastnum++;
							numloc_num++;
						}
					}

					else {
						float a = res[i].at<float>(m, n);
						cout << "highv: " << a << endl;
						cout << i << endl;
						test1->numloc[numloc_num].x = n;
						test1->numloc[numloc_num].y = m;
						test1->number[lastnum] = i;
						lastnum++;
						numloc_num++;
					}
				}
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		rectangle(img, Rect(test1->numloc[i].x, test1->numloc[i].y, templ->cols, templ->rows),
			Scalar(0, 0, 255), 2);
	}

	//버블정렬 번호판 순서대로 
	for (int h = 0; h < 6; h++) {
		for (int i = 0; i < 6 - h - 1; i++) {
			if (test1->numloc[i].x > test1->numloc[i + 1].x) {
				test1->temploc.x = test1->numloc[i].x;
				test1->temp = test1->number[i];
				test1->numloc[i].x = test1->numloc[i + 1].x;
				test1->number[i] = test1->number[i + 1];
				test1->numloc[i + 1].x = test1->temploc.x;
				test1->number[i + 1] = test1->temp;
			}
		}
	}

	for (int i = 2; i < 6; i++) {
		cout << test1->number[i];
	}
	
	imshow("img", img);
	imshow("bin", bin);


	delete[] templ, res;
	delete test1;

	return;
}