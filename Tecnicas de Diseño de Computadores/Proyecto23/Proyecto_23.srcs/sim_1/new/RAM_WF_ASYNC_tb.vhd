library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity RAM_WF_ASYNC_tb is
end;

architecture bench of RAM_WF_ASYNC_tb is

  component RAM_WF_ASYNC
      generic ( DATA_WIDTH: positive := 4;
                ADDR_WIDTH: positive := 10);
      Port ( CLK_i : in STD_LOGIC;
             ADDR_RAM_i : in STD_LOGIC_VECTOR (ADDR_WIDTH - 1 downto 0);
             DATA_RAM_i : in STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
             DATA_RAM_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
             WE_i : in STD_LOGIC);
  end component;

  constant DATA_WIDTH: positive := 4;
  constant ADDR_WIDTH: positive := 10;
  signal CLK_i: STD_LOGIC;
  signal ADDR_RAM_i: STD_LOGIC_VECTOR (ADDR_WIDTH - 1 downto 0);
  signal DATA_RAM_i: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
  signal DATA_RAM_o: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
  signal WE_i: STD_LOGIC;

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  -- Insert values for generic parameters !!
  uut: RAM_WF_ASYNC generic map ( DATA_WIDTH => DATA_WIDTH,
                                  ADDR_WIDTH =>  ADDR_WIDTH)
                       port map ( CLK_i      => CLK_i,
                                  ADDR_RAM_i => ADDR_RAM_i,
                                  DATA_RAM_i => DATA_RAM_i,
                                  DATA_RAM_o => DATA_RAM_o,
                                  WE_i       => WE_i );

  stimulus: process
  begin
  
    ADDR_RAM_i <= "0000000000";
    DATA_RAM_i <= "0101";
    WE_i <= '1';
    wait for 20 ns;
    
    --EScribir DATO en DIR(1)
    ADDR_RAM_i <= "0000000001";
    DATA_RAM_i <= "0111";
    WE_i <= '1';
    wait for 20 ns;
    
    --Leer DATO en DIR(0)
    ADDR_RAM_i <= "0000000010";
    DATA_RAM_i <= "1101";
    WE_i <= '0';
    wait for 20 ns;
    
    --Leer DATO en DIR(1)
    ADDR_RAM_i <= "0000000100";
    DATA_RAM_i <= "1111";
    WE_i <= '0';
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