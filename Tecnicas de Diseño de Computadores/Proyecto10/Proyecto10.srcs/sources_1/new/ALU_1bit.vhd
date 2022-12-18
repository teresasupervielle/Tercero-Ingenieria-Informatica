----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03.03.2021 10:12:03
-- Design Name: 
-- Module Name: ALU_1bit - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.combinational_components.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ALU_1bit is
    Port (A_i: in STD_LOGIC;
          B_i: in STD_LOGIC;
          CARRY_i: in STD_LOGIC;
          OP_i: in STD_LOGIC_VECTOR (1 downto 0);
          CARRY_o: out STD_LOGIC;
          RESULT_o: out STD_LOGIC);
end ALU_1bit;

architecture Behavioral of ALU_1bit is
    signal DATA_AND: STD_LOGIC;
    signal DATA_XOR: STD_LOGIC_VECTOR (0 downto 0);
    signal DATA_ADD: STD_LOGIC;
    signal DATA_MOV: STD_LOGIC;
    
begin
    andgate: AND_GATE
        port map (A_i => A_i, B_i => B_i, Z_o => DATA_AND);
    
    xorgate: XOR_GATE generic map (WIDTH => 1)
        port map (A_i(0) => A_i, B_i(0) => B_i, Z_o => DATA_XOR);
    
    add: FULL_ADDER port map (A_i => A_i, B_i => B_i,
                              CARRY_i => CARRY_i,
                              SUM_o => DATA_ADD,
                              CARRY_o => CARRY_o);
                          
     DATA_MOV <= A_i;
     
     mux: MUX4 generic map (WIDTH => 1)
          port map (A_i(0) => DATA_AND, B_i => DATA_XOR, 
                    C_i(0) => DATA_ADD, D_i(0) => DATA_MOV, 
                    SEL_i => OP_i, Z_o(0) => RESULT_o);
end Behavioral;