LOC     LABEL    OPCODE   OPERAND   ObjectCode
0000    COPY     START    0  
0000    FIRST    STL      RETADR    17202D
0003             LDB      #LENGTH   69202D
                 BASE     LENGTH          
0006    CLOOP    +JSUB    RDREC     4B101036
000A             LDA      LENGTH    032026
000D             COMP     #0        290000
0010             JEQ      ENDFIL    332007
0013             +JSUB    WRREC     4B10105D
0017             J        CLOOP     3F2FEC
001A    ENDFIL   LDA      EOF       032010
001D             STA      BUFFER    0F2016
0020             LDA      #3        010003
0023             STA      LENGTH    0F200D
0026             +JSUB    WRREC     4B10105D
002A             J        @RETADR   3E2003
002D    EOF      BYTE     C'EOF'    454F46
0030    RETADR   RESW     1         
0033    LENGTH   RESW     1         
0036    BUFFER   RESB     4096      
1036    RDREC    CLEAR    X         B410
1038             CLEAR    A         B400
103A             CLEAR    S         B440
103C             +LDT     1000      75101000
1040    RLOOP    TD       INPUT     E32019
1043             JEQ      RLOOP     332FFA
1046             RD       INPUT     DB2013
1049             COMPR    A,S       A004
104B             JEQ      EXIT      332008
104E             STCH     BUFFER,X  57C003
1051             TIXR     T         B850
1053             JLT      RLOOP     3B2FEA
1056    EXIT     STX      LENGTH    134000
1059             RSUB               4F0000
105C    INPUT    BYTE     X'F1'     F1
105D    WRREC    CLEAR    X         B410
105F             LDT      LENGTH    774000
1062    WLOOP    TD       OUTPUT    E32011
1065             JEQ      WLOOP     332FFA
1068             LDCH     BUFFER,X  53C003
106B             WD       OUTPUT    DF2008
106E             TIXR     T         B850
1070             JLT      WLOOP     3B2FEF
1073             RSUB               4F0000
1076    OUTPUT   BYTE     X'05'     05
                 END      000000                    
