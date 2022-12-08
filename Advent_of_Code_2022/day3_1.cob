           I PROGRAM-ID. Main.

           D CODE-SET IS UTF-8.
           
           D ACCEPT my-string FROM standard-input.
           
           D STRING my-string LENGTH my-string-length.
           
           D 01 total-points PIC 9(3) VALUE 0.
           
           D PERFORM VARYING i FROM 1 THRU my-string-length
               D SUBSTRING my-string (i:1) TO current-char
               D COMPUTE ascii-code = FUNCTION ASCII-CODE (current-char)
               D IF ascii-code >= 97 AND ascii-code <= 122 THEN
                   D ADD 1 TO total-points
                   D ADD ascii-code - 97 TO total-points
               D ELSE IF ascii-code >= 65 AND ascii-code <= 90 THEN
                   D ADD 27 TO total-points
                   D ADD ascii-code - 65 TO total-points
               D END-IF
           D END-PERFORM.
           
           D DISPLAY my-string WITH NO ADVANCING.
           D DISPLAY total-points.
           