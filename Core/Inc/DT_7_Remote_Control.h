//
// Created by zhouzhi on 2025/10/25.
//

#ifndef DT_7_REMOTE_CONTROL_H
#define DT_7_REMOTE_CONTROL_H
#include <cstdint>

typedef struct {
    uint16_t ch0;
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint8_t s1;
    uint8_t s2;
}rc_ctrl;

enum dt_status{up, mid, down};

class dt_7 {
private:
    rc_ctrl ctrl;
    uint32_t currtick;
    dt_status s_status[2];
    float left_hori_status;
    float left_vert_status;
    float right_hori_status;
    float right_vert_status;
public:
    bool isConnected();
    void process_rc_frame(uint8_t *frame, uint8_t size);
};

#endif //DT_7_REMOTE_CONTROL_H
