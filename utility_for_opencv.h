/** 
 * @file  utility_for_opencv.h
 * @brief OpenCV関連のユーティリティ
 */

#ifndef UTILITY_FOR_OPENCV_H
#define UTILITY_FOR_OPENCV_H

#include <opencv2/opencv.hpp>

/**
 * @brief   確実にゼロで初期化されたオブジェクトを返す。
 * @details TpはMatの要素の型になり得るもののみ。
 *          int   a = zero<int>();   // a = 0;
 *          Vec3f v = zero<Vec3f>(); // v = [0.f, 0.f, 0.f];
 */
template<typename Tp>
Tp zero() {
	cv::Mat_<Tp> m1(1,1);
	cv::Mat m2 = m1.reshape(1);
	m2 = 0;
	m1 = m2.reshape(m1.channels());
	return m1(0,0);
}

/**
 * @brief 8ビットBGRを32ビットLabに変換する。
 * @param bgr_img 入力。CV_8UC3
 * @param lab_img 出力。CV_32FC3
 */
void convertTo32bitLab(const cv::Mat& bgr_img, cv::Mat& lab_img) {
	bgr_img.convertTo(lab_img, CV_32FC3, 1/255.0);
	cvtColor(lab_img, lab_img, CV_BGR2Lab);
}
/**
 * @brief 32ビットLabを8ビットBGRに変換する。
 * @param lab_img 入力。CV_32FC3
 * @param bgr_img 出力。CV_8UC3
 */
void convertFrom32bitLab(const cv::Mat& lab_img, cv::Mat& bgr_img) {
	cvtColor(lab_img, bgr_img, CV_Lab2BGR);
	bgr_img.convertTo(bgr_img, CV_8UC3, 255);
}

/**
 * @brief   cv::Vecや配列からcv::Scalarを作成。
 * @details make_scalar(Vec3f(1,2,3)); などとして使う。
 * @param   vec 添字で[0]~[n-1]までアクセスできるならOK。
 * @param   n   第一引数の要素の数。5以上を指定するとエラー。
 */
template<typename Tp> cv::Scalar make_scalar(const Tp& vec, int n=3)
{
	cv::Scalar ret;
	for(int i=0; i<n; ++i) ret[i]=vec[i];
	return ret;
}

/**
 * @brief	cv::Matの要素をハッシュ化し、ハッシュのインデックスに置き換える。
 * @details	R風に書くとこんな感じ：dst <- as.numeric(as.factor(src));
 * @param	src_img 入力配列。要素にat<Tp>でアクセスする。
 * @param	dst_img 出力配列。Mat(src_img.size(), CV_32SC1).
 */
template<typename Tp>
int quantize(const cv::Mat& src_img, cv::Mat& dst_img){
	dst_img.create(src_img.size(), CV_32SC1);
	std::map<Tp,int> elem_map;
	int code = 0;
	for(int i=0; i<src_img.total(); ++i){
		const Tp& value = src_img.at<Tp>(i);
		if(elem_map.insert(std::make_pair(value, code)).second) ++code;
		dst_img.at<int>(i) = elem_map[value];
	}
	return elem_map.size();
}

#endif