[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver GT30L32S4W

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/gt30l32s4w/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

GT30L32S4W is a Chinese character library chip that includes 12x12 dot matrix, 16x16 dot matrix, 24x24 dot matrix, and 32x32 dot matrix. It supports GB2312 national standard Chinese characters (including legal authorization from the National Information and Standardization Commission) and ASCII characters. The arrangement format is horizontal. Users can use the method provided in this manual to calculate the address of the character matrix in the chip through the character internal code, and continuously read the character matrix information from this address.

LibDriver GT30L32S4W is a full-featured driver of GT30L32S4W launched by LibDriver.It provides the function of dot matrix reading. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver GT30L32S4W source files.

/interface includes LibDriver GT30L32S4W SPI platform independent template.

/test includes LibDriver GT30L32S4W driver test code and this code can test the chip necessary function simply.

/example includes LibDriver GT30L32S4W sample code.

/doc includes LibDriver GT30L32S4W offline document.

/datasheet includes GT30L32S4W datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_gt30l32s4w_basic.h"

uint8_t res;
uint8_t buf[128];
uint8_t len;
uint16_t ch = 'A';

/* basic init */
res = gt30l32s4w_basic_init();
if (res != 0)
{
    return 1;
}

...

/* read 32 */
res = gt30l32s4w_basic_read_32(ch, buf, &len);
if (res != 0)
{
    /* basic deinit */
    (void)gt30l32s4w_basic_deinit();

    return 1;
}

...
    
/* print */
if (len == 64)
{
    (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_16X32_ASCII, buf, 64);
}
else
{
    (void)gt30l32s4w_basic_print_pattern(GT30L32S4W_TYPE_32X32_GB2312, buf, 128);
}

...
    
/* basic deinit */
(void)gt30l32s4w_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/gt30l32s4w/index.html](https://www.libdriver.com/docs/gt30l32s4w/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.