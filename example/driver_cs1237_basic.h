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
 * @file      driver_cs1237_basic.h
 * @brief     driver cs1237 basic header file
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

#ifndef DRIVER_CS1237_BASIC_H
#define DRIVER_CS1237_BASIC_H

#include "driver_cs1237_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup cs1237_example_driver cs1237 example driver function
 * @brief    cs1237 example driver modules
 * @ingroup  cs1237_driver
 * @{
 */

/**
 * @brief cs1237 basic example default definition
 */
#define CS1237_BASIC_DEFAULT_ADC_RATE        CS1237_ADC_RATE_10HZ        /**< 10hz */
#define CS1237_BASIC_DEFAULT_CHANNEL         CS1237_CHANNEL_A            /**< channel a */
#define CS1237_BASIC_DEFAULT_PGA             CS1237_PGA_128              /**< pga 128 */

/**
 * @brief     basic example init
 * @param[in] reference_voltage_v reference voltage volt
 * @param[in] temperature_raw temperature raw value
 * @param[in] temperature_deg temperature degrees
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t cs1237_basic_init(float reference_voltage_v, int32_t temperature_raw, float temperature_deg);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t cs1237_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *mv pointer to a mv buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t cs1237_basic_read(double *mv);

/**
 * @brief      basic example read temperature
 * @param[out] *degrees pointer to a degrees buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 * @note       none
 */
uint8_t cs1237_basic_read_temperature(float *degrees);

/**
 * @brief  basic example wake up
 * @return status code
 *         - 0 success
 *         - 1 wake up failed
 * @note   none
 */
uint8_t cs1237_basic_wake_up(void);

/**
 * @brief  basic example power down
 * @return status code
 *         - 0 success
 *         - 1 power down failed
 * @note   none
 */
uint8_t cs1237_basic_power_down(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
