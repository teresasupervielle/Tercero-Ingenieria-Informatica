library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity DATAPATH_0_tb is
end;

architecture bench of DATAPATH_0_tb is

  component DATAPATH_0
      generic (DATA_WIDTH: integer := 4;
               CW_WIDTH: integer := 10;
               N_ALU : integer := 2;
               ADDR_WIDTH: integer := 4;
               ADDR_ROM_WIDTH: integer := 3;
               DATA_ROM_WIDTH: integer := 11);
      Port ( RST_i : in STD_LOGIC;
             CLK_i : in STD_LOGIC;
             CW_i : in STD_LOGIC_VECTOR (CW_WIDTH - 1 downto 0);
             ALU_RESULT_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
             REG_A_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
             REG_B_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
             FZ_o : out STD_LOGIC;
             DATA_BUS_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0));  
  end component;

  constant DATA_WIDTH: integer := 4;
  constant CW_WIDTH: integer := 10;
  constant N_ALU: integer := 2;
  constant ADDR_WIDTH: integer := 4;
  constant ADDR_ROM_WIDTH: integer := 3;
  constant DATA_ROM_WIDTH: integer := 11;
  signal RST_i: STD_LOGIC;
  signal CLK_i: STD_LOGIC;
  signal CW_i: STD_LOGIC_VECTOR (CW_WIDTH - 1 downto 0);
  signal ALU_RESULT_o: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
  signal REG_A_o: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
  signal REG_B_o: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
  signal FZ_o: STD_LOGIC;
  signal DATA_BUS_o: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: DATAPATH_0 generic map ( DATA_WIDTH     => DATA_WIDTH,
                                CW_WIDTH       => CW_WIDTH,
                                N_ALU          => N_ALU,
                                ADDR_WIDTH     => ADDR_WIDTH,
                                ADDR_ROM_WIDTH => ADDR_ROM_WIDTH,
                                DATA_ROM_WIDTH =>  DATA_ROM_WIDTH)
                     port map ( RST_i          => RST_i,
                                CLK_i          => CLK_i,
                                CW_i           => CW_i,
                                ALU_RESULT_o   => ALU_RESULT_o,
                                REG_A_o        => REG_A_o,
                                REG_B_o        => REG_B_o,
                                FZ_o           => FZ_o,
                                DATA_BUS_o     => DATA_BUS_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    --C1
    CW_i(7) <= '1';
    CW_i(6) <= '1';
    CW_i(5) <= '0';
    CW_i(4) <= '1';
    CW_i(3) <= '0';
    CW_i(2) <= '0';
    CW_i(1) <= '0';
    CW_i(0) <= '0';
    wait for 20 ns;
    
    --C2
    wait for 20 ns;
    
    --C3
    CW_i(7) <= '0';
    CW_i(6) <= '0';
    CW_i(5) <= '0';
    CW_i(4) <= '0';
    CW_i(3) <= '0';
    CW_i(2) <= '1';
    CW_i(1) <= '0';
    CW_i(0) <= '0';
    wait for 20 ns;
    
    --C4
    CW_i(7) <= '0';
    CW_i(6) <= '0';
    CW_i(5) <= '1';
    CW_i(4) <= '0';
    CW_i(3) <= '0';
    CW_i(2) <= '0';
    CW_i(1) <= '0';
    CW_i(0) <= '0';
    wait for 20 ns;
    
    --C5
    CW_i(7) <= '0';
    CW_i(6) <= '0';
    CW_i(5) <= '1';
    CW_i(4) <= '0';
    CW_i(3) <= '0';
    CW_i(2) <= '0';
    CW_i(1) <= '0';
    CW_i(0) <= '0';
    wait for 20 ns;
    
    --C6
    CW_i(7) <= '0';
    CW_i(6) <= '0';
    CW_i(5) <= '1';
    CW_i(4) <= '0';
    CW_i(3) <= '1';
    CW_i(2) <= '0';
    CW_i(1) <= '0';
    CW_i(0) <= '1';
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