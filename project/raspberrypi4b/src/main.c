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
 * @file      main.c
 * @brief     main source file
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
#include "driver_cs1237_read_test.h"
#include "driver_cs1237_basic.h"
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief     cs1237 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t cs1237(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    char short_options[] = "hipe:t:";
    struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"ref", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {"temp-raw", required_argument, NULL, 3},
        {"temp-deg", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    float ref = 3.3f;
    uint32_t times = 3;
    int32_t temperature_raw = 0;
    float temperature_deg = 0.0f;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* reference voltage */
            case 1 :
            {
                /* reference voltage */
                ref = (float)atof(optarg);

                break;
            }

            /* times */
            case 2 :
            {
                /* convert times */
                times = (uint32_t)atol(optarg);
                
                break;
            }
            
            /* temperature raw */
            case 3 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                temperature_raw = hex_data & 0xFFFFFFFF;
                
                break;
            }
            
            /* temperature deg */
            case 4 :
            {
                /* convert temperature */
                temperature_deg = (float)atof(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run the register test */
        if (cs1237_register_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run the output test */
        if (cs1237_read_test(ref, temperature_raw, temperature_deg, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* init */
        res = cs1237_basic_init(ref, temperature_raw, temperature_deg);
        if (res != 0)
        {
            return 1;
        }
        
        for (i = 0; i < times; i++)
        {
            double mv;
            
            /* delay 1000ms */
            cs1237_interface_delay_ms(1000);
            
            /* read data */
            res = cs1237_basic_read(&mv);
            if (res != 0)
            {
                cs1237_interface_debug_print("cs1237: read failed.\n");
                (void)cs1237_basic_deinit();
                
                return 1;
            }
            
            /* output */
            cs1237_interface_debug_print("cs1237: adc is %fmV.\n", mv);
        }
        
        /* deinit */
        (void)cs1237_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_temperature", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* init */
        res = cs1237_basic_init(ref, temperature_raw, temperature_deg);
        if (res != 0)
        {
            return 1;
        }
        
        for (i = 0; i < times; i++)
        {
            float deg;
            
            /* delay 1000ms */
            cs1237_interface_delay_ms(1000);
            
            /* read data */
            res = cs1237_basic_read_temperature(&deg);
            if (res != 0)
            {
                cs1237_interface_debug_print("cs1237: read temperature failed.\n");
                (void)cs1237_basic_deinit();
                
                return 1;
            }
            
            /* output */
            cs1237_interface_debug_print("cs1237: temperature is %0.2fC.\n", deg);
        }
        
        /* deinit */
        (void)cs1237_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        cs1237_interface_debug_print("Usage:\n");
        cs1237_interface_debug_print("  cs1237 (-i | --information)\n");
        cs1237_interface_debug_print("  cs1237 (-h | --help)\n");
        cs1237_interface_debug_print("  cs1237 (-p | --port)\n");
        cs1237_interface_debug_print("  cs1237 (-t reg | --test=reg)\n");
        cs1237_interface_debug_print("  cs1237 (-t read | --test=read) [--ref=<voltage>] [--temp-raw=<hex>] [--temp-deg=<deg>] [--times=<num>]\n");
        cs1237_interface_debug_print("  cs1237 (-e read | --example=read) [--ref=<voltage>] [--times=<num>]\n");
        cs1237_interface_debug_print("  cs1237 (-e temperature | --example=temperature) [--temp-raw=<hex>] [--temp-deg=<deg>] [--times=<num>]\n");
        cs1237_interface_debug_print("\n");
        cs1237_interface_debug_print("Options:\n");
        cs1237_interface_debug_print("  -e <read | temperature>, --example=<read | temperature>\n");
        cs1237_interface_debug_print("                                         Run the driver example.\n");
        cs1237_interface_debug_print("  -h, --help                             Show the help.\n");
        cs1237_interface_debug_print("  -i, --information                      Show the chip information.\n");
        cs1237_interface_debug_print("  -p, --port                             Display the pin connections of the current board.\n");
        cs1237_interface_debug_print("      --ref=<voltage>                    Set the reference voltage.([default: 3.3])\n");
        cs1237_interface_debug_print("  -t <reg | read>, --test=<reg | read>   Run the driver test.\n");
        cs1237_interface_debug_print("      --times=<num>                      Set the test times.([default: 3])\n");
        cs1237_interface_debug_print("      --temp-raw=<hex>                   Set the temperature raw data.([default: 0x0000])\n");
        cs1237_interface_debug_print("      --temp-deg=<deg>                   Set the temperature degree.([default: 0.0])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        cs1237_info_t info;

        /* print cs1237 info */
        cs1237_info(&info);
        cs1237_interface_debug_print("cs1237: chip is %s.\n", info.chip_name);
        cs1237_interface_debug_print("cs1237: manufacturer is %s.\n", info.manufacturer_name);
        cs1237_interface_debug_print("cs1237: interface is %s.\n", info.interface);
        cs1237_interface_debug_print("cs1237: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        cs1237_interface_debug_print("cs1237: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        cs1237_interface_debug_print("cs1237: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        cs1237_interface_debug_print("cs1237: max current is %0.2fmA.\n", info.max_current_ma);
        cs1237_interface_debug_print("cs1237: max temperature is %0.1fC.\n", info.temperature_max);
        cs1237_interface_debug_print("cs1237: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        cs1237_interface_debug_print("cs1237: GPIO interface SCLK connected to GPIO27(BCM).\n");
        cs1237_interface_debug_print("cs1237: GPIO interface DIO connected to GPIO17(BCM).\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = cs1237(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        cs1237_interface_debug_print("cs1237: run failed.\n");
    }
    else if (res == 5)
    {
        cs1237_interface_debug_print("cs1237: param is invalid.\n");
    }
    else
    {
        cs1237_interface_debug_print("cs1237: unknown status code.\n");
    }

    return 0;
}
