#ifndef QMC5883L_QMC5883L_H
#define QMC5883L_QMC5883L_H

#include "qmc5883l_config.h"
#include "qmc5883l_registers.h"

typedef struct {
    qmc5883l_config_t config;
    qmc5883l_interface_t interface;
} qmc5883l_t;

qmc5883l_err_t
qmc5883l_initialize(qmc5883l_t* qmc5883l, qmc5883l_config_t const* config, qmc5883l_interface_t const* interface);
qmc5883l_err_t qmc5883l_deinitialize(qmc5883l_t* qmc5883l);

qmc5883l_err_t qmc5883l_get_mag_data_x_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled);
qmc5883l_err_t qmc5883l_get_mag_data_y_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled);
qmc5883l_err_t qmc5883l_get_mag_data_z_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled);
qmc5883l_err_t qmc5883l_get_mag_data_scaled(qmc5883l_t const* qmc5883l, vec3_float32_t* scaled);

qmc5883l_err_t qmc5883l_get_temp_data_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled);

qmc5883l_err_t qmc5883l_get_mag_data_x_raw(qmc5883l_t const* qmc5883l, int16_t* raw);
qmc5883l_err_t qmc5883l_get_mag_data_y_raw(qmc5883l_t const* qmc5883l, int16_t* raw);
qmc5883l_err_t qmc5883l_get_mag_data_z_raw(qmc5883l_t const* qmc5883l, int16_t* raw);
qmc5883l_err_t qmc5883l_get_mag_data_raw(qmc5883l_t const* qmc5883l, vec3_int16_t* raw);

qmc5883l_err_t qmc5883l_get_temp_data_raw(qmc5883l_t const* qmc5883l, int16_t* raw);

qmc5883l_err_t qmc5883l_get_xout_reg(qmc5883l_t const* qmc5883l, qmc5883l_xout_reg_t* reg);
qmc5883l_err_t qmc5883l_get_yout_reg(qmc5883l_t const* qmc5883l, qmc5883l_yout_reg_t* reg);
qmc5883l_err_t qmc5883l_get_zout_reg(qmc5883l_t const* qmc5883l, qmc5883l_zout_reg_t* reg);
qmc5883l_err_t qmc5883l_get_out_reg(qmc5883l_t const* qmc5883l, qmc5883l_out_reg_t* reg);

qmc5883l_err_t qmc5883l_get_tout_reg(qmc5883l_t const* qmc5883l, qmc5883l_tout_reg_t* reg);

qmc5883l_err_t qmc5883l_get_control_1_reg(qmc5883l_t const* qmc5883l, qmc5883l_control_1_reg_t* reg);
qmc5883l_err_t qmc5883l_set_control_1_reg(qmc5883l_t const* qmc5883l, qmc5883l_control_1_reg_t const* reg);

qmc5883l_err_t qmc5883l_get_control_2_reg(qmc5883l_t const* qmc5883l, qmc5883l_control_2_reg_t* reg);
qmc5883l_err_t qmc5883l_set_control_2_reg(qmc5883l_t const* qmc5883l, qmc5883l_control_2_reg_t const* reg);

qmc5883l_err_t qmc5883l_get_sr_period_reg(qmc5883l_t const* qmc5883l, qmc5883l_sr_period_reg_t* reg);
qmc5883l_err_t qmc5883l_set_sr_period_reg(qmc5883l_t const* qmc5883l, qmc5883l_sr_period_reg_t const* reg);

qmc5883l_err_t qmc5883l_get_chip_id_reg(qmc5883l_t const* qmc5883l, qmc5883l_chip_id_reg_t* reg);

#endif // QMC5883L_QMC5883L_H