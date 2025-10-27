//
// Created by zhouzhi on 2025/10/25.
//

#include "../Inc/DT_7_Remote_Control.h"

#include "stm32f4xx_hal.h"
#include "m3508_motor.h"

bool dt_7::isConnected() {
    bool temp = false;
    if (HAL_GetTick() == currtick + 1) temp = true;
    currtick = HAL_GetTick();
    return temp;
}

void dt_7::process_rc_frame(uint8_t *frame, uint8_t len) {
    if (len != 18) return;
    ctrl.ch0 = ((frame[0] | frame[1] << 8) & 0x07FF);
    ctrl.ch1 = ((frame[1] >> 3 | frame[2] << 5) & 0x07FF);
    ctrl.ch2 = ((frame[2] >> 6 | frame[3] << 2 | frame[4] << 10) & 0x07FF);
    ctrl.ch3 = ((frame[4] >> 1 | frame[5] << 7) & 0x07FF);
    ctrl.s1 = (frame[5] >> 4) & 0x03;
    ctrl.s2 = (frame[5] >> 6) & 0x03;

    if (ctrl.s2 == 0x01) s_status[0] = up;
    else if (ctrl.s2 == 0x03) s_status[0] = mid;
    else if (ctrl.s2 == 0x02) s_status[0] = down;

    if (ctrl.s1 == 0x01) s_status[1] = up;
    else if (ctrl.s1 == 0x03) s_status[1] = mid;
    else if (ctrl.s1 == 0x02) s_status[1] = down;

    left_hori_status = linearMapping(ctrl.ch2, 364, 1684, -1, 1);
    left_vert_status = linearMapping(ctrl.ch3, 364, 1684, -1, 1);
    right_hori_status = linearMapping(ctrl.ch0, 364, 1684, -1, 1);
    right_vert_status = linearMapping(ctrl.ch1, 364, 1684, -1, 1);
}


