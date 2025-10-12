//
// Created by zhouzhi on 2025/10/12.
//

#include "callback.h"

uint16_t x_acc;
uint16_t y_acc;
uint16_t z_acc;
uint16_t x_gyro;
uint16_t y_gyro;
uint16_t z_gyro;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim6.Instance) {
        uint8_t temp_msb, temp_lsb;
        bmi088_accel_read_reg(0x13, &temp_msb);
        bmi088_accel_read_reg(0x12, &temp_lsb);
        x_acc = (temp_msb << 8) | temp_lsb; //读取x轴加速度原始值

        bmi088_accel_read_reg(0x15, &temp_msb);
        bmi088_accel_read_reg(0x14, &temp_lsb);
        y_acc = (temp_msb << 8) | temp_lsb; //读取y轴加速度原始值

        bmi088_accel_read_reg(0x17, &temp_msb);
        bmi088_accel_read_reg(0x16, &temp_lsb);
        z_acc = (temp_msb << 8) | temp_lsb; //读取x轴加速度原始值

        bmi088_gyro_read_reg(0x03, &temp_msb);
        bmi088_gyro_read_reg(0x02, &temp_lsb);
        x_gyro = (temp_msb << 8) | temp_lsb; //读取x轴加速度原始值

        bmi088_gyro_read_reg(0x05, &temp_msb);
        bmi088_gyro_read_reg(0x04, &temp_lsb);
        y_gyro = (temp_msb << 8) | temp_lsb; //读取y轴加速度原始值

        bmi088_gyro_read_reg(0x07, &temp_msb);
        bmi088_gyro_read_reg(0x06, &temp_lsb);
        z_gyro = (temp_msb << 8) | temp_lsb; //读取x轴加速度原始值
    }
}
