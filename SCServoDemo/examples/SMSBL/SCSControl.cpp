#include "stdafx.h"
#include "SCSControl.h"
using namespace std;
void getMovePosAndSpeed(double da, double db, double dga, double dth, double dtime)
{
    double R1 = 5;
    double R1_back = 2.5;
    double R2 = 6.5;
    double R2_back = 3.25;
    double R3 = 7.5;
    double R3_back = 3.75;
    double R_LR = 7.5;

    static s16 lastmovePos[20] = { 0 };



    double Mradius[5] = { 11 , 7.9 , 4.4 , 11 , 11 };//舵机半径

    // 构造矩阵A
    double A[5][4] = {
        {R1, R2, R3, 0},
        {-R1_back, R2, R3, 0},
        {0, -R2_back, R3, 0},
        {0, 0, -R3_back, R_LR},
        {0, 0, -R3_back, -R_LR}
    };



    // 角度输入
    //double da = 0;
    //double db = 30;
    //double dga = 120;
    //double dth = 0;

        // 速度输入
    double valpha = 1;
    double vbeta = 1;
    double vgama = 1;
    double vtheta = 1;

    // 度转弧度
    double alpha = da / 180.0 * M_PI;
    double beta = db / 180.0 * M_PI;
    double gama = dga / 180.0 * M_PI;
    double theta = dth / 180.0 * M_PI;

    // 构造列向量joint
    double joint[4] = { alpha, beta, gama, theta };

    // 计算结果
    double result[5] = { 0 };

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i] += A[i][j] * joint[j];

        }
    }

    for (int i = 0; i < 5; i++)
    {
        result[i] = result[i] / (M_PI * 2 * Mradius[i]) * 4096;
    }
    movePos[17] = result[0];
    movePos[15] = result[1];
    movePos[19] = result[2];

    movePos[16] = -result[3];
    movePos[18] = -result[4];


    // 输出结果
    cout << "m1: " << result[0] << endl;
    cout << "m2: " << result[1] << endl;
    cout << "m3: " << result[2] << endl;
    cout << "m4: " << result[3] << endl;
    cout << "m5: " << result[4] << endl;


    //// 构造列向量 vjoint
    //double vjoint[4] = { valpha, vbeta, vgama, vtheta };

    //// 计算结果
    //double Speedresult[5] = { 0 };

    //for (int i = 0; i < 5; ++i) {
    //    for (int j = 0; j < 4; ++j) {
    //        Speedresult[i] += A[i][j] * vjoint[j];
    //    }
    //}


    //for (int i = 0; i < 5; ++i) {
    //    for (int j = 0; j < 4; ++j) {
    //        result[i] += A[i][j] * joint[j];

    //    }
    //}

    //for (int i = 0; i < 5; i++)
    //{
    //    Speedresult[i] = Speedresult[i] / (M_PI * 22) * 4096;
    //}




    moveSpeed[17] = 1 + abs(movePos[17] - lastmovePos[17]) / dtime;
    moveSpeed[15] = 1 + abs(movePos[15] - lastmovePos[15]) / dtime;
    moveSpeed[19] = 1 + abs(movePos[19] - lastmovePos[19]) / dtime;
    moveSpeed[16] = 1 + abs(movePos[16] - lastmovePos[16]) / dtime;
    moveSpeed[18] = 1 + abs(movePos[18] - lastmovePos[18]) / dtime;
    lastmovePos[17] = movePos[17];
    lastmovePos[15] = movePos[15];
    lastmovePos[19] = movePos[19];
    lastmovePos[16] = movePos[16];
    lastmovePos[18] = movePos[18];
    // 输出结果
    std::cout << "v1: " << moveSpeed[17] << std::endl;
    std::cout << "v2: " << moveSpeed[15] << std::endl;
    std::cout << "v3: " << moveSpeed[19] << std::endl;
    std::cout << "v4: " << moveSpeed[16] << std::endl;
    std::cout << "v5: " << moveSpeed[18] << std::endl;


}