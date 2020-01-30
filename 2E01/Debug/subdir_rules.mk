################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/msp430-gcc-8.3.1.25_win64/bin/msp430-elf-gcc-8.3.1.exe" -c -mmcu=msp430f5529 -mhwmult=f5series -I"C:/ti/ccs930/ccs/ccs_base/msp430/include_gcc" -I"C:/Users/dougl/Desktop/UnB-Documentos/SISTEMAS OPERACIONAIS EMBARCADOS EM TEMPO REAL/2E01" -I"C:/ti/ccs930/ccs/tools/compiler/msp430-gcc-8.3.1.25_win64/msp430-elf/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -mlarge -mcode-region=none -mdata-region=none -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


