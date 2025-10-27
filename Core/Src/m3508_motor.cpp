//
// Created by zhouzhi on 2025/10/24.
//

#include "m3508_motor.h"
#include "pid.h"

float linearMapping(int in, int in_min, int in_max, float out_min, float out_max) {
    float temp = out_min + (in - in_min) * (out_max - out_min) / (in_max - in_min);
    return temp;
}

void m3508_motor::canRxMsgCallback(const uint8_t rx_data[8]) {
    int ecd_angle = (rx_data[0] << 8) | rx_data[1];
    ecd_angle_ = linearMapping(ecd_angle, 0, 255, 0, 255);
    delta_ecd_angle_ = ecd_angle_ - last_ecd_angle_;
    if (delta_ecd_angle_ > 180) delta_ecd_angle_ -= 360;
    if (delta_ecd_angle_ < -180) delta_ecd_angle_ += 360;
    delta_angle_ = delta_ecd_angle_ / ratio_;
    angle_ += delta_angle_;
    rotate_speed_ = (rx_data[2] << 8) | rx_data[3];
    rotate_speed_ = rotate_speed_ / 60 / 3.14159 * 180;
    current_ = (rx_data[4] << 8) | rx_data[5];
    temp_ = rx_data[6];
    last_ecd_angle_ = ecd_angle_;
}
