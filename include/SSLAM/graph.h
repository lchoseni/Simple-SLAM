#ifndef GRAPH_H
#define GRAPH_H

#include <opencv2/cvv.hpp>

#include "frame.h"
#include "common_include.h"
#include "front_end.h"
#include "dataset.h"
#include "hmm.h"
#include "map.h"

namespace sslam {

class Map;

typedef struct {
  cv::Mat R;
  cv::Mat T;
  cv::Mat points4D;
  cv::Mat inlinerMask;
  vector<cv::DMatch> matches;
  cv::Mat R_i, C_i, R_j, C_j;
} RELA_RT;

class Graph {
 private:
  map<unsigned int, map<unsigned int, RELA_RT>> id_to_RTs_;
  map<unsigned int, map<unsigned int, cv::Mat>> id_to_NCC;
  map<unsigned int, map<unsigned int, cv::Mat>> id_to_H;
  vector<shared_ptr<Frame>> frames;
  vector<shared_ptr<Frame>> readed_frames;
  int out_bound_pix = 0;
  map<unsigned int, map<unsigned int, SE3>> id_to_trans;

  cv::Mat depth;
  Dataset *dataset_;
  int ref_width_, ref_height_;
  double depth_max, depth_min;
  Hmm *hmm;
  int start_row, end_row, start_col, end_col;
  int rotate = 0;
  int iterations = 0;
  shared_ptr<GMap> g_map_;

 public:

  Graph(Dataset *dataset, shared_ptr<Frame> ref_img);
  shared_ptr<FrontEnd> front_end_;
  shared_ptr<Frame> ref_img_;

  //  void AddFrame(Frame &frame);
  bool ComputeRAndTOfTwoImgs(shared_ptr<Frame> &frame1,
                             shared_ptr<Frame> &frame2,
                             cv::Mat &R_,
                             cv::Mat &t_,
                             cv::Mat &points4D_,
                             cv::Mat &inlinerMask_,
                             vector<cv::DMatch> &matches_);
  void ComputeAllRAndT();
  double ComputeNCC(Frame &ref, Frame &src, int row_pix, int col_pix, int win_size, double depth_pix,  cv::Mat K_src, cv::Mat K_ref);
  void AddMapPoints(shared_ptr<Frame> &frame1, shared_ptr<Frame> &frame2, RELA_RT &rt);

  void InitialRandomDepth();
  void ComputeHomography(const cv::Mat &K_src,
                         const cv::Mat &K_ref,
                         RELA_RT rt,
                         double &depth,
                         cv::Mat &H,
                         int row, int col);
  void ComputeAllNCC(int win_size);
  void Propagate();
  void ComputeSelectionProb(int row,
                            int col,
                            map<unsigned int, map<unsigned int, vector<double>>> &id_back_msg,
                            map<unsigned int, map<unsigned int, vector<double>>> &id_forward_msg, int win_size);
  void Sampling(vector<double> &all_prob);
  double ComputeEmissionProb(double ncc);
  void UpdateRowCol(int &row, int &col);
  void ConvertToDepthMap();
  void Rotate();
  ~Graph();
};

}

#endif