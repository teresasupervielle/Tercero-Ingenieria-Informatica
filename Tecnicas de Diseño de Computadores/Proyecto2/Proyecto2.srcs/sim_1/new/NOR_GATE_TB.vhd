-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity NOR_GATE_tb is
end;

architecture bench of NOR_GATE_tb is

  component NOR_GATE
      Port ( A_i : in STD_LOGIC_VECTOR (1 downto 0);
             B_i : in STD_LOGIC_VECTOR (1 downto 0);
             Z_o : out STD_LOGIC_VECTOR (1 downto 0));
  end component;

  signal A_i: STD_LOGIC_VECTOR (1 downto 0);
  signal B_i: STD_LOGIC_VECTOR (1 downto 0);
  signal Z_o: STD_LOGIC_VECTOR (1 downto 0);

begin

  uut: NOR_GATE port map ( A_i => A_i,
                           B_i => B_i,
                           Z_o => Z_o );

  stimulus: process
  begin
  
    A_i <= "00";
    B_i <= "00";
    wait for 40 ns;
    
    --
    
    A_i <= "00";
    B_i <= "01";
    wait for 40 ns;
        
    A_i <= "00";
    B_i <= "10";
    wait for 40 ns; 
    
    A_i <= "00";
    B_i <= "11";
    wait for 40 ns;   
    
    --

    A_i <= "01";
    B_i <= "00";
    wait for 40 ns;
    
    A_i <= "10";
    B_i <= "00";
    wait for 40 ns;
        
    A_i <= "11";
    B_i <= "00";
    wait for 40 ns;
    
    --
    
    A_i <= "01";
    B_i <= "01";
    wait for 40 ns;
    
    --
    
    A_i <= "10";
    B_i <= "10";
    wait for 40 ns;
    
    --
    
    A_i <= "11";
    B_i <= "11";
    wait for 40 ns;
        
    A_i <= "01";
    B_i <= "10";
    wait for 40 ns; 
    
    A_i <= "10";
    B_i <= "01";
    wait for 40 ns;
    wait;
  end process;


end;