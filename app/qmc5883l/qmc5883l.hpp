#ifndef QMC5883L_HPP
#define QMC5883L_HPP

#include "i2c_device.hpp"
#include "qmc5883l_config.hpp"
#include "qmc5883l_registers.hpp"
#include "vector3d.hpp"
#include <cstdint>
#include <optional>

namespace QMC5883L {

    struct QMC5883L {
    public:
        using I2CDevice = Utility::I2CDevice;

        QMC5883L() noexcept = default;
        QMC5883L(I2CDevice&& i2c_device, Config const& config) noexcept;

        QMC5883L(QMC5883L const& other) = delete;
        QMC5883L(QMC5883L&& other) noexcept = default;

        QMC5883L& operator=(QMC5883L const& other) = delete;
        QMC5883L& operator=(QMC5883L&& other) noexcept = default;

        ~QMC5883L() noexcept;

        std::optional<float> get_magnetic_field_x_scaled() const noexcept;
        std::optional<float> get_magnetic_field_y_scaled() const noexcept;
        std::optional<float> get_magnetic_field_z_scaled() const noexcept;
        std::optional<Vec3D<float>> get_magnetic_field_scaled() const noexcept;

        std::optional<float> get_temperature_scaled() const noexcept;

    private:
        std::uint8_t read_byte(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const reg_address) const noexcept;

        void write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const reg_address, std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void initialize(Config const& config) noexcept;
        void deinitialize() noexcept;

        void device_reset() const noexcept;
        std::uint8_t get_device_id() const noexcept;
        bool is_valid_device_id() const noexcept;

        std::optional<std::int16_t> get_magnetic_field_x_raw() const noexcept;
        std::optional<std::int16_t> get_magnetic_field_y_raw() const noexcept;
        std::optional<std::int16_t> get_magnetic_field_z_raw() const noexcept;
        std::optional<Vec3D<std::int16_t>> get_magnetic_field_raw() const noexcept;

        std::optional<std::int16_t> get_temperature_raw() const noexcept;

        XOUT get_xout_registers() const noexcept;
        YOUT get_yout_registers() const noexcept;
        ZOUT get_zout_registers() const noexcept;
        OUT get_out_registers() const noexcept;

        TOUT get_tout_registers() const noexcept;

        CONTROL_1 get_control_1_register() const noexcept;
        void set_control_1_register(CONTROL_1 const control_1) const noexcept;

        CONTROL_2 get_control_2_register() const noexcept;
        void set_control_2_register(CONTROL_2 const control_2) const noexcept;

        SR_PERIOD get_sr_period_register() const noexcept;
        void set_sr_period_register(SR_PERIOD const sr_period) const noexcept;

        CHIP_ID get_chip_id_register() const noexcept;

        bool initialized_{false};

        float scale_{};

        I2CDevice i2c_device_{};
    };

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> QMC5883L::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_bytes<SIZE>(reg_address);
    }

    template <std::size_t SIZE>
    void QMC5883L::write_bytes(std::uint8_t const reg_address,
                               std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->i2c_device_.write_bytes(reg_address, bytes);
    }

}; // namespace QMC5883L

#endif // QMC5883L_HPP