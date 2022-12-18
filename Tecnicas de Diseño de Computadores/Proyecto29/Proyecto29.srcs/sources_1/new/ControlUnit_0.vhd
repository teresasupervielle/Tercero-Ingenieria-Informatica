----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12.05.2021 12:35:14
-- Design Name: 
-- Module Name: ControlUnit_0 - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ControlUnit_0 is
  Generic (COP_WIDHT: integer := 4;
           CW_WIDHT: integer := 10);
  Port (COP_i: in STD_LOGIC_VECTOR (COP_WIDHT - 1 downto 0);
        CLK_i: in STD_LOGIC;
        RST_i: in STD_LOGIC;
        FZ_i: in STD_LOGIC;
        CW_o: out STD_LOGIC_VECTOR (10 - 1 downto 0));
end ControlUnit_0;

architecture Behavioral of ControlUnit_0 is

------------------------------------------------------
-- DEFINITION of STATES
-------------------------------------------------------
    type STATES_FSM is (IDLE,LOAD,DECO,OPE_A,ADDR_B, OPE_B,MOV_A,
    INC_A,A_ADD_B,A_SUB_B);
    signal NEXT_STATE: STATES_FSM;
------------------------------------------------------
-- DEFINITION of the OUTPUTS for each STATE
-------------------------------------------------------
    constant OUTPUT_IDLE: std_logic_Vector(9 downto 0):="0000000000";--000h
    constant OUTPUT_LOAD: std_logic_Vector(9 downto 0):="0010010000";--050h
    constant OUTPUT_DECO: std_logic_Vector(9 downto 0):="0000000000";--000h
    constant OUTPUT_OPE_A: std_logic_Vector(9 downto 0):="0000000001";--001h
    constant OUTPUT_ADDR_B: std_logic_Vector(9 downto 0):="0000100000";--020h
    constant OUTPUT_OPE_B: std_logic_Vector(9 downto 0):="0000100010";--022h
    constant OUTPUT_MOV_A: std_logic_Vector(9 downto 0):="0000101100";--02Ch
    constant OUTPUT_INC_A: std_logic_Vector(9 downto 0):="0100101100";--12Ch
    constant OUTPUT_A_ADD_B: std_logic_Vector(9 downto 0):="1000101100";--22Ch
    constant OUTPUT_A_SUB_B: std_logic_Vector(9 downto 0):="1100101100";--32Ch
    ----------------------------------------------------------------

begin

process (CLK_i, RST_i)
begin
    if RST_i = '1' then
        NEXT_STATE <= IDLE;
    elsif rising_edge(CLK_i)then
        case NEXT_STATE is
            -- State "IDLE" -
            when IDLE=>
                NEXT_STATE <= LOAD;
            -- State "LOAD"
            when LOAD =>
                NEXT_STATE <= DECO;
            -- State "DECO"
            when DECO =>
                if COP_i = "0100" then
                    if FZ_i = '0' then
                        NEXT_STATE <= LOAD;
                    else
                        NEXT_STATE <= DECO;
                    end if;
                else
                    NEXT_STATE <= OPE_A;
                end if;
            -- State "OPE_A"
            when OPE_A =>
                if COP_i = "0010" OR COP_i = "0011" then
                   NEXT_STATE <= ADDR_B;
                elsif COP_i = "0001" then
                        NEXT_STATE <= INC_A;
                elsif COP_i = "0000" then
                        NEXT_STATE <= MOV_A;
                end if;
            -- State "ADDR_B"
            when ADDR_B =>
                NEXT_STATE <= OPE_B;
            -- State "OPE_B"
            when OPE_B =>
                if COP_i = "0010" then
                    NEXT_STATE <= A_ADD_B;
                elsif COP_i = "0011" then
                    NEXT_STATE <= A_SUB_B;
                end if;
            --State A_ADD_B
            when A_ADD_B =>
                NEXT_STATE <= LOAD;
            --State A_SUB_B
            when A_SUB_B =>
                NEXT_STATE <= LOAD;
            when MOV_A =>
                NEXT_STATE <= LOAD;    
            when INC_A =>
                 NEXT_STATE <= LOAD;  
            when others =>
                Next_State <= IDLE;
        end case;
    end if;
end process;
-----------------------------------------------------------
with NEXT_STATE select
CW_o <= OUTPUT_IDLE when IDLE,
        OUTPUT_LOAD when LOAD,
        OUTPUT_OPE_A when OPE_A,
        OUTPUT_ADDR_B when ADDR_B,
        OUTPUT_OPE_B when OPE_B,
        OUTPUT_A_ADD_B when A_ADD_B,
        OUTPUT_DECO when DECO,
        OUTPUT_MOV_A when MOV_A,
        OUTPUT_INC_A when INC_A,
        OUTPUT_A_SUB_B when A_SUB_B,
        OUTPUT_IDLE when others;

end Behavioral;
