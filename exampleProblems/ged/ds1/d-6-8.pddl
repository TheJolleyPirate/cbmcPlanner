;; original sequence 1: (1 34 13 24 28 15 10 9 4 7 11 17 16 19 2 36 35 20 21 -29 -25 -27 -12 -30 -18 -14 -26 -6 -32 31 8 -33 -3 22 5 23)
;; original sequence 2: (1 17 2 12 -19 -9 -21 -8 -7 33 -32 -11 -10 28 -4 -25 -24 -13 -34 -14 -26 -16 -36 -35 -29 -20 -18 3 23 15 30 27 22 6 31 5)
;; simplified sequence 1: (1 37 28 15 10 9 4 7 11 17 16 19 2 36 35 20 21 -29 -25 -27 -12 -30 -18 38 -6 -32 31 8 -33 -3 22 5 23)
;; simplified sequence 2: (1 17 2 12 -19 -9 -21 -8 -7 33 -32 -11 -10 28 -4 -25 -37 38 -16 -36 -35 -29 -20 -18 3 23 15 30 27 22 6 31 5)
;; common subsequences: (((34 13 24) . 37) ((-14 -26) . 38))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL COX1) (NORMAL SUB1) (NORMAL P) (NORMAL A) (NORMAL NAD6) (NORMAL NAD5) (NORMAL NAD1) (NORMAL NAD4L) (NORMAL COB) (NORMAL D) (NORMAL C) (NORMAL F) (NORMAL COX2) (NORMAL Y) (NORMAL W) (NORMAL G) (NORMAL H) (INVERTED Q) (INVERTED L2) (INVERTED N) (INVERTED ATP6) (INVERTED R) (INVERTED E) (NORMAL SUB2) (INVERTED NAD3) (INVERTED S2) (NORMAL S1) (NORMAL NAD4) (INVERTED T) (INVERTED COX3) (NORMAL I) (NORMAL NAD2) (NORMAL K))
;; sequence 2 (names): ((NORMAL COX1) (NORMAL D) (NORMAL COX2) (NORMAL ATP6) (INVERTED F) (INVERTED NAD5) (INVERTED H) (INVERTED NAD4) (INVERTED NAD4L) (NORMAL T) (INVERTED S2) (INVERTED COB) (INVERTED NAD6) (NORMAL P) (INVERTED NAD1) (INVERTED L2) (INVERTED SUB1) (NORMAL SUB2) (INVERTED C) (INVERTED Y) (INVERTED W) (INVERTED Q) (INVERTED G) (INVERTED E) (NORMAL COX3) (NORMAL K) (NORMAL A) (NORMAL R) (NORMAL N) (NORMAL I) (NORMAL NAD3) (NORMAL S1) (NORMAL NAD2))

(DEFINE (PROBLEM ALBINARIA-COERULEA-TO-KATHARINA-TUNICATA)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB2 SUB1 Y W T S2 S1 R Q P N L2 K I H G F E D C A
            ATP6 COB NAD6 NAD5 NAD4 NAD4L NAD3 NAD2 NAD1 COX3 COX2
            COX1)
        (:INIT (NORMAL COX1) (NORMAL SUB1) (NORMAL P) (NORMAL A)
               (NORMAL NAD6) (NORMAL NAD5) (NORMAL NAD1) (NORMAL NAD4L)
               (NORMAL COB) (NORMAL D) (NORMAL C) (NORMAL F)
               (NORMAL COX2) (NORMAL Y) (NORMAL W) (NORMAL G)
               (NORMAL H) (INVERTED Q) (INVERTED L2) (INVERTED N)
               (INVERTED ATP6) (INVERTED R) (INVERTED E) (NORMAL SUB2)
               (INVERTED NAD3) (INVERTED S2) (NORMAL S1) (NORMAL NAD4)
               (INVERTED T) (INVERTED COX3) (NORMAL I) (NORMAL NAD2)
               (NORMAL K) (PRESENT COX1) (PRESENT SUB1) (PRESENT P)
               (PRESENT A) (PRESENT NAD6) (PRESENT NAD5) (PRESENT NAD1)
               (PRESENT NAD4L) (PRESENT COB) (PRESENT D) (PRESENT C)
               (PRESENT F) (PRESENT COX2) (PRESENT Y) (PRESENT W)
               (PRESENT G) (PRESENT H) (PRESENT Q) (PRESENT L2)
               (PRESENT N) (PRESENT ATP6) (PRESENT R) (PRESENT E)
               (PRESENT SUB2) (PRESENT NAD3) (PRESENT S2) (PRESENT S1)
               (PRESENT NAD4) (PRESENT T) (PRESENT COX3) (PRESENT I)
               (PRESENT NAD2) (PRESENT K) (CW K COX1) (CW NAD2 K)
               (CW I NAD2) (CW COX3 I) (CW T COX3) (CW NAD4 T)
               (CW S1 NAD4) (CW S2 S1) (CW NAD3 S2) (CW SUB2 NAD3)
               (CW E SUB2) (CW R E) (CW ATP6 R) (CW N ATP6) (CW L2 N)
               (CW Q L2) (CW H Q) (CW G H) (CW W G) (CW Y W)
               (CW COX2 Y) (CW F COX2) (CW C F) (CW D C) (CW COB D)
               (CW NAD4L COB) (CW NAD1 NAD4L) (CW NAD5 NAD1)
               (CW NAD6 NAD5) (CW A NAD6) (CW P A) (CW SUB1 P)
               (CW COX1 SUB1) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL COX1) (NORMAL D) (NORMAL COX2)
                    (NORMAL ATP6) (INVERTED F) (INVERTED NAD5)
                    (INVERTED H) (INVERTED NAD4) (INVERTED NAD4L)
                    (NORMAL T) (INVERTED S2) (INVERTED COB)
                    (INVERTED NAD6) (NORMAL P) (INVERTED NAD1)
                    (INVERTED L2) (INVERTED SUB1) (NORMAL SUB2)
                    (INVERTED C) (INVERTED Y) (INVERTED W) (INVERTED Q)
                    (INVERTED G) (INVERTED E) (NORMAL COX3) (NORMAL K)
                    (NORMAL A) (NORMAL R) (NORMAL N) (NORMAL I)
                    (NORMAL NAD3) (NORMAL S1) (NORMAL NAD2)
                    (CW NAD2 COX1) (CW S1 NAD2) (CW NAD3 S1)
                    (CW I NAD3) (CW N I) (CW R N) (CW A R) (CW K A)
                    (CW COX3 K) (CW E COX3) (CW G E) (CW Q G) (CW W Q)
                    (CW Y W) (CW C Y) (CW SUB2 C) (CW SUB1 SUB2)
                    (CW L2 SUB1) (CW NAD1 L2) (CW P NAD1) (CW NAD6 P)
                    (CW COB NAD6) (CW S2 COB) (CW T S2) (CW NAD4L T)
                    (CW NAD4 NAD4L) (CW H NAD4) (CW NAD5 H) (CW F NAD5)
                    (CW ATP6 F) (CW COX2 ATP6) (CW D COX2) (CW COX1 D)))
        (:METRIC MINIMIZE (TOTAL-COST)))