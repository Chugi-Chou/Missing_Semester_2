//
// Created by zhouzhi on 2025/10/17.
//

#ifndef IMU_MODULE_NEW_H
#define IMU_MODULE_NEW_H

#include "bmi088.h"
#include "main.h"
#include <math.h>

class IMU_Module {
public:
    IMU_Module();

    void init();          // 初始化
    void update();        // 从 BMI088 读取并计算姿态
    void getEuler(float &roll, float &pitch, float &yaw) const;

private:
    // 原始数据
    int16_t ax_raw, ay_raw, az_raw;
    int16_t gx_raw, gy_raw, gz_raw;

    // 转换后的物理量
    float ax, ay, az;
    float gx, gy, gz;

    // 姿态角
    float roll, pitch, yaw;

    // 参数
    float alpha;  // 互补滤波系数
    float dt;     // 采样周期 (s)

    void read_accel();
    void read_gyro();
    void complementary_filter();
};

// ⚙️ 对 C 提供封装接口（供 callback.cpp / main.c 调用）
#ifdef __cplusplus
extern "C" {
#endif

    void imu_module_init(void);
    void imu_module_update(void);
    void imu_module_get_euler(float *roll, float *pitch, float *yaw);

#ifdef __cplusplus
}
#endif

#endif //IMU_MODULE_NEW_H
