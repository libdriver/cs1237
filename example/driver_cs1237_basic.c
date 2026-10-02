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
 * @file      driver_cs1237_basic.c
 * @brief     driver cs1237 basic source file
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

#include "driver_cs1237_basic.h"

static cs1237_handle_t gs_handle;        /**< cs1237 handle */

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
uint8_t cs1237_basic_init(float reference_voltage_v, int32_t temperature_raw, float temperature_deg)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_CS1237_LINK_INIT(&gs_handle, cs1237_handle_t);
    DRIVER_CS1237_LINK_SCLK_GPIO_INIT(&gs_handle, cs1237_interface_sclk_gpio_init);
    DRIVER_CS1237_LINK_SCLK_GPIO_DEINIT(&gs_handle, cs1237_interface_sclk_gpio_deinit);
    DRIVER_CS1237_LINK_SCLK_GPIO_WRITE(&gs_handle, cs1237_interface_sclk_gpio_write);
    DRIVER_CS1237_LINK_DOUT_GPIO_INIT(&gs_handle, cs1237_interface_dout_gpio_init);
    DRIVER_CS1237_LINK_DOUT_GPIO_DEINIT(&gs_handle, cs1237_interface_dout_gpio_deinit);
    DRIVER_CS1237_LINK_DOUT_GPIO_WRITE(&gs_handle, cs1237_interface_dout_gpio_write);
    DRIVER_CS1237_LINK_DOUT_GPIO_READ(&gs_handle, cs1237_interface_dout_gpio_read);
    DRIVER_CS1237_LINK_DELAY_US(&gs_handle, cs1237_interface_delay_us);
    DRIVER_CS1237_LINK_DELAY_MS(&gs_handle, cs1237_interface_delay_ms);
    DRIVER_CS1237_LINK_DEBUG_PRINT(&gs_handle, cs1237_interface_debug_print);
    
    /* set reference voltage */
    res = cs1237_set_reference_voltage(&gs_handle, reference_voltage_v);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set reference voltage failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set temperature calibration point */
    res = cs1237_set_temperature_calibration_point(&gs_handle, temperature_raw, temperature_deg);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set temperature calibration point failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* cs1237 init */
    res = cs1237_init(&gs_handle);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: init failed.\n");
        
        return 1;
    }
    
    /* wake up */
    res = cs1237_wake_up(&gs_handle);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: wake up failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable reference voltage output */
    res = cs1237_set_reference_voltage_output(&gs_handle, CS1237_BOOL_TRUE);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set reference voltage output failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default adc rate */
    res = cs1237_set_adc_rate(&gs_handle, CS1237_BASIC_DEFAULT_ADC_RATE);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default channel */
    res = cs1237_set_channel(&gs_handle, CS1237_BASIC_DEFAULT_CHANNEL);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pga */
    res = cs1237_set_pga(&gs_handle, CS1237_BASIC_DEFAULT_PGA);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *mv pointer to a mv buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t cs1237_basic_read(double *mv)
{
    uint8_t res;
    int32_t raw;
    
    /* read */
    res = cs1237_read(&gs_handle, &raw, mv);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read temperature
 * @param[out] *degrees pointer to a degrees buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 * @note       none
 */
uint8_t cs1237_basic_read_temperature(float *degrees)
{
    uint8_t res;
    int32_t raw;
    
    /* set channel temperature */
    res = cs1237_set_channel(&gs_handle, CS1237_CHANNEL_TEMPERATURE);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set pga 1 */
    res = cs1237_set_pga(&gs_handle, CS1237_PGA_1);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* read */
    res = cs1237_read_temperature(&gs_handle, &raw, degrees);
    if (res != 0)
    {
        return 1;
    }
    
    /* set default channel */
    res = cs1237_set_channel(&gs_handle, CS1237_BASIC_DEFAULT_CHANNEL);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pga */
    res = cs1237_set_pga(&gs_handle, CS1237_BASIC_DEFAULT_PGA);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t cs1237_basic_deinit(void)
{
    uint8_t res;
    
    /* deinit cs1237 */
    res = cs1237_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example wake up
 * @return status code
 *         - 0 success
 *         - 1 wake up failed
 * @note   none
 */
uint8_t cs1237_basic_wake_up(void)
{
    uint8_t res;
    
    /* wake up */
    res = cs1237_wake_up(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example power down
 * @return status code
 *         - 0 success
 *         - 1 power down failed
 * @note   none
 */
uint8_t cs1237_basic_power_down(void)
{
    uint8_t res;
    
    /* power down */
    res = cs1237_power_down(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
