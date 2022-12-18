-- Testbench created online at:
--   https://www.doulos.com/knowhow/perl/vhdl-testbench-creation-using-perl/
-- Copyright Doulos Ltd

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity ALU_0_N_BITS_OP_tb is
end;

architecture bench of ALU_0_N_BITS_OP_tb is

  component ALU_0_N_BITS_OP
      generic(width: integer:=4);
      Port ( A_i : in STD_LOGIC_VECTOR (width-1 downto 0);
             B_i : in STD_LOGIC_VECTOR (width-1 downto 0);
             OP_i : in STD_LOGIC_VECTOR (2 downto 0);
             RESULT_o : out STD_LOGIC_VECTOR (width-1 downto 0);
             ZERO_F_o : out STD_LOGIC;
             CARRY_F_o : out STD_LOGIC);
  end component;
constant width: integer:=4;
  signal A_i: STD_LOGIC_VECTOR (width-1 downto 0);
  signal B_i: STD_LOGIC_VECTOR (width-1 downto 0);
  signal OP_i: STD_LOGIC_VECTOR (2 downto 0);
  signal RESULT_o: STD_LOGIC_VECTOR (width-1 downto 0);
  signal ZERO_F_o: STD_LOGIC;
  signal CARRY_F_o: STD_LOGIC;

begin

  -- Insert values for generic parameters !!
  uut: ALU_0_N_BITS_OP generic map ( width     =>  width)
                          port map ( A_i       => A_i,
                                     B_i       => B_i,
                                     OP_i      => OP_i,
                                     RESULT_o  => RESULT_o,
                                     ZERO_F_o  => ZERO_F_o,
                                     CARRY_F_o => CARRY_F_o );

  stimulus: process
  begin
  
    A_i <= "0001";
    B_i <= "0010";
    OP_i <= "000";
    wait for 20 ns;
    
    A_i <= "0101";
    B_i <= "1001";
    OP_i <= "001";
    wait for 20 ns;
    
    A_i <= "0001";
    B_i <= "0010";
    OP_i <= "010";
    wait for 20 ns;

  end process;
end;
