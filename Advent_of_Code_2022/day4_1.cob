        IDENTIFICATION DIVISION.
        PROGRAM-ID. UNSTRING_SAMPLE03.
        
        ENVIRONMENT     DIVISION.
        CONFIGURATION SECTION.
        DATA       DIVISION.
            WORKING-STORAGE SECTION.
            01 TEST-WORK-AREA.
            03 WORK-STR      PIC x(20).
            03 WORK-RESULT   PIC 9(05).
            03 WORK-ITEM     PIC x(03)   OCCURS 4.
            03 ANS           PIC 9(05).
        
        PROCEDURE        DIVISION.
            MAIN        SECTION.
        
            PERFORM UNTIL 1 = 2
                ACCEPT WORK-STR
                IF WORK-STR = SPACES
                    EXIT PERFORM
                END-IF
                MOVE ZERO          TO WORK-RESULT
            
                UNSTRING WORK-STR DELIMITED BY "," OR "-"
                   INTO  WORK-ITEM(1) WORK-ITEM(2)
                       WORK-ITEM(3) WORK-ITEM(4)
                TALLYING IN WORK-RESULT
            
            *>結果を出力
               
               IF ((FUNCTION NUMVAL(WORK-ITEM(1)) <= 
               FUNCTION NUMVAL(WORK-ITEM(3))) AND 
               (FUNCTION NUMVAL(WORK-ITEM(4)) <= 
               FUNCTION NUMVAL(WORK-ITEM(2))) OR 
               (FUNCTION NUMVAL(WORK-ITEM(3)) <= 
               FUNCTION NUMVAL(WORK-ITEM(1))) AND 
               (FUNCTION NUMVAL(WORK-ITEM(2)) <= 
               FUNCTION NUMVAL(WORK-ITEM(4))))
                   ADD 1 TO ANS
               END-IF
            END-PERFORM.
            DISPLAY "[ANS : "ANS"]"  UPON CONSOLE.
        
        STOP RUN.