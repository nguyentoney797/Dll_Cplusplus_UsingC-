#include "ImageLabel.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <array>
#include <list>
#include <string>
#define ImageLabel __declspec(dllimport)

extern "C"
{

	class ImageLabel DLReport
	{
	public:
		std::string Label = "";
		std::list<cv::Point> Vertice;
		bool Status;
		cv::Point Location;
		DLReport(std::string label, std::list<cv::Point> vertice, bool status, cv::Point location)
		{
			Label = label;
			Vertice = vertice;
			Status = status;
			Location = location;
		}

	};
	std::list<std::string, cv::Mat> b;
	class ImageLabel LabelSegmentation
	{
	public:
		int Weight;
		int Height;
		int ArrayColor[5][3] = { {0,0,0},{0,60,100},{119,11,32},{150,100,100},{70,70,70} };
		int ArrayID[5] = { 0,1,2,3,4 };
		int LimitUpper[5][3] = { { 5, 5, 5 }, { 5, 65, 105 }, { 121, 16, 37 }, { 155, 105, 105 }, { 75, 75, 75 } };
		int LimitLower[5][3] = { { 0, 0, 0 }, { 0, 55, 95 }, { 114, 5, 27 }, { 145, 95, 95 }, { 65, 65, 65 } };
		std::string ListName[5] = { "BackGound", "Bridge", "Fat", "OK", "Over" };
		void Create(int w, int h)
		{
			Weight = w;
			Height = h;
		}
		std::list<DLReport> ColorSpace(cv::Mat img, int RoiPoint[2], int MinArea, int MaxArea)
		{
			std::list<DLReport> ListObj;
			bool status = true;
			int length = sizeof(ArrayID);
			for (int i = 1; i < length; i++)
			{
				std::vector<std::vector<cv::Point> > contours;
				cv::Mat obj;
				cv::inRange(img, cv::Scalar(LimitLower[i][2], LimitLower[i][1], LimitLower[i][0]), cv::Scalar(LimitUpper[i][2], LimitUpper[i][1], LimitUpper[i][0]), obj);
				cv::findContours(obj, contours, 2, 2);
				for (std::vector<cv::Point> cnt : contours)
				{
					cv::RotatedRect Rect = cv::minAreaRect(cnt);
					int Area = Rect.size.area();
					if (MinArea < Area && Area <= MaxArea)
					{
						std::list<cv::Point>  listPoint;
						for (cv::Point point : cnt)
						{
							listPoint.push_back(cv::Point(point.x + RoiPoint[0], point.y + RoiPoint[1]));
						}
						if (i != 3)
						{
							status = false;
						}
						else if (i == 3)
						{
							status = true;
						}
						ListObj.push_back(DLReport(ListName[i],listPoint,status,Rect.center));
					}
				}
				obj.release();
			}
			return ListObj;
		}
	};

}
