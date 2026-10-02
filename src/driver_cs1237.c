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
 * @file      driver_cs1237.c
 * @brief     driver cs1237 source file
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

#include "driver_cs1237.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "CHIPSEA CS1237"        /**< chip name */
#define MANUFACTURER_NAME         "CHIPSEA"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.0f                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                    /**< chip max supply voltage */
#define MAX_CURRENT               2.34f                   /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                   /**< chip max operating temperature */
#define DRIVER_VERSION            1000                    /**< driver version */

/**
 * @brief chip command definition
 */
#define CS1237_COMMAND_READ         0x56        /**< read command */
#define CS1237_COMMAND_WRITE        0x65        /**< write command */

/**
 * @brief      check ready
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *ready pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 check ready failed
 * @note       none
 */
static uint8_t a_cs1237_check_ready(cs1237_handle_t *handle, uint8_t *ready)
{
    uint8_t level;
    uint16_t timeout = 500;                                                 /* 500ms */
    
    while (timeout != 0)                                                    /* loop */
    {
        timeout--;                                                          /* timeout-- */
        
        if (handle->dout_gpio_read(&level) != 0)                            /* read level */
        {
            handle->debug_print("cs1237: dout gpio read failed.\n");        /* dout gpio read failed */
            
            return 1;                                                       /* return error */
        }
        
        if (level == 0)                                                     /* check low */
        {
            *ready = 1;                                                     /* set true */
            
            return 0;                                                       /* return ok */
        }
        
        handle->delay_ms(1);                                                /* delay 1ms */
    }
    
    *ready = 0;                                                             /* set false */
    
    return 0;                                                               /* return ok */
}

/**
 * @brief      read data
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_cs1237_read_data(cs1237_handle_t *handle, int32_t *data)
{
    uint8_t i;
    uint8_t level;
    uint8_t ready;
    uint32_t raw = 0;                                                        /* init 0 */
    
    if (a_cs1237_check_ready(handle, &ready) != 0)                           /* check ready */
    {
        return 1;                                                            /* return error */
    }
    if (ready == 0)                                                          /* check ready */
    {
        handle->debug_print("cs1237: data is not ready.\n");                 /* data is not ready */
        
        return 1;                                                            /* return error */
    }
    
    for (i = 0; i < 24; i++)                                                 /* 24bits */
    {
        if (handle->sclk_gpio_write(1) != 0)                                 /* set high */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        if (handle->sclk_gpio_write(0) != 0)                                 /* set low */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        
        raw <<= 1;                                                           /* left shift */
        
        if (handle->dout_gpio_read(&level) != 0)                             /* read level */
        {
            handle->debug_print("cs1237: dout gpio read failed.\n");         /* dout gpio read failed */
            
            return 1;                                                        /* return error */
        }
        
        if (level != 0)                                                      /* high level */
        {
            raw |= 0x01;                                                     /* set bit */
        }
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    if ((raw & 0x800000U) != 0)                                              /* check msb */
    {
        raw |= 0xFF000000U;                                                  /* set negative */
    }
    
    *data = (int32_t)(raw);                                                  /* set output */
    
    return 0;                                                                /* return ok */
}

/**
 * @brief     write config
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] command input command
 * @param[in] configuration input configuration
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_cs1237_write_config(cs1237_handle_t *handle, uint8_t command, uint8_t configuration)
{
    uint8_t i;
    uint8_t cmd;
    uint8_t config;
    uint8_t level;
    int32_t data;
    
    if (a_cs1237_read_data(handle, &data) != 0)                              /* read data */
    {
        return 1;                                                            /* return error */
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    cmd = command;                                                           /* set command */
    for (i = 0; i < 7; i++)                                                  /* loop */
    {
        if (handle->dout_gpio_write((cmd & 0x40) ? 1 : 0) != 0)              /* write level */
        {
            handle->debug_print("cs1237: dout gpio write failed.\n");        /* dout gpio write failed */
            
            return 1;                                                        /* return error */
        }
        
        if (handle->sclk_gpio_write(1) != 0)                                 /* set high */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        if (handle->sclk_gpio_write(0) != 0)                                 /* set low */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        
        cmd <<= 1;                                                           /* left shift */
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    config = configuration;                                                  /* set config */
    for (i = 0; i < 8; i++)                                                  /* loop */
    {
        if (handle->dout_gpio_write((config & 0x80) ? 1 : 0) != 0)           /* write level */
        {
            handle->debug_print("cs1237: dout gpio write failed.\n");        /* dout gpio write failed */
            
            return 1;                                                        /* return error */
        }
        
        if (handle->sclk_gpio_write(1) != 0)                                 /* set high */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        if (handle->sclk_gpio_write(0) != 0)                                 /* set low */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        
        config <<= 1;                                                        /* left shift */
    }
    
    if (handle->dout_gpio_read(&level) != 0)                                 /* read level */
    {
        handle->debug_print("cs1237: dout gpio read failed.\n");             /* dout gpio read failed */
        
        return 1;                                                            /* return error */
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    return 0;                                                                /* return ok */
}

/**
 * @brief      read config
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[in]  command input command
 * @param[out] *configuration pointer to an output configuration buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_cs1237_read_config(cs1237_handle_t *handle, uint8_t command, uint8_t *configuration)
{
    uint8_t i;
    uint8_t cmd;
    uint8_t config;
    uint8_t level;
    int32_t data;
    
    if (a_cs1237_read_data(handle, &data) != 0)                              /* read data */
    {
        return 1;                                                            /* return error */
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    cmd = command;                                                           /* set command */
    for (i = 0; i < 7; i++)                                                  /* loop */
    {
        if (handle->dout_gpio_write((cmd & 0x40) ? 1 : 0) != 0)              /* write level */
        {
            handle->debug_print("cs1237: dout gpio write failed.\n");        /* dout gpio write failed */
            
            return 1;                                                        /* return error */
        }
        
        if (handle->sclk_gpio_write(1) != 0)                                 /* set high */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        if (handle->sclk_gpio_write(0) != 0)                                 /* set low */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        
        cmd <<= 1;                                                           /* left shift */
    }
    
    if (handle->dout_gpio_read(&level) != 0)                                 /* change to read mode */
    {
        handle->debug_print("cs1237: dout gpio read failed.\n");             /* dout gpio read failed */
        
        return 1;                                                            /* return error */
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    
    config = 0;                                                              /* set 0 */
    for (i = 0; i < 8; i++)                                                  /* loop */
    {
        if (handle->sclk_gpio_write(1) != 0)                                 /* set high */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        if (handle->sclk_gpio_write(0) != 0)                                 /* set low */
        {
            handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
            
            return 1;                                                        /* return error */
        }
        handle->delay_us(CS1237_COMMAND_DATA_DELAY);                         /* delay */
        
        config <<= 1;                                                        /* left shift */
        
        if (handle->dout_gpio_read(&level) != 0)                             /* read level */
        {
            handle->debug_print("cs1237: dout gpio read failed.\n");         /* dout gpio read failed */
            
            return 1;                                                        /* return error */
        }
        
        if (level != 0)                                                      /* high level */
        {
            config |= 0x01;                                                  /* set bit */
        }
    }
    
    if (handle->sclk_gpio_write(1) != 0)                                     /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    if (handle->sclk_gpio_write(0) != 0)                                     /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");            /* sclk gpio write failed */
        
        return 1;                                                            /* return error */
    }
    handle->delay_us(CS1237_COMMAND_DATA_DELAY);                             /* delay */
    *configuration = config;                                                 /* set config */
    
    return 0;                                                                /* return ok */
}

/**
 * @brief     power down
 * @param[in] *handle pointer to a cs1237 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 * @note      none
 */
static uint8_t a_cs1237_power_down(cs1237_handle_t *handle)
{
    if (handle->sclk_gpio_write(1) != 0)                                 /* set high */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
        
        return 1;                                                        /* return error */
    }
    handle->delay_us(150);                                               /* delay 150us */
    
    return 0;                                                            /* return ok */
}

/**
 * @brief     wake up
 * @param[in] *handle pointer to a cs1237 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 wake up failed
 * @note      none
 */
static uint8_t a_cs1237_wake_up(cs1237_handle_t *handle)
{
    if (handle->sclk_gpio_write(0) != 0)                                 /* set low */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");        /* sclk gpio write failed */
        
        return 1;                                                        /* return error */
    }
    handle->delay_us(20);                                                /* delay 20us */
    
    return 0;                                                            /* return ok */
}

/**
 * @brief     set reference voltage
 * @param[in] *handle pointer to a cs1237 handle structure
 * @param[in] volt reference voltage
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t cs1237_set_reference_voltage(cs1237_handle_t *handle, float volt)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    
    handle->reference_voltage_v = volt;        /* set volt */
    
    return 0;                                  /* return ok */
}

/**
 * @brief      get reference voltage
 * @param[in]  *handle pointer to a cs1237 handle structure
 * @param[out] *volt pointer to a reference voltage buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs1237_get_reference_voltage(cs1237_handle_t *handle, float *volt)
{
    if (handle == NULL)                        /* check handle */
    {
        return 2;                              /* return error */
    }
    
    *volt = handle->reference_voltage_v;       /* set volt */
    
    return 0;                                  /* return ok */
}

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
uint8_t cs1237_set_temperature_calibration_point(cs1237_handle_t *handle, int32_t temperature_raw, float temperature_deg)
{
    if (handle == NULL)                               /* check handle */
    {
        return 2;                                     /* return error */
    }
    
    handle->temperature_raw = temperature_raw;        /* set temperature raw */
    handle->temperature_deg = temperature_deg;        /* set temperature degrees */
    
    return 0;                                         /* return ok */
}

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
uint8_t cs1237_get_temperature_calibration_point(cs1237_handle_t *handle, int32_t *temperature_raw, float *temperature_deg)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    
    *temperature_raw = handle->temperature_raw;        /* set temperature raw */
    *temperature_deg = handle->temperature_deg;        /* set temperature degrees */
    
    return 0;                                          /* return ok */
}

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
uint8_t cs1237_set_reference_voltage_output(cs1237_handle_t *handle, cs1237_bool_t enable)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);          /* read config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    config &= ~(1 << 6);                                                       /* clear settings */
    config |= !enable << 6;                                                    /* set bool */
    res =  a_cs1237_write_config(handle, CS1237_COMMAND_WRITE, config);        /* write config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t cs1237_get_reference_voltage_output(cs1237_handle_t *handle, cs1237_bool_t *enable)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        return 1;                                                            /* return error */
    }
    *enable = (cs1237_bool_t)(!((config >> 6) & 0x01));                      /* set bool */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t cs1237_set_adc_rate(cs1237_handle_t *handle, cs1237_adc_rate_t rate)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);          /* read config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    config &= ~(3 << 4);                                                       /* clear settings */
    config |= rate << 4;                                                       /* set rate */
    res =  a_cs1237_write_config(handle, CS1237_COMMAND_WRITE, config);        /* write config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t cs1237_get_adc_rate(cs1237_handle_t *handle, cs1237_adc_rate_t *rate)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        return 1;                                                            /* return error */
    }
    *rate = (cs1237_adc_rate_t)((config >> 4) & 0x03);                       /* set rate */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t cs1237_set_pga(cs1237_handle_t *handle, cs1237_pga_t pga)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);          /* read config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    config &= ~(3 << 2);                                                       /* clear settings */
    config |= pga << 2;                                                        /* set pga */
    res =  a_cs1237_write_config(handle, CS1237_COMMAND_WRITE, config);        /* write config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    
    if (pga == CS1237_PGA_1)                                                   /* pga 1 */
    {
        handle->pga = 1;                                                       /* set 1 */
    }
    else if (pga == CS1237_PGA_2)                                              /* pga 2 */
    {
        handle->pga = 2;                                                       /* set 2 */
    }
    else if (pga == CS1237_PGA_64)                                             /* pga 64 */
    {
        handle->pga = 64;                                                      /* set 64 */
    }
    else                                                                       /* pga 128 */
    {
        handle->pga = 128;                                                     /* set 128 */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t cs1237_get_pga(cs1237_handle_t *handle, cs1237_pga_t *pga)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        return 1;                                                            /* return error */
    }
    *pga = (cs1237_pga_t)((config >> 2) & 0x03);                             /* set pga */
    
    if ((*pga) == CS1237_PGA_1)                                              /* pga 1 */
    {
        handle->pga = 1;                                                     /* set 1 */
    }
    else if ((*pga) == CS1237_PGA_2)                                         /* pga 2 */
    {
        handle->pga = 2;                                                     /* set 2 */
    }
    else if ((*pga) == CS1237_PGA_64)                                        /* pga 64 */
    {
        handle->pga = 64;                                                    /* set 64 */
    }
    else                                                                     /* pga 128 */
    {
        handle->pga = 128;                                                   /* set 128 */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t cs1237_set_channel(cs1237_handle_t *handle, cs1237_channel_t channel)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);          /* read config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    config &= ~(3 << 0);                                                       /* clear settings */
    config |= channel << 0;                                                    /* set channel */
    res =  a_cs1237_write_config(handle, CS1237_COMMAND_WRITE, config);        /* write config */
    if (res != 0)                                                              /* check error */
    {
        return 1;                                                              /* return error */
    }
    
    if (channel == CS1237_CHANNEL_A)                                           /* channel a */
    {
        handle->channel = (uint8_t)CS1237_CHANNEL_A;                           /* set channel a */
    }
    else if (channel == CS1237_CHANNEL_TEMPERATURE)                            /* channel temperature */
    {
        handle->channel = (uint8_t)CS1237_CHANNEL_TEMPERATURE;                 /* set channel temperature */
    }
    else                                                                       /* channel short circuit */
    {
        handle->channel = (uint8_t)CS1237_CHANNEL_SHORT_CIRCUIT;               /* set channel short circuit */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t cs1237_get_channel(cs1237_handle_t *handle, cs1237_channel_t *channel)
{
    uint8_t res;
    uint8_t config;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_cs1237_read_config(handle, CS1237_COMMAND_READ, &config);        /* read config */
    if (res != 0)                                                            /* check error */
    {
        return 1;                                                            /* return error */
    }
    *channel = (cs1237_channel_t)((config >> 0) & 0x03);                     /* set channel */
    
    if ((*channel) == CS1237_CHANNEL_A)                                      /* channel a */
    {
        handle->channel = (uint8_t)CS1237_CHANNEL_A;                         /* set channel a */
    }
    else if ((*channel) == CS1237_CHANNEL_TEMPERATURE)                       /* channel temperature */
    {
        handle->channel = (uint8_t)CS1237_CHANNEL_TEMPERATURE;               /* set channel temperature */
    }
    else                                                                     /* channel short circuit */
    {
        handle->channel = (uint8_t)CS1237_CHANNEL_SHORT_CIRCUIT;             /* set channel short circuit */
    }
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t cs1237_power_down(cs1237_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }
    
    res = a_cs1237_power_down(handle);        /* power down */
    if (res != 0)                             /* check error */
    {
        return 1;                             /* return error */
    }
    
    return 0;                                 /* success return 0 */
}

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
uint8_t cs1237_wake_up(cs1237_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }
    
    res = a_cs1237_wake_up(handle);        /* wake up */
    if (res != 0)                          /* check error */
    {
        return 1;                          /* return error */
    }
    
    return 0;                              /* success return 0 */
}

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
uint8_t cs1237_read(cs1237_handle_t *handle, int32_t *raw, double *mv)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (handle->channel == (uint8_t)CS1237_CHANNEL_TEMPERATURE)              /* check channel */
    {
        handle->debug_print("cs1237: can't be temperature channel.\n");      /* can't be temperature channel */
        
        return 4;                                                            /* return error */
    }
    
    res = a_cs1237_read_data(handle, raw);                                   /* read data */
    if (res != 0)                                                            /* check error */
    {
        return 1;                                                            /* return error */
    }
    
    *mv = (double)(*raw) * 
          (0.5 * handle->reference_voltage_v / (double)handle->pga) / 
           8388607.0 * 1000.0;                                               /* set mv */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t cs1237_read_temperature(cs1237_handle_t *handle, int32_t *raw, float *degrees)
{
    uint8_t res;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if (handle->channel != (uint8_t)CS1237_CHANNEL_TEMPERATURE)              /* check channel */
    {
        handle->debug_print("cs1237: not temperature channel.\n");           /* not temperature channel */
        
        return 4;                                                            /* return error */
    }
    if (handle->pga != 1)                                                    /* check pga */
    {
        handle->debug_print("cs1237: pga must be 1.\n");                     /* pga must be 1 */
        
        return 5;                                                            /* return error */
    }
    if (handle->temperature_raw == 0)                                        /* check 0 */
    {
        handle->debug_print("cs1237: temperature raw can't be 0.\n");        /* temperature raw can't be 0 */
        
        return 6;                                                            /* return error */
    }
    
    res = a_cs1237_read_data(handle, raw);                                   /* read data */
    if (res != 0)                                                            /* check error */
    {
        return 1;                                                            /* return error */
    }
    
    *degrees = ((float)(*raw) * (273.15f + handle->temperature_deg) /
                (float)handle->temperature_raw) - 273.15f;                   /* set degrees */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t cs1237_init(cs1237_handle_t *handle)
{
    uint8_t res;
    uint8_t level;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->debug_print == NULL)                                       /* check debug_print */
    {
        return 3;                                                          /* return error */
    }
    if (handle->sclk_gpio_init == NULL)                                    /* check sclk_gpio_init */
    {
        handle->debug_print("cs1237: sclk_gpio_init is null.\n");          /* sclk_gpio_init is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->sclk_gpio_deinit == NULL)                                  /* check sclk_gpio_deinit */
    {
        handle->debug_print("cs1237: sclk_gpio_deinit is null.\n");        /* sclk_gpio_deinit is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->sclk_gpio_write == NULL)                                   /* check sclk_gpio_write */
    {
        handle->debug_print("cs1237: sclk_gpio_write is null.\n");         /* sclk_gpio_write is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->dout_gpio_init == NULL)                                    /* check dout_gpio_init */
    {
        handle->debug_print("cs1237: dout_gpio_init is null.\n");          /* dout_gpio_init is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->dout_gpio_deinit == NULL)                                  /* check dout_gpio_deinit */
    {
        handle->debug_print("cs1237: dout_gpio_deinit is null.\n");        /* dout_gpio_deinit is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->dout_gpio_write == NULL)                                   /* check dout_gpio_write */
    {
        handle->debug_print("cs1237: dout_gpio_write is null.\n");         /* dout_gpio_write is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->dout_gpio_read == NULL)                                    /* check dout_gpio_read */
    {
        handle->debug_print("cs1237: dout_gpio_read is null.\n");          /* dout_gpio_read is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->delay_us == NULL)                                          /* check delay_us */
    {
        handle->debug_print("cs1237: delay_us is null.\n");                /* delay_us is null */
        
        return 3;                                                          /* return error */
    }
    if (handle->delay_ms == NULL)                                          /* check delay_ms */
    {
        handle->debug_print("cs1237: delay_ms is null.\n");                /* delay_ms is null */
        
        return 3;                                                          /* return error */
    }
    
    res = handle->sclk_gpio_init();                                        /* sclk gpio init */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("cs1237: sclk gpio init failed.\n");           /* sclk gpio init failed */
        
        return 1;                                                          /* return error */
    }
    res = handle->dout_gpio_init();                                        /* dout gpio init */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("cs1237: dout gpio init failed.\n");           /* dout gpio init failed */
        (void)handle->sclk_gpio_deinit();                                  /* sclk gpio deinit */
        
        return 1;                                                          /* return error */
    }

    res = handle->sclk_gpio_write(0);                                      /* set low */
    if (res != 0)                                                          /* check result */
    {
        handle->debug_print("cs1237: sclk gpio write failed.\n");          /* sclk gpio write failed */
        (void)handle->sclk_gpio_deinit();                                  /* sclk gpio deinit */
        (void)handle->dout_gpio_deinit();                                  /* dout gpio deinit */
        
        return 1;                                                          /* return error */
    }
    if (handle->dout_gpio_read(&level) != 0)                               /* change to read mode */
    {
        handle->debug_print("cs1237: dout gpio read failed.\n");           /* dout gpio read failed */
        (void)handle->sclk_gpio_deinit();                                  /* sclk gpio deinit */
        (void)handle->dout_gpio_deinit();                                  /* dout gpio deinit */
        
        return 1;                                                          /* return error */
    }
    handle->pga = 128;                                                     /* set 128 */
    handle->channel = (uint8_t)CS1237_CHANNEL_A;                           /* set channel a */
    handle->inited = 1;                                                    /* flag inited */
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t cs1237_deinit(cs1237_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_cs1237_power_down(handle);                                    /* write command */
    if (res != 0)                                                         /* check error */
    {
        return 4;                                                         /* return error */
    }
    
    res = handle->sclk_gpio_deinit();                                     /* sclk gpio deinit */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("cs1237: sclk gpio deinit failed.\n");        /* sclk gpio deinit failed */
        
        return 1;                                                         /* return error */
    }
    res = handle->dout_gpio_deinit();                                     /* dout gpio deinit */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("cs1237: dout gpio deinit failed.\n");        /* dout gpio deinit failed */
        
        return 1;                                                         /* return error */
    }
    
    handle->inited = 0;                                                   /* flag close */
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t cs1237_set_command(cs1237_handle_t *handle, uint8_t command, uint8_t config)
{
    uint8_t res;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    res = a_cs1237_write_config(handle, command, config);        /* write */
    if (res != 0)                                                /* check error */
    {
        return 1;                                                /* return error */
    }
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t cs1237_get_command(cs1237_handle_t *handle, uint8_t command, uint8_t *config)
{
    uint8_t res;
    
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }
    
    res = a_cs1237_read_config(handle, command, config);        /* read */
    if (res != 0)                                               /* check error */
    {
        return 1;                                               /* return error */
    }
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t cs1237_get_data(cs1237_handle_t *handle, int32_t *data)
{
    uint8_t res;
    
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    if (handle->inited != 1)                       /* check handle initialization */
    {
        return 3;                                  /* return error */
    }
    
    res = a_cs1237_read_data(handle, data);        /* read data */
    if (res != 0)                                  /* check error */
    {
        return 1;                                  /* return error */
    }
    
    return 0;                                      /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a cs1237 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs1237_info(cs1237_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(cs1237_info_t));                         /* initialize cs1237 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set maximum temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set minimal temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
