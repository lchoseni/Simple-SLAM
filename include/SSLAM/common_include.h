#ifndef COMMON_INCLUDE_H
#define COMMON_INCLUDE_H



#include<vector>
#include<memory>
#include <map>

// Sophus
#include<sophus/se3.hpp>
#include<sophus/so3.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/core/eigen.hpp>

using namespace std;


typedef Eigen::Matrix<double, 2, 1> Vec2;
typedef Eigen::Matrix<double, 3, 1> Vec3;

typedef Eigen::Matrix<double, 3, 3> Mat33;
typedef Eigen::Matrix<double, 4, 4> Mat44;


#endif