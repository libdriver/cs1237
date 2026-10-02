[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver CS1237

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/cs1237/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

CS1237 is a high-precision, low-power analog-to-digital conversion chip with a differential input channel, built-in temperature sensor, and high-precision oscillator. CS1237 offers PGA options of 1, 2, 64, and 128, with the default being 128. The ADC data output rate of CS1237 in normal mode can be selected from 10Hz, 40Hz, 640Hz, 1.28kHz, with a default of 10Hz. The MCU can communicate with CS1237 through the 2-wire SPI interface SCLK, DRDY/DOUT, and configure it, such as channel selection, PGA selection, output rate selection, etc.

LibDriver CS1237 is a full function driver for CS1237, launched by LibDiver.It provides differential reading and additional features. LibDriver is MISRA compliant.

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

/src includes LibDriver CS1237 source files.

/interface includes LibDriver CS1237 GPIO platform independent template.

/test includes LibDriver CS1237driver test code and this code can test the chip necessary function simply.

/example includes LibDriver CS1237 sample code.

/doc includes LibDriver CS1237 offline document.

/datasheet includes CS1237 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface GPIO platform independent template and finish your platform GPIO driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_cs1237_basic.h"

uint8_t res;
uint32_t i;
float ref = 3.3f;
int32_t temperature_raw = 0xC2000;
float temperature_deg = 23.0f;

/* init */
res = cs1237_basic_init(ref, temperature_raw, temperature_deg);
if (res != 0)
{
    return 1;
}

for (i = 0; i < 3; i++)
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
```

### Document

Online documents: [https://www.libdriver.com/docs/cs1237/index.html](https://www.libdriver.com/docs/cs1237/index.html).

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