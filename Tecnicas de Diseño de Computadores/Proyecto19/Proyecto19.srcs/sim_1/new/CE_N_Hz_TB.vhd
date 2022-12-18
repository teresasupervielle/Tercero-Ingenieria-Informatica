library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity CE_N_Hz_tb is
end;

architecture bench of CE_N_Hz_tb is

  component CE_N_Hz
      generic (END_COUNT : integer := 100);
      Port ( CLK_i : in STD_LOGIC;
             RST_i : in STD_LOGIC;
             CLK_N_Hz_o : out STD_LOGIC);
  end component;

  signal CLK_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal CLK_N_Hz_o: STD_LOGIC;

  constant END_COUNT: integer := 100;
  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: CE_N_Hz generic map ( END_COUNT  =>  END_COUNT)
                  port map ( CLK_i      => CLK_i,
                             RST_i      => RST_i,
                             CLK_N_Hz_o => CLK_N_Hz_o );

  stimulus: process
  begin
  
    -- Put initialisation code here

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    -- Put test bench stimulus code here

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
