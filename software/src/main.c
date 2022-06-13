#include "xaxidma.h"
#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xil_cache.h"

u32 checkHalted(u32 baseAddress, u32 offset);

int main(){
    u32 arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t arr_size = 8;
    u32 rec[arr_size];

    XAxiDma_Config *myDmaConfig;
    myDmaConfig = XAxiDma_LookupConfigBaseAddr(XPAR_AXI_DMA_0_BASEADDR);

    XAxiDma myDma;
    int dma_init_result = XAxiDma_CfgInitialize(&myDma, myDmaConfig);

    if (dma_init_result != XST_SUCCESS){
        xil_printf("ERR: DMA init failed \r\n");
        return -1;
    }
    xil_printf("INFO: DMA init succesful \r\n");

    u32 dma_halt_status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x4);
    xil_printf("INFO: DMA status before transfer 0x%x\r\n", dma_halt_status);

    Xil_DCacheFlushRange((u32) arr, arr_size*sizeof(u32));

    u32 rec_status = XAxiDma_SimpleTransfer(&myDma, (u32) rec, arr_size*sizeof(u32), XAXIDMA_DEVICE_TO_DMA);
    u32 transfer_result = XAxiDma_SimpleTransfer(&myDma, (u32)arr, arr_size*sizeof(u32), XAXIDMA_DMA_TO_DEVICE);

    if (transfer_result != XST_SUCCESS || rec_status != XST_SUCCESS){
        xil_printf("ERR: DMA transfer failed \r\n");
        return -1;
    }

    dma_halt_status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x4);
    while (dma_halt_status != 1){
        dma_halt_status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x4);
    }


    dma_halt_status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x34);
    while (dma_halt_status != 1){
        dma_halt_status = checkHalted(XPAR_AXI_DMA_0_BASEADDR, 0x34);
    }

    xil_printf("DMA status after transfer 0x%x\r\n", dma_halt_status);

    xil_printf("INFO: DMA transfer succesful\r\n");

    for ( int i = 0; i < arr_size; i++){
        xil_printf("%x to %x\r\n", (u32)arr[i], (u32)rec[i]);
    }
}

u32 checkHalted(u32 baseAddress, u32 offset){
    u32 status = XST_FAILURE;
    status = (XAxiDma_ReadReg(baseAddress, offset)) & XAXIDMA_HALTED_MASK;
    return status;
}
