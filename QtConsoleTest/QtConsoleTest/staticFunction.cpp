#include "QtConsoleTest.h"

void OnBrightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}

void On_level_change(int pos, void* userdata)
{
	Mat img = *(Mat*)userdata;

	img.setTo(pos * 16 < 255 ? 255 : pos * 16);
	imshow("image", img);
}

void On_mouse1(int event, int x, int y, int flag, void*)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN : " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP : " << x << ", " << y << endl;

		break;
	case EVENT_MOUSEMOVE:
		if (flag & EVENT_FLAG_LBUTTON)
		{
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}

void On_mouse2(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (cnt < 4)
		{
			srcQuad[cnt++] = Point2f(x, y);

			circle(s_src, Point(x, y), 5, Scalar(0, 0, 255), -1);
			imshow("s_src", s_src);

			if (cnt == 4)
			{
				int w = 200, h = 300;

				dstQuad[0] = Point2f(0, 0);
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);

				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				warpPerspective(s_src, dst, pers, Size(w, h));

				imshow("dst", dst);
			}
		}
	}
}

void on_hue_changed(int, void*)
{
	Scalar lowerb(s_lowerHue, 100, 0);
	Scalar upperb(s_upperHue, 255, 255);
	inRange(s_srcHsv, lowerb, upperb, s_mask);

	imshow("mask", s_mask);
}

void on_theshold(int pos, void* userdata)
{
	Mat s_src = *(Mat*)userdata;

	Mat s_dst;
	threshold(s_src, s_dst, pos, 255, THRESH_BINARY);

	imshow("dst", s_dst);
}

void on_trackbar(int pos, void* userdata)
{
	Mat s_src = *(Mat*)userdata;

	int bsize = pos;
	if (bsize % 2 == 0) bsize--;
	if (bsize < 3) bsize = 3;

	Mat dst;
	adaptiveThreshold(s_src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 
		bsize, 5);
	imshow("dst", dst);
}

char* UTF8ToANSI(char* pszCode)
{
	BSTR    bstrWide;
	char* pszAnsi;
	int     nLength;
	// Get nLength of the Wide Char buffer
	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen((wchar_t*)pszCode) + 1,
		NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);
	// Change UTF-8 to Unicode (UTF-16)
	MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen((wchar_t*)pszCode) + 1, bstrWide,
		nLength);
	// Get nLength of the multi byte buffer
	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];
	// Change from unicode to mult byte
	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);
	return pszAnsi;
}

void setLabel(Mat img, vector<Point> pts, Scalar color)
{
	Rect rc = boundingRect(pts);
	rectangle(img, rc, color, 1);
}

Point theta_point(vector<Point> pts)
{
	Rect rc = boundingRect(pts);
	Point p1(rc.x, rc.y);
	return p1;
}