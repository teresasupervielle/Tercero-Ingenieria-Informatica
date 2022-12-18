----------------------------------------------------------------------------------
-- PROYECTOR FINAL TÉCNICAS DE DISEÑO DE COMPUTADORES --

-- DATAPATH_1_TB incluye:
    -- A + B
    -- MOV B
    -- CMP A B
    -- BEZ dir
    
-- HECHO POR: Mª Teresa Supervielle Sánchez :D --
----------------------------------------------------------------------------------


library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity DATAPATH_1_tb is
end;

architecture bench of DATAPATH_1_tb is

  component DATAPATH_1
      generic (CW_TAM: integer := 10;
               N_ALU: integer := 2;
               Data_TAM: integer := 4;
               Direccion_TAM: integer := 4;
               RAM_TAM: integer := 12);
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

  constant CW_TAM: integer := 10;
  constant N_ALU: integer := 2;
  constant Data_TAM: integer := 4;
  constant Direccion_TAM: integer := 4;
  constant RAM_TAM: integer := 12;
               
  signal RST_i: STD_LOGIC;
  signal CLK_i: STD_LOGIC;
  signal CW_i: STD_LOGIC_VECTOR (CW_TAM - 1 downto 0);
  signal FZ_o: STD_LOGIC;
  signal PC_o: STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0);
  signal A_o: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
  signal B_o: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
  signal DataBus_o: STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);
  signal ALU_o: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
  signal Instruccion_o: STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: DATAPATH_1 generic map ( CW_TAM        => CW_TAM       ,
                                N_ALU         => N_ALU        ,
                                Data_TAM      => Data_TAM     ,
                                Direccion_TAM => Direccion_TAM,
                                RAM_TAM       => RAM_TAM       )
                     port map ( RST_i         => RST_i,
                                CLK_i         => CLK_i,
                                CW_i          => CW_i,
                                FZ_o          => FZ_o,
                                PC_o          => PC_o,
                                A_o           => A_o,
                                B_o           => B_o,
                                DataBus_o     => DataBus_o,
                                ALU_o         => ALU_o,
                                Instruccion_o => Instruccion_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;
    
                                        -- A + B --
                                        
    -- CICLO 1: Leer instruccion de PC[0] e incrementar PC, habilitando el Registro de Instrucciones
    CW_i <= "0010010000";
    wait for 10 ns;
    
    -- CICLO 2: Mandamos al Multiplexor del Bus de Direcciones, la salida del registro F
    CW_i <= "0001000000";
    wait for 10 ns;
    
    -- CICLO 3: Habilitamos la entrada en el RegA y mandamos al Multiplexor del Bus de Direcciones, la salida del registro D
    CW_i <= "0001100001";
    wait for 10 ns;
 
    -- CICLO 4: Seleccionamos la operación a realizar, y habilitamos la entrada del RegB
    CW_i <= "0001100010";
    wait for 10 ns;
    
    -- CICLO 5: Habilitamos la salida de la ALU, la flag de cero y la entrada a memoria RAM
    CW_i <= "0001101100";
    wait for 10 ns;

    -- CICLO DE ESPERA:
    CW_i <= "0000000000";
    wait for 10 ns;
    
                                            -- MOV B --
    
    -- CICLO 1: Leer instruccion de PC[1] e incrementar PC, habilitando el Registro de Instrucciones
    CW_i <= "0010010000";
    wait for 10 ns;
    
    -- CICLO 2: Mandamos al Multiplexor del Bus de Direcciones, la salida del registro F
    CW_i <= "0001000000";
    wait for 10 ns;
    
    -- CICLO 3: Habilitamos la entrada en el RegB, activamos la salida del registro D y seleccionamos la operación de la ALU
    CW_i <= "0101100010";
    wait for 10 ns;
    
    -- CICLO 4: Habilitamos la salida de la ALU, la flag de cero y la entrada a memoria RAM
    CW_i <= "0101101100";
    wait for 10 ns;
    
    -- CICLO DE ESPERA
    CW_i <= "0000000000";
    wait for 10 ns;
    
                                            -- CMP A, B --
    
    -- CICLO 1: Leer instruccion de PC[2] e incrementar PC, habilitando el Registro de Instrucciones
    CW_i <= "0010010000";
    wait for 10 ns;
    
    -- CICLO 2: Mandamos al Multiplexor del Bus de Direcciones, la salida del registro F
    CW_i <= "0001000000";
    wait for 10 ns;
    
    -- CICLO 3: Habilitamos la entrada en el RegA y mandamos al Multiplexor del Bus de Direcciones, la salida del registro D
    CW_i <= "0001100001";
    wait for 10 ns;
    
    -- CICLO 4: Habilitamos la entrada del RegB
    CW_i <= "0001100010";
    wait for 10 ns;
    
    -- CICLO 5: Seleccionamos la operación a realizar, habilitamos la salida de la ALU y la flag de cero
    CW_i <= "1001100100";
    wait for 10 ns;
    
    -- CICLO DE ESPERA:
    CW_i <= "0000000000";
    wait for 10 ns;
    
                                                -- BEZ dir --

    -- CICLO 1: Leer instruccion de PC[3], e incrementamos el PC, habilitando el Registro de Instrucciones
    CW_i <= "0010010000";
    wait for 10 ns;
    
    -- CICLO 2: Mandamos al Multiplexor del Bus de Direcciones, la salida del registro D y activamos la FZ
    CW_i <= "0001100000";
    wait for 10 ns;
    
    -- CICLO 3: Incrementamos el PC, que tendrá como Dirección la salida del multiplexor
    CW_i <= "0011100000";
    wait for 10 ns;
    
    -- CICLO DE ESPERA:
    CW_i <= "0000000000";
    wait for 10 ns;

    stop_the_clock <= true;
    wait;
  end process;

  clocking: process
  begin
    while not stop_the_clock loop
      CLK_i <= '0', '1' after clock_period / 2;
      wait for clock_period;
    end loop;
    wait;
  end process;

end;