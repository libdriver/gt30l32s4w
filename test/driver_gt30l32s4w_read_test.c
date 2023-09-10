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
 * @file      driver_gt30l32s4w_read_test.c
 * @brief     driver gt30l32s4w read test source file
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

#include "driver_gt30l32s4w_read_test.h"

static gt30l32s4w_handle_t gs_handle;        /**< gt30l32s4w handle */

/**
 * @brief  read test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t gt30l32s4w_read_test(void)
{
    uint8_t res;
    uint8_t buf[130];
    gt30l32s4w_info_t info;
    
    /* link function */
    DRIVER_GT30L32S4W_LINK_INIT(&gs_handle, gt30l32s4w_handle_t);
    DRIVER_GT30L32S4W_LINK_SPI_INIT(&gs_handle, gt30l32s4w_interface_spi_init);
    DRIVER_GT30L32S4W_LINK_SPI_DEINIT(&gs_handle, gt30l32s4w_interface_spi_deinit);
    DRIVER_GT30L32S4W_LINK_SPI_WRITE_READ(&gs_handle, gt30l32s4w_interface_spi_write_read);
    DRIVER_GT30L32S4W_LINK_DELAY_MS(&gs_handle, gt30l32s4w_interface_delay_ms);
    DRIVER_GT30L32S4W_LINK_DEBUG_PRINT(&gs_handle, gt30l32s4w_interface_debug_print);
    
    /* get chip information */
    res = gt30l32s4w_info(&info);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        gt30l32s4w_interface_debug_print("gt30l32s4w: chip is %s.\n", info.chip_name);
        gt30l32s4w_interface_debug_print("gt30l32s4w: manufacturer is %s.\n", info.manufacturer_name);
        gt30l32s4w_interface_debug_print("gt30l32s4w: interface is %s.\n", info.interface);
        gt30l32s4w_interface_debug_print("gt30l32s4w: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        gt30l32s4w_interface_debug_print("gt30l32s4w: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        gt30l32s4w_interface_debug_print("gt30l32s4w: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        gt30l32s4w_interface_debug_print("gt30l32s4w: max current is %0.2fmA.\n", info.max_current_ma);
        gt30l32s4w_interface_debug_print("gt30l32s4w: max temperature is %0.1fC.\n", info.temperature_max);
        gt30l32s4w_interface_debug_print("gt30l32s4w: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: start read test.\n");
    
    /* gt30l32s4w init */
    res = gt30l32s4w_init(&gs_handle);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: init failed.\n");
       
        return 1;
    }
    
    /* normal read test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: normal read test.\n");
    
    /* normal read */
    res = gt30l32s4w_set_mode(&gs_handle, GT30L32S4W_MODE_READ);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: set mode failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
        
        return 1;
    }
    
    /* gt30l32s4w_read_char_12x12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_12x12 test.\n");
    
    /* read char 12x12 */
    res = gt30l32s4w_read_char_12x12(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 12x12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12X12_GB2312, buf, 24);
    
    /* gt30l32s4w_read_char_15x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_15x16 test.\n");
    
    /* read char 15x16 */
    res = gt30l32s4w_read_char_15x16(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 15x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_15X16_GB2312, buf, 32);
    
    /* gt30l32s4w_read_char_24x24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_24x24 test.\n");
    
    /* read char 24x24 */
    res = gt30l32s4w_read_char_24x24(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 24x24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_24X24_GB2312, buf, 72);
    
    /* gt30l32s4w_read_char_32x32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_32x32 test.\n");
    
    /* read char 32x32 */
    res = gt30l32s4w_read_char_32x32(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 32x32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_32X32_GB2312, buf, 128);
    
    /* gt30l32s4w_read_char_extend_6x12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_6x12 test.\n");
    
    /* read char extend 6x12 */
    res = gt30l32s4w_read_char_extend_6x12(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 6x12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_6X12_GB2312_EX, buf, 12);
    
    /* gt30l32s4w_read_char_extend_8x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_8x16 test.\n");
    
    /* read char extend 8x16 */
    res = gt30l32s4w_read_char_extend_8x16(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 8x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_8X16_GB2312_EX, buf, 16);
    
    /* gt30l32s4w_read_char_special_8x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_special_8x16 test.\n");
    
    /* read char special 8x16 */
    res = gt30l32s4w_read_char_special_8x16(&gs_handle, 0xACB1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char special 8x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_8X16_GB2312_SP, buf, 16);
    
    /* gt30l32s4w_read_char_extend_12x24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_12x24 test.\n");
    
    /* read char extend 12x24 */
    res = gt30l32s4w_read_char_extend_12x24(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 12x24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12X24_GB2312_EX, buf, 48);
    
    /* gt30l32s4w_read_char_extend_16x32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_16x32 test.\n");
    
    /* read char extend 16x32 */
    res = gt30l32s4w_read_char_extend_16x32(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 16x32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16X32_GB2312_EX, buf, 64);
    
    /* gt30l32s4w_read_ascii_5x7 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_5x7 test.\n");
    
    /* read ascii 5x7 */
    res = gt30l32s4w_read_ascii_5x7(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 5x7 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_5X7_ASCII, buf, 8);
    
    /* gt30l32s4w_read_ascii_7x8 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_7x8 test.\n");
    
    /* read ascii 7x8 */
    res = gt30l32s4w_read_ascii_7x8(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 7x8 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_7X8_ASCII, buf, 8);
    
    /* gt30l32s4w_read_ascii_6x12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_6x12 test.\n");
    
    /* read ascii 6x12 */
    res = gt30l32s4w_read_ascii_6x12(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 6x12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_6X12_ASCII, buf, 12);
    
    /* gt30l32s4w_read_ascii_8x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_8x16 test.\n");
    
    /* read ascii 8x16 */
    res = gt30l32s4w_read_ascii_8x16(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 8x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_8X16_ASCII, buf, 16);
    
    /* gt30l32s4w_read_ascii_12x24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_12x24 test.\n");
    
    /* read ascii 12x24 */
    res = gt30l32s4w_read_ascii_12x24(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 12x24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12X24_ASCII, buf, 48);
    
    /* gt30l32s4w_read_ascii_16x32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_16x32 test.\n");
    
    /* read ascii 16x32 */
    res = gt30l32s4w_read_ascii_16x32(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 16x32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16X32_ASCII, buf, 64);
    
    /* gt30l32s4w_read_ascii_arial_12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_12 test.\n");
    
    /* read ascii arial 12 */
    res = gt30l32s4w_read_ascii_arial_12(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12_ARIAL_ASCII, buf, 26);
    
    /* gt30l32s4w_read_ascii_times_12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_12 test.\n");
    
    /* read ascii times 12 */
    res = gt30l32s4w_read_ascii_times_12(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12_TIMES_ASCII, buf, 26);
    
    /* gt30l32s4w_read_ascii_arial_16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_16 test.\n");
    
    /* read ascii arial 16 */
    res = gt30l32s4w_read_ascii_arial_16(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16_ARIAL_ASCII, buf, 34);
    
    /* gt30l32s4w_read_ascii_times_16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_16 test.\n");
    
    /* read ascii times 16 */
    res = gt30l32s4w_read_ascii_times_16(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16_TIMES_ASCII, buf, 34);
    
    /* gt30l32s4w_read_ascii_arial_24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_24 test.\n");
    
    /* read ascii arial 24 */
    res = gt30l32s4w_read_ascii_arial_24(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_24_ARIAL_ASCII, buf, 74);
    
    /* gt30l32s4w_read_ascii_times_24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_24 test.\n");
    
    /* read ascii times 24 */
    res = gt30l32s4w_read_ascii_times_24(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_24_TIMES_ASCII, buf, 74);
    
    /* gt30l32s4w_read_ascii_arial_32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_32 test.\n");
    
    /* read ascii arial 32 */
    res = gt30l32s4w_read_ascii_arial_32(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_32_ARIAL_ASCII, buf, 130);
    
    /* gt30l32s4w_read_ascii_times_32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_32 test.\n");
    
    /* read ascii times 32 */
    res = gt30l32s4w_read_ascii_times_32(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_32_TIMES_ASCII, buf, 130);
    
    /* fast read test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: fast read test.\n");
    
    /* fast read */
    res = gt30l32s4w_set_mode(&gs_handle, GT30L32S4W_MODE_FAST_MODE);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: set mode failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
        
        return 1;
    }
    
    /* gt30l32s4w_read_char_12x12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_12x12 test.\n");
    
    /* read char 12x12 */
    res = gt30l32s4w_read_char_12x12(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 12x12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12X12_GB2312, buf, 24);
    
    /* gt30l32s4w_read_char_15x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_15x16 test.\n");
    
    /* read char 15x16 */
    res = gt30l32s4w_read_char_15x16(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 15x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_15X16_GB2312, buf, 32);
    
    /* gt30l32s4w_read_char_24x24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_24x24 test.\n");
    
    /* read char 24x24 */
    res = gt30l32s4w_read_char_24x24(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 24x24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_24X24_GB2312, buf, 72);
    
    /* gt30l32s4w_read_char_32x32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_32x32 test.\n");
    
    /* read char 32x32 */
    res = gt30l32s4w_read_char_32x32(&gs_handle, 0xD7D6U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char 32x32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_32X32_GB2312, buf, 128);
    
    /* gt30l32s4w_read_char_extend_6x12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_6x12 test.\n");
    
    /* read char extend 6x12 */
    res = gt30l32s4w_read_char_extend_6x12(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 6x12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_6X12_GB2312_EX, buf, 12);
    
    /* gt30l32s4w_read_char_extend_8x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_8x16 test.\n");
    
    /* read char extend 8x16 */
    res = gt30l32s4w_read_char_extend_8x16(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 8x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_8X16_GB2312_EX, buf, 16);
    
    /* gt30l32s4w_read_char_special_8x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_special_8x16 test.\n");
    
    /* read char special 8x16 */
    res = gt30l32s4w_read_char_special_8x16(&gs_handle, 0xACB1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char special 8x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_8X16_GB2312_SP, buf, 16);
    
    /* gt30l32s4w_read_char_extend_12x24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_12x24 test.\n");
    
    /* read char extend 12x24 */
    res = gt30l32s4w_read_char_extend_12x24(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 12x24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12X24_GB2312_EX, buf, 48);
    
    /* gt30l32s4w_read_char_extend_16x32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_char_extend_16x32 test.\n");
    
    /* read char extend 16x32 */
    res = gt30l32s4w_read_char_extend_16x32(&gs_handle, 0xAAA1U, buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read char extend 16x32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16X32_GB2312_EX, buf, 64);
    
    /* gt30l32s4w_read_ascii_5x7 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_5x7 test.\n");
    
    /* read ascii 5x7 */
    res = gt30l32s4w_read_ascii_5x7(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 5x7 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_5X7_ASCII, buf, 8);
    
    /* gt30l32s4w_read_ascii_7x8 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_7x8 test.\n");
    
    /* read ascii 7x8 */
    res = gt30l32s4w_read_ascii_7x8(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 7x8 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_7X8_ASCII, buf, 8);
    
    /* gt30l32s4w_read_ascii_6x12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_6x12 test.\n");
    
    /* read ascii 6x12 */
    res = gt30l32s4w_read_ascii_6x12(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 6x12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_6X12_ASCII, buf, 12);
    
    /* gt30l32s4w_read_ascii_8x16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_8x16 test.\n");
    
    /* read ascii 8x16 */
    res = gt30l32s4w_read_ascii_8x16(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 8x16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_8X16_ASCII, buf, 16);
    
    /* gt30l32s4w_read_ascii_12x24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_12x24 test.\n");
    
    /* read ascii 12x24 */
    res = gt30l32s4w_read_ascii_12x24(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 12x24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12X24_ASCII, buf, 48);
    
    /* gt30l32s4w_read_ascii_16x32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_16x32 test.\n");
    
    /* read ascii 16x32 */
    res = gt30l32s4w_read_ascii_16x32(&gs_handle, '!', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii 16x32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16X32_ASCII, buf, 64);
    
    /* gt30l32s4w_read_ascii_arial_12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_12 test.\n");
    
    /* read ascii arial 12 */
    res = gt30l32s4w_read_ascii_arial_12(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12_ARIAL_ASCII, buf, 26);
    
    /* gt30l32s4w_read_ascii_times_12 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_12 test.\n");
    
    /* read ascii times 12 */
    res = gt30l32s4w_read_ascii_times_12(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 12 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_12_TIMES_ASCII, buf, 26);
    
    /* gt30l32s4w_read_ascii_arial_16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_16 test.\n");
    
    /* read ascii arial 16 */
    res = gt30l32s4w_read_ascii_arial_16(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16_ARIAL_ASCII, buf, 34);
    
    /* gt30l32s4w_read_ascii_times_16 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_16 test.\n");
    
    /* read ascii times 16 */
    res = gt30l32s4w_read_ascii_times_16(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 16 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_16_TIMES_ASCII, buf, 34);
    
    /* gt30l32s4w_read_ascii_arial_24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_24 test.\n");
    
    /* read ascii arial 24 */
    res = gt30l32s4w_read_ascii_arial_24(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_24_ARIAL_ASCII, buf, 74);
    
    /* gt30l32s4w_read_ascii_times_24 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_24 test.\n");
    
    /* read ascii times 24 */
    res = gt30l32s4w_read_ascii_times_24(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 24 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_24_TIMES_ASCII, buf, 74);
    
    /* gt30l32s4w_read_ascii_arial_32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_arial_32 test.\n");
    
    /* read ascii arial 32 */
    res = gt30l32s4w_read_ascii_arial_32(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii arial 32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_32_ARIAL_ASCII, buf, 130);
    
    /* gt30l32s4w_read_ascii_times_32 test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: gt30l32s4w_read_ascii_times_32 test.\n");
    
    /* read ascii times 32 */
    res = gt30l32s4w_read_ascii_times_32(&gs_handle, '?', buf);
    if (res != 0)
    {
        gt30l32s4w_interface_debug_print("gt30l32s4w: read ascii times 32 failed.\n");
        (void)gt30l32s4w_deinit(&gs_handle);
       
        return 1;
    }
    
    /* output */
    (void)gt30l32s4w_print_pattern(&gs_handle, GT30L32S4W_TYPE_32_TIMES_ASCII, buf, 130);
    
    /* finish read test */
    gt30l32s4w_interface_debug_print("gt30l32s4w: finish read test.\n");
    (void)gt30l32s4w_deinit(&gs_handle);
    
    return 0;
}
