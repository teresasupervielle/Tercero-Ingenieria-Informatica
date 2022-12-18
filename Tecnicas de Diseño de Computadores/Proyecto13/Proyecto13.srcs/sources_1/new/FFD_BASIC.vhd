----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10.03.2021 12:18:12
-- Design Name: 
-- Module Name: FFD_BASIC - Behavioral
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
use IEEE.Numeric_Std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity FFD_BASIC is
    Port ( D_i : in STD_LOGIC;
           Q_o : out STD_LOGIC;
           CLK_i : in STD_LOGIC);
end FFD_BASIC;

architecture Behavioral of FFD_BASIC is

begin
    process(CLK_i)
    begin
       if rising_edge(CLK_i) then
            Q_o <= D_i;
       end if;
    end process;


end Behavioral;
