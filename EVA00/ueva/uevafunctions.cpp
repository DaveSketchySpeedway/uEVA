#include "uevafunctions.h"

Mat qImage2cvMat(const QImage &qImage)
{
	// indexed8 to 8uc1 
	//Mat cvMat(qImage.height(), qImage.width(), CV_8UC1,
	//	const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	//return cvMat.clone(); // 1 deep copy otherwise data gone as qImage go out of scope


	// rgb888 to 8uc1
	//Mat color(qImage.height(), qImage.width(), CV_8UC3,
	//	const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	//Mat cvMat;
	//cvtColor(color, cvMat, CV_RGB2GRAY); // deep copy 1
	//return cvMat;

	// argb32 to 8uc1
	Mat color = Mat(qImage.height(), qImage.width(), CV_8UC4,
		const_cast<uchar*>(qImage.bits()), qImage.bytesPerLine());
	Mat cvMat;
	cvtColor(color, cvMat, CV_BGRA2GRAY); // 1 deep copy
	return cvMat;
}



QImage cvMat2qImage(const Mat &cvMat)
{
	// 8uc1 to indexed8 
	//static QVector<QRgb> colorTable;
	//if (colorTable.empty())
	//{
	//	for (int i = 0; i < 256; i++)
	//	{
	//		colorTable.push_back(qRgb(i, i, i));
	//	}
	//}
	//QImage qImage(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_Indexed8);
	//qImage.setColorTable(colorTable);
	//return qImage; // no need to clone because of qimage implicit sharing

	// rbg8uc3 to rbg888
	QImage qImage = QImage(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_RGB888);
	return qImage; // no deep copy
}



void bigPassFilter(vector<vector< Point_<int> >> &contours, const int &size)
{
	vector<vector< Point_<int> >>::iterator iter;
	iter = contours.begin();
	while (iter != contours.end())
	{
		Moments mom = moments(*iter);
		if (mom.m00 < size)
		{
			iter = contours.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

bool isPointInMask(Point_<int> &point, Mat &mask)
{
	uchar *p = mask.ptr<uchar>(point.y);
	if (p[point.x])
		return true;
	
	return false;
}

