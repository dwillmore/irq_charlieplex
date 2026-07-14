all : flash

TARGET:=irq_charlieplex

TARGET_MCU:=CH32V003

include ch32fun/ch32fun/ch32fun.mk

POWER_FLASH_COMMAND_OFF?=$(MINICHLINK)/minichlink -t
POWER_FLASH_COMMAND_ON?=$(MINICHLINK)/minichlink -3
POWER_FLASH_COMMAND?=$(MINICHLINK)/minichlink -w $< $(WRITE_SECTION) -b
power_flash : $(TARGET).bin $(MINICHLINK)/minichlink
	$(POWER_FLASH_COMMAND_OFF)
	sleep 1
	-$(POWER_FLASH_COMMAND_ON)
	$(POWER_FLASH_COMMAND)

flash : power_flash
clean : cv_clean
