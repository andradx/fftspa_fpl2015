pwd
open_project ldpc_gf4
set_top fftspa
add_files fftspa.cpp -cflags "-D__SYNTHESIZE__"
add_files -tb fftspa_testbench.cpp
open_solution "solution1"
set_part {xc7vx690tffg1761-2}
create_clock -period 233MHz -name default

csim_design -clean
csynth_design
cosim_design -tool modelsim -rtl verilog -trace_level all
export_design -format ip_catalog -description "LDPC decoder" -vendor "blind_for_review" -library "LDPC" -version "1.0"
exit
