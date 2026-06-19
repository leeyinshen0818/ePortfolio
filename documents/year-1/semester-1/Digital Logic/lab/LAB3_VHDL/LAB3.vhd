------------------------------------------------------------
-- Deeds (Digital Electronics Education and Design Suite)
-- VHDL Code generated on (1/5/2024, 9:44:22 PM)
--      by Deeds (Digital Circuit Simulator)(Deeds-DcS)
--      Ver. 2.50.200 (Feb 18, 2022)
-- Copyright (c) 2002-2022 University of Genoa, Italy
--      Web Site:  https://www.digitalelectronicsdeeds.com
------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.all;


ENTITY LAB3 IS
  PORT( 
    --------------------------------------> Inputs:
    iPRE:         IN  std_logic;
    iSwitch_7:    IN  std_logic;
    iCLR:         IN  std_logic;
    iSwitch_A:    IN  std_logic;
    --------------------------------------> Outputs:
    oLED_1:       OUT std_logic;
    oLED0:        OUT std_logic 
    ------------------------------------------------------
    );
END LAB3;


ARCHITECTURE structural OF LAB3 IS 

  ----------------------------------------> Components:
  COMPONENT NOT_gate IS
    PORT( I: IN std_logic;
          O: OUT std_logic );
  END COMPONENT;
  --
  COMPONENT AND2_gate IS
    PORT( I0,I1: IN std_logic;
          O: OUT std_logic );
  END COMPONENT;
  --
  COMPONENT OR2_gate IS
    PORT( I0,I1: IN std_logic;
          O: OUT std_logic );
  END COMPONENT;
  --
  COMPONENT JKpetFF IS
    PORT( J, K, Ck: IN std_logic;
          nCL, nPR: IN std_logic;
          Q, nQ   : OUT std_logic );
  END COMPONENT;

  ----------------------------------------> Signals:
  SIGNAL S001: std_logic;
  SIGNAL S002: std_logic;
  SIGNAL S003: std_logic;
  SIGNAL S004: std_logic;
  SIGNAL S005: std_logic;
  SIGNAL S006: std_logic;
  SIGNAL S007: std_logic;
  SIGNAL S008: std_logic;
  SIGNAL S009: std_logic;
  SIGNAL S010: std_logic;
  SIGNAL S011: std_logic;
  SIGNAL S012: std_logic;
  SIGNAL S013: std_logic;


BEGIN -- structural

  ----------------------------------------> Input:
  S001 <= iPRE;
  S003 <= iSwitch_7;
  S006 <= iCLR;
  S012 <= iSwitch_A;

  ----------------------------------------> Output:
  oLED_1 <= S013;
  oLED0 <= S007;

  ----------------------------------------> Component Mapping:
  C004: NOT_gate PORT MAP ( S003, S002 );
  C005: OR2_gate PORT MAP ( S002, S013, S008 );
  C006: AND2_gate PORT MAP ( S002, S007, S005 );
  C007: AND2_gate PORT MAP ( S003, S009, S011 );
  C008: JKpetFF PORT MAP ( S005, S011, S012, S006, S001, S013, 
                           S004 );
  C009: OR2_gate PORT MAP ( S004, S003, S010 );
  C010: JKpetFF PORT MAP ( S008, S010, S012, S006, S001, S007, 
                           S009 );
END structural;
