#ifndef QMC5883L_QMC5883L_CONFIG_H
#define QMC5883L_QMC5883L_CONFIG_H

#include <stddef.h>
#include <stdint.h>

#define QMC5883L_DEV_ADDRESS 0b0001101;
#define QMC5883L_TEMP_SCALE 1.0F / 100.0F

typedef float float32_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} vec3_int16_t;

typedef struct {
    float32_t x;
    float32_t y;
    float32_t z;
} vec3_float32_t;

typedef enum {
    QMC5883L_ERR_OK = 0,
    QMC5883L_ERR_FAIL = 1 << 0,
    QMC5883L_ERR_NULL = 1 << 1,
} qmc5883l_err_t;

typedef enum {
    QMC5883L_REG_ADDR_XOUT_LSB = 0x00,
    QMC5883L_REG_ADDR_XOUT_MSB = 0x01,
    QMC5883L_REG_ADDR_YOUT_LSB = 0x02,
    QMC5883L_REG_ADDR_YOUT_MSB = 0x03,
    QMC5883L_REG_ADDR_ZOUT_LSB = 0x04,
    QMC5883L_REG_ADDR_ZOUT_MSB = 0x05,
    QMC5883L_REG_ADDR_STATUS = 0x06,
    QMC5883L_REG_ADDR_TOUT_LSB = 0x07,
    QMC5883L_REG_ADDR_TOUT_MSB = 0x08,
    QMC5883L_REG_ADDR_CONTROL_1 = 0x09,
    QMC5883L_REG_ADDR_CONTROL_2 = 0x0A,
    QMC5883L_REG_ADDR_SR_PERIOD = 0x0B,
    QMC5883L_REG_ADDR_CHIP_ID = 0x0D,
} qmc5883l_reg_addr_t;

typedef enum {
    QMC5883L_FULL_SCALE_RANGE_2G = 0b00,
    QMC5883L_FULL_SCALE_RANGE_8G = 0b01,
} qmc5883_full_scale_range_t;

typedef enum {
    QMC5883L_MODE_STANDBY = 0b00,
    QMC5883L_MODE_CONTINUOUS = 0b01,
} qmc5883l_mode_t;

typedef enum {
    QMC5883L_OVERSAMPLE_RATIO_512 = 0b00,
    QMC5883L_OVERSAMPLE_RATIO_256 = 0b01,
    QMC5883L_OVERSAMPLE_RATIO_128 = 0b10,
    QMC5883L_OVERSAMPLE_RATIO_64 = 0b11,
} qmc5883l_oversample_ratio_t;

typedef enum {
    QMC5883_OUTPUT_DATA_RATE_10HZ = 0b00,
    QMC5883_OUTPUT_DATA_RATE_50HZ = 0b01,
    QMC5883_OUTPUT_DATA_RATE_100HZ = 0b10,
    QMC5883_OUTPUT_DATA_RATE_200HZ = 0b11,
} qmc5883l_output_data_rate_t;

typedef struct {
    float32_t scale;
} qmc5883l_config_t;

typedef struct {
    void* bus_user;
    qmc5883l_err_t (*bus_init)(void*);
    qmc5883l_err_t (*bus_deinit)(void*);
    qmc5883l_err_t (*bus_write)(void*, uint8_t, uint8_t const*, size_t);
    qmc5883l_err_t (*bus_read)(void*, uint8_t, uint8_t*, size_t);
} qmc5883l_interface_t;

inline float32_t qmc5883l_range_to_scale(qmc5883_full_scale_range_t range)
{
    switch (range) {
        case QMC5883L_FULL_SCALE_RANGE_2G:
            return 0.0F;
        case QMC5883L_FULL_SCALE_RANGE_8G:
            return 0.0F;
        default:
            return 0.0F;
    }
}

#endif // QMC5883L_QMC5883L_CONFIG_H