;; original sequence 1: (1 25 2 23 17 12 3 20 6 15 30 27 31 18 -19 -9 -21 -8 -7 33 -28 10 11 32 -4 -24 -13 -34 -14 22 -29 26 5 35 -16 -36)
;; original sequence 2: (1 34 13 24 28 15 10 9 4 7 11 17 16 19 2 36 35 20 21 -29 -25 -27 -12 -30 -18 -14 -26 -6 -32 31 8 -33 -3 22 5 23)
;; simplified sequence 1: (1 25 2 23 17 12 3 20 6 15 30 27 31 18 -19 -9 -21 -8 -7 33 -28 10 11 32 -4 37 -14 22 -29 26 5 35 -16 -36)
;; simplified sequence 2: (1 -37 28 15 10 9 4 7 11 17 16 19 2 36 35 20 21 -29 -25 -27 -12 -30 -18 -14 -26 -6 -32 31 8 -33 -3 22 5 23)
;; common subsequences: (((-24 -13 -34) . 37))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL COX1) (NORMAL L2) (NORMAL COX2) (NORMAL K) (NORMAL D) (NORMAL ATP6) (NORMAL COX3) (NORMAL G) (NORMAL NAD3) (NORMAL A) (NORMAL R) (NORMAL N) (NORMAL S1) (NORMAL E) (INVERTED F) (INVERTED NAD5) (INVERTED H) (INVERTED NAD4) (INVERTED NAD4L) (NORMAL T) (INVERTED P) (NORMAL NAD6) (NORMAL COB) (NORMAL S2) (INVERTED NAD1) (NORMAL SUB1) (INVERTED RRNS) (NORMAL I) (INVERTED Q) (NORMAL M) (NORMAL NAD2) (NORMAL W) (INVERTED C) (INVERTED Y))
;; sequence 2 (names): ((NORMAL COX1) (INVERTED SUB1) (NORMAL P) (NORMAL A) (NORMAL NAD6) (NORMAL NAD5) (NORMAL NAD1) (NORMAL NAD4L) (NORMAL COB) (NORMAL D) (NORMAL C) (NORMAL F) (NORMAL COX2) (NORMAL Y) (NORMAL W) (NORMAL G) (NORMAL H) (INVERTED Q) (INVERTED L2) (INVERTED N) (INVERTED ATP6) (INVERTED R) (INVERTED E) (INVERTED RRNS) (INVERTED M) (INVERTED NAD3) (INVERTED S2) (NORMAL S1) (NORMAL NAD4) (INVERTED T) (INVERTED COX3) (NORMAL I) (NORMAL NAD2) (NORMAL K))

(DEFINE (PROBLEM DROSOPHILA-YAKUBA-TO-ALBINARIA-COERULEA)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB1 Y W T S2 S1 R Q P N M L2 K I H G F E D C A RRNS
            ATP6 COB NAD6 NAD5 NAD4 NAD4L NAD3 NAD2 NAD1 COX3 COX2
            COX1)
        (:INIT (NORMAL COX1) (NORMAL L2) (NORMAL COX2) (NORMAL K)
               (NORMAL D) (NORMAL ATP6) (NORMAL COX3) (NORMAL G)
               (NORMAL NAD3) (NORMAL A) (NORMAL R) (NORMAL N)
               (NORMAL S1) (NORMAL E) (INVERTED F) (INVERTED NAD5)
               (INVERTED H) (INVERTED NAD4) (INVERTED NAD4L) (NORMAL T)
               (INVERTED P) (NORMAL NAD6) (NORMAL COB) (NORMAL S2)
               (INVERTED NAD1) (NORMAL SUB1) (INVERTED RRNS) (NORMAL I)
               (INVERTED Q) (NORMAL M) (NORMAL NAD2) (NORMAL W)
               (INVERTED C) (INVERTED Y) (PRESENT COX1) (PRESENT L2)
               (PRESENT COX2) (PRESENT K) (PRESENT D) (PRESENT ATP6)
               (PRESENT COX3) (PRESENT G) (PRESENT NAD3) (PRESENT A)
               (PRESENT R) (PRESENT N) (PRESENT S1) (PRESENT E)
               (PRESENT F) (PRESENT NAD5) (PRESENT H) (PRESENT NAD4)
               (PRESENT NAD4L) (PRESENT T) (PRESENT P) (PRESENT NAD6)
               (PRESENT COB) (PRESENT S2) (PRESENT NAD1) (PRESENT SUB1)
               (PRESENT RRNS) (PRESENT I) (PRESENT Q) (PRESENT M)
               (PRESENT NAD2) (PRESENT W) (PRESENT C) (PRESENT Y)
               (CW Y COX1) (CW C Y) (CW W C) (CW NAD2 W) (CW M NAD2)
               (CW Q M) (CW I Q) (CW RRNS I) (CW SUB1 RRNS)
               (CW NAD1 SUB1) (CW S2 NAD1) (CW COB S2) (CW NAD6 COB)
               (CW P NAD6) (CW T P) (CW NAD4L T) (CW NAD4 NAD4L)
               (CW H NAD4) (CW NAD5 H) (CW F NAD5) (CW E F) (CW S1 E)
               (CW N S1) (CW R N) (CW A R) (CW NAD3 A) (CW G NAD3)
               (CW COX3 G) (CW ATP6 COX3) (CW D ATP6) (CW K D)
               (CW COX2 K) (CW L2 COX2) (CW COX1 L2) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL COX1) (INVERTED SUB1) (NORMAL P) (NORMAL A)
                    (NORMAL NAD6) (NORMAL NAD5) (NORMAL NAD1)
                    (NORMAL NAD4L) (NORMAL COB) (NORMAL D) (NORMAL C)
                    (NORMAL F) (NORMAL COX2) (NORMAL Y) (NORMAL W)
                    (NORMAL G) (NORMAL H) (INVERTED Q) (INVERTED L2)
                    (INVERTED N) (INVERTED ATP6) (INVERTED R)
                    (INVERTED E) (INVERTED RRNS) (INVERTED M)
                    (INVERTED NAD3) (INVERTED S2) (NORMAL S1)
                    (NORMAL NAD4) (INVERTED T) (INVERTED COX3)
                    (NORMAL I) (NORMAL NAD2) (NORMAL K) (CW K COX1)
                    (CW NAD2 K) (CW I NAD2) (CW COX3 I) (CW T COX3)
                    (CW NAD4 T) (CW S1 NAD4) (CW S2 S1) (CW NAD3 S2)
                    (CW M NAD3) (CW RRNS M) (CW E RRNS) (CW R E)
                    (CW ATP6 R) (CW N ATP6) (CW L2 N) (CW Q L2)
                    (CW H Q) (CW G H) (CW W G) (CW Y W) (CW COX2 Y)
                    (CW F COX2) (CW C F) (CW D C) (CW COB D)
                    (CW NAD4L COB) (CW NAD1 NAD4L) (CW NAD5 NAD1)
                    (CW NAD6 NAD5) (CW A NAD6) (CW P A) (CW SUB1 P)
                    (CW COX1 SUB1)))
        (:METRIC MINIMIZE (TOTAL-COST)))