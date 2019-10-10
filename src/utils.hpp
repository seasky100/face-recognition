/*
author:jiaopan
date:2019-09-26
email:jiaopaner@163.com
*/
#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
class Utils{
	public:
		static unsigned char* matToBytes(Mat& image, unsigned char* &bytes) {
			int size = image.total() * image.elemSize();
			bytes = new unsigned char[size];  //  have to delete[] that later
			std::memcpy(bytes, image.data, size * sizeof(unsigned char));
			return bytes;
		}

		static Mat bytesToMat(unsigned char* bytes, int width, int height) {
			Mat image = Mat(height, width, CV_8UC3, bytes).clone(); // make a copy
			return image;
		}

		static std::string base64Decode(const char* Data, int DataByte){
			const char DecodeTable[] ={
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				62, // '+'
				0, 0, 0,
				63, // '/'
				52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
				0, 0, 0, 0, 0, 0, 0,
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
				13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
				0, 0, 0, 0, 0, 0,
				26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
				39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
			};
			std::string strDecode;
			int nValue;
			int i = 0;
			while (i < DataByte){
				if (*Data != '\r' && *Data != '\n'){
					nValue = DecodeTable[*Data++] << 18;
					nValue += DecodeTable[*Data++] << 12;strDecode += (nValue & 0x00FF0000) >> 16;
					if (*Data != '='){
						nValue += DecodeTable[*Data++] << 6;strDecode += (nValue & 0x0000FF00) >> 8;
						if (*Data != '='){
							nValue += DecodeTable[*Data++];
							strDecode += nValue & 0x000000FF;
						}
					}
					i += 4;
				}
				else{
					Data++;
					i++;
				}
			}
			return strDecode;
		}

		static cv::Mat base64ToMat(std::string &base64_data){
			cv::Mat img;
			std::string s_mat;
			s_mat = base64Decode(base64_data.data(), base64_data.size());
			std::vector<char> base64_img(s_mat.begin(), s_mat.end());
			img = cv::imdecode(base64_img, CV_LOAD_IMAGE_COLOR);
			return img;
		}
		
		~Utils() {
			
		}
};

