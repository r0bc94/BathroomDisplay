/**
 * @file displayconfig.hpp
 * @author Robin
 * @brief Struct which defines a display configuration
 * @date 2025-01-05
 * 
 */
struct DISPLAYCONFIG {
    unsigned int width;
    unsigned int height;
    __UINT8_TYPE__ sda_pin;
    __UINT8_TYPE__ sdc_pin;
}; 