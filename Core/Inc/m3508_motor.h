//
// Created by zhouzhi on 2025/10/24.
//

#ifndef M3508_MOTOR_H
#define M3508_MOTOR_H

#include <cstdint>

class m3508_motor {
private:
    const float ratio_;

    float angle_ = 0.f;
    float delta_angle_ = 0.f;
    float ecd_angle_ = 0.f;
    float last_ecd_angle_ = 0.f;
    float delta_ecd_angle_ = 0.f;
    float rotate_speed_ = 0.f;
    float current_ = 0.f;
    float temp_ = 0.f;

public:
    explicit m3508_motor(const float ratio): ratio_(ratio) {};
    void canRxMsgCallback(const uint8_t rx_data[8]);
} ;

#endif //M3508_MOTOR_H
