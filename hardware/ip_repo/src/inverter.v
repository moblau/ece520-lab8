`timescale 1ns / 1ps

module inverter #(parameter DATA_WIDTH=32)(
    input axi_clk,
    input axi_reset_n,
    //Slave stream interfaace
    input s_axis_valid,
    input [31:0] s_axis_data,
    output s_axis_ready,
    //master stream interface
    output reg m_axis_valid,
    output reg [31:0] m_axis_data,
    input m_axis_ready
    );


    integer i;
    
    assign s_axis_ready = m_axis_ready;
    
    always @(posedge axi_clk)
    begin
        if (s_axis_valid & s_axis_ready)
        begin
            for (i=0; i < DATA_WIDTH/8; i = i+1)
            begin
                m_axis_data[i*8+:8] <= 255 - s_axis_data[i*8+:8];
            end
        end
    end    
    
    always @(posedge axi_clk)
    begin
        m_axis_valid <= s_axis_valid;
    end
endmodule