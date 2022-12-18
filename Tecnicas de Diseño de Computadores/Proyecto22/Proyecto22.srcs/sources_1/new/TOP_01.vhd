----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 14.04.2021 12:29:22
-- Design Name: 
-- Module Name: TOP_01 - Behavioral
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

entity TOP_01 is
    generic (DATA_WIDTH: integer := 4;
             CW_WIDTH: integer := 5);
    Port ( DATA_BUS_i : in STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           CW_i : in STD_LOGIC_VECTOR (CW_WIDTH - 1 downto 0);
           CLK_i : in STD_LOGIC;
           RST_i : in STD_LOGIC;
           ANODE_o : out STD_LOGIC_VECTOR (7 downto 0);
           CATHODE_o : out STD_LOGIC_VECTOR (6 downto 0);
           FZ_o : out STD_LOGIC);
end TOP_01;

architecture Behavioral of TOP_01 is

component DATAPATH_0 is
    generic (DATA_WIDTH: integer := 4;
             CW_WIDTH: integer := 5;
             N_ALU : integer := 2);
    Port ( DATA_BUS_i : in STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           RST_i : in STD_LOGIC;
           CLK_i : in STD_LOGIC;
           CW_i : in STD_LOGIC_VECTOR (CW_WIDTH - 1 downto 0);
           ALU_RESULT_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           REG_A_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           REG_B_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
           FZ_o : out STD_LOGIC;
           DATA_BUS_o : out STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0));
end component;

component DISP7SEG_8ON is
    Port ( CLK_i : in STD_LOGIC;
           RST_i : in STD_LOGIC;
           DATA0_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA1_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA2_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA3_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA4_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA5_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA6_i : in STD_LOGIC_VECTOR (3 downto 0);
           DATA7_i : in STD_LOGIC_VECTOR (3 downto 0);
           ANODE_o: out STD_LOGIC_VECTOR (7 downto 0);
           CATHODE_o: out STD_LOGIC_VECTOR (6 downto 0));
end component;

    signal REG_A: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
    signal REG_B: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
    signal ALU_RES: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);
    signal DATA_BUS: STD_LOGIC_VECTOR (DATA_WIDTH - 1 downto 0);

begin

DATAPATH: DATAPATH_0
port map (
    DATA_BUS_i => DATA_BUS_i,
    RST_i => RST_i,
    CLK_i => CLK_i,
    CW_i => CW_i,
    ALU_RESULT_o => ALU_RES,
    REG_A_o => REG_A,
    REG_B_o => REG_B,
    FZ_o => FZ_o,
    DATA_BUS_o => DATA_BUS
);

DISP7SEG: DISP7SEG_8ON
    port map (
        CLK_i => CLK_i,
        RST_i => RST_i,
        DATA0_i => DATA_BUS,
        DATA1_i => REG_A,
        DATA2_i => REG_B,
        DATA3_i => ALU_RES,
        DATA4_i => "0000",
        DATA5_i => "0000",
        DATA6_i => "0000",
        DATA7_i => "0000",
        ANODE_o => ANODE_o,
        CATHODE_o => CATHODE_o
);
end Behavioral;
