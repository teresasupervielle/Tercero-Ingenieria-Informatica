library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity REG_N_bits_tb is
end;

architecture bench of REG_N_bits_tb is

  component REG_N_bits
      generic (N: integer := 5);
      Port ( RST_i : in STD_LOGIC;
             CLK_i : in STD_LOGIC;
             ENA_i : in STD_LOGIC;
             DATA_IN_i : in STD_LOGIC_VECTOR (N-1 downto 0);
             DATA_OUT_o : out STD_LOGIC_VECTOR (N-1 downto 0));
  end component;

  constant N: integer := 5;
  signal RST_i: STD_LOGIC;
  signal CLK_i: STD_LOGIC;
  signal ENA_i: STD_LOGIC;
  signal DATA_IN_i: STD_LOGIC_VECTOR (N-1 downto 0);
  signal DATA_OUT_o: STD_LOGIC_VECTOR (N-1 downto 0);
  

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: REG_N_bits generic map ( N          =>  N)
                     port map ( RST_i      => RST_i,
                                CLK_i      => CLK_i,
                                ENA_i      => ENA_i,
                                DATA_IN_i  => DATA_IN_i,
                                DATA_OUT_o => DATA_OUT_o );

  stimulus: process
  begin
  
    -- Put initialisation code here

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    DATA_IN_i <= "00110";
    wait for 20 ns;
    
    DATA_IN_i <= "00010";
    wait for 20 ns;
    
    DATA_IN_i <= "00001";
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