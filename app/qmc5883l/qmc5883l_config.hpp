#ifndef QMC5883L_CONFIG_HPP
#define QMC5883L_CONFIG_HPP

#include "qmc5883l_registers.hpp"
#include "vector3d.hpp"
#include <cstdint>

namespace QMC5883L {

    template <typename T>
    using Vec3D = Utility::Vector3D<T>;

    constexpr std::uint8_t DEV_ADDRESS = 0b0001101;

    enum struct RA : std::uint8_t {
        XOUT_LSB = 0x00,
        XOUT_MSB = 0x01,
        YOUT_LSB = 0x02,
        YOUT_MSB = 0x03,
        ZOUT_LSB = 0x04,
        ZOUT_MSB = 0x05,
        STATUS = 0x06,
        TOUT_LSB = 0x07,
        TOUT_MSB = 0x08,
        CONTROL_1 = 0x09,
        CONTROL_2 = 0x0A,
        SR_PERIOD = 0x0B,
        CHIP_ID = 0x0D,
    };

    enum struct Range : std::uint8_t {
        RANGE_2G = 0b00,
        RANGE_8G = 0b01,
    };

    enum struct Mode : std::uint8_t {
        STANDBY = 0b00,
        CONTINUOUS = 0b01,
    };

    enum struct OverSampleRatio : std::uint8_t {
        RATIO_512 = 0b00,
        RATIO_256 = 0b01,
        RATIO_128 = 0b10,
        RATIO_64 = 0b11,
    };

    enum struct OutputDataRate : std::uint8_t {
        RATE_10HZ = 0b00,
        RATE_50HZ = 0b01,
        RATE_100HZ = 0b10,
        RATE_200HZ = 0b11,
    };

    inline float range_to_scale(Range const range) noexcept
    {
        switch (range) {
            case Range::RANGE_2G:
                return 0.0F;
            case Range::RANGE_8G:
                return 0.0F;
            default:
                return 0.0F;
        }
    }

    inline float config_to_scale(Config const& config) noexcept
    {
        return range_to_scale(static_cast<Range>(config.control_1.rng));
    }

}; // namespace QMC5883L

#endif // QMC5883L_CONFIG_HPP