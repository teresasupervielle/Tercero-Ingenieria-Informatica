-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity TOGGLE_01_tb is
end;

architecture bench of TOGGLE_01_tb is

  component TOGGLE_01
      Port ( RST_i : in STD_LOGIC;
             PUSH_i : in STD_LOGIC;
             CLK_i : in STD_LOGIC;
             LED_o : out STD_LOGIC);
  end component;

  signal RST_i: STD_LOGIC;
  signal PUSH_i: STD_LOGIC;
  signal CLK_i: STD_LOGIC;
  signal LED_o: STD_LOGIC;

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: TOGGLE_01 port map ( RST_i  => RST_i,
                            PUSH_i => PUSH_i,
                            CLK_i  => CLK_i,
                            LED_o  => LED_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    PUSH_i <= '1';
    wait for 100 ns;
    
    PUSH_i <= '0';
    wait for 100 ns;
    

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