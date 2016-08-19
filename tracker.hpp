#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <unordered_map>

#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/features2d.hpp"

#include "opencv2/reg/mapprojec.hpp"
#include "opencv2/reg/mappergradproj.hpp"
#include "opencv2/reg/mapperpyramid.hpp"

#include "parameters.hpp"

using namespace cv;
using namespace std;
using namespace cv::reg;

struct matchComp {
    bool operator()(DMatch a, DMatch b) {
        return a.distance < b.distance;
    }
};

class Tracker
{
private:
    int checkArea(Point2f p, int n_c, int n_r);
protected:
    Ptr<ORB> detector;
    Ptr<DescriptorMatcher> matcher;

    Mat mask;
    Mat targetFrame;
    Mat targetDesc;
    vector<KeyPoint> targetKp;

    int max_num_features;
    float quality_level;
    int min_distance;
    int blur_size;
    float blur_var;
    float nn_match_thres;
    float ransac_thres;
    int board_size;
    int num_grid;
    int pp_grid;
    int blur_size_grid;
    float blur_var_grid;
    int blur_scale_grid;
    float match_thres_grid;
    float ransac_thres_grid;

public:
    Tracker();
    void changeParam(int mnf, float ql, int md, int bs, float bv, float nmt, float rt, int bds, int ng, int pg, int bsg, int bvg, int bscg, float mtg, float rtg);
    void setTarget(const Mat& frame);
    int featureMatch(const Mat& frame, Mat& homography, bool showImg=false, string windowName="No Name");
    void gridInline(const Mat& frame, vector<Point2f> *inline_target, vector<Point2f> *inline_matched);
    Mat pixelMatch(const Mat& recMatchedFrame);

    //helpers
    void showDifference(const Mat& image1, const Mat& image2, string title);
    void showDifferenceEdge(const Mat& image1, const Mat& image2, string name);
    Mat pixelWiseMatch(const Mat& img1, const Mat& img2);
};

#endif // TRACKER_HPP
