----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03.03.2021 13:06:14
-- Design Name: 
-- Module Name: ALU_0_N_BITS_OP - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ALU_0_N_BITS_OP is
    generic(width: integer:=4);
    Port ( A_i : in STD_LOGIC_VECTOR (width-1 downto 0);
           B_i : in STD_LOGIC_VECTOR (width-1 downto 0);
           OP_i : in STD_LOGIC_VECTOR (2 downto 0);
           RESULT_o : out STD_LOGIC_VECTOR (width-1 downto 0);
           ZERO_F_o : out STD_LOGIC;
           CARRY_F_o : out STD_LOGIC);
end ALU_0_N_BITS_OP;

architecture Behavioral of ALU_0_N_BITS_OP is
    signal A, B: unsigned (width downto 0);
    signal RESULT: unsigned (width downto 0);
    constant ZERO : unsigned (width-1 downto 0) := (others => '0');
    
begin
    ALU: process (A, B, OP_i)
    begin
        A <= '0' & unsigned(A_i);
        B <= '0' & unsigned (B_i);
        case (OP_i) is
            when "000" => RESULT <= A + 1;
            when "001" => RESULT <= B + 1;
            when "010" => RESULT <= A srl 1;
            when "011" => RESULT <= A sll 1;
            when "100" => RESULT <= A + B;
            when "101" => RESULT <= A - B;
            when "110" => RESULT <= A;
            when "111" => RESULT <= B;
            when others => RESULT <= ZERO;
        end case;
   end process ALU;
        RESULT_o <= std_logic_Vector(RESULT(width - 1 downto 0));
        ZERO_F_o <= '1' when RESULT = ZERO else '0';
        CARRY_F_o <= RESULT(width);
end Behavioral;
