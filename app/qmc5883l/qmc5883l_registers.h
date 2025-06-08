#ifndef QMC5883L_QMC5883L_REGISTERS_H
#define QMC5883L_QMC5883L_REGISTERS_H

#include <stdint.h>

typedef struct {
    int16_t xout : 16;
} qmc5883l_xout_reg_t;

typedef struct {
    int16_t yout : 16;
} qmc5883l_yout_reg_t;

typedef struct {
    int16_t zout : 16;
} qmc5883l_zout_reg_t;

typedef struct {
    int16_t xout : 16;
    int16_t yout : 16;
    int16_t zout : 16;
} qmc5883l_out_reg_t;

typedef struct {
    int16_t tout : 16;
} qmc5883l_tout_reg_t;

typedef struct {
    uint8_t osr : 2;
    uint8_t rng : 2;
    uint8_t odr : 2;
    uint8_t mode : 2;
} qmc5883l_control_1_reg_t;

typedef struct {
    uint8_t soft_rst : 1;
    uint8_t rol_pnt : 1;
    uint8_t int_enb : 1;
} qmc5883l_control_2_reg_t;

typedef struct {
    uint8_t period_fbr : 8;
} qmc5883l_sr_period_reg_t;

typedef struct {
    uint8_t chip_id : 8;
} qmc5883l_chip_id_reg_t;

#endif // QMC5883L_QMC5883L_REGISTERS_H