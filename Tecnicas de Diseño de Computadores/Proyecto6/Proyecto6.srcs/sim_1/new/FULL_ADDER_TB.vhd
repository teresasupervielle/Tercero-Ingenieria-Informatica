-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity FULL_ADDER_tb is
end;

architecture bench of FULL_ADDER_tb is

  component FULL_ADDER
      Port ( A_i : in STD_LOGIC;
             B_i : in STD_LOGIC;
             CARRY_i : in STD_LOGIC;
             CARRY_o : out STD_LOGIC;
             SUM_o : out STD_LOGIC);
  end component;

  signal A_i: STD_LOGIC;
  signal B_i: STD_LOGIC;
  signal CARRY_i: STD_LOGIC;
  signal CARRY_o: STD_LOGIC;
  signal SUM_o: STD_LOGIC;

begin

  uut: FULL_ADDER port map ( A_i     => A_i,
                             B_i     => B_i,
                             CARRY_i => CARRY_i,
                             CARRY_o => CARRY_o,
                             SUM_o   => SUM_o );

  stimulus: process
  begin
    A_i <= '0';
    B_i <= '0';
    CARRY_i <= '0';
    wait for 40 ns;
    
    A_i <= '1';
    B_i <= '0';
    CARRY_i <= '0';
    wait for 40 ns;
       
    A_i <= '1';
    B_i <= '1';
    CARRY_i <= '0';
    wait for 40 ns;
     
    A_i <= '1';
    B_i <= '1';
    CARRY_i <= '1';
    wait for 40 ns;  
      
    A_i <= '0';
    B_i <= '1';
    CARRY_i <= '0';
    wait for 40 ns;
       
    A_i <= '0';
    B_i <= '1';
    CARRY_i <= '1';
    wait for 40 ns;    

    A_i <= '0';
    B_i <= '0';
    CARRY_i <= '1';
    wait for 40 ns;
         
    A_i <= '1';
    B_i <= '0';
    CARRY_i <= '1';
    wait for 40 ns;
  end process;


end;
