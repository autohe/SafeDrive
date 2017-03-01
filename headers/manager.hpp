#ifndef MANAGER_H
#define MANAGER_H

#include "headers/three_d_handler.hpp"
#include "headers/matcher.hpp"
#include "headers/lane_detector.hpp"
#include "headers/img_fetcher.hpp"

using namespace cv;
using namespace std;

class Manager
{
private:

    shared_ptr<ThreeDHandler> three_d_handler;
    shared_ptr<Matcher> matcher;
    shared_ptr<LaneDetector> lane_detector;
    shared_ptr<IMGFetcher> fetcher;

    string searchPath;

    int blur_size;
    float blur_var;

    float lat;
    float lon;
    float head;
    float pitch;

    Mat targetFrame;
    Mat matchedFrameLeft;
    Mat matchedFrameRight;

    bool findBestMatch();
public:
    Manager();
    void changeParam(int bs, float bv, int mnf, float ql, int md,  int ngf, float mtf, float rtf, int sws, int nd, int pfc, int mod, int ur, int sw, int sr, int dmd, int s1, int s2);
    void initialize(string targetName, float lt, float ln, float hd, float ph, string sp);
    void process();
};

#endif // MANAGER_H