//
// Created by zhouzhi on 2025/10/12.
//

#include "callback.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim6.Instance) {
        imu_module_update();
    }
}
