//
// Created by zhouzhi on 2025/10/17.
//

#include "usercode.h"

#include "can.h"
#include "tim.h"
#include "imu_module_new.h"

extern float Roll, Pitch, Yaw;

#ifdef __cplusplus
extern "C" {
#endif

    extern CAN_TxHeaderTypeDef tx_header;
    extern CAN_RxHeaderTypeDef rx_header;
    extern CAN_FilterTypeDef filter;
    extern uint8_t tx_data[8];
    extern uint8_t rx_data[8];
    extern CAN_FilterTypeDef filter_config;

#ifdef __cplusplus
}
#endif

void userinit() {
    imu_module_init();
    HAL_CAN_ConfigFilter(&hcan1, &filter_config);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_TIM_Base_Start_IT(&htim6);
}

void userloop() {
    imu_module_get_euler(&Roll, &Pitch, &Yaw);
}
