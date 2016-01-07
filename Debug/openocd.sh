#!/bin/bash
$(openocd_path)/bin/openocd -s $(openocd_path)/share/openocd/scripts/ -f stm32-openocd.cfg
