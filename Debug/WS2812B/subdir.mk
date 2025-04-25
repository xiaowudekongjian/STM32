################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# 将这些工具调用的输入和输出添加到构建变量 
C_SRCS += \
../WS2812B/WS2812B.c 

OBJS += \
./WS2812B/WS2812B.o 

C_DEPS += \
./WS2812B/WS2812B.d 


# 每个子目录必须为构建它所贡献的源提供规则
WS2812B/%.o WS2812B/%.su WS2812B/%.cyclo: ../WS2812B/%.c WS2812B/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32/STM32CubeIDE(C8T6)/WS2812B/WS2812B" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-WS2812B

clean-WS2812B:
	-$(RM) ./WS2812B/WS2812B.cyclo ./WS2812B/WS2812B.d ./WS2812B/WS2812B.o ./WS2812B/WS2812B.su

.PHONY: clean-WS2812B

