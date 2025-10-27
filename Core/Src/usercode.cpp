//
// Created by zhouzhi on 2025/10/17.
//

#include "usercode.h"

#include "can.h"
#include "tim.h"
#include "imu_module_new.h"
#include "usart.h"
#include "DT_7_Remote_Control.h"

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

uint8_t uart_rx_buf[18];
uint8_t uart_rx_data[18];

extern dt_7 newController;

void userinit() {
    imu_module_init();
    HAL_CAN_ConfigFilter(&hcan1, &filter_config);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_TIM_Base_Start_IT(&htim6);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, uart_rx_buf, sizeof(uart_rx_buf));
}

void userloop() {
    imu_module_get_euler(&Roll, &Pitch, &Yaw);
}

