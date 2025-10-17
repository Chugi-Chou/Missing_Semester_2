//
// Created by zhouzhi on 2025/10/17.
//

#include "../Inc/imu_module_new.h"

static IMU_Module imu;  // 全局 IMU 实例

IMU_Module::IMU_Module() : ax(0), ay(0), az(0), gx(0), gy(0), gz(0),
                            roll(0), pitch(0), yaw(0), alpha(0.98f), dt(0.01f) {}

void IMU_Module::init() {
    bmi088_init();
}

void IMU_Module::read_accel() {
    uint8_t msb, lsb;
    bmi088_accel_read_reg(0x13, &msb);
    bmi088_accel_read_reg(0x12, &lsb);
    ax_raw = (msb << 8) | lsb;

    bmi088_accel_read_reg(0x15, &msb);
    bmi088_accel_read_reg(0x14, &lsb);
    ay_raw = (msb << 8) | lsb;

    bmi088_accel_read_reg(0x17, &msb);
    bmi088_accel_read_reg(0x16, &lsb);
    az_raw = (msb << 8) | lsb;

    // 转换为 g
    const float accel_scale = 0.00098f; // 约等于 ±16g 量程
    ax = ax_raw * accel_scale;
    ay = ay_raw * accel_scale;
    az = az_raw * accel_scale;
}

void IMU_Module::read_gyro() {
    uint8_t msb, lsb;
    bmi088_gyro_read_reg(0x03, &msb);
    bmi088_gyro_read_reg(0x02, &lsb);
    gx_raw = (msb << 8) | lsb;

    bmi088_gyro_read_reg(0x05, &msb);
    bmi088_gyro_read_reg(0x04, &lsb);
    gy_raw = (msb << 8) | lsb;

    bmi088_gyro_read_reg(0x07, &msb);
    bmi088_gyro_read_reg(0x06, &lsb);
    gz_raw = (msb << 8) | lsb;

    // 转换为 deg/s
    const float gyro_scale = 0.0038f; // 约等于 ±2000°/s
    gx = gx_raw * gyro_scale;
    gy = gy_raw * gyro_scale;
    gz = gz_raw * gyro_scale;
}

void IMU_Module::complementary_filter() {
    // 积分更新角度
    roll += gx * dt;
    pitch += gy * dt;
    yaw += gz * dt;

		float M_PI = 3.142;
	
    // 根据加速度计算倾角
    float acc_roll = atan2f(ay, az) * 180.0f / M_PI;
    float acc_pitch = atan2f(-ax, sqrtf(ay * ay + az * az)) * 180.0f / M_PI;

    // 互补滤波
    roll = alpha * roll + (1 - alpha) * acc_roll;
    pitch = alpha * pitch + (1 - alpha) * acc_pitch;
}

void IMU_Module::update() {
    read_accel();
    read_gyro();
    complementary_filter();
}

void IMU_Module::getEuler(float &r, float &p, float &y) const {
    r = roll; p = pitch; y = yaw;
}

// ------------------ 对 C 的接口 ------------------

void imu_module_init(void) {
    imu.init();
}

void imu_module_update(void) {
    imu.update();
}

void imu_module_get_euler(float *roll, float *pitch, float *yaw) {
    if (roll && pitch && yaw) imu.getEuler(*roll, *pitch, *yaw);
}


