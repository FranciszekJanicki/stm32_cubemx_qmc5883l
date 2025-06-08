#include "qmc5883l.h"
#include "qmc5883l_registers.h"
#include <assert.h>
#include <string.h>

static qmc5883l_err_t qmc5883l_bus_init(qmc5883l_t const* qmc5883l)
{
    assert(qmc5883l);

    if (qmc5883l->interface.bus_init) {
        return qmc5883l->interface.bus_init(qmc5883l->interface.bus_user);
    }

    return QMC5883L_ERR_NULL;
}

static qmc5883l_err_t qmc5883l_bus_deinit(qmc5883l_t const* qmc5883l)
{
    assert(qmc5883l);

    if (qmc5883l->interface.bus_deinit) {
        return qmc5883l->interface.bus_deinit(qmc5883l->interface.bus_user);
    }

    return QMC5883L_ERR_NULL;
}

static qmc5883l_err_t qmc5883l_bus_write(qmc5883l_t const* qmc5883l,
                                         uint8_t write_address,
                                         uint8_t const* write_data,
                                         size_t write_size)
{
    assert(qmc5883l && write_data);

    if (qmc5883l->interface.bus_write) {
        return qmc5883l->interface.bus_write(qmc5883l->interface.bus_user,
                                             write_address,
                                             write_data,
                                             write_size);
    }

    return QMC5883L_ERR_NULL;
}

static qmc5883l_err_t qmc5883l_bus_read(qmc5883l_t const* qmc5883l,
                                        uint8_t read_address,
                                        uint8_t* read_data,
                                        size_t read_size)
{
    assert(qmc5883l && read_data);

    if (qmc5883l->interface.bus_read) {
        return qmc5883l->interface.bus_read(qmc5883l->interface.bus_user,
                                            read_address,
                                            read_data,
                                            read_size);
    }

    return QMC5883L_ERR_NULL;
}

qmc5883l_err_t qmc5883l_initialize(qmc5883l_t* qmc5883l,
                                   qmc5883l_config_t const* config,
                                   qmc5883l_interface_t const* interface)
{
    assert(qmc5883l && config && interface);

    memset(qmc5883l, 0, sizeof(*qmc5883l));
    memcpy(&qmc5883l->config, config, sizeof(*config));
    memcpy(&qmc5883l->interface, interface, sizeof(*interface));

    return qmc5883l_bus_init(qmc5883l);
}

qmc5883l_err_t qmc5883l_deinitialize(qmc5883l_t* qmc5883l)
{
    assert(qmc5883l);

    qmc5883l_err_t err = qmc5883l_bus_deinit(qmc5883l);

    memset(qmc5883l, 0, sizeof(*qmc5883l));

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_x_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled)
{
    assert(qmc5883l && scaled);

    int16_t raw = {};

    qmc5883l_err_t err = qmc5883l_get_mag_data_z_raw(qmc5883l, &raw);

    *scaled = (float32_t)raw * qmc5883l->config.scale;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_y_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled)
{
    assert(qmc5883l && scaled);

    int16_t raw = {};

    qmc5883l_err_t err = qmc5883l_get_mag_data_y_raw(qmc5883l, &raw);

    *scaled = (float32_t)raw * qmc5883l->config.scale;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_z_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled)
{
    assert(qmc5883l && scaled);

    int16_t raw = {};

    qmc5883l_err_t err = qmc5883l_get_mag_data_z_raw(qmc5883l, &raw);

    *scaled = (float32_t)raw * qmc5883l->config.scale;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_scaled(qmc5883l_t const* qmc5883l, vec3_float32_t* scaled)
{
    assert(qmc5883l && scaled);

    vec3_int16_t raw = {};

    qmc5883l_err_t err = qmc5883l_get_mag_data_raw(qmc5883l, &raw);

    scaled->x = (float32_t)raw.x * qmc5883l->config.scale;
    scaled->y = (float32_t)raw.y * qmc5883l->config.scale;
    scaled->z = (float32_t)raw.z * qmc5883l->config.scale;

    return err;
}

qmc5883l_err_t qmc5883l_get_temp_data_scaled(qmc5883l_t const* qmc5883l, float32_t* scaled)
{
    assert(qmc5883l && scaled);

    int16_t raw = {};

    qmc5883l_err_t err = qmc5883l_get_temp_data_raw(qmc5883l, &raw);

    *scaled = (float32_t)raw * QMC5883L_TEMP_SCALE;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_x_raw(qmc5883l_t const* qmc5883l, int16_t* raw)
{
    assert(qmc5883l && raw);

    qmc5883l_xout_reg_t reg = {};

    qmc5883l_err_t err = qmc5883l_get_xout_reg(qmc5883l, &reg);

    *raw = reg.xout;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_y_raw(qmc5883l_t const* qmc5883l, int16_t* raw)
{
    assert(qmc5883l && raw);

    qmc5883l_yout_reg_t reg = {};

    qmc5883l_err_t err = qmc5883l_get_yout_reg(qmc5883l, &reg);

    *raw = reg.yout;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_z_raw(qmc5883l_t const* qmc5883l, int16_t* raw)
{
    assert(qmc5883l && raw);

    qmc5883l_zout_reg_t reg = {};

    qmc5883l_err_t err = qmc5883l_get_zout_reg(qmc5883l, &reg);

    *raw = reg.zout;

    return err;
}

qmc5883l_err_t qmc5883l_get_mag_data_raw(qmc5883l_t const* qmc5883l, vec3_int16_t* raw)
{
    assert(qmc5883l && raw);

    qmc5883l_out_reg_t reg = {};

    qmc5883l_err_t err = qmc5883l_get_out_reg(qmc5883l, &reg);

    raw->x = reg.xout;
    raw->y = reg.yout;
    raw->z = reg.zout;

    return err;
}

qmc5883l_err_t qmc5883l_get_temp_data_raw(qmc5883l_t const* qmc5883l, int16_t* raw)
{
    assert(qmc5883l && raw);

    qmc5883l_tout_reg_t reg = {};

    qmc5883l_err_t err = qmc5883l_get_tout_reg(qmc5883l, &reg);

    *raw = reg.tout;

    return err;
}

qmc5883l_err_t qmc5883l_get_xout_reg(qmc5883l_t const* qmc5883l, qmc5883l_xout_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data[2] = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_XOUT_LSB, data, sizeof(data));

    reg->xout = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

qmc5883l_err_t qmc5883l_get_yout_reg(qmc5883l_t const* qmc5883l, qmc5883l_yout_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data[2] = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_YOUT_LSB, data, sizeof(data));

    reg->yout = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

qmc5883l_err_t qmc5883l_get_zout_reg(qmc5883l_t const* qmc5883l, qmc5883l_zout_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data[2] = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_ZOUT_LSB, data, sizeof(data));

    reg->zout = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

qmc5883l_err_t qmc5883l_get_out_reg(qmc5883l_t const* qmc5883l, qmc5883l_out_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data[6] = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_XOUT_LSB, data, sizeof(data));

    reg->xout = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));
    reg->yout = (int16_t)((data[2] & 0xFF) | ((data[3] & 0xFF) << 8));
    reg->zout = (int16_t)((data[4] & 0xFF) | ((data[5] & 0xFF) << 8));

    return err;
}

qmc5883l_err_t qmc5883l_get_tout_reg(qmc5883l_t const* qmc5883l, qmc5883l_tout_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data[2] = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_TOUT_LSB, data, sizeof(data));

    reg->tout = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

qmc5883l_err_t qmc5883l_get_control_1_reg(qmc5883l_t const* qmc5883l, qmc5883l_control_1_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_CONTROL_1, &data, sizeof(data));

    reg->osr = (data >> 6U) & 0x03U;
    reg->rng = (data >> 4U) & 0x03U;
    reg->odr = (data >> 2U) & 0x03U;
    reg->mode = data & 0x03U;

    return err;
}

qmc5883l_err_t qmc5883l_set_control_1_reg(qmc5883l_t const* qmc5883l,
                                          qmc5883l_control_1_reg_t const* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    data |= (reg->osr & 0x03U) << 6U;
    data |= (reg->rng & 0x03U) << 4U;
    data |= (reg->odr & 0x03U) << 2U;
    data |= reg->mode & 0x03U;

    return qmc5883l_bus_write(qmc5883l, QMC5883L_REG_ADDR_CONTROL_1, &data, sizeof(data));
}

qmc5883l_err_t qmc5883l_get_control_2_reg(qmc5883l_t const* qmc5883l, qmc5883l_control_2_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_CONTROL_2, &data, sizeof(data));

    reg->soft_rst = (data >> 7U) & 0x01U;
    reg->rol_pnt = (data >> 6U) & 0x01U;
    reg->int_enb = data & 0x01U;

    return err;
}

qmc5883l_err_t qmc5883l_set_control_2_reg(qmc5883l_t const* qmc5883l,
                                          qmc5883l_control_2_reg_t const* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_CONTROL_2, &data, sizeof(data));

    data &= ~((0x01U << 7U) | (0x01U << 6U) | 0x01U);

    data |= (reg->soft_rst & 0x01U) << 7U;
    data |= (reg->rol_pnt & 0x01U) << 6U;
    data |= reg->int_enb & 0x01U;

    err |= qmc5883l_bus_write(qmc5883l, QMC5883L_REG_ADDR_CONTROL_2, &data, sizeof(data));

    return err;
}

qmc5883l_err_t qmc5883l_get_sr_period_reg(qmc5883l_t const* qmc5883l, qmc5883l_sr_period_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_SR_PERIOD, &data, sizeof(data));

    reg->period_fbr = data & 0xFFU;

    return err;
}

qmc5883l_err_t qmc5883l_set_sr_period_reg(qmc5883l_t const* qmc5883l,
                                          qmc5883l_sr_period_reg_t const* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    data |= reg->period_fbr & 0xFFU;

    return qmc5883l_bus_write(qmc5883l, QMC5883L_REG_ADDR_SR_PERIOD, &data, sizeof(data));
}

qmc5883l_err_t qmc5883l_get_chip_id_reg(qmc5883l_t const* qmc5883l, qmc5883l_chip_id_reg_t* reg)
{
    assert(qmc5883l && reg);

    uint8_t data = {};

    qmc5883l_err_t err =
        qmc5883l_bus_read(qmc5883l, QMC5883L_REG_ADDR_CHIP_ID, &data, sizeof(data));

    reg->chip_id = data & 0xFFU;

    return err;
}
