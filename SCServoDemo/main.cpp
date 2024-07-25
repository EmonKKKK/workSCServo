#include "stdafx.h"
#include "config.h"

using namespace std;


#define ID1  0
#define ID2  1
#define MOTOR_NUM   5
#define TAR_POS     3072
#define TAR_SPEED   2000



u16 param[128] = { 0 };
s16 movePos[20] = { 0 };
u16 moveSpeed[20] = { 0 };

int CurrentSpeed[20] = { 0 };
int CurrentLoad[20] = { 0 };
int CurrentPos[20] = { 0 };

int angle[4] = { 0 };
int targetAngle[43][4] = {

      {0,0,0,0},
    {30,30,0,0},
    {60,60,0,0},
    {80,100,0,0},
     {60,60,0,0},
     {30,30,0,0},
      {0,0,0,0},
       {0,0,0,0},
       {0,0,0,0},

     {0,0,0,0},
    {20,0,0,0},
    {40,0,0,0},
    {70,0,0,0},
    {40,0,0,0},
    {0,0,0,0},
   

     {0,0,0,0},
    {0,30,0,0},
    {0,70,0,0},
    {0,110,0,0},
    {0,70,0,0},
    {0,30,0,0},
    {0,0,0,0},
    

    {0,0,0,0},
    {0,0,30,0},
    {0,0,60,0},
    {0,0,90,0},
    {0,0,120,0},
    {0,0,90,0},
    {0,0,60,0},
    {0,0,30,0},
    {0,0,0,0},
    


    {0,0,0,10},
    {0,0,0,20},
    {0,0,0,30},
    {0,0,0,20},
    {0,0,0,10},
    {0,0,0,0},
    {0,0,0,-10},
    {0,0,0,-20},
    {0,0,0,-30},
    {0,0,0,-20},
    {0,0,0,-10},
     {0,0,0,0}
};
SMSBL sm;
std::atomic<bool> stopFlag(false);
std::condition_variable cv;
std::mutex cv_m;
//u8 MID[MOTOR_NUM] = {5,4, 2 ,3,4,5};
//u16 TargetSpeed[MOTOR_NUM] = { TAR_SPEED,TAR_SPEED ,TAR_SPEED ,TAR_SPEED ,TAR_SPEED ,TAR_SPEED };
//s16 TargetPos[MOTOR_NUM] = { TAR_POS, TAR_POS ,TAR_POS ,TAR_POS ,TAR_POS ,TAR_POS}; //4096
u8 Acc[MOTOR_NUM] = {0};
int RunMode[MOTOR_NUM] = {0};// 0:伺服位置模式 2:开环电机模式 1：恒速模式 3:步进电机模式 
int step = 0;


int Ftime = 20;
bool increasing = true; // 初始状态为增加速度







//void getMovePosAndSpeed(double da, double db, double dga, double dth,double dtime)
//{
//    double R1 = 5;
//    double R1_back = 2.5;
//    double R2 = 6.5;
//    double R2_back = 3.25;
//    double R3 = 7.5;
//    double R3_back = 3.75;
//    double R_LR = 7.5;
//
//    static s16 lastmovePos[20] = { 0 };
//
//
//
//    double Mradius[5] = { 11 , 7.9 , 4.4 , 11 , 11};//舵机半径
//
//    // 构造矩阵A
//    double A[5][4] = {
//        {R1, R2, R3, 0},
//        {-R1_back, R2, R3, 0},
//        {0, -R2_back, R3, 0},
//        {0, 0, -R3_back, R_LR},
//        {0, 0, -R3_back, -R_LR}
//    };
//
//
//
//    // 角度输入
//    //double da = 0;
//    //double db = 30;
//    //double dga = 120;
//    //double dth = 0;
//    
//        // 速度输入
//    double valpha = 1;
//    double vbeta = 1;
//    double vgama = 1;
//    double vtheta = 1;
//
//    // 度转弧度
//    double alpha = da / 180.0 * M_PI;
//    double beta = db / 180.0 * M_PI;
//    double gama = dga / 180.0 * M_PI;
//    double theta = dth / 180.0 * M_PI;
//
//    // 构造列向量joint
//    double joint[4] = { alpha, beta, gama, theta };
//
//    // 计算结果
//    double result[5] = { 0 };
//
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            result[i] += A[i][j] * joint[j];
//
//        }
//    }
//
//    for (int i = 0; i < 5; i++)
//    {
//        result[i] = result[i] / (M_PI * 2*Mradius[i]) * 4096;
//    }
//    movePos[17] = result[0];
//    movePos[15] = result[1];
//    movePos[19] = result[2];
//
//    movePos[16] = -result[3];
//    movePos[18] = -result[4];
//
//
//    // 输出结果
//    cout << "m1: " << result[0] << endl;
//    cout << "m2: " << result[1] << endl;
//    cout << "m3: " << result[2] << endl;
//    cout << "m4: " << result[3] << endl;
//    cout << "m5: " << result[4] << endl;
//
//
//    //// 构造列向量 vjoint
//    //double vjoint[4] = { valpha, vbeta, vgama, vtheta };
//
//    //// 计算结果
//    //double Speedresult[5] = { 0 };
//
//    //for (int i = 0; i < 5; ++i) {
//    //    for (int j = 0; j < 4; ++j) {
//    //        Speedresult[i] += A[i][j] * vjoint[j];
//    //    }
//    //}
//
//
//    //for (int i = 0; i < 5; ++i) {
//    //    for (int j = 0; j < 4; ++j) {
//    //        result[i] += A[i][j] * joint[j];
//
//    //    }
//    //}
//
//    //for (int i = 0; i < 5; i++)
//    //{
//    //    Speedresult[i] = Speedresult[i] / (M_PI * 22) * 4096;
//    //}
//
//
//
//
//    moveSpeed[17] = 1+abs(movePos[17] - lastmovePos[17]) / dtime;
//    moveSpeed[15] = 1+abs(movePos[15] - lastmovePos[15]) / dtime;
//    moveSpeed[19] = 1+abs(movePos[19] - lastmovePos[19]) / dtime;
//    moveSpeed[16] = 1+abs(movePos[16] - lastmovePos[16]) / dtime;
//    moveSpeed[18] = 1+abs(movePos[18] - lastmovePos[18]) / dtime;
//    lastmovePos[17] = movePos[17];
//    lastmovePos[15] = movePos[15];
//    lastmovePos[19] = movePos[19];
//    lastmovePos[16] = movePos[16];
//    lastmovePos[18] = movePos[18];
//    // 输出结果
//    std::cout << "v1: " <<  moveSpeed[17] << std::endl;
//    std::cout << "v2: " <<  moveSpeed[15] << std::endl;
//    std::cout << "v3: " <<  moveSpeed[19] << std::endl;
//    std::cout << "v4: " <<  moveSpeed[16] << std::endl;
//    std::cout << "v5: " <<  moveSpeed[18] << std::endl;
//    
//
//}




void high_resolution_sleep(std::chrono::milliseconds duration) {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + duration;
    while (std::chrono::high_resolution_clock::now() < end) {
        std::this_thread::yield();  // 提高精度，减少CPU占用
    }
}

int ReadSpeed(int ID) {
    int Speed;
    Speed = sm.ReadSpeed(ID);

    return Speed;
}

int ReadLoad(int ID) {
    int Load;
    Load = sm.ReadLoad(ID);
    return Load;
}

int ReadPos(int ID) {
    int Pos;
    Pos = sm.ReadPos(ID);
    return Pos;
}


int ReadTemper(int ID) {
    int Temper;
    Temper = sm.ReadTemper(ID);
    return Temper;
}

void motorControl(std::ofstream& outFile) {


    Init_program_table();//初始化列表
    for (int i = 0; i < MOTOR_NUM; i++)//测试串口通信
    {
        std::cout << "ID"<< i+15 << " Position:" << sm.ReadPos(i+15) << std::endl;
    }

    for (int i = 0; i < MOTOR_NUM; i++)
    {
        sm.unLockEprom(i+15);//eprom解锁





       sm.CalibrationOfs(i + 15);////中位校准
        sm.AngleLimit(i + 15,param[0],param[1]);//配置角度限制
        sm.MaxLoad(i + 15, param[2]);//最大扭矩
        sm.SetRunMode(i + 15, param[03]);//运行模式
        sm.OverLoadProtect(i + 15, param[4], param[5], param[6]);//设置 保护扭矩 保护时间 过载扭矩





        sm.WriteAcc(i + 15, param[7]);//配置加速度
        sm.WriteSpeed(i + 15, param[8]);//配置速度
        //sm.WritePositon(i + 15,2048); //设置目标位置

        sm.LockEprom(i + 15);//eprom加锁

    }


    sm.WritePositon(15, 2048 - 300);
    sm.WritePositon(17, 2048 - 200);
    sm.WritePositon(19, 2048 - 300);
    sm.WritePositon(18, 2048+200);
    sm.WritePositon(16, 2048+200);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    sm.CalibrationOfs(15);////中位校准
    sm.CalibrationOfs(16);////中位校准
    sm.CalibrationOfs(17);////中位校准
    sm.CalibrationOfs(18);////中位校准
    sm.CalibrationOfs(19);////中位校准

    std::cout << "电机初始化完成" << std::endl;




    int Count = 0;

    u8 ID[MOTOR_NUM] = { 15,16,17,18,19 };
    u16 moveSpeed15_19[MOTOR_NUM] = { 0 };
    s16 movePos15_19[MOTOR_NUM] = { 0 };
    bool firstTimeConditionMet = false;
    auto startTime = std::chrono::high_resolution_clock::now();
    while ((Count < 10) && (!stopFlag)) { //!stopFlag
        auto LastTime = std::chrono::high_resolution_clock::now();
        if (step == 0) {

            getMovePosAndSpeed(angle[0], angle[1], angle[2], angle[3],0.5); //da, db, dga,dth,dtime

            for (int i = 0; i < MOTOR_NUM; ++i)
            {
               moveSpeed15_19[i] = moveSpeed[ID[i]];
               movePos15_19[i] = (2048 - movePos[ID[i]]);
            }
            sm.SyncWritePosEx(ID, MOTOR_NUM, movePos15_19, moveSpeed15_19, 0);//同步发指令




            step = 1;
        }
        if (step == 1) {

            //保留

            step = 2;
        }

        if (step == 2) {
            
            u8 IsAllStop = 1;
            u8 IsMove = 1;
            for (int i = 0; i < 5; i++)
            {
                IsMove = sm.ReadMove(i + 15);
                
                if (sm.ReadMove(i + 15) == 1) {
                    IsAllStop = 0;
                    break;
                }
            }
            if (IsAllStop)
            {

                Count++;
                if (Count == 10)
                {
                    Count = 0;
                    //break ;
                }
                for (int i = 0; i < 4; ++i) {
                    angle[i] = targetAngle[Count][i];
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                CurrentPos[15] = ReadPos(15);
                CurrentPos[16] = ReadPos(16);
                CurrentPos[17] = ReadPos(17);
                CurrentPos[18] = ReadPos(18);
                CurrentPos[19] = ReadPos(19);
                for (int i = 0; i < MOTOR_NUM; ++i)
                {
                    std::cout << "ID" << i+15 << " CPosition:" << CurrentPos[ID[i]] << "targetPos" << movePos15_19[i] << std::endl;
                }
    
                
   

                step = 0;
            }
            else
            {
                step = 2;
            }


        }

    }


    for (int i = 0; i < MOTOR_NUM; i++)
    {
        sm.WritePositon(i+15, 2048); //设置目标位置
    }
}



void waitForKeypress() {
    std::cin.get();
    {
        std::lock_guard<std::mutex> lk(cv_m);
        stopFlag = true;

    }
    cv.notify_all();
}

int main(int argc, char** argv)
{

    const char* serialPort = "COM4";

    if (argc < 2) {
        std::cout << "argc error!" << std::endl;
        getchar();
        return 0;
    }
    std::cout << "serial:" << serialPort << std::endl;
    if (!sm.begin(1000000, serialPort)) {
        std::cout << "Failed to init smsbl motor!" << std::endl;
        getchar();
        return 0;
    }
    std::string fileName = "Data/loadtest/A0_V" + std::to_string(TAR_SPEED) + "load6shu_Num2.csv";
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    std::thread motorThread(motorControl, std::ref(outFile));
    std::thread inputThread(waitForKeypress);
    {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [] { return stopFlag.load(); });
    }
    motorThread.join();
    inputThread.join();

    sm.end();
    outFile.close();
    return 1;
}
