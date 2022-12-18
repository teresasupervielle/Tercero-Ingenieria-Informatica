----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.03.2021 12:46:09
-- Design Name: 
-- Module Name: DATAPATH_0 - Behavioral
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

entity DATAPATH_0 is
    generic (DATA_WIDTH: integer := 4;
             CW_WIDTH: integer := 6;
             N_ALU : integer := 2;
             ADDR_WIDTH: positive := 4);
    Port ( RST_i : in STD_LOGIC;
           CLK_i : in STD_LOGIC;
           CW_i : in STD_LOGIC_VECTOR (CW_WIDTH - 1 downto 0);
           ADDR_RAM_i : in STD_LOGIC_VECTOR (ADDR_WIDTH - 1 downto 0);
           ALU_RESULT_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           REG_A_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           REG_B_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           FZ_o : out STD_LOGIC;
           DATA_BUS_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0));
end DATAPATH_0;
    
architecture Behavioral of DATAPATH_0 is
    signal REG_A: unsigned (DATA_WIDTH - 1 downto 0);
    signal REG_B: unsigned (DATA_WIDTH - 1 downto 0);
    signal ALU_RES: unsigned (DATA_WIDTH - 1 downto 0);
    signal FZ: STD_LOGIC;
    signal DATA_BUS: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
    
    type RAM_TYPE is array((2**ADDR_WIDTH)-1 downto 0) of std_logic_vector(DATA_WIDTH-1 downto 0);
    signal RAM : RAM_TYPE := ("0000", "0001", "0010", "0011", "0000", "1111", "0000", "0000", 
                              "0000", "1111", "1100", "0011", "0010", "0001", "0000", "0000");

begin

process (CLK_i)
begin
    if rising_edge(CLK_i) then
    -- Operación de LECTURA/ESCRITURA síncrona
        if CW_i(3) = '1' then
            RAM(to_integer(unsigned(ADDR_RAM_i))) <= std_logic_vector(ALU_RES);
            -- El dato que se lee, es el mismo que se escribe
            DATA_BUS <= std_logic_vector(ALU_RES);
        else
            -- Operación de SOLO LECTURA SÍNCRONA
            DATA_BUS <= RAM(to_integer(unsigned(ADDR_RAM_i)));
        end if;
    end if;
end process;

process(RST_i, CLK_i, CW_i)
begin
    if RST_i='1' then
        REG_A <= (others=>'0');
        REG_B <= (others=>'0');
        FZ <= '0';
    elsif rising_edge(CLK_i) then
        if CW_i(1) = '1' then
            REG_B <= unsigned(DATA_BUS);
        elsif CW_i(2) = '1' then         
            REG_A <= unsigned(DATA_BUS);
        end if;
        if CW_i(0) = '1' then
            if ALU_RES = "0000" then
                FZ <= '1';
            end if;
        end if;
    end if;
end process;

    with CW_i(CW_WIDTH - 1 downto CW_WIDTH-N_ALU) select
        ALU_RES <= REG_A when "00",
                   REG_A + 1 when "01",
                   REG_A + REG_B when "10",
                   REG_A - REG_B when others;
                        
        ALU_RESULT_o <= STD_LOGIC_VECTOR(ALU_RES);
        REG_A_o <= STD_LOGIC_VECTOR(REG_A);
        REG_B_o <= STD_LOGIC_VECTOR(REG_B);
        FZ_o <= STD_LOGIC(FZ);
        DATA_BUS_o <= DATA_BUS;
end Behavioral;
