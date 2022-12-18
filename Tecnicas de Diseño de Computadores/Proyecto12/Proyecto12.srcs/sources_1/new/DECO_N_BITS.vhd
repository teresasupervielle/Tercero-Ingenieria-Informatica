----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10.03.2021 10:57:40
-- Design Name: 
-- Module Name: DECO_N_BITS - Behavioral
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
use IEEE.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DECO_N_BITS is
    generic ( WIDTH: integer := 4);
    Port ( A_i : in STD_LOGIC_VECTOR (WIDTH-1 downto 0);
           Z_o : out STD_LOGIC_VECTOR (2**WIDTH-1 downto 0));
end DECO_N_BITS;

architecture Behavioral of DECO_N_BITS is

begin
    demultiplexor: process (A_i)
    begin
        Z_o <= (others => '0');
        Z_o(to_integer (unsigned (A_i))) <= '1';
    end process;

end Behavioral;
