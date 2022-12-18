library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity COUNTER_N_bits_tb is
end;

architecture bench of COUNTER_N_bits_tb is

  component COUNTER_N_bits
      generic (DATA_WIDTH: natural:=4);
      Port ( CLK_i : in STD_LOGIC;
             RST_i : in STD_LOGIC;
             ENA_i : in STD_LOGIC;
             Q_o : out STD_LOGIC_VECTOR (DATA_WIDTH-1 downto 0));
  end component;

  constant DATA_WIDTH : integer := 4;
  signal CLK_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal ENA_i: STD_LOGIC;
  signal Q_o: STD_LOGIC_VECTOR (DATA_WIDTH-1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: COUNTER_N_bits generic map ( DATA_WIDTH =>  DATA_WIDTH)
                         port map ( CLK_i      => CLK_i,
                                    RST_i      => RST_i,
                                    ENA_i      => ENA_i,
                                    Q_o        => Q_o );

  stimulus: process
  begin
  
    -- Put initialisation code here

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;
    
    ENA_i <= '0';
    wait for 20 ns;
    
    ENA_i <= '1';
    wait for 20 ns;

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