library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity DECO_N_BITS_tb is
end;

architecture bench of DECO_N_BITS_tb is

  component DECO_N_BITS
      generic ( WIDTH: integer := 4);
      Port ( A_i : in STD_LOGIC_VECTOR (WIDTH-1 downto 0);
             Z_o : out STD_LOGIC_VECTOR (2**WIDTH-1 downto 0));
  end component;
  constant WIDTH: integer:=4;
  signal A_i: STD_LOGIC_VECTOR (WIDTH-1 downto 0);
  signal Z_o: STD_LOGIC_VECTOR (2**WIDTH-1 downto 0);

begin

  -- Insert values for generic parameters !!
  uut: DECO_N_BITS generic map ( WIDTH =>  WIDTH)
                      port map ( A_i   => A_i,
                                 Z_o   => Z_o );

  stimulus: process
  begin
  
    A_i <= "0000";
    wait for 40ns;
    
    A_i <= "0001";
    wait for 40ns;
       
    A_i <= "0010";
    wait for 40ns;
    
    A_i <= "0011";
    wait for 40ns;
  end process;


end;