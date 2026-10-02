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
 * @file      driver_cs1237_register_test.c
 * @brief     driver cs1237 register test source file
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

#include "driver_cs1237_register_test.h"
#include <stdlib.h>

static cs1237_handle_t gs_handle;        /**< cs1237 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t cs1237_register_test(void)
{
    uint8_t res;
    cs1237_bool_t enable;
    cs1237_adc_rate_t rate;
    cs1237_pga_t pga;
    cs1237_channel_t channel;
    cs1237_info_t info;
    
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
    
    /* get information */
    res = cs1237_info(&info);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip info */
        cs1237_interface_debug_print("cs1237: chip is %s.\n", info.chip_name);
        cs1237_interface_debug_print("cs1237: manufacturer is %s.\n", info.manufacturer_name);
        cs1237_interface_debug_print("cs1237: interface is %s.\n", info.interface);
        cs1237_interface_debug_print("cs1237: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        cs1237_interface_debug_print("cs1237: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        cs1237_interface_debug_print("cs1237: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        cs1237_interface_debug_print("cs1237: max current is %0.2fmA.\n", info.max_current_ma);
        cs1237_interface_debug_print("cs1237: max temperature is %0.1fC.\n", info.temperature_max);
        cs1237_interface_debug_print("cs1237: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    cs1237_interface_debug_print("cs1237: start register test.\n");
    
    /* init */
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
    
    /* cs1237_set_reference_voltage_output/cs1237_get_reference_voltage_output test */
    cs1237_interface_debug_print("cs1237: cs1237_set_reference_voltage_output/cs1237_get_reference_voltage_output test.\n");
    
    /* enable reference voltage output */
    res = cs1237_set_reference_voltage_output(&gs_handle, CS1237_BOOL_TRUE);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set reference voltage output failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: enable reference voltage output.\n");
    res = cs1237_get_reference_voltage_output(&gs_handle, &enable);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get reference voltage output failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check reference voltage output %s.\n", (enable == CS1237_BOOL_TRUE) ? "ok" : "error");
    
    /* disable reference voltage output */
    res = cs1237_set_reference_voltage_output(&gs_handle, CS1237_BOOL_FALSE);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set reference voltage output failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: disable reference voltage output.\n");
    res = cs1237_get_reference_voltage_output(&gs_handle, &enable);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get reference voltage output failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check reference voltage output %s.\n", (enable == CS1237_BOOL_FALSE) ? "ok" : "error");
    
    /* cs1237_set_adc_rate/cs1237_get_adc_rate test */
    cs1237_interface_debug_print("cs1237: cs1237_set_adc_rate/cs1237_get_adc_rate test.\n");
    
    /* set adc rate 10hz */
    res = cs1237_set_adc_rate(&gs_handle, CS1237_ADC_RATE_10HZ);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set adc rate 10hz.\n");
    res = cs1237_get_adc_rate(&gs_handle, &rate);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check adc rate %s.\n", (rate == CS1237_ADC_RATE_10HZ) ? "ok" : "error");
    
    /* set adc rate 40hz */
    res = cs1237_set_adc_rate(&gs_handle, CS1237_ADC_RATE_40HZ);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set adc rate 40hz.\n");
    res = cs1237_get_adc_rate(&gs_handle, &rate);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check adc rate %s.\n", (rate == CS1237_ADC_RATE_40HZ) ? "ok" : "error");
    
    /* set adc rate 640hz */
    res = cs1237_set_adc_rate(&gs_handle, CS1237_ADC_RATE_640HZ);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set adc rate 640hz.\n");
    res = cs1237_get_adc_rate(&gs_handle, &rate);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check adc rate %s.\n", (rate == CS1237_ADC_RATE_640HZ) ? "ok" : "error");
    
    /* set adc rate 1280hz */
    res = cs1237_set_adc_rate(&gs_handle, CS1237_ADC_RATE_1280HZ);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set adc rate 1280hz.\n");
    res = cs1237_get_adc_rate(&gs_handle, &rate);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get adc rate failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check adc rate %s.\n", (rate == CS1237_ADC_RATE_1280HZ) ? "ok" : "error");
    
    /* cs1237_set_pga/cs1237_get_pga test */
    cs1237_interface_debug_print("cs1237: cs1237_set_pga/cs1237_get_pga test.\n");
    
    /* set pga 1 */
    res = cs1237_set_pga(&gs_handle, CS1237_PGA_1);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set pga 1.\n");
    res = cs1237_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check pga %s.\n", (pga == CS1237_PGA_1) ? "ok" : "error");
    
    /* set pga 2 */
    res = cs1237_set_pga(&gs_handle, CS1237_PGA_2);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set pga 2.\n");
    res = cs1237_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check pga %s.\n", (pga == CS1237_PGA_2) ? "ok" : "error");
    
    /* set pga 64 */
    res = cs1237_set_pga(&gs_handle, CS1237_PGA_64);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set pga 64.\n");
    res = cs1237_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check pga %s.\n", (pga == CS1237_PGA_64) ? "ok" : "error");
    
    /* set pga 128 */
    res = cs1237_set_pga(&gs_handle, CS1237_PGA_128);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set pga 128.\n");
    res = cs1237_get_pga(&gs_handle, &pga);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get pga failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check pga %s.\n", (pga == CS1237_PGA_128) ? "ok" : "error");
    
    /* cs1237_set_channel/cs1237_get_channel test */
    cs1237_interface_debug_print("cs1237: cs1237_set_channel/cs1237_get_channel test.\n");
    
    /* set channel short circuit */
    res = cs1237_set_channel(&gs_handle, CS1237_CHANNEL_SHORT_CIRCUIT);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set channel short circuit.\n");
    res = cs1237_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check channel %s.\n", (channel == CS1237_CHANNEL_SHORT_CIRCUIT) ? "ok" : "error");
    
    /* set channel temperature */
    res = cs1237_set_channel(&gs_handle, CS1237_CHANNEL_TEMPERATURE);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set channel temperature.\n");
    res = cs1237_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check channel %s.\n", (channel == CS1237_CHANNEL_TEMPERATURE) ? "ok" : "error");
    
    /* set channel a */
    res = cs1237_set_channel(&gs_handle, CS1237_CHANNEL_A);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: set channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    cs1237_interface_debug_print("cs1237: set channel a.\n");
    res = cs1237_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: get channel failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check channel %s.\n", (channel == CS1237_CHANNEL_A) ? "ok" : "error");
    
    /* cs1237_wake_up test */
    cs1237_interface_debug_print("cs1237: cs1237_wake_up test.\n");
    
    /* wake up */
    res = cs1237_wake_up(&gs_handle);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: wake up failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check wake up %s.\n", (res == 0) ? "ok" : "error");
    
    /* cs1237_power_down test */
    cs1237_interface_debug_print("cs1237: cs1237_wake_up test.\n");
    
    /* power down */
    res = cs1237_power_down(&gs_handle);
    if (res != 0)
    {
        cs1237_interface_debug_print("cs1237: power down failed.\n");
        (void)cs1237_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    cs1237_interface_debug_print("cs1237: check power down %s.\n", (res == 0) ? "ok" : "error");
    
    /* finish register test */
    cs1237_interface_debug_print("cs1237: finish register test.\n");
    (void)cs1237_deinit(&gs_handle);
    
    return 0;
}
