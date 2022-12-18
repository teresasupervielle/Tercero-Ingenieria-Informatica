----------------------------------------------------------------------------------
-- PROYECTOR FINAL TÉCNICAS DE DISEÑO DE COMPUTADORES --

-- DATAPATH_1 incluye:
    -- Multiplexor para el Bus de Dirección
    -- Memoria RAM
    -- CLK
    -- ALU
    
-- HECHO POR: Mª Teresa Supervielle Sánchez :D --
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity DATAPATH_1 is
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
end DATAPATH_1;

architecture Behavioral of DATAPATH_1 is
    
    signal ALU_s: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0); -- Señal de la ALU
    signal DataBus_s: STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0); -- Señal del Bus de Datos
    signal DireccionBus_s: STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0); -- Señal del Bus de Direcciones
    signal Instruccion_s: STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0); -- Señal del Registro de Instrucciones
    
    signal FZ_s: STD_LOGIC; -- Señal de la Flag de Cero
    signal PC_s: STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0); -- Señal del Contador de Programa
    signal A_s: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0); -- Señal del Registro A
    signal B_s: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0); -- Señal del Registro B
    
    signal ZERO: signed (Data_TAM - 1 downto 0) := (others => '0'); -- Constante ZERO para parametrizar la salida de la ALU, para activar la FZ
    
    type RAM_TYPE is array((2**Direccion_TAM) - 1 downto 0) of std_logic_vector(RAM_TAM - 1 downto 0); -- Creación del tipo RAM (16 posiciones de memoria x 12 bits de ancho)
    signal RAM : RAM_TYPE := ("000000001000", "000000000111", "000000000110", "000000000101", "000000000100", "000000000011", "000000000010", "000000000001", -- DATOS (Posiciones: 15 a 8)
                              "000000000000", "000000000000", "000000000000", "000000000000", "001100000110", "001010111011", "000110110110", "000010001001"); -- INSTRUCCIONES (Posiciones: 7 a 0)

begin

-- MULTIPLEXOR BUS DE DIRECCIONES
    with CW_i(6 downto 5) select
        DireccionBus_s   <= PC_s when "00", -- Salida del PC
                            Instruccion_s(RAM_TAM - Data_TAM - 1 downto Data_TAM) when "10", -- Salida del registro F (fuente)
                            Instruccion_s(Data_TAM - 1 downto 0) when "11", -- Salida del registro D (destino)
                            (others => '0') when others;    

-- RAM
process(CLK_i)
begin
    if rising_edge(CLK_i) then
        if CW_i(3) = '1' then -- Escritura
            RAM(to_integer(unsigned(DireccionBus_s)))(Data_TAM - 1 downto 0) <= ALU_s;
            DataBus_s(Data_TAM - 1 downto 0) <= ALU_s;
        else -- Lectura
            DataBus_s <= RAM(to_integer(unsigned(DireccionBus_s)));
        end if;
    end if;
end process;

-- CLK
process(RST_i, CLK_i)
begin
    if RST_i='1' then -- Inicializamos las señales a 0 para cada Reset
        FZ_s <= '0';
        A_s <= (others => '0');
        B_s <= (others => '0');
        PC_s <= (others => '0');
        Instruccion_s <= (others => '0');
    elsif rising_edge(CLK_i) then
         if CW_i(0) = '1' then -- Carga de A con el dato de Memoria[D]
             A_s <= DataBus_s(Data_TAM - 1 downto 0);
         end if;
         if CW_i(1) = '1' then -- Carga de B con el dato de Memoria[D]
             B_s <= DataBus_s(Data_TAM - 1 downto 0);
         end if;
         if CW_i(4) = '1' then -- Cargamos en el Registro de Instrucciones el valor de Data Bus
           Instruccion_s <= DataBus_s;
         end if;
         if CW_i(7) = '1' then
            PC_s <= STD_LOGIC_VECTOR(unsigned(DireccionBus_s) + 1); --Contador de Programas
         end if;      
         if CW_i(2) = '1' then -- Flag Zero
            if ALU_s = STD_LOGIC_VECTOR(ZERO) then
                FZ_s <= '1';
             else
                FZ_s <= '0';
            end if;
        end if;
    end if;
end process;

-- ALU
    with CW_i(CW_TAM - 1 downto CW_TAM - N_ALU) select
        ALU_s   <= STD_LOGIC_VECTOR(unsigned(A_s) + unsigned(B_s)) when "00",   -- A + B
                   B_s when "01",                                               -- MOV B
                   STD_LOGIC_VECTOR(unsigned(A_s) - unsigned(B_s)) when others; -- COMP A, B; haciendo una resta dependiendo del valor de la FZ, sabemos si son iguales o no                 

-- ASIGNACIÓN DE LAS SEÑALES
    ALU_o <= ALU_s;
    A_o <= A_s;
    B_o <= B_s;
    FZ_o <= FZ_s;
    PC_o <= PC_s;
    DataBus_o <= DataBus_s;
    Instruccion_o <= Instruccion_s;
end Behavioral;
