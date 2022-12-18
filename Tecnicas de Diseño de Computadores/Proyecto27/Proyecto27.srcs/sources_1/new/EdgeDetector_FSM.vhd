----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05.05.2021 11:01:15
-- Design Name: 
-- Module Name: EdgeDetector_FSM - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity EdgeDetector_FSM is
    Port ( RST_i : in STD_LOGIC;
           CLK_i : in STD_LOGIC;
           PUSH_i : in STD_LOGIC;
           PULSE_o : out STD_LOGIC);
end EdgeDetector_FSM;

architecture Behavioral of EdgeDetector_FSM is

    type EdgeDetector_States is(inic, S0, S01);
    signal STATE: EdgeDetector_States;
    signal PUSH: STD_LOGIC;
    
begin

process (RST_i, CLK_i)
begin
    if RST_i = '1' then
        PUSH <= '0'; -- INICIO CON RESET
    elsif rising_edge(CLK_i) then
        PUSH <= PUSH_i;
    end if;
end process;

Process (RST_i, CLK_i)
begin
    if RST_i = '1' then
        STATE <= inic; -- INICIO CON RESET
    elsif rising_edge(CLK_i) then
         case STATE is
             when inic => if PUSH = '0' then
                     STATE <= S0; --llega "0-"
                 end if;
             when S0 => if PUSH = '1' then
                     STATE <= S01; --llega "01"
                 end if;
             when S01 => if PUSH = '0' then
                     STATE <= S0;--"0" para "0-"
                 else
                     STATE <= inic; --llega un "1",
                 end if;
             when others => STATE <= inic;
          end case;
    end if;
end process;

with STATE select
    PULSE_o <= '0' when inic,
               '0' when S0,
               '1' when S01,
               '0' when others; -- catch all
end Behavioral;