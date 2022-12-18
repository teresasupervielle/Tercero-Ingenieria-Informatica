library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity COMP_MS_tb is
end;

architecture bench of COMP_MS_tb is

  component COMP_MS
    generic ( CW_TAM: integer := 10;
              Direccion_TAM: integer := 4;
              Data_TAM: integer := 4;
              RAM_TAM: integer := 12); 
    Port ( RST_i : in STD_LOGIC;
           CLK_i : in STD_LOGIC;
           FZ_o : out STD_LOGIC;
           A_o: out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
           B_o: out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
           PC_o : out STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0); 
           DataBus_o : out STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);
           Instruccion_o: out STD_LOGIC_VECTOR (RAM_TAM -1 downto 0); 
           ALU_o : out STD_LOGIC_VECTOR (Data_TAM - 1 downto 0));
  end component;

  constant CW_TAM: integer := 10;
  constant Direccion_TAM: integer := 4;
  constant Data_TAM: integer := 4;
  constant RAM_TAM: integer := 12;
  signal RST_i: STD_LOGIC;
  signal CLK_i: STD_LOGIC;
  signal FZ_o: STD_LOGIC;
  signal A_o: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
  signal B_o: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);
  signal PC_o: STD_LOGIC_VECTOR (Direccion_TAM - 1 downto 0);
  signal DataBus_o: STD_LOGIC_VECTOR (RAM_TAM - 1 downto 0);
  signal Instruccion_o: STD_LOGIC_VECTOR (RAM_TAM -1 downto 0);
  signal ALU_o: STD_LOGIC_VECTOR (Data_TAM - 1 downto 0);

  constant clock_period: time := 10 ns;
  signal stop_the_clock: boolean;

begin

  uut: COMP_MS generic map ( CW_TAM        => CW_TAM,
                             Direccion_TAM => Direccion_TAM,
                             Data_TAM      => Data_TAM,
                             RAM_TAM       =>  RAM_TAM)
                  port map ( RST_i         => RST_i,
                             CLK_i         => CLK_i,
                             FZ_o          => FZ_o,
                             A_o           => A_o,
                             B_o           => B_o,
                             PC_o          => PC_o,
                             DataBus_o     => DataBus_o,
                             Instruccion_o => Instruccion_o,
                             ALU_o         => ALU_o );

  stimulus: process
  begin

    RST_i <= '1';
    wait for 5 ns;
    RST_i <= '0';
    wait for 5 ns;

    wait for 300 ns;

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