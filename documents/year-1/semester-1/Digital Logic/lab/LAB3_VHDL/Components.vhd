------------------------------------------------------------
-- Deeds (Digital Electronics Education and Design Suite)
-- VHDL Code generated on (1/5/2024, 9:44:22 PM)
--      by Deeds (Digital Circuit Simulator)(Deeds-DcS)
--      Ver. 2.50.200 (Feb 18, 2022)
-- Copyright (c) 2002-2022 University of Genoa, Italy
--      Web Site:  https://www.digitalelectronicsdeeds.com
------------------------------------------------------------

--------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY NOT_gate IS
  PORT( I: IN std_logic;
  	O: OUT std_logic );
END NOT_gate;

--------------------------------------------------------------------
ARCHITECTURE behavioral OF NOT_gate IS
BEGIN
  O <= (not I);
END behavioral;



--------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY AND2_gate IS
  PORT( I0,I1: IN std_logic;
        O: OUT std_logic );
END AND2_gate;

--------------------------------------------------------------------
ARCHITECTURE behavioral OF AND2_gate IS
BEGIN
  O <= (I0 and I1);
END behavioral;


--------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY OR2_gate IS
  PORT( I0,I1: IN std_logic;
        O: OUT std_logic );
END OR2_gate;

--------------------------------------------------------------------
ARCHITECTURE behavioral OF OR2_gate IS
BEGIN
  O <= (I0 or I1);
END behavioral;


--------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY JKpetFF IS
  PORT(  J, K, Ck: IN std_logic;
         nCL, nPR: IN std_logic;
         Q, nQ   : OUT std_logic );
END JKpetFF;

ARCHITECTURE behavioral OF JKpetFF IS 
BEGIN
  JKff: PROCESS( Ck, nCL, nPR )
    variable  OutQ: STD_LOGIC;
  BEGIN
    if    (nCL = '0') and (nPR = '1') then  OutQ := '0'; 
    elsif (nCL = '1') and (nPR = '0') then  OutQ := '1';
    elsif (nCL = '1') and (nPR = '1') then
      if (Ck'event) AND (Ck='1') THEN
        -- Positive Edge
        if    (J = '0') AND (K = '1') THEN  OutQ := '0';
        elsif (J = '1') AND (K = '0') THEN  OutQ := '1';
        elsif (J = '1') AND (K = '1') THEN  OutQ := not OutQ;
        elsif not((J='0')AND(K='0'))  THEN  OutQ := 'X';
        END IF;
      END IF;
    else                                    OutQ := 'X';
    END IF;
    --
    Q  <= (    OutQ);
    nQ <= (not OutQ);
    --
  END PROCESS;
END behavioral;

