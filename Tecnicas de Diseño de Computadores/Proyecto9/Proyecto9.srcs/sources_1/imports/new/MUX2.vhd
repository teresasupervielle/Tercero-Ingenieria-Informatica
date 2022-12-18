-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity MUX2_tb is
end;

architecture bench of MUX2_tb is

  component MUX2
      generic(WIDTH: integer := 2);
      Port ( A_i : in STD_LOGIC_VECTOR (WIDTH-1 downto 0);
             B_i : in STD_LOGIC_VECTOR (WIDTH-1 downto 0);
             SEL_i : in STD_LOGIC;
             Y_o : out STD_LOGIC_VECTOR (WIDTH-1 downto 0));
  end component;
  
  constant WIDTH: integer := 2;

  signal A_i: STD_LOGIC_VECTOR (WIDTH-1 downto 0);
  signal B_i: STD_LOGIC_VECTOR (WIDTH-1 downto 0);
  signal SEL_i: STD_LOGIC;
  signal Y_o: STD_LOGIC_VECTOR (WIDTH-1 downto 0);

begin

  -- Insert values for generic parameters !!
  uut: MUX2 generic map ( WIDTH =>  WIDTH)
               port map ( A_i   => A_i,
                          B_i   => B_i,
                          SEL_i => SEL_i,
                          Y_o   => Y_o );

  A_B: process
  begin
  A_i <= "00";
  B_i <= "11";
  wait for 80 ns;
  
  A_i <= "01";
  B_i <= "10";
  wait for 80 ns;
  
  end process;
  
  Sel_process: process
  begin
  SEL_i <= '0';
  wait for 20 ns;
  
  SEL_i <= '1';
  wait for 20 ns;
  end process;

end architecture bench;