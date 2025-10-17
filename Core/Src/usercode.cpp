//
// Created by zhouzhi on 2025/10/17.
//

#include "usercode.h"

#include "imu_module_new.h"

extern float Roll, Pitch, Yaw;

void userinit() {
    imu_module_init();
}

void userloop() {
    imu_module_get_euler(&Roll, &Pitch, &Yaw);
}
