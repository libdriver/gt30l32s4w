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
 * @date      2023-09-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/09/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_gt30l32s4w_basic.h"
#include "driver_gt30l32s4w_read_test.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     gt30l32s4w full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t gt30l32s4w(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"ch", required_argument, NULL, 1},
        {"font", required_argument, NULL, 2},
        {"type", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint16_t ch = 'A';
    char font[17] = "32";
    gt30l32s4w_basic_type_t font_type = GT30L32S4W_BASIC_TYPE_ARIAL;

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

            /* char */
            case 1 :
            {
                /* set the char*/
                uint16_t l = (uint16_t)strlen(optarg);
                if (l == 1)
                {
                    ch = optarg[0];
                }
                else if (l >= 2)
                {
                    ch = optarg[0] * 256 + optarg[1];
                }
                else
                {

                }

                break;
            }

            /* font */
            case 2 :
            {
                /* set the font */
                memset(font, 0, sizeof(char) * 17);
                snprintf(font, 17, "%s", optarg);

                break;
            }

            /* font type */
            case 3 :
            {
                if (strcmp("arial", optarg) == 0)
                {
                    font_type = GT30L32S4W_BASIC_TYPE_ARIAL;
                }
                else if (strcmp("times", optarg) == 0)
                {
                    font_type = GT30L32S4W_BASIC_TYPE_TIMES;
                }
                else
                {

                }

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
    if (strcmp("t_read", type) == 0)
    {
        uint8_t res;

        /* run read test */
        res = gt30l32s4w_read_test();
        if (res != 0)
        {
            return 1;
        }

        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = gt30l32s4w_basic_init();
        if (res != 0)
        {
            return 1;
        }

        if (strcmp(font, "12") == 0)
        {
            uint8_t buf[24];
            uint8_t len;

            /* read 12 */
            res = gt30l32s4w_basic_read_12(ch, buf, &len);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            if (len == 12)
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_6X12_ASCII, buf, 12);
            }
            else
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_12X12_GB2312, buf, 24);
            }

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "16") == 0)
        {
            uint8_t buf[32];
            uint8_t len;

            /* read 16 */
            res = gt30l32s4w_basic_read_16(ch, buf, &len);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            if (len == 16)
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_8X16_ASCII, buf, 16);
            }
            else
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_15X16_GB2312, buf, 32);
            }

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "24") == 0)
        {
            uint8_t buf[72];
            uint8_t len;

            /* read 24 */
            res = gt30l32s4w_basic_read_24(ch, buf, &len);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            if (len == 48)
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_12X24_ASCII, buf, 48);
            }
            else
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_24X24_GB2312, buf, 72);
            }

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "32") == 0)
        {
            uint8_t buf[128];
            uint8_t len;

            /* read 32 */
            res = gt30l32s4w_basic_read_32(ch, buf, &len);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            if (len == 64)
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_16X32_ASCII, buf, 64);
            }
            else
            {
                (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_32X32_GB2312, buf, 128);
            }

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "ascii-7") == 0)
        {
            uint8_t buf[8];

            /* read ascii 7 */
            res = gt30l32s4w_basic_read_ascii_7(ch, buf);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_5X7_ASCII, buf, 8);

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "ascii-8") == 0)
        {
            uint8_t buf[8];

            /* read ascii 8 */
            res = gt30l32s4w_basic_read_ascii_8(ch, buf);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_7X8_ASCII, buf, 8);

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "ascii-12") == 0)
        {
            uint8_t buf[26];

            /* read ascii 12 */
            res = gt30l32s4w_basic_read_ascii_12_with_length(font_type, ch, buf);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_12_ARIAL_ASCII, buf, 26);

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "ascii-16") == 0)
        {
            uint8_t buf[34];

            /* read ascii 16 */
            res = gt30l32s4w_basic_read_ascii_16_with_length(font_type, ch, buf);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_16_ARIAL_ASCII, buf, 34);

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "ascii-24") == 0)
        {
            uint8_t buf[74];

            /* read ascii 24 */
            res = gt30l32s4w_basic_read_ascii_24_with_length(font_type, ch, buf);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_24_ARIAL_ASCII, buf, 74);

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else if (strcmp(font, "ascii-32") == 0)
        {
            uint8_t buf[130];

            /* read ascii 32 */
            res = gt30l32s4w_basic_read_ascii_32_with_length(font_type, ch, buf);
            if (res != 0)
            {
                /* basic deinit */
                (void)gt30l32s4w_basic_deinit();

                return 1;
            }

            /* print */
            (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_32_ARIAL_ASCII, buf, 130);

            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 0;
        }
        else
        {
            /* basic deinit */
            (void)gt30l32s4w_basic_deinit();

            return 5;
        }
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        gt30l32s4w_interface_debug_print("Usage:\n");
        gt30l32s4w_interface_debug_print("  gt30l32s4w (-i | --information)\n");
        gt30l32s4w_interface_debug_print("  gt30l32s4w (-h | --help)\n");
        gt30l32s4w_interface_debug_print("  gt30l32s4w (-p | --port)\n");
        gt30l32s4w_interface_debug_print("  gt30l32s4w (-t read | --test=read)\n");
        gt30l32s4w_interface_debug_print("  gt30l32s4w (-e read | --example=read) [--font=<12 | 16 | 24 | 32 | ascii-7 | ascii-8 | ascii-12 | ascii-16 | ascii-24 | ascii-32>]\n");
        gt30l32s4w_interface_debug_print("             [--ch=<char>] [--type=<arial | times>]\n");
        gt30l32s4w_interface_debug_print("\n");
        gt30l32s4w_interface_debug_print("Options:\n");
        gt30l32s4w_interface_debug_print("      --ch=<char>                Set the display char, char is the display char.([default: A])\n");
        gt30l32s4w_interface_debug_print("  -e <read>, --example=<read>    Run the driver example.\n");
        gt30l32s4w_interface_debug_print("      --font=<12 | 16 | 24 | 32 | ascii-7 | ascii-8 | ascii-12 | ascii-16 | ascii-24 | ascii-32>\n");
        gt30l32s4w_interface_debug_print("                                 Set display font.([default: 32])\n");
        gt30l32s4w_interface_debug_print("  -h, --help                     Show the help.\n");
        gt30l32s4w_interface_debug_print("  -i, --information              Show the chip information.\n");
        gt30l32s4w_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        gt30l32s4w_interface_debug_print("  -t <read>, --test=<read>       Run the driver test.\n");
        gt30l32s4w_interface_debug_print("      --type=<arial | times>     Set font type.([default: arial])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        gt30l32s4w_info_t info;

        /* print gt30l32s4w info */
        gt30l32s4w_info(&info);
        gt30l32s4w_interface_debug_print("gt30l32s4w: chip is %s.\n", info.chip_name);
        gt30l32s4w_interface_debug_print("gt30l32s4w: manufacturer is %s.\n", info.manufacturer_name);
        gt30l32s4w_interface_debug_print("gt30l32s4w: interface is %s.\n", info.interface);
        gt30l32s4w_interface_debug_print("gt30l32s4w: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        gt30l32s4w_interface_debug_print("gt30l32s4w: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        gt30l32s4w_interface_debug_print("gt30l32s4w: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        gt30l32s4w_interface_debug_print("gt30l32s4w: max current is %0.2fmA.\n", info.max_current_ma);
        gt30l32s4w_interface_debug_print("gt30l32s4w: max temperature is %0.1fC.\n", info.temperature_max);
        gt30l32s4w_interface_debug_print("gt30l32s4w: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        gt30l32s4w_interface_debug_print("gt30l32s4w: SCK connected to GPIO11(BCM).\n");
        gt30l32s4w_interface_debug_print("gt30l32s4w: MISO connected to GPIO9(BCM).\n");
        gt30l32s4w_interface_debug_print("gt30l32s4w: MOSI connected to GPIO10(BCM).\n");
        gt30l32s4w_interface_debug_print("gt30l32s4w: CS connected to GPIO8(BCM).\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = gt30l32s4w(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: run failed.\n");
    }
    else if (res == 5)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: param is invalid.\n");
    }
    else
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: unknown status code.\n");
    }

    return 0;
}
