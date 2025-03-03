#include "qmc5883l.hpp"
#include <optional>
#include <utility>

namespace QMC5883L {

    QMC5883L::QMC5883L(I2CDevice&& i2c_device, Config const& config) noexcept :
        i2c_device_{std::forward<I2CDevice>(i2c_device)}, scale_{config_to_scale(config)}
    {
        this->initialize(config);
    }

    QMC5883L::~QMC5883L() noexcept
    {
        this->deinitialize();
    }

    std::optional<float> QMC5883L::get_magnetic_field_x_scaled() const noexcept
    {
        return this->get_magnetic_field_x_raw().transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) / this->scale_; });
    }

    std::optional<float> QMC5883L::get_magnetic_field_y_scaled() const noexcept
    {
        return this->get_magnetic_field_y_raw().transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) / this->scale_; });
    }

    std::optional<float> QMC5883L::get_magnetic_field_z_scaled() const noexcept
    {
        return this->get_magnetic_field_z_raw().transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) / this->scale_; });
    }

    std::optional<Vec3D<float>> QMC5883L::get_magnetic_field_scaled() const noexcept
    {
        return this->get_magnetic_field_raw().transform(
            [this](Vec3D<std::int16_t> const& raw) { return static_cast<Vec3D<float>>(raw) / this->scale_; });
    }

    std::optional<float> QMC5883L::get_temperature_scaled() const noexcept
    {
        return this->get_magnetic_field_z_raw().transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) / 100.0F; });
    }

    std::uint8_t QMC5883L::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_byte(reg_address);
    }

    void QMC5883L::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->i2c_device_.write_byte(reg_address, byte);
    }

    void QMC5883L::initialize(Config const& config) noexcept
    {
        if (is_valid_device_id()) {
            this->device_reset();
            this->set_control_1_register(config.control_1);
            this->set_control_2_register(config.control_2);
            this->set_sr_period_register(config.sr_period);
            this->initialized_ = true;
        }
    }

    void QMC5883L::deinitialize() noexcept
    {
        if (is_valid_device_id()) {
            this->device_reset();
            this->initialized_ = false;
        }
    }

    void QMC5883L::device_reset() const noexcept
    {
        auto control_2 = this->get_control_2_register();
        control_2.soft_rst = true;
        this->set_control_2_register(control_2);
        HAL_Delay(200UL);
    }

    std::uint8_t QMC5883L::get_device_id() const noexcept
    {
        return std::bit_cast<std::uint8_t>(this->get_chip_id_register());
    }

    bool QMC5883L::is_valid_device_id() const noexcept
    {
        return this->get_device_id() == 0xFF;
    }

    std::optional<std::int16_t> QMC5883L::get_magnetic_field_x_raw() const noexcept
    {
        return this->initialized_
                   ? std::optional<std::int16_t>{std::byteswap(std::bit_cast<std::int16_t>(this->get_xout_registers()))}
                   : std::optional<std::int16_t>{std::nullopt};
    }

    std::optional<std::int16_t> QMC5883L::get_magnetic_field_y_raw() const noexcept
    {
        return this->initialized_
                   ? std::optional<std::int16_t>{std::byteswap(std::bit_cast<std::int16_t>(this->get_yout_registers()))}
                   : std::optional<std::int16_t>{std::nullopt};
    }

    std::optional<std::int16_t> QMC5883L::get_magnetic_field_z_raw() const noexcept
    {
        return this->initialized_
                   ? std::optional<std::int16_t>{std::byteswap(std::bit_cast<std::int16_t>(this->get_zout_registers()))}
                   : std::optional<std::int16_t>{std::nullopt};
    }

    std::optional<Vec3D<std::int16_t>> QMC5883L::get_magnetic_field_raw() const noexcept
    {
        auto const out = this->get_out_registers();
        return this->initialized_
                   ? std::optional<Vec3D<std::int16_t>>{std::in_place,
                                                        std::byteswap(std::bit_cast<std::int16_t>(out.xout)),
                                                        std::byteswap(std::bit_cast<std::int16_t>(out.yout)),
                                                        std::byteswap(std::bit_cast<std::int16_t>(out.zout))}
                   : std::optional<Vec3D<std::int16_t>>{std::nullopt};
    }

    std::optional<std::int16_t> QMC5883L::get_temperature_raw() const noexcept
    {
        return std::byteswap(std::bit_cast<std::int16_t>(this->get_tout_registers()));
    }

    XOUT QMC5883L::get_xout_registers() const noexcept
    {
        return std::bit_cast<XOUT>(this->read_bytes<sizeof(XOUT)>(std::to_underlying(RA::XOUT_LSB)));
    }

    YOUT QMC5883L::get_yout_registers() const noexcept
    {
        return std::bit_cast<YOUT>(this->read_bytes<sizeof(YOUT)>(std::to_underlying(RA::YOUT_LSB)));
    }

    ZOUT QMC5883L::get_zout_registers() const noexcept
    {
        return std::bit_cast<ZOUT>(this->read_bytes<sizeof(ZOUT)>(std::to_underlying(RA::ZOUT_LSB)));
    }

    OUT QMC5883L::get_out_registers() const noexcept
    {
        return std::bit_cast<OUT>(this->read_bytes<sizeof(OUT)>(std::to_underlying(RA::XOUT_LSB)));
    }

    TOUT QMC5883L::get_tout_registers() const noexcept
    {
        return std::bit_cast<TOUT>(this->read_bytes<sizeof(TOUT)>(std::to_underlying(RA::TOUT_LSB)));
    }

    CONTROL_1 QMC5883L::get_control_1_register() const noexcept
    {
        return std::bit_cast<CONTROL_1>(this->read_byte(std::to_underlying(RA::CONTROL_1)));
    }

    void QMC5883L::set_control_1_register(CONTROL_1 const control_1) const noexcept
    {
        this->write_byte(std::to_underlying(RA::CONTROL_1), std::bit_cast<std::uint8_t>(control_1));
    }

    CONTROL_2 QMC5883L::get_control_2_register() const noexcept
    {
        return std::bit_cast<CONTROL_2>(this->read_byte(std::to_underlying(RA::CONTROL_2)));
    }

    void QMC5883L::set_control_2_register(CONTROL_2 const control_2) const noexcept
    {
        this->write_byte(std::to_underlying(RA::CONTROL_2), std::bit_cast<std::uint8_t>(control_2));
    }

    SR_PERIOD QMC5883L::get_sr_period_register() const noexcept
    {
        return std::bit_cast<SR_PERIOD>(this->read_byte(std::to_underlying(RA::SR_PERIOD)));
    }

    void QMC5883L::set_sr_period_register(SR_PERIOD const sr_period) const noexcept
    {
        this->write_byte(std::to_underlying(RA::SR_PERIOD), std::bit_cast<std::uint8_t>(sr_period));
    }

    CHIP_ID QMC5883L::get_chip_id_register() const noexcept
    {
        return std::bit_cast<CHIP_ID>(this->read_byte(std::to_underlying(RA::CHIP_ID)));
    }
}; // namespace QMC5883L