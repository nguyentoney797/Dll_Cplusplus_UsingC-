#include "LabelSegmen.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <array>
#include <list>
#include <string>
#include <cstddef>
#include <vector>

#define LabelSegmen __declspec(dllexport)
extern "C"
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="single_layer"></param>
	/// <param name="Label"></param>
	/// <param name="ListColor"></param>
	/// <param name="StartRow"></param>
	/// <returns></returns>
	LabelSegmen cv::Mat ID_TO_RGB(int single_layer[224*224],int ListColor[5*3],int startRow )
	{
		cv::Mat out=cv::Mat(224, 224, CV_8UC3);
		int ListColor2[15] = { 0, 0, 0 ,0, 60, 100 ,119, 11, 32 , 150, 100, 100 , 70, 70, 70 };
		for(int obj=0;obj<5 ;obj++)
		{
			for (int k = 0; k < 224*224; k++)
			{
				int row = k /224;
				int col = k - row * 224;
				if (row >= 0)
				{
					std::string id =std::to_string(single_layer[k]);
					if (id == std::to_string(obj))
					{
						out.at<cv::Vec3b>(row, col) = ((ListColor2[obj * 3 + 2]), ListColor2[obj * 3 + 1], ListColor2[obj * 3 + 0]);
					}
				}
			}
		}
		cv::imwrite("D://img12.png", out);
		return out;
	}
	//LabelSegmen void  COLOR_SPACE(int single_layer[224 * 224], int ListColor[5 * 3], int startRow,int roi[2],int minArea,int maxArea,int LimitLower[5*3],int LimitUpper[5*3],std::string listName[5], std::vector<std::vector<int[]>> & outCnt,std::list<std::string> & outLabel,std::list<bool> & outStatus,std::list<int[]> & outLocation)
	//{
	//	auto img = ID_TO_RGB(single_layer, ListColor, startRow);
	//	bool status = true;
	//	std::vector<std::vector<int[2]>> ListObj;
	//	std::vector<int[2]> ListLoca;
	//	for (int i = 1; i < 5; i++)
	//	{
	//		cv::Mat obj = cv::Mat(500, 480, CV_8UC1);
	//		cv::inRange(img, cv::Scalar(LimitLower[i*3+2], LimitLower[i*3+1], LimitLower[i*3+0]), cv::Scalar(LimitUpper[i*3+2], LimitUpper[i*3+1], LimitUpper[i*3+0]), obj);
	//		std::vector<std::vector<cv::Point>> contours;
	//		cv::findContours(obj, contours, 2, 2);
	//		for(auto cnt:contours)
	//		{
	//			cv::RotatedRect Rect=cv::minAreaRect(cnt);
	//			int Area = (int)(Rect.size.area());
	//			if (minArea <= Area && Area >= maxArea)
	//			{
	//				std::vector<int[2]> listPoint;
	//				for (cv::Point point : cnt)
	//				{
	//					int point2[2] ={ point.x + roi[0], point.y + roi[1] };
	//					listPoint.push_back(point2);
	//				}
	//				if (i != 3)
	//				{
	//					status = false;
	//				}
	//				else if (i == 3)
	//				{
	//					status = true;
	//				}
	//				//Add thêm giá trị label là point (label int,status)
	//				outLabel.push_back(listName[i]);
	//				outStatus.push_back(status);
	//				int loca[2] = { (int)cv::minAreaRect(cnt).center.x,(int)cv::minAreaRect(cnt).center.y };
	//				ListLoca.push_back(loca);
	//			}
	//		}
	//		obj.release();
	//		
	//	}
	//}
}