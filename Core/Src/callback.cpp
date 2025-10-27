//
// Created by zhouzhi on 2025/10/12.
//

#include "callback.h"

#include <cstring>

#include "DT_7_Remote_Control.h"
#include "can.h"
#include "m3508_motor.h"

m3508_motor Motor_0(19);
dt_7 newController;

#ifdef __cplusplus
extern "C" {
#endif

    extern CAN_TxHeaderTypeDef tx_header;
    extern CAN_RxHeaderTypeDef rx_header;
    extern CAN_FilterTypeDef filter;
    extern uint8_t tx_data[8];
    extern uint8_t rx_data[8];
    extern uint32_t can_tx_mail_box_;

#ifdef __cplusplus
    }
#endif

extern uint8_t uart_rx_buf[18];
extern uint8_t uart_rx_data[18];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim6.Instance) {
        imu_module_update();
        HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data, &can_tx_mail_box_);
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (hcan->Instance == CAN1) {
        HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);
        if (rx_header.StdId == 0x201) {
            Motor_0.canRxMsgCallback(rx_data);
        }
    }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    static uint8_t frame_index = 0;
    if (huart->Instance == USART3) {
        if (__HAL_DMA_GET_COUNTER(huart->hdmarx) == 0) {
            for (uint8_t i = 0; i < Size; i++) {
                uart_rx_data[i] = uart_rx_buf[i];
            }
            newController.process_rc_frame(uart_rx_data, 18);
        }
        else {}
        HAL_UARTEx_ReceiveToIdle_DMA(huart, uart_rx_buf, 18);
    }
}
