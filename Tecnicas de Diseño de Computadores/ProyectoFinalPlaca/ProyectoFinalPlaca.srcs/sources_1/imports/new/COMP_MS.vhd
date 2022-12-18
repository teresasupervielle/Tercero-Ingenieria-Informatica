----------------------------------------------------------------------------------
-- PROYECTOR FINAL TÉCNICAS DE DISEÑO DE COMPUTADORES --

-- COMP_MS incluye:
    -- Mapeado DataPath
    -- Mapeado UC
    -- Mapeado Debounce
    -- Mapeado EDGE_DETECTOR_4
    -- Mapeado EDGE_DETECTOR_6
    
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
         PUSH_i: in STD_LOGIC;
         FZ_o : out STD_LOGIC;
         ANODE_o: out STD_LOGIC_VECTOR (7 downto 0);
         CATHODE_o: out STD_LOGIC_VECTOR (6 downto 0));
end COMP_MS;

architecture Behavioral of COMP_MS is

signal CW_s : STD_LOGIC_VECTOR (CW_TAM - 1 downto 0);
signal CW_c : STD_LOGIC_VECTOR (CW_TAM - 1 downto 0);
signal FZ_s: STD_LOGIC;
signal PUSH_s: STD_LOGIC;
signal PULSE4_s: STD_LOGIC;
signal PULSE7_s: STD_LOGIC;
signal Instruccion_s : STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);
signal ALU_s: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
signal PC_s: STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0);
signal A_s: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
signal B_s: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
signal DataBus_s : STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);

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
        PUSH_i: in STD_LOGIC;
        RST_i: in STD_LOGIC;
        FZ_i: in STD_LOGIC;
        CW_o: out STD_LOGIC_VECTOR (CW_TAM - 1 downto 0));
end component;

component EDGE_DETECTOR is
	Generic(END_COUNT: integer:= 30000000);
    Port ( CLK_i : in STD_LOGIC;
           RST_i : in STD_LOGIC;
           PUSH_i : in STD_LOGIC;
           PULSE_o : out STD_LOGIC);
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

begin

DATAPATH : DATAPATH_1
port map(
    RST_i => RST_i,
    CLK_i => CLK_i,
    CW_i => CW_c, -- CW concatenado
    FZ_o => FZ_s,
    PC_o => PC_s,
    A_o => A_s,
    B_o => B_s,
    DataBus_o => DataBus_s,
    ALU_o => ALU_s,
    Instruccion_o => Instruccion_s
 );

CONT_UNIT : CONT_UNIT_1
 port map (
    CodOperacion_i => Instruccion_s(RAM_TAM - 1 downto 2*Data_TAM),
    CLK_i => CLK_i,
    PUSH_i => PUSH_s,
    RST_i => RST_i,
    FZ_i => FZ_s,
    CW_o => CW_s
 );
 
 EDGE_DETECTOR_4: EDGE_DETECTOR
  port map (
     CLK_i => CLK_i,
     RST_i => RST_i,
     PUSH_i => CW_s(4),
     PULSE_o => PULSE4_s
  );
 
  EDGE_DETECTOR_7: EDGE_DETECTOR
   port map (
      CLK_i => CLK_i,
      RST_i => RST_i,
      PUSH_i => CW_s(7),
      PULSE_o => PULSE7_s
   );
   
 DEBOUNCE: EDGE_DETECTOR
    port map (
       CLK_i => CLK_i,
       RST_i => RST_i,
       PUSH_i => PUSH_i,
       PULSE_o => PUSH_s
    );

  DISP7SEG_8_ON_1: DISP7SEG_8ON
    port map (
        CLK_i => CLK_i,
        RST_i => RST_i,
        DATA0_i => PC_s,
        DATA1_i => "0000",
        DATA2_i => A_s,
        DATA3_i => B_s,
        DATA4_i => ALU_s,
        DATA5_i => Instruccion_s (RAM_TAM - 1 downto 2*Data_TAM), 
        DATA6_i => Instruccion_s (2*Data_TAM - 1 downto Data_TAM), 
        DATA7_i => Instruccion_s (Data_TAM - 1 downto 0), 
        ANODE_o => ANODE_o,
        CATHODE_o => CATHODE_o
    );
  
 FZ_o <= FZ_s;
 CW_c <= CW_s(CW_TAM - 1 downto 8) & PULSE7_s & CW_s(6 downto 5) & PULSE4_s & CW_s(3 downto 0);
 
end Behavioral;
