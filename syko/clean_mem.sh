#!/bin/bash

#preparowanie PC
dd if=/dev/zero of=file_pc.bin count=1 bs=2

#preparowanie licznika cykli 
dd if=/dev/zero of=file_counter.bin count=1 bs=4

#preparowanie rejestru R2 wartoscia ustawiajaca w pierwszej instrukcji 
#odwolania out do EIMSK zmienna int0_enabled
#??? echo -ne "\001" > file_data.bin

#preparowanie data space kodem 
#dd if=file_data.bin of=file_code.bin bs=10 count=1