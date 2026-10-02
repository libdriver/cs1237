### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: SCLK/DIO PA0/PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. CS1237

#### 3.1 Command Instruction

1. Show cs1237 chip and driver information.

    ```shell
    cs1237 (-i | --information)  
    ```

2. Show cs1237 help.

    ```shell
    cs1237 (-h | --help)        
    ```

3. Show cs1237 pin connections of the current board.

    ```shell
    cs1237 (-p | --port)        
    ```

4. Run cs1237 register test.

    ```shell
    cs1237 (-t reg | --test=reg)
    ```

5. Run cs1237 read test, voltage is the reference voltage in volt, hex is the temperature raw data, deg is the temperature  in C and num is the test times.

    ```shell
    cs1237 (-t read | --test=read) [--ref=<voltage>] [--temp-raw=<hex>] [--temp-deg=<deg>] [--times=<num>]
    ```
    
6. Run cs1237 read function,  voltage is the reference voltage in volt and num is the test times.

    ```shell
    cs1237 (-e read | --example=read) [--ref=<voltage>] [--times=<num>]
    ```
    
7. Run cs1237 temperature function, hex is the temperature raw data, deg is the temperature  in C and num is the test times.

    ```shell
    cs1237 (-e temperature | --example=temperature) [--temp-raw=<hex>] [--temp-deg=<deg>] [--times=<num>]
    ```

#### 3.2 Command Example

```shell
cs1237 -i

cs1237: chip is CHIPSEA CS1237.
cs1237: manufacturer is CHIPSEA.
cs1237: interface is GPIO.
cs1237: driver version is 1.0.
cs1237: min supply voltage is 3.0V.
cs1237: max supply voltage is 5.5V.
cs1237: max current is 2.34mA.
cs1237: max temperature is 85.0C.
cs1237: min temperature is -40.0C.
```

```shell
cs1237 -p

cs1237: GPIO interface SCLK connected to GPIOA PIN0.
cs1237: GPIO interface DIO connected to GPIOA PIN8.
```

```shell
cs1237 -t reg

cs1237: chip is CHIPSEA CS1237.
cs1237: manufacturer is CHIPSEA.
cs1237: interface is GPIO.
cs1237: driver version is 1.0.
cs1237: min supply voltage is 3.0V.
cs1237: max supply voltage is 5.5V.
cs1237: max current is 2.34mA.
cs1237: max temperature is 85.0C.
cs1237: min temperature is -40.0C.
cs1237: start register test.
cs1237: cs1237_set_reference_voltage_output/cs1237_get_reference_voltage_output test.
cs1237: enable reference voltage output.
cs1237: check reference voltage output ok.
cs1237: disable reference voltage output.
cs1237: check reference voltage output ok.
cs1237: cs1237_set_adc_rate/cs1237_get_adc_rate test.
cs1237: set adc rate 10hz.
cs1237: check adc rate ok.
cs1237: set adc rate 40hz.
cs1237: check adc rate ok.
cs1237: set adc rate 640hz.
cs1237: check adc rate ok.
cs1237: set adc rate 1280hz.
cs1237: check adc rate ok.
cs1237: cs1237_set_pga/cs1237_get_pga test.
cs1237: set pga 1.
cs1237: check pga ok.
cs1237: set pga 2.
cs1237: check pga ok.
cs1237: set pga 64.
cs1237: check pga ok.
cs1237: set pga 128.
cs1237: check pga ok.
cs1237: cs1237_set_channel/cs1237_get_channel test.
cs1237: set channel short circuit.
cs1237: check channel ok.
cs1237: set channel temperature.
cs1237: check channel ok.
cs1237: set channel a.
cs1237: check channel ok.
cs1237: cs1237_wake_up test.
cs1237: check wake up ok.
cs1237: cs1237_wake_up test.
cs1237: check power down ok.
cs1237: finish register test.
```

```shell
cs1237 -t read --ref=3.3 --temp-raw=0xC2000 --temp-deg=25.0 --times=3

cs1237: chip is CHIPSEA CS1237.
cs1237: manufacturer is CHIPSEA.
cs1237: interface is GPIO.
cs1237: driver version is 1.0.
cs1237: min supply voltage is 3.0V.
cs1237: max supply voltage is 5.5V.
cs1237: max current is 2.34mA.
cs1237: max temperature is 85.0C.
cs1237: min temperature is -40.0C.
cs1237: start read test.
cs1237: set channel a.
cs1237: set pga 1.
cs1237: adc is -0.248623mV.
cs1237: adc is -0.179780mV.
cs1237: adc is -0.160307mV.
cs1237: set pga 2.
cs1237: adc is -0.112116mV.
cs1237: adc is -0.118312mV.
cs1237: adc is -0.119787mV.
cs1237: set pga 64.
cs1237: adc is -0.012103mV.
cs1237: adc is -0.011925mV.
cs1237: adc is -0.012856mV.
cs1237: set pga 128.
cs1237: adc is -0.011095mV.
cs1237: adc is -0.011064mV.
cs1237: adc is -0.011516mV.
cs1237: set adc rate 10hz.
cs1237: adc is -0.011242mV.
cs1237: adc is -0.011327mV.
cs1237: adc is -0.011115mV.
cs1237: set adc rate 40hz.
cs1237: adc is -0.010817mV.
cs1237: adc is -0.010104mV.
cs1237: adc is -0.010829mV.
cs1237: set adc rate 640hz.
cs1237: adc is -0.011934mV.
cs1237: adc is -0.014276mV.
cs1237: adc is -0.012008mV.
cs1237: set adc rate 1280hz.
cs1237: adc is -0.011448mV.
cs1237: adc is -0.013085mV.
cs1237: adc is -0.009507mV.
cs1237: read temperature test.
cs1237: raw is 0xC0D44, temperature is 23.20C.
cs1237: raw is 0xC1D22, temperature is 24.72C.
cs1237: raw is 0xC124C, temperature is 23.68C.
cs1237: finish read test.
```

```shell
cs1237 -e read --ref=3.3 --times=3

cs1237: adc is -0.010414mV.
cs1237: adc is -0.010366mV.
cs1237: adc is -0.012081mV.
```
```shell
cs1237 -e temperature --temp-raw=0xC2000 --temp-deg=25 --times=3

cs1237: temperature is 23.61C.
cs1237: temperature is 23.65C.
cs1237: temperature is 23.64C.
```
```shell
cs1237 -h

Usage:
  cs1237 (-i | --information)
  cs1237 (-h | --help)
  cs1237 (-p | --port)
  cs1237 (-t reg | --test=reg)
  cs1237 (-t read | --test=read) [--ref=<voltage>] [--temp-raw=<hex>] [--temp-deg=<deg>] [--times=<num>]
  cs1237 (-e read | --example=read) [--ref=<voltage>] [--times=<num>]
  cs1237 (-e temperature | --example=temperature) [--temp-raw=<hex>] [--temp-deg=<deg>] [--times=<num>]

Options:
  -e <read | temperature>, --example=<read | temperature>
                                         Run the driver example.
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
  -p, --port                             Display the pin connections of the current board.
      --ref=<voltage>                    Set the reference voltage.([default: 3.3])
  -t <reg | read>, --test=<reg | read>   Run the driver test.
      --times=<num>                      Set the test times.([default: 3])
      --temp-raw=<hex>                   Set the temperature raw data.([default: 0x0000])
      --temp-deg=<deg>                   Set the temperature degree.([default: 0.0])
```
