#ifndef QMC5883L_REGISTERS_HPP
#define QMC5883L_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace QMC5883L {

    struct XOUT {
        std::uint8_t xout_lsb : 8;
        std::uint8_t xout_msb : 8;
    } PACKED;

    struct YOUT {
        std::uint8_t yout_lsb : 8;
        std::uint8_t yout_msb : 8;
    } PACKED;

    struct ZOUT {
        std::uint8_t zout_lsb : 8;
        std::uint8_t zout_msb : 8;
    } PACKED;

    struct OUT {
        XOUT xout;
        YOUT yout;
        ZOUT zout;
    } PACKED;

    struct TOUT {
        std::uint8_t tout_lsb : 8;
        std::uint8_t tout_msb : 8;
    } PACKED;

    struct CONTROL_1 {
        std::uint8_t osr : 2;
        std::uint8_t rng : 2;
        std::uint8_t odr : 2;
        std::uint8_t mode : 2;
    } PACKED;

    struct CONTROL_2 {
        std::uint8_t soft_rst : 1;
        std::uint8_t rol_pnt : 1;
        std::uint8_t : 5;
        std::uint8_t int_enb : 1;
    } PACKED;

    struct SR_PERIOD {
        std::uint8_t period_fbr : 8;
    } PACKED;

    struct CHIP_ID {
        std::uint8_t chip_id : 8;
    } PACKED;

    struct Config {
        CONTROL_1 control_1{};
        CONTROL_2 control_2{};
        SR_PERIOD sr_period{};
    };

}; // namespace QMC5883L

#undef PACKED

#endif // QMC5883L_REGISTERS_HPP