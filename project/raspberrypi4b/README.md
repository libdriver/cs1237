### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

GPIO Pin: SCLK/DIO GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(cs1237 REQUIRED)
```

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
./cs1237 -i

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
./cs1237 -p

cs1237: GPIO interface SCLK connected to GPIO27(BCM).
cs1237: GPIO interface DIO connected to GPIO17(BCM).
```

```shell
./cs1237 -t reg

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
./cs1237 -t read --ref=3.3 --temp-raw=0xC2000 --temp-deg=25.0 --times=3

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
cs1237: adc is -72.838058mV.
cs1237: adc is -69.614418mV.
cs1237: adc is -66.416151mV.
cs1237: set pga 2.
cs1237: adc is -62.835411mV.
cs1237: adc is -59.798238mV.
cs1237: adc is -56.843382mV.
cs1237: set pga 64.
cs1237: adc is -1.592605mV.
cs1237: adc is -1.471920mV.
cs1237: adc is -1.394217mV.
cs1237: set pga 128.
cs1237: adc is -10.116343mV.
cs1237: adc is -7.842483mV.
cs1237: adc is -6.322013mV.
cs1237: set adc rate 10hz.
cs1237: adc is -3.688843mV.
cs1237: adc is -2.324861mV.
cs1237: adc is -1.500873mV.
cs1237: set adc rate 40hz.
cs1237: adc is -0.937667mV.
cs1237: adc is -0.677320mV.
cs1237: adc is -0.519397mV.
cs1237: set adc rate 640hz.
cs1237: adc is -0.431934mV.
cs1237: adc is -0.370468mV.
cs1237: adc is -0.649319mV.
cs1237: set adc rate 1280hz.
cs1237: adc is -0.551163mV.
cs1237: adc is -0.719107mV.
cs1237: adc is -0.855336mV.
cs1237: read temperature test.
cs1237: raw is 0xBF55E, temperature is 20.90C.
cs1237: raw is 0xBF563, temperature is 20.91C.
cs1237: raw is 0xBF4DB, temperature is 20.86C.
cs1237: finish read test.
```

```shell
./cs1237 -e read --ref=3.3 --times=3

cs1237: adc is -0.406608mV.
cs1237: adc is -0.796569mV.
cs1237: adc is -0.887864mV.
```
```shell
./cs1237 -e temperature --temp-raw=0xC2000 --temp-deg=25 --times=3

cs1237: temperature is 20.34C.
cs1237: temperature is 20.37C.
cs1237: temperature is 20.29C.
```
```shell
./cs1237 -h

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
