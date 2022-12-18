----------------------------------------------------------------------------------
-- PROYECTOR FINAL TÉCNICAS DE DISEÑO DE COMPUTADORES --

-- COMP_MS incluye:
    -- Mapeado DataPath
    -- Mapeado UC
    
-- HECHO POR: Mª Teresa Supervielle Sánchez :D --
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity COMP_MS is
  generic ( CW_TAM: integer := 10; -- Tamaño de la Control Word
            Direccion_TAM: integer := 4; -- Tamaño del Bus de Direcciones
            Data_TAM: integer := 4; -- Tamaño del Bus de Datos
            RAM_TAM: integer := 12); -- Tamaño del ancho de datos de la RAM
  Port ( RST_i : in STD_LOGIC;
         CLK_i : in STD_LOGIC;
         FZ_o : out STD_LOGIC;
         A_o: out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
         B_o: out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
         PC_o : out STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0); 
         DataBus_o : out STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);
         Instruccion_o: out STD_LOGIC_VECTOR (RAM_TAM -1 downto 0); 
         ALU_o : out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0));
end COMP_MS;

architecture Behavioral of COMP_MS is

signal CW_s : STD_LOGIC_VECTOR (CW_TAM - 1 downto 0);
signal FZ_s: STD_LOGIC;
signal Instruccion_s : STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);

component DATAPATH_1 is
    generic (CW_TAM: integer := 10; -- Tamaño de la Control Word
             N_ALU: integer := 2; -- Tamaño de la entrada del multiplexor de la ALU 2^2 = 4 (Suma, Incremento, Comparacion y Salto)
             Data_TAM: integer := 4; -- Tamaño del Bus de Datos
             Direccion_TAM: integer := 4; -- Tamaño del Bus de Direcciones
             RAM_TAM: integer := 12); -- Tamaño del ancho de datos de la RAM
    Port ( RST_i : in STD_LOGIC;
           CLK_i : in STD_LOGIC;
           CW_i : in STD_LOGIC_VECTOR (CW_TAM - 1 downto 0);
           FZ_o : out STD_LOGIC;
           PC_o : out STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0);   
           A_o : out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
           B_o : out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);  
           DataBus_o : out STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);
           ALU_o : out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
           Instruccion_o : out STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0));
end component;

component CONT_UNIT_1 is
  Generic (CodOperacion_TAM: integer := 4;
           CW_TAM: integer := 10);
  Port (CodOperacion_i: in STD_LOGIC_VECTOR (CodOperacion_TAM - 1 downto 0);
        CLK_i: in STD_LOGIC;
        RST_i: in STD_LOGIC;
        FZ_i: in STD_LOGIC;
        CW_o: out STD_LOGIC_VECTOR (CW_TAM - 1 downto 0));
end component;

begin

DATAPATH : DATAPATH_1
port map(
    RST_i => RST_i,
    CLK_i => CLK_i,
    CW_i => CW_s,
    FZ_o => FZ_s,
    PC_o => PC_o,
    A_o => A_o,
    B_o => B_o,
    DataBus_o => DataBus_o,
    ALU_o => ALU_o,
    Instruccion_o => Instruccion_s
 );

CONT_UNIT : CONT_UNIT_1
 port map (
    CodOperacion_i => Instruccion_s(RAM_TAM - 1 downto 2*Data_TAM),
    CLK_i => CLK_i,
    RST_i => RST_i,
    FZ_i => FZ_s,
    CW_o => CW_s
 );
 
 process (CLK_i, RST_i)
 begin
     if RST_i = '1' then
     elsif rising_edge(CLK_i)then
     end if;
 end process; 
  
 FZ_o <= FZ_s;
 Instruccion_o <= Instruccion_s;
end Behavioral;
