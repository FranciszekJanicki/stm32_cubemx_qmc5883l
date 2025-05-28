#ifndef QMC5883L_QMC5883L_REGISTERS_H
#define QMC5883L_QMC5883L_REGISTERS_H

#include <stdint.h>

#define PACKED __attribute__((packed))

typedef struct {
    int8_t xout_7to0 : 8;
    int8_t xout_15to8 : 8;
} PACKED qmc5883l_xout_reg_t;

typedef struct {
    int8_t yout_7to0 : 8;
    int8_t yout_15to8 : 8;
} PACKED qmc5883l_yout_reg_t;

typedef struct {
    int8_t zout_7to0 : 8;
    int8_t zout_15to8 : 8;
} PACKED qmc5883l_zout_reg_t;

typedef struct {
    int8_t xout_7to0 : 8;
    int8_t xout_15to8 : 8;
    int8_t yout_7to0 : 8;
    int8_t yout_15to8 : 8;
    int8_t zout_7to0 : 8;
    int8_t zout_15to8 : 8;
} PACKED qmc5883l_out_reg_t;

typedef struct {
    int8_t tout_7to0;
    int8_t tout_15to8;
} PACKED qmc5883l_tout_reg_t;

typedef struct {
    uint8_t osr : 2;
    uint8_t rng : 2;
    uint8_t odr : 2;
    uint8_t mode : 2;
} PACKED qmc5883l_control_1_reg_t;

typedef struct {
    uint8_t soft_rst : 1;
    uint8_t rol_pnt : 1;
    uint8_t : 5;
    uint8_t int_enb : 1;
} PACKED qmc5883l_control_2_reg_t;

typedef struct {
    uint8_t period_fbr : 8;
} PACKED qmc5883l_sr_period_reg_t;

typedef struct {
    uint8_t chip_id : 8;
} PACKED qmc5883l_chip_id_reg_t;

#undef PACKED

#endif // QMC5883L_QMC5883L_REGISTERS_H