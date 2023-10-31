SET PATH=C:\Program Files\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\VMware\VMware Workstation\bin\;C:\Program Files\Python311\Scripts\;C:\Program Files\Python311\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Microsoft VS Code\bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\cygwin64\bin;C:\Program Files (x86)\NetSarang\Xshell 7\;C:\Program Files\Git\cmd;C:\Program Files (x86)\MAVProxy;C:\Users\zbn02\AppData\Local\Microsoft\WindowsApps;;C:\Program Files\altera\13.1\modelsim_ase\win32aloem
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=ADC-DEMO
SET CPU_CLOCK=0x00B71B00
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\ojbects\startup_stm32f10x_md._ia"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\key.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\led.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\main.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_it.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\systick.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\time_test.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\usart1.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_gpio.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_rcc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_flash.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_rtc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\misc.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_tim.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_pwr.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\stm32f10x_usart.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\core_cm3.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ojbects\system_stm32f10x.__i"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Ojbects\STM32-DEMO.lnp"
"C:\Program Files\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Ojbects\STM32-DEMO.axf" --i32combined --output ".\Ojbects\STM32-DEMO.hex"
