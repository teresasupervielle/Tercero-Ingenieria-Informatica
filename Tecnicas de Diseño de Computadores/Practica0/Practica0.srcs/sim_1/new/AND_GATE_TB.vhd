----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 17.02.2021 10:38:14
-- Design Name: 
-- Module Name: AND_GATE_TB - Behavioral
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


-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity AND_GATE_tb is
end;

architecture bench of AND_GATE_tb is

  component AND_GATE
      Port ( A_i : in STD_LOGIC;
             B_i : in STD_LOGIC;
             Z_o : out STD_LOGIC);
  end component;

  signal A_i: STD_LOGIC;
  signal B_i: STD_LOGIC;
  signal Z_o: STD_LOGIC;

begin

  uut: AND_GATE port map ( A_i => A_i,
                           B_i => B_i,
                           Z_o => Z_o );

  stimulus: process
  begin
    A_i <= '0';
    B_i <= '0';
    wait for 40 ns;
    
    A_i <= '0';
    B_i <= '1';
    wait for 40 ns;
    
    A_i <= '1';
    B_i <= '0';
    wait for 40 ns;
    
    A_i <= '1';
    B_i <= '1';
    wait for 40 ns;
    -- Put initialisation code here


    -- Put test bench stimulus code here

    wait;
  end process;


end;