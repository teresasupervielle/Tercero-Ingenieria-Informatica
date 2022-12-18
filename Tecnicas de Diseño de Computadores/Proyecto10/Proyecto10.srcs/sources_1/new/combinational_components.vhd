----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03.03.2021 10:12:34
-- Design Name: 
-- Module Name: combinational_components - Behavioral
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


package combinational_components is

    component AND_GATE
         Port ( A_i : in STD_LOGIC;
         B_i : in STD_LOGIC;
         Z_o : out STD_LOGIC);
     end component;

     component XOR_GATE
     generic (WIDTH : INTEGER := 2);
         Port ( A_i : in STD_LOGIC_VECTOR(WIDTH-1 downto 0);
         B_i : in STD_LOGIC_VECTOR(WIDTH-1 downto 0);
         Z_o : out STD_LOGIC_VECTOR(WIDTH-1 downto 0));
     end component;
     
      component FULL_ADDER
          Port ( A_i : in STD_LOGIC;
          B_i : in STD_LOGIC;
          CARRY_i : in STD_LOGIC;
          SUM_o : out STD_LOGIC;
          CARRY_o : out STD_LOGIC);
      end component;
     
      component MUX4
      Generic (width: integer := 2);
          Port ( A_i : in STD_LOGIC_VECTOR (width-1 downto 0);
          B_i : in STD_LOGIC_VECTOR (width-1 downto 0);
          C_i : in STD_LOGIC_VECTOR (width-1 downto 0);
          D_i : in STD_LOGIC_VECTOR (width-1 downto 0);
          SEL_i : in STD_LOGIC_VECTOR (1 downto 0);
          Z_o : out STD_LOGIC_VECTOR (width-1 downto 0));
      end component;

end package;
