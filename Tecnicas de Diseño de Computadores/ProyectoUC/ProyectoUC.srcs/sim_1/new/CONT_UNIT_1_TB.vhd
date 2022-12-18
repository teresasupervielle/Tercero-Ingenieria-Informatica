library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity CONT_UNIT_1_tb is
end;

architecture bench of CONT_UNIT_1_tb is

  component CONT_UNIT_1
    Generic (CodOperacion_TAM: integer := 4;
             CW_TAM: integer := 10);
    Port (CodOperacion_i: in STD_LOGIC_VECTOR (CodOperacion_TAM - 1 downto 0);
          CLK_i: in STD_LOGIC;
          RST_i: in STD_LOGIC;
          FZ_i: in STD_LOGIC;
          CW_o: out STD_LOGIC_VECTOR (CW_TAM - 1 downto 0));
  end component;

  constant CodOperacion_TAM: integer := 4;
  constant CW_TAM: integer := 10;
  signal CodOperacion_i: STD_LOGIC_VECTOR (CodOperacion_TAM - 1 downto 0);
  signal CLK_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal FZ_i: STD_LOGIC;
  signal CW_o: STD_LOGIC_VECTOR (CW_TAM - 1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: CONT_UNIT_1 generic map ( CodOperacion_TAM => CodOperacion_TAM,
                                 CW_TAM           =>  CW_TAM)
                      port map ( CodOperacion_i   => CodOperacion_i,
                                 CLK_i            => CLK_i,
                                 RST_i            => RST_i,
                                 FZ_i             => FZ_i,
                                 CW_o             => CW_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    CodOperacion_i <= "0000";
    FZ_i <= '0';
    wait for 90 ns;
    
    CodOperacion_i <= "0001";
    FZ_i <= '0';
    wait for 60 ns;
        
    CodOperacion_i <= "0010";
    FZ_i <= '0';
    wait for 80 ns;
    
    CodOperacion_i <= "0011";
    FZ_i <= '1';
    wait for 40 ns;                

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