#  8 - DMA and Custom Stream AXI
## Introduction
Lab 8 is about learning how to implement direct memory access with the zynq processor and use it with a custom inverter IP via AXI stream. The custom inverter IP takes a 32 bit input and inverts all the bits of the number. For example, if the input to the inverter is 0x0000FFFF, then the output of the inverter is 0xFFFF0000. Additionally, the integrated logic analyzer was used in Vivado to monitor the signals in the programmable logic part of the system. 

## Procedure
The procedure for lab 8 includes the following steps:
1. Create inverter custom IP
   1. Create code in verilog to accept a 32 bit input and invert all of the bits. Simulate the verilog code to ensure it works.
2. Create PL block design in Vivado
   1. Follow along the creation of the block design in Vivado. It includes a Zynq processor, DMA, inverter IP, and the necessary peripherals to connect each AXI bus.
3. Export hardware without bitstream
   1. The hardware is programmed seperate from Vitis, in Vivado. Thus, the bitstream is not included in the .xsa file and the FPGA is not programmed from Vitis. 
4. Import the hardware to Vitis and add required source code.
   1. The source code came from the lab session. It was recreated.
5. Program FPGA with Vivado
   1. The target device was connected and then programmed in Vivado
6. Run software in Vitis
   1. The software was built in Vitis and then run. One important step was to disable "reset FPGA" so that Vitis did not reset the program from Vivado.
7. Monitor integrated logic analyzer with Vivado
   1. The trigger was set to monitor the AXI valid signal and set to standby. When the Vitis program was run again, the integrated logic analyzer displayed the proper waveforms.

![block design](/img/blockdesign.png)  
**Figure 8.1: Block Design for DMA system PL**  

## Results
![simulation results](/img/simulation.png)  
**Figure 8.2: Simulation Results of inverter IP**  

![integrated logic analyzer](/img/ila.png)  
**Figure 8.3: Integrated Logic Analyzer Results**

Results for Lab 8 [here](https://youtu.be/2cWwHK7egWc)  

## Conclusion

Lab 8 was pretty much required to follow along with what was done in the lab session. Though it was clear what to do, there were a lot of required steps which made the possibility for error higher. Initially, the correct output was not showing in the console. An error was made in copying the source code. Once the error was fixed, the correct output displayed. 

Lab 8 introduced me to several new concepts in Vivado, such as the DMA block, the integrated logic analzyer, and programming FPGA seperately in Vivado instead of all at once in Vitis. Overall, it wasn't too challenging but I learned a lot.