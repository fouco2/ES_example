library ieee;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Counter is

	port(
	
	--avalon signals
		Clk: in std_logic;
		nReset: in std_logic;
		Address: in std_logic_vector (2 downto 0);
		ChipSelect: in std_logic;
		ReadX: in std_logic;
		WriteX: in std_logic;
		ReadData: out std_logic_vector (31 downto 0);
		WriteData: in std_logic_vector (31 downto 0);
	
	--Interruptions
		IRQ: out std_logic
	);
	end Counter;
	
architecture rtl of Counter is
	--constants
	
	constant Cnt_zero: unsigned(31 downto 0) := (others => '0');
	--registers
	
	signal Cnt_next, Cnt_reg: unsigned(31 downto 0);
	signal En_next, En_reg: std_logic;
	signal Rz_next, Rz_reg: std_logic;
	signal EOT_next, EOT_reg: std_logic;
	signal ClrEOT_next, ClrEOT_reg: std_logic;
	signal IRQEn_next, IRQEn_reg: std_logic;
	signal CompVal_next, CompVal_reg: unsigned(31 downto 0); --value to compare with
	
	--intermediate signals
	
begin
	
	REG: process(Clk, nReset)
	begin
		if nReset = '0' then
		
			Cnt_reg <= Cnt_zero;
			En_reg <= '0';
			Rz_reg <= '0';
			IRQEn_reg <= '0';
			ClrEOT_reg <= '0';
			CompVal_reg <= (others => '0');
		
			
		elsif rising_edge(Clk) then
			
			Cnt_reg <= Cnt_next;
			En_reg <= En_next;
			Rz_reg <= Rz_next;
			IRQEn_reg <= IRQEn_next;
			ClrEOT_reg <= ClrEOT_next;
			CompVal_reg <= CompVal_next;
		end if;
	end process REG;
		
	
	REG_2: process(Clk, ClrEOT_reg, nReset)
	begin
		if (nReset = '0' or ClrEOT_reg = '1') then
		
			EOT_reg <= '0';
			
		elsif rising_edge(Clk) then
			
			EOT_reg <= EOT_next;
		end if;
	end process REG_2;
		
	AV_RW: process(ChipSelect, WriteX, ReadX, WriteData, Address, 
						Rz_reg, En_reg, IRQEn_reg, ClrEOT_reg, Cnt_reg, CompVal_reg, EOT_reg)
	begin
		--default case: avoid latches
		Rz_next <= '0';
		En_next <= En_reg;
		IRQEn_next <= IRQEn_reg;
		ClrEOT_next <= '0';
		ReadData <= (others => '0');
		
		if ChipSelect = '1' then
			if WriteX = '1' then
				case Address is
					when "001" => Rz_next <= '1';
					when "010" => En_next <= '1';
					when "011" => En_next <= '0';
					when "100" => IRQEn_next <= WriteData(0);
					when "101" => ClrEOT_next <= WriteData(0);
					when "111" => CompVal_next <= unsigned(WriteData);
					when others => null; 
				end case;
				
			elsif ReadX = '1' then
				case Address is
					when "000" => ReadData <= std_logic_vector(Cnt_reg);
					when "100" => ReadData(0) <= IRQEn_reg;
					when "101" => ReadData(0) <= EOT_reg;
									  ReadData(1) <= En_reg;
					when "111" => ReadData <= std_logic_vector(CompVal_reg);
					when others => null;
				end case;
			end if;
		end if;
	end process AV_RW;
		
	
	--Counter logic 
	Cnt_next <= Cnt_zero when Rz_reg = '1' else
				Cnt_reg + 1 when En_reg = '1' else
				Cnt_reg;
	
	--Interrupt logic
	
	INTERRUPT: process(Cnt_reg, ClrEOT_reg, CompVal_reg, EOT_reg)
	begin
	--default
	EOT_next <= EOT_reg;
		if Cnt_reg = CompVal_reg then
			EOT_next <= '1';
		elsif ClrEOT_reg = '1' then
			EOT_next <= '0';
		end if;
	end process INTERRUPT;
	
 IRQ <= '1' when EOT_reg = '1' and IRQEn_reg = '1' and En_reg = '1' else
		  '0';
			
			
end architecture rtl;