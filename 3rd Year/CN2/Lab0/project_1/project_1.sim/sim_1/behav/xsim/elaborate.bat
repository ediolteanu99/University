@echo off
REM ****************************************************************************
REM Vivado (TM) v2019.2.1 (64-bit)
REM
REM Filename    : elaborate.bat
REM Simulator   : Xilinx Vivado Simulator
REM Description : Script for elaborating the compiled design
REM
REM Generated by Vivado on Tue Oct 13 17:58:46 +0300 2020
REM SW Build 2729669 on Thu Dec  5 04:49:17 MST 2019
REM
REM Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
REM
REM usage: elaborate.bat
REM
REM ****************************************************************************
echo "xelab -wto bef693a0d5574968a5b66588f921faf3 --incr --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot task03_test_behav xil_defaultlib.task03_test xil_defaultlib.glbl -log elaborate.log"
call xelab  -wto bef693a0d5574968a5b66588f921faf3 --incr --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot task03_test_behav xil_defaultlib.task03_test xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
