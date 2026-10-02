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
 * @file      driver_cs1237_interface.h
 * @brief     driver cs1237 interface header file
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

#ifndef DRIVER_CS1237_INTERFACE_H
#define DRIVER_CS1237_INTERFACE_H

#include "driver_cs1237.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup cs1237_interface_driver cs1237 interface driver function
 * @brief    cs1237 interface driver modules
 * @ingroup  cs1237_driver
 * @{
 */

/**
 * @brief  interface sclk gpio init
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio init failed
 * @note   none
 */
uint8_t cs1237_interface_sclk_gpio_init(void);

/**
 * @brief  interface sclk gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 sclk gpio deinit failed
 * @note   none
 */
uint8_t cs1237_interface_sclk_gpio_deinit(void);

/**
 * @brief     interface sclk gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 sclk gpio write failed
 * @note      none
 */
uint8_t cs1237_interface_sclk_gpio_write(uint8_t level);

/**
 * @brief  interface dout gpio init
 * @return status code
 *         - 0 success
 *         - 1 dout gpio init failed
 * @note   none
 */
uint8_t cs1237_interface_dout_gpio_init(void);

/**
 * @brief  interface dout gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 dout gpio deinit failed
 * @note   none
 */
uint8_t cs1237_interface_dout_gpio_deinit(void);

/**
 * @brief     interface dout gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 dout gpio write failed
 * @note      none
 */
uint8_t cs1237_interface_dout_gpio_write(uint8_t level);

/**
 * @brief      interface dout gpio read
 * @param[out] *level pointer to a gpio level buffer
 * @return     status code
 *             - 0 success
 *             - 1 dout gpio read failed
 * @note       none
 */
uint8_t cs1237_interface_dout_gpio_read(uint8_t *level);

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void cs1237_interface_delay_us(uint32_t us);

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void cs1237_interface_delay_ms(uint32_t ms);

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void cs1237_interface_debug_print(const char *const fmt, ...);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
