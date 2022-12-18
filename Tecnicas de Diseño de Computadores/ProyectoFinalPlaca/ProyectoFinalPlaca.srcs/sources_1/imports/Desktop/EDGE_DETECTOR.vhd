library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity EDGE_DETECTOR is
	Generic(END_COUNT: integer:= 30000000);
    Port ( CLK_i : in STD_LOGIC;
           RST_i : in STD_LOGIC;
           PUSH_i : in STD_LOGIC;
           PULSE_o : out STD_LOGIC);
end EDGE_DETECTOR;

architecture Behavioral of EDGE_DETECTOR is

type EDGE_DETECTOR is (inic, S0, S01, S_WAIT);
signal ESTADO: EDGE_DETECTOR;

signal PUSH: std_logic;
signal COUNTER : integer range 0 to END_COUNT;	-- Contador

begin

process (CLK_i, RST_i)
begin
	if RST_i = '1' then
		ESTADO <= inic;
		PUSH <= '0';
		COUNTER <= 0;
	elsif rising_edge(CLK_i) then
		case ESTADO is
			when inic =>	
			    if PUSH = '0' then
				    ESTADO <= S0;
				end if;
			when S0 =>		
			    if PUSH = '1' then
					ESTADO <= S01;
				end if;
			when S01 =>		
			    ESTADO <= S_WAIT;
			--				COUNTER <= (others =>'0');
			when S_WAIT =>	
			    if COUNTER = END_COUNT then
				    ESTADO <= inic;
					COUNTER <= 0;
				else
					COUNTER <= COUNTER + 1;
				end if;
			when others => ESTADO <= inic;
		end case;
		
		PUSH <= PUSH_i;
		
	end if;
end process;

with ESTADO select
	PULSE_o <=	'0' when inic,
				'0' when S0,
				'1' when S01,
				'0' when others;	--catch all

end Behavioral;
