/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_cs1237.h
 * @brief     driver cs1237 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-09-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/09/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_CS1237_H
#define DRIVER_CS1237_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup cs1237_driver cs1237 driver function
 * @brief    cs1237 driver modules
 * @{
 */

/**
 * @addtogroup cs1237_basic_driver
 * @{
 */

/**
 * @brief cs1237 command data delay definition
 */
#ifndef CS1237_COMMAND_DATA_DELAY
    #define CS1237_COMMAND_DATA_DELAY        5        /**< 5us */
#endif

/**
 * @brief cs1237 bool enumeration definition
 */
typedef enum
{
    CS1237_BOOL_FALSE = 0x00,        /**< false */
    CS1237_BOOL_TRUE  = 0x01,        /**< true */
} cs1237_bool_t;

/**
 * @brief cs1237 adc rate enumeration definition
 */
typedef enum
{
    CS1237_ADC_RATE_10HZ   = 0x00,        /**< 10hz */
    CS1237_ADC_RATE_40HZ   = 0x01,        /**< 40hz */
    CS1237_ADC_RATE_640HZ  = 0x02,        /**< 640hz */
    CS1237_ADC_RATE_1280HZ = 0x03,        /**< 1280hz */
} cs1237_adc_rate_t;

/**
 * @brief cs1237 pga enumeration definition
 */
typedef enum
{
    CS1237_PGA_1   = 0x00,        /**< 1 */
    CS1237_PGA_2   = 0x01,        /**< 2 */
    CS1237_PGA_64  = 0x02,        /**< 64 */
    CS1237_PGA_128 = 0x03,        /**< 128 */
} cs1237_pga_t;

/**
 * @brief cs1237 channel enumeration definition
 */
typedef enum
{
    CS1237_CHANNEL_A             = 0x00,        /**< channel a */
    CS1237_CHANNEL_TEMPERATURE   = 0x02,        /**< channel temperature */
    CS1237_CHANNEL_SHORT_CIRCUIT = 0x03,        /**< channel short circuit */
} cs1237_channel_t;

/**
 * @brief cs1237 handle structure definition
 */
typedef struct cs1237_handle_s
{
    uint8_t (*sclk_gpio_init)(void);                        /**< point to a sclk_gpio_init function address */
    uint8_t (*sclk_gpio_deinit)(void);                      /**< point to a sclk_gpio_deinit function address */
    uint8_t (*sclk_gpio_write)(uint8_t level);              /**< point to a sclk_gpio_write function address */
    uint8_t (*dout_gpio_init)(void);                        /**< point to a dout_gpio_init function address */
    uint8_t (*dout_gpio_deinit)(void);                      /**< point to a dout_gpio_deinit function address */
    uint8_t (*dout_gpio_write)(uint8_t level);              /**< point to a dout_gpio_write function address */
    uint8_t (*dout_gpio_read)(uint8_t *level);              /**< point to a dout_gpio_read function address */
    void (*delay_us)(uint32_t us);                          /**< point to a delay_us function address */
    void (*delay_ms)(uint32_t ms);                          /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);        /**< point to a debug_print function address */
    uint8_t pga;                                            /**< pag */
    uint8_t channel;                                        /**< channel */
    int32_t temperature_raw;                                /**< temperature raw */
    float temperature_deg;                                  /**< temperature degrees */
    float reference_voltage_v;                              /**< reference voltage */
    uint8_t inited;                                         /**< inited flag */
} cs1237_handle_t;

/**
 * @brief cs1237 information structure definition
 */
typedef struct cs1237_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} cs1237_info_t;

/**
 * @}
 */

/**
 * @defgroup cs1237_link_driver cs1237 link driver function
 * @brief    cs1237 link driver modules
 * @ingroup  cs1237_driver
 * @{
 */

/**
 * @brief     initialize cs1237_handle_t structure
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] STRUCTURE cs1237_handle_t
 * @note      none
 */
#define DRIVER_CS1237_LINK_INIT(HANDLE, STRUCTURE)                 memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link sclk_gpio_init function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a sclk_gpio_init function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_SCLK_GPIO_INIT(HANDLE, FUC)             (HANDLE)->sclk_gpio_init = FUC

/**
 * @brief     link sclk_gpio_deinit function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a sclk_gpio_deinit function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_SCLK_GPIO_DEINIT(HANDLE, FUC)           (HANDLE)->sclk_gpio_deinit = FUC

/**
 * @brief     link sclk_gpio_write function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a sclk_gpio_write function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_SCLK_GPIO_WRITE(HANDLE, FUC)            (HANDLE)->sclk_gpio_write = FUC

/**
 * @brief     link dout_gpio_init function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a dout_gpio_init function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DOUT_GPIO_INIT(HANDLE, FUC)             (HANDLE)->dout_gpio_init = FUC

/**
 * @brief     link dout_gpio_deinit function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a dout_gpio_deinit function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DOUT_GPIO_DEINIT(HANDLE, FUC)           (HANDLE)->dout_gpio_deinit = FUC

/**
 * @brief     link dout_gpio_write function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a dout_gpio_write function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DOUT_GPIO_WRITE(HANDLE, FUC)            (HANDLE)->dout_gpio_write = FUC

/**
 * @brief     link dout_gpio_read function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a dout_gpio_read function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DOUT_GPIO_READ(HANDLE, FUC)             (HANDLE)->dout_gpio_read = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a delay_us function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DELAY_US(HANDLE, FUC)                   (HANDLE)->delay_us = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a cs1237 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_CS1237_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup cs1237_basic_driver cs1237 basic driver function
 * @brief    cs1237 basic driver modules
 * @ingroup  cs1237_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a cs1237 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs1237_info(cs1237_info_t *info);

/**
 * @brief     set reference voltage
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] volt reference voltage
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t cs1237_set_reference_voltage(cs1237_handle_t *handle, float volt);

/**
 * @brief      get reference voltage
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *volt pointer to a reference voltage buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs1237_get_reference_voltage(cs1237_handle_t *handle, float *volt);

/**
 * @brief     set temperature calibration point
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] temperature_raw temperature raw value
 * @param[in] temperature_deg temperature degrees
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t cs1237_set_temperature_calibration_point(cs1237_handle_t *handle, int32_t temperature_raw, float temperature_deg);

/**
 * @brief      get temperature calibration point
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *temperature_raw pointer to a temperature raw value buffer
 * @param[out] *temperature_deg pointer to a temperature degrees buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs1237_get_temperature_calibration_point(cs1237_handle_t *handle, int32_t *temperature_raw, float *temperature_deg);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a cs1237 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t cs1237_init(cs1237_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a cs1237 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 gpio deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t cs1237_deinit(cs1237_handle_t *handle);

/**
 * @brief      read voltage
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *raw pointer to a raw buffer
 * @param[out] *mv pointer to a mv buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 can't be temperature channel
 * @note       none
 */
uint8_t cs1237_read(cs1237_handle_t *handle, int32_t *raw, double *mv);

/**
 * @brief      read temperature
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *raw pointer to a raw buffer
 * @param[out] *degrees pointer to a degrees buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 not temperature channel
 *             - 5 pga must be 1
 *             - 6 temperature raw can't be 0
 * @note       none
 */
uint8_t cs1237_read_temperature(cs1237_handle_t *handle, int32_t *raw, float *degrees);

/**
 * @brief     wake up
 * @param[in] *handle pointer to a cs1237 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 wake up failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_wake_up(cs1237_handle_t *handle);

/**
 * @brief     power down
 * @param[in] *handle pointer to a cs1237 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_power_down(cs1237_handle_t *handle);

/**
 * @brief     enable or disable reference voltage output
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set reference voltage output failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_set_reference_voltage_output(cs1237_handle_t *handle, cs1237_bool_t enable);

/**
 * @brief      get reference voltage output status
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get reference voltage output failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs1237_get_reference_voltage_output(cs1237_handle_t *handle, cs1237_bool_t *enable);

/**
 * @brief     set adc rate
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] rate adc rate
 * @return    status code
 *            - 0 success
 *            - 1 set adc rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_set_adc_rate(cs1237_handle_t *handle, cs1237_adc_rate_t rate);

/**
 * @brief      get adc rate
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *rate pointer to an adc rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get adc rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs1237_get_adc_rate(cs1237_handle_t *handle, cs1237_adc_rate_t *rate);

/**
 * @brief     set adc pga
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] pga adc pga
 * @return    status code
 *            - 0 success
 *            - 1 set pga failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_set_pga(cs1237_handle_t *handle, cs1237_pga_t pga);

/**
 * @brief      get adc pga
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *pga pointer to an adc pga buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pga failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs1237_get_pga(cs1237_handle_t *handle, cs1237_pga_t *pga);

/**
 * @brief     set adc channel
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] channel adc channel
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_set_channel(cs1237_handle_t *handle, cs1237_channel_t channel);

/**
 * @brief      get adc channel
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *channel pointer to an adc channel buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs1237_get_channel(cs1237_handle_t *handle, cs1237_channel_t *channel);

/**
 * @}
 */

/**
 * @defgroup cs1237_extern_driver cs1237 extern driver function
 * @brief    cs1237 extern driver modules
 * @ingroup  cs1237_driver
 * @{
 */

/**
 * @brief     set command
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] command input command
 * @param[in] config input configuration
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs1237_set_command(cs1237_handle_t *handle, uint8_t command, uint8_t config);

/**
 * @brief      get command
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[in]  command input command
 * @param[out] *config pointer to a configuration buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs1237_get_command(cs1237_handle_t *handle, uint8_t command, uint8_t *config);

/**
 * @brief      get data
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs1237_get_data(cs1237_handle_t *handle, int32_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
