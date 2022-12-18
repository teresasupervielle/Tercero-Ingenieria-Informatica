-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity YOUR_TURN_tb is
end;

architecture bench of YOUR_TURN_tb is

  component YOUR_TURN
      generic (DATA_WIDTH: integer := 4);
      Port ( CLK_i : in STD_LOGIC;
             RST_i : in STD_LOGIC;
             INC_i : in STD_LOGIC;
             NUMBER_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0));
  end component;

  constant DATA_WIDTH: integer:= 4;
  signal CLK_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal INC_i: STD_LOGIC;
  signal NUMBER_o: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: YOUR_TURN generic map ( DATA_WIDTH => DATA_WIDTH )
                    port map ( CLK_i      => CLK_i,
                               RST_i      => RST_i,
                               INC_i      => INC_i,
                               NUMBER_o   => NUMBER_o );

  stimulus: process
  begin
  
      RST_i <= '1';
      wait for 5 ns;
      RST_i <= '0';
      wait for 5 ns;
  
      INC_i <= '0';
      wait for 20 ns;
      
      INC_i <= '1';
      wait for 20 ns;
      
      INC_i <= '0';
      wait for 20 ns;
         
      INC_i <= '1';
      wait for 20 ns;

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