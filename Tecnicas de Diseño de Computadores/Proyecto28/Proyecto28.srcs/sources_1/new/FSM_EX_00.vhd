----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05.05.2021 13:20:08
-- Design Name: 
-- Module Name: FSM_EX_00 - Behavioral
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

entity FSM_EX_00 is
    generic (FIN : integer := 8);
    Port ( CLK_i : in STD_LOGIC;
           ENA_i : in STD_LOGIC;
           RST_i: in STD_LOGIC;
           LED_o : out STD_LOGIC_VECTOR (FIN - 1 downto 0));
end FSM_EX_00;

architecture Behavioral of FSM_EX_00 is

component CE_N_Hz
    generic (END_COUNT : integer := 100);
    Port ( CLK_i : in STD_LOGIC;
           RST_i : in STD_LOGIC;
           CLK_N_Hz_o : out STD_LOGIC);
end component;

    type EdgeDetector_States is(inic, derecha, izquierda);
    signal STATE: EdgeDetector_States;
    signal CONT: integer range 0 to FIN;
    signal DATA: STD_LOGIC;
    signal LED: STD_LOGIC_VECTOR (FIN - 1 downto 0);
    
begin

CE_N_Hz_0 : CE_N_Hz
    port map (
        CLK_i => CLK_i,
        RST_i => RST_i,
        CLK_N_Hz_o => DATA
);
    DATA <= ENA_i;
        
Process (RST_i, CLK_i)
begin
    if RST_i = '1' then
        STATE <= inic; -- INICIO CON RESET
    elsif rising_edge(CLK_i) then
         case STATE is
             when inic => if ENA_i = '1' then
                    CONT <= CONT + 1;
                    STATE <= derecha; --llega "0-"
                 end if;
             when derecha => if ENA_i = '1' then
                    if CONT = FIN - 1 then
                        CONT <= 0;
                        STATE <= izquierda;
                    else
                        CONT <= CONT + 1;
                        STATE <= derecha; --llega "0-"
                    end if;
                  end if;
             when izquierda => if ENA_i = '1' then
                    if CONT = FIN - 1 then
                         CONT <= 0;
                         STATE <= derecha;
                    else
                         CONT <= CONT + 1;
                         STATE <= izquierda; --llega "0-"
                     end if;
                   end if;
             when others => STATE <= inic;
          end case;
    end if;
end process;

with STATE select
    LED_o <= "00000000" when inic,
             ((CONT) => '1', others => '0') when derecha,
             ((CONT) => '1', others => '0') when izquierda,
             "00000000" when others; -- catch all
end Behavioral;