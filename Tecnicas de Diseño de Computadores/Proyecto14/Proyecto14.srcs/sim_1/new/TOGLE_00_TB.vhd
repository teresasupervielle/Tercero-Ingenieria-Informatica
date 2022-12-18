library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity TOGGLE_00_tb is
end;

architecture bench of TOGGLE_00_tb is

  component TOGGLE_00
      Port ( ENA_i : in STD_LOGIC;
             RST_i : in STD_LOGIC;
             CLK_i : in STD_LOGIC;
             Q_o : out STD_LOGIC);
  end component;

  signal ENA_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal CLK_i: STD_LOGIC;
  signal Q_o: STD_LOGIC;

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: TOGGLE_00 port map ( ENA_i => ENA_i,
                            RST_i => RST_i,
                            CLK_i => CLK_i,
                            Q_o   => Q_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    ENA_i <= '1';
    wait for 100ns;
    
    ENA_i <='0';
    wait for 100ns;
    
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