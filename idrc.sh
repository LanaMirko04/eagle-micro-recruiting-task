#!/bin/bash
openocd -f openocd.cfg -c "program build/micro-recruiting-task.elf verify reset exit"
