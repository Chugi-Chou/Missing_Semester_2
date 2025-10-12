//
// Created by zhouzhi on 2025/10/12.
//

#ifndef BMI088_H
#define BMI088_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../Inc/main.h"

void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data);
void bmi088_accel_read_reg(uint8_t reg, uint8_t *data);
void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t data);
void bmi088_gyro_read_reg(uint8_t reg, uint8_t *data);
void bmi088_init();

#ifdef __cplusplus
}
#endif

#endif //BMI088_H
