# stm32f103-template

This is a template project for [stm32f103](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32f1-series/stm32f103.html?querycriteria=productId=LN1565) microcontroller (driving an LED).
The project requires the following:
- [GNU Tools for ARM Embedded Processors toolchain](https://launchpad.net/gcc-arm-embedded) (compiler, objcopy)
```
  sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
  sudo apt install cmake
```
- stm32flash
```
  sudo apt-get install stm32flash
```
- [STM32 Standard Peripheral Libraries](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html)

For more information please see [A template project for STM32 on Linux](https://blog.gypsyengineer.com/fun/a-template-project-for-stm32f103-on-linux.html).

## Usage
`arm-none-eabi-gcc` and `arm-none-eabi-objcopy` should be in `${PATH}`. `${STD_PERIPH_LIBS}` contains a path to STM32 Standard Peripheral Libraries. `${ST_FLASH}` contains a path to `stm32flash`.
```
# clean up
make clean

# compile and link the project
STD_PERIPH_LIBS=/home/artem/projects/stm32/src/STM32F10x_StdPeriph_Lib_V3.5.0/ make all

# upload the code to stm32f103 (requires root privileges)
ST_FLASH=/home/artem/tools/stlink/st-flash make burn
```

