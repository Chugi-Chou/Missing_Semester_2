//
// Created by zhouzhi on 2025/10/24.
//

#ifndef M3508_MOTOR_H
#define M3508_MOTOR_H

#include <cstdint>
#include "pid.h"

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

    PID spid_, ppid_;
    float target_angle_, fdb_angle_;
    float target_speed_, fdb_speed_, feedforward_speed_;
    float feedforward_intensity_, output_intensity_;
    enum {
        TORQUE,
        SPEED,
        POSITION_SPEED,
      } control_method_;
public:
    explicit m3508_motor(const float ratio, const float sp, const float si, const float sd, const float pp, const float pi, const float pd): ratio_(ratio), ppid_(pp, pi, pd, 16384, 16384, 0.5), spid_(sp, si, sd, 16384, 16384, 0.5) {};
    void canRxMsgCallback(const uint8_t rx_data[8]);

    void SetPosition(float target_position, float feedforward_speed, float feedforward_intensity);
    void SetSpeed(float target_speed, float feedforward_intensity);
    void SetIntensity(float intensity);
} ;

float linearMapping(int in, int in_min, int in_max, float out_min, float out_max);

#endif //M3508_MOTOR_H
