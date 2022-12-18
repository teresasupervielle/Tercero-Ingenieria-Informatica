library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity ControlUnit_0_tb is
end;

architecture bench of ControlUnit_0_tb is

  component ControlUnit_0
    Generic (COP_WIDHT: integer := 4;
             CW_WIDHT: integer := 10);
    Port (COP_i: in STD_LOGIC_VECTOR (COP_WIDHT - 1 downto 0);
          CLK_i: in STD_LOGIC;
          RST_i: in STD_LOGIC;
          FZ_i: in STD_LOGIC;
          CW_o: out STD_LOGIC_VECTOR (10 - 1 downto 0));
  end component;

  constant COP_WIDHT: integer := 4;
  constant CW_WIDHT: integer := 10;
  signal COP_i: STD_LOGIC_VECTOR (COP_WIDHT - 1 downto 0);
  signal CLK_i: STD_LOGIC;
  signal RST_i: STD_LOGIC;
  signal FZ_i: STD_LOGIC;
  signal CW_o: STD_LOGIC_VECTOR (10 - 1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: ControlUnit_0 generic map ( COP_WIDHT => COP_WIDHT,
                                   CW_WIDHT  =>  CW_WIDHT)
                        port map ( COP_i     => COP_i,
                                   CLK_i     => CLK_i,
                                   RST_i     => RST_i,
                                   FZ_i      => FZ_i,
                                   CW_o      => CW_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    COP_i <= "0000";
    wait for 20 ns;
    
    COP_i <= "0001";
    wait for 20 ns;
        
    COP_i <= "0010";
    wait for 20 ns;

   COP_i <= "0011";
    wait for 20 ns;

    COP_i <= "0100";
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