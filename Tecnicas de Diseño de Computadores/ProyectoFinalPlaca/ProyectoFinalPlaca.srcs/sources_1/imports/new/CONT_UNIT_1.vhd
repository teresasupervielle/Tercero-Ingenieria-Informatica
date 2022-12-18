----------------------------------------------------------------------------------
-- PROYECTOR FINAL TÉCNICAS DE DISEÑO DE COMPUTADORES --

-- CONT_UNIT_1 incluye:
    -- Definición de Estados
    -- Inicialización de las Salidas de los Estados
    -- Proceso Secuencial de la asignación de Estados
    -- Proceso Combinacional para las Salidas
    
-- HECHO POR: Mª Teresa Supervielle Sánchez :D --
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity CONT_UNIT_1 is
  Generic (CodOperacion_TAM: integer := 4;
           CW_TAM: integer := 10);
  Port (CodOperacion_i: in STD_LOGIC_VECTOR (CodOperacion_TAM - 1 downto 0);
        CLK_i: in STD_LOGIC;
        PUSH_i: in STD_LOGIC;
        RST_i: in STD_LOGIC;
        FZ_i: in STD_LOGIC;
        CW_o: out STD_LOGIC_VECTOR (CW_TAM - 1 downto 0));
end CONT_UNIT_1;

architecture Behavioral of CONT_UNIT_1 is

--Definición de los Estados

    type ESTADOS is (IDLE, LOAD, DECO, OPE_A, ADDR_A, ADDR_B, OPE_B, MOV_B, A_ADD_B, A_CMP_B, BRANCH, BRANCH_INST);
    signal ESTADO: ESTADOS;

-- Definición de las Salidas de los Estados

    constant OUTPUT_IDLE: std_logic_Vector(9 downto 0) := "0000000000";
    constant OUTPUT_LOAD: std_logic_Vector(9 downto 0) := "0010010000";
    constant OUTPUT_DECO: STD_LOGIC_VECTOR(9 downto 0) := "0000000000";
    constant OUTPUT_OPE_A: STD_LOGIC_VECTOR(9 downto 0) := "0001000001";
    constant OUTPUT_ADDR_A: STD_LOGIC_VECTOR(9 downto 0) := "0001000000";
    constant OUTPUT_OPE_B: STD_LOGIC_VECTOR(9 downto 0) := "0001100010";
    constant OUTPUT_ADDR_B: STD_LOGIC_VECTOR(9 downto 0) := "0001100000";
    constant OUTPUT_MOV_B: STD_LOGIC_VECTOR(9 downto 0) := "0101001100";
    constant OUTPUT_A_ADD_B: STD_LOGIC_VECTOR(9 downto 0) := "0001101100";
    constant OUTPUT_A_CMP_B: STD_LOGIC_VECTOR(9 downto 0) := "1000000100";
    constant OUTPUT_BRANCH: STD_LOGIC_VECTOR(9 downto 0) := "0001100000";
    constant OUTPUT_BRANCH_INST: STD_LOGIC_VECTOR(9 downto 0) := "0011110000";

begin

process (CLK_i, RST_i)
begin
    if RST_i = '1' then
        ESTADO <= IDLE;
    elsif rising_edge(CLK_i)then
        if PUSH_i = '1' then
            case ESTADO is
                when IDLE=>
                    ESTADO <= LOAD;
                when LOAD =>
                    ESTADO <= DECO;
                when DECO =>
                    if CodOperacion_i = "0011" then
                        if FZ_i = '0' then
                            ESTADO <= LOAD;
                        else
                            ESTADO <= BRANCH;
                        end if;
                    else
                        ESTADO <= ADDR_B;
                    end if;
                when BRANCH =>
                    ESTADO <= BRANCH_INST;
                when BRANCH_INST =>
                    ESTADO <= DECO;
                when ADDR_B =>
                    ESTADO <= OPE_B;
                when OPE_B =>
                    if CodOperacion_i = "0001" then
                        ESTADO <= MOV_B;
                    else
                       ESTADO <= ADDR_A;
                    end if;   
                when MOV_B =>
                    ESTADO <= IDLE;
                when ADDR_A =>
                    ESTADO <= OPE_A;             
                when OPE_A =>
                    if CodOperacion_i = "0010"  then
                       ESTADO <= A_CMP_B;
                    else
                       ESTADO <= A_ADD_B;
                    end if;
                when A_CMP_B =>
                    ESTADO <= IDLE;
                when A_ADD_B =>
                    ESTADO <= IDLE;
            end case;
        end if;
    end if;
end process;

-----------------------------------------------------------

with ESTADO select
CW_o <= OUTPUT_IDLE when IDLE,
        OUTPUT_LOAD when LOAD,
        OUTPUT_DECO when DECO,
        OUTPUT_OPE_A when OPE_A,
        OUTPUT_ADDR_A when ADDR_A,
        OUTPUT_OPE_B when OPE_B,
        OUTPUT_ADDR_B when ADDR_B,
        OUTPUT_MOV_B when MOV_B,
        OUTPUT_A_ADD_B when A_ADD_B,
        OUTPUT_A_CMP_B when A_CMP_B,
        OUTPUT_BRANCH when BRANCH,
        OUTPUT_BRANCH_INST when BRANCH_INST,
        OUTPUT_IDLE when others;

end Behavioral;