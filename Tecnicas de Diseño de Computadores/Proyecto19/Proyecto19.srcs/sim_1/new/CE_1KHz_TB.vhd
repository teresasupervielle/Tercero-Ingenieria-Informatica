-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity CE_1KHz_tb is
end;

architecture bench of CE_1KHz_tb is

  component CE_1KHz
      Port ( CLK_i : in STD_LOGIC;
             RST_i : in STD_LOGIC;
             CLK_1KHz_o : out STD_LOGIC);
  end component;

  signal CLK_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal CLK_1KHz_o: STD_LOGIC;

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: CE_1KHz port map ( CLK_i      => CLK_i,
                          RST_i      => RST_i,
                          CLK_1KHz_o => CLK_1KHz_o );

  stimulus: process
  begin
  
    -- Put initialisation code here

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    wait for 100 ms;
    
    stop_the_clock <= true;
    wait;
  end process;

  clocking: process
  begin
    while not stop_the_clock loop
      CLK_i <= '0', '1' after clock_period / 2;
      wait for clock_period;
    end loop;
    wait;
  end process;

end;