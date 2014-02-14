# add library for module configuration
add_avr_library(
   module_config
   matrixbar_config.h
   can_config_mcp2515.c
   can_config_mcp2515.h
   spi_config.h
   timer_config.h
)

