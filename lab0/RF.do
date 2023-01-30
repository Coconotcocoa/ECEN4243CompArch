# Copyright 1991-2007 Mentor Graphics Corporation
# 
# Modification by Oklahoma State University
# Use with Testbench 
# James Stine, 2008
# Go Cowboys!!!!!!
#
# All Rights Reserved.
#
# THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION
# WHICH IS THE PROPERTY OF MENTOR GRAPHICS CORPORATION
# OR ITS LICENSORS AND IS SUBJECT TO LICENSE TERMS.

# Use this run.do file to run this example.
# Either bring up ModelSim and type the following at the "ModelSim>" prompt:
#     do run.do
# or, to run from a shell, type the following at the shell prompt:
#     vsim -do run.do -c
# (omit the "-c" to see the GUI while running from the shell)

onbreak {resume}

# create library
if [file exists work] {
    vdel -all
}
vlib work

# compile source files
vlog regfile.sv RF_tb.sv

# start and run simulation
vsim -voptargs=+acc work.RF 

view list
view wave

-- display input and output signals as hexidecimal values
# Diplays All Signals recursively

# add wave -hex -r /RF/*

# Adapt to make Waveform Viewer prettier :)
add wave  -noupdate -divider -height 32 "Clock"
add wave  -hex -r /RF/clock
add wave  -noupdate -divider -height 32 "Write Enable"
add wave  -hex -r /RF/write_enable3
add wave  -noupdate -divider -height 32 "Wide Data"
add wave  -hex -r /RF/wide_data3
add wave  -noupdate -divider -height 32 "Write Address"
add wave  -hex -r /RF/write_address3
add wave  -noupdate -divider -height 32 "Read Addresses"
add wave  -hex -r /RF/read_address1
add wave  -hex -r /RF/read_address2
add wave  -noupdate -divider -height 32 "Read Data"
add wave  -hex -r /RF/read_data1
add wave  -hex -r /RF/read_data2

add list -hex -r /RF/*
#add log -hex -r /*

-- Set Wave Output Items 
TreeUpdate [SetDefaultTree]
WaveRestoreZoom {0 ps} {75 ns}
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2

-- Run the Simulation
run 200ns


