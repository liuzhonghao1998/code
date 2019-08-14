library ieee;
use ieee.std_logic_1164.all;

entity asd is
port(w1,w2,w3,t3,clr,c,z:in std_logic;
	sw:in std_logic_vector(2 downto 0);
	ir:in std_logic_vector(7 downto 4);
	cin,m,drw,selctl,ldc,ldz,lar,lir,lpc,arinc,pcinc,pcadd,mbus,abus,sbus,memw,stop,short,long:out std_logic;
	sel,s:out std_logic_vector(3 downto 0));
end asd;

architecture cpu of asd is
signal st0:std_logic;
signal sst0:std_logic;
signal ir0:std_logic_vector(7 downto 4);
begin

process(w1,w2,w3,t3,clr,sw,st0,sst0,ir,ir0)
begin

cin<='0';
m<='0';
drw<='0';
selctl<='0';
ldc<='0';
ldz<='0';
lar<='0';
lir<='0';
lpc<='0';
arinc<='0';
pcinc<='0';
pcadd<='0';
mbus<='0';
abus<='0';
sbus<='0';
memw<='0';
stop<='0';
short<='0';
long<='0';
sel<="0000";
s<="0000";

if(clr='0')then
	st0<='0';
	sst0<='0';
	ir0<="0000";
else
	sst0<=((not st0)and
	((sw(2)and (not sw(1))and (not sw(0))and w2)
	or((not sw(2))and sw(1)and(not sw(0))and w1)
	or((not sw(2))and(not sw(1))and sw(0)and w1)
	or((not sw(2))and(not sw(1))and (not sw(0))and w1)))
	or(st0 and
	((sw(2)and(not sw(1))and(not sw(0))and w1)
	or((not sw(2))and sw(1)and(not sw(0))and w1)
	or((not sw(2))and(not sw(1))and sw(0)and w1)))
	;
	if(sst0='1')then
		if(t3'event and (t3='0'))then
			st0<='1';
		end if;
	end if;
	if(t3'event and (t3='0'))then
		ir0<=ir;
	end if;
case sw is
when "100"=>
	if(st0='0')then
		if(w1='1')then
			sbus<='1';
			sel<="0011";
			selctl<='1';
			drw<='1';
			stop<='1';
		end if;
		if(w2='1')then
			sbus<='1';
			sel<="0100";
			selctl<='1';
			drw<='1';
			stop<='1';
			
		end if;
	end if;
	
	if(st0='1')then
		if(w1='1')then
			sbus<='1';
			sel<="1001";
			selctl<='1';
			drw<='1';
			stop<='1';
		end if;
		if(w2='1')then
			sbus<='1';
			sel<="1110";
			selctl<='1';
			drw<='1';
			stop<='1';
			
		end if;
	end if;
	
when "011"=>
	if(w1='1')then
		sel<="0001";
		selctl<='1';
		stop<='1';
	end if;
	if(w2='1')then
		sel<="1011";
		selctl<='1';
		stop<='1';
	end if;

when "010"=> 
	 if(st0='0')then
		if(w1='1')then 
			sbus<='1';
			lar<='1';
			stop<='1';
			short<='1';
			selctl<='1';
			
	   end if;
	 end if;
	 if(st0='1')then
		if(w1='1')then
			mbus<='1';
			arinc<='1';
			stop<='1';
			short<='1';
			selctl<='1';
	    end if;
	 end if;

when "001"=>
	if(st0='0')then
		if(w1='1')then
			sbus<='1';
			lar<='1';
			stop<='1';
			short<='1';
			selctl<='1';
			
		end if;
	end if;
	if(st0='1')then
		if(w1='1')then
			sbus<='1';
			memw<='1';
			arinc<='1';
			stop<='1';
			short<='1';
			selctl<='1';
		end if;
	end if;

when "000"=>
	case ir0 is
	when "0000"=>
        if(st0='0')then
          if(w1 = '1')then
	        sbus<='1';
	        lpc<='1';
	        short<='1';
	       end if;
	     end if;
        if(st0='1')then
          if(w1 = '1')then
	        lir<='1';
	        pcinc<='1';
	        short<='1';
	       end if;
	     end if;
	when "0001" =>
		if(w1 = '1') then
			s <= "1001";
			cin <= '1';
			abus <= '1';
			drw <= '1';
			ldz <= '1';
			ldc <= '1';
			short<='1';
			lir<='1';
			pcinc<='1';
		end if;
	when "0010" =>
		if(w1 = '1') then
			s <= "0110";
			abus <= '1';
			drw <= '1';
			ldz <= '1';
			ldc <= '1';
			short<='1';
			lir<='1';
			pcinc<='1';
		end if;
	when "0011" =>
		if(w1 = '1') then
			m <= '1';
			s <= "1011";
			abus <= '1';
			drw <= '1';
			ldz <= '1';
			short<='1';
			lir<='1';
			pcinc<='1';			
		end if;
	when "0100" =>
		if(w1 = '1') then
			s <= "0000";
			abus <= '1';
			drw <= '1';
			ldz <= '1';
			ldc <= '1';
			short<='1';
			lir<='1';
			pcinc<='1';			
		end if;
	when "0101" =>
		if(w1 = '1') then
			m <= '1';
			s <= "1010";
			abus <= '1';
			lar <= '1';
		end if;
		if(w2 = '1') then
			drw <= '1';
			mbus <= '1';
			lir<='1';
			pcinc<='1';
		end if;
	when "0110" =>
		if(w1='1') then
			m <='1';
			s<="1111";
			abus<='1';
			lar<='1';
		end if;
		if(w2 ='1') then
			m<='1';
			abus<='1';
			s<="1010";
			memw<='1';
			lir<='1';
			pcinc<='1';
			end if;
	when "0111" =>
		if(w1='1') then
			if(c='1')then
				pcadd<='1';
			else
				short<='1';
				lir<='1';
				pcinc<='1';
			end if;
		end if;
		if(w2='1')then
			lir<='1';
			pcinc<='1';
		end if;
	when "1000"=>
		if(w1='1') then
			if(z='1')then
				pcadd<='1';
			else
				short<='1';
				lir<='1';
				pcinc<='1';
			end if;
		end if;
		if(w2='1')then
			lir<='1';
			pcinc<='1';
		end if;
	when "1001" =>
		if(w1='1') then
			m<='1';
			s<="1111";
			abus<='1';
			lpc<='1';
		end if;
		if(w2='1')then
			lir<='1';
			pcinc<='1';
		end if;
	when "1010"=>
		if(w1='1')then
			m<='1';
			s<="1010";
			abus<='1';
			short<='1';
			lir<='1';
			pcinc<='1';
		end if;
	when "1011"=>
		if(w1='1') then
			m<='1';
			s<="1010";
			abus<='1';
			drw<='1';
			short<='1';
			lir<='1';
			pcinc<='1';
		end if;
	when "1110" =>
		if(w1='1') then 
			stop<='1';
			short<='1';
			lir<='1';
			pcinc<='1';
		end if;
	when others=>sbus<='0';	
	end case;
when others=>sbus<='0';
end case;
end if;
end process;
end cpu;