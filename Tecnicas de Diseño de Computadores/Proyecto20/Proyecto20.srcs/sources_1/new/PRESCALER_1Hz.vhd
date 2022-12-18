----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.03.2021 11:24:14
-- Design Name: 
-- Module Name: PRESCALER_1Hz - Behavioral
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

entity PRESCALER_1Hz is
    Port ( CLK_i : in STD_LOGIC;
           RST_i : in STD_LOGIC;
           CLK_1Hz_o : out STD_LOGIC);
end PRESCALER_1Hz;

architecture Behavioral of PRESCALER_1Hz is
    constant END_COUNT: integer :=100000000; -- Número de ciclos de CLK a contar.
    signal COUNTER: integer range 0 to END_COUNT - 1; -- Sub-rango para contar de 0 a 100.000
    signal CLK_o: std_logic;
begin
process (CLK_i, RST_i)
begin
---------------------------------------------------
-- RESET pone a 0 el contador y el puerto de salida
---------------------------------------------------
    if RST_i='1' then
        CLK_o <= '0';
        COUNTER <= 0;
        -------------------------------------------- -----------------
        -- Mantiene a 0 la salida hasta que transcurren 10.000 ciclos
        -- Entonces asigna '1' a la salida durante un ciclo de CLK
        --------------------------------------------------------------
        elsif rising_edge(CLK_i) then
        if (COUNTER = END_COUNT / 2) then -- Si ya ha contado 100.000 ciclos de CLK
        CLK_o <= not CLK_o; -- Pone el contador a 0
        COUNTER <= 0; -- Manda un '1' durante un ciclo de CLK
        else
        COUNTER <= COUNTER +1; -- Si no ha llegado al final de la cuenta
        -- incrementa la cuenta de ciclos
        end if;
    end if;
end process;

    CLK_1Hz_o <= CLK_o;
    
end Behavioral;