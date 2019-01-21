//
// Created by libaoyu on 18-11-7.
//

#ifndef WINDOWOPTIMIZATION_POINT_H
#define WINDOWOPTIMIZATION_POINT_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include "../alg_config.h"
#include "../alg_utils.h"

class Camera;
class Residual;
class Point;

typedef enum StateE{
    ACTIVED,IMMUENT,MARGINALIZED,TOBE_MARGINLIZE
}State;
class Point{
public:
    int id;
    Camera *host;
    std::vector<Residual*> residuals;
    Point(int _id,Camera *_host):id(_id),host(_host){
        for (int i = 0; i < WINDOW_SIZE_MAX; ++i) {
            auto *tmp = new Eigen::Matrix<SCALAR,FRAME_DIM,POINT_DIM>();
            tmp->setZero();
            Eik.push_back(tmp);
            C.setZero();
        }
        jp_r.setZero();
        state=ACTIVED;
    }
    ~Point();
    int getId(){return id;}
    std::vector<Residual*>& getResiduals(){return residuals;}
    int hasResidualWithTarget(int camId);
    // i 为相机个数， k为点数，而k即指自己，所以为一维数组，8个，为窗口大小
    std::vector<Eigen::Matrix<SCALAR,FRAME_DIM,POINT_DIM> *> Eik;
    Eigen::Matrix<SCALAR,POINT_DIM,POINT_DIM> C;
    Vector pointV;  //Jdrdp * r (w)
    Eigen::Matrix<SCALAR,POINT_DIM,1> jp_r;
    Eigen::Matrix<SCALAR,POINT_DIM,1> prior;
    Vector delta;
    State state;

//前端数据结构
    float idepth;
    float u;
    float v;
    //仅仅在视差匹配时使用
    float u_stereo;
    float v_stereo;
};


#endif //WINDOWOPTIMIZATION_POINT_H