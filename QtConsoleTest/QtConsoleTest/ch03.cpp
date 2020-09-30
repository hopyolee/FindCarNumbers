#include "QtConsoleTest.h"

void ch03::MatOp7()
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat:\n" << mat1 << endl;
	cout << "mat:\n" << mat2 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << "mat1:\n" << mat1 << endl;

	mat1.resize(6, 100);
	cout << "mat1:\n" << mat1 << endl;

	mat1.pop_back(2);
	cout << "mat1:\n" << mat1 << endl;
}

void ch03::MatOp6()
{
	float data[] = { 1, 1, 2, 3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;

	cout << "mat1.t():\n" << mat1.t() << endl;
	cout << "mat1 + 3:\n" << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2:\n" << mat1 * mat2 << endl;
}

void ch03::MatOp5()
{
	Mat img1 = imread("lenna.bmp");

	cout << "Width : " << img1.cols << endl;
	cout << "Height : " << img1.rows << endl;
	cout << "Channels : " << img1.channels() << endl;

	if (img1.type() == CV_8UC1)
		cout << "img5 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img5 is a truecolor image." << endl;

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
}

void ch03::MatOp4()
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat1.rows; j++)
	{
		for (int i = 0; i < mat1.cols; i++)
		{
			mat1.at<uchar>(j, i)++;
		}
	}

	Mat mat2 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat2.rows; j++)
	{
		uchar* p = mat2.ptr<uchar>(j);
		for (int i = 0; i < mat2.cols; i++)
		{
			p[i]++;
		}
	}

	Mat mat3 = Mat::zeros(3, 4, CV_8UC1);

	for (MatIterator_<uchar> it = mat3.begin<uchar>(); it != mat3.end<uchar>(); ++it)
	{
		(*it)++;
	}

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;
	cout << "mat3:\n" << mat3 << endl;
}

void ch03::MatOp3()
{
	Mat img1 = imread("cat.bmp");
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone(); //깊은 복사
	Mat img2 = img1(Rect(220, 120, 340, 240)); // Mat 클래스 괄호연산자 재정의
	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
}

void ch03::MatOp2()
{
	Mat img1 = imread("dog.bmp");

	Mat img2 = img1; // (얕은 복사) 복사생성자
	Mat img3 = img1; // (얕은 복사) 대입연사자

	Mat img4 = img1.clone(); // 깊은 복사
	Mat img5;
	img1.copyTo(img5); // 깊은 복사

	img1.setTo(Scalar(0, 255, 255)); // 노란색

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();

}

void ch03::MatOp1()
{
	Mat img1;

	Mat img2(480, 640, CV_8UC1);
	Mat img3(480, 640, CV_8UC3);
	Mat img4(Size(640, 480), CV_8UC3);

	Mat img5(480, 640, CV_8UC1, Scalar(128));
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));

	Mat mat1 = Mat::zeros(480, 640, CV_32SC1);
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);

	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({ 2,3 }, { 1, 2, 3, 4, 5, 6 });

	mat4.create(256, 256, CV_8UC3);

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
	mat1.setTo(0.0f);


	if (img5.empty())
		std::cout << "failed to open img.jpg" << std::endl;
	else
	{
		std::cout << "img.jpg loaded OK" << std::endl;
		imshow("mat5", mat5);
	}
}