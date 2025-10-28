//
// Created by zhouzhi on 2025/10/24.
//

#include "m3508_motor.h"

extern uint8_t txdata[8];

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

    fdb_speed_ = rotate_speed_;
    fdb_angle_ = angle_;
    output_intensity_ = current_;
}

void m3508_motor::SetIntensity(float intensity) {
    control_method_ = TORQUE;
    output_intensity_ = intensity;

    if (output_intensity_ > 20.0f) output_intensity_ = 20.0f;
    if (output_intensity_ < -20.0f) output_intensity_ = -20.0f;

    int16_t cmd = (int16_t)(output_intensity_ * 16384.0f / 20.0f);
    if (cmd > 16384) cmd = 16384;
    if (cmd < -16384) cmd = -16384;

    txdata = {0};
    txdata[0] = (cmd >> 8) & 0xFF;
    txdata[1] = cmd & 0xFF;
}

void m3508_motor::SetSpeed(float speed, float feedforward_intensity) {
    control_method_ = SPEED;
    target_speed_ = speed;
    fdb_speed_ = rotate_speed_;

    float torque = spid_.calc(target_speed_, fdb_speed_);
    torque += feedforward_intensity;

    if (torque > 20.0f) torque = 20.0f;
    if (torque < -20.0f) torque = -20.0f;
    output_intensity_ = torque;

    int16_t cmd = (int16_t)(torque * 16384.0f / 20.0f);
    if (cmd > 16384) cmd = 16384;
    if (cmd < -16384) cmd = -16384;

    txdata = {0};
    txdata[0] = (cmd >> 8) & 0xFF;
    txdata[1] = cmd & 0xFF;

}

void m3508_motor::SetPosition(float target_position, float feedforward_speed, float feedforward_intensity) {
    control_method_ = POSITION_SPEED;
    target_angle_ = target_position;
    fdb_angle_ = angle_;

    target_speed_ = ppid_.calc(target_angle_, fdb_angle_);
    target_speed_ += feedforward_speed;

    fdb_speed_ = rotate_speed_;
    float torque = spid_.calc(target_speed_, fdb_speed_);
    torque += feedforward_intensity;

    if (torque > 20.0f) torque = 20.0f;
    if (torque < -20.0f) torque = -20.0f;
    output_intensity_ = torque;

    int16_t cmd = (int16_t)(torque * 16384.0f / 20.0f);
    if (cmd > 16384) cmd = 16384;
    if (cmd < -16384) cmd = -16384;

    txdata = {0};
    txdata[0] = (cmd >> 8) & 0xFF;
    txdata[1] = cmd & 0xFF;
}