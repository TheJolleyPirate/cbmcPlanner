;; original sequence 1: (1 25 2 23 17 12 3 20 6 15 30 27 31 18 -19 -9 -21 -8 -7 33 -28 10 11 32 -4 -24 -13 -34 -14 26 5 35 -22 -29 -16 -36)
;; original sequence 2: (1 30 7 2 23 12 3 -32 6 8 21 31 9 -10 11 19 14 18 33 28 -29 27 24 -15 35 16 -34 26 -17 36 20 25 4 22 5 13)
;; simplified sequence 1: (1 25 38 17 37 20 6 15 30 27 31 18 -19 -9 39 -7 33 -28 10 11 32 -4 -24 -13 -34 -14 26 5 35 -22 -29 -16 -36)
;; simplified sequence 2: (1 30 7 38 37 -32 6 -39 31 9 -10 11 19 14 18 33 28 -29 27 24 -15 35 16 -34 26 -17 36 20 25 4 22 5 13)
;; common subsequences: (((12 3) . 37) ((2 23) . 38) ((-21 -8) . 39))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL COX1) (NORMAL L2) (NORMAL SUB2) (NORMAL D) (NORMAL SUB1) (NORMAL G) (NORMAL NAD3) (NORMAL A) (NORMAL R) (NORMAL N) (NORMAL S1) (NORMAL E) (INVERTED F) (INVERTED NAD5) (NORMAL SUB3) (INVERTED NAD4L) (NORMAL T) (INVERTED P) (NORMAL NAD6) (NORMAL COB) (NORMAL S2) (INVERTED NAD1) (INVERTED L1) (INVERTED RRNL) (INVERTED V) (INVERTED RRNS) (NORMAL M) (NORMAL NAD2) (NORMAL W) (INVERTED I) (INVERTED Q) (INVERTED C) (INVERTED Y))
;; sequence 2 (names): ((NORMAL COX1) (NORMAL R) (NORMAL NAD4L) (NORMAL SUB2) (NORMAL SUB1) (INVERTED S2) (NORMAL NAD3) (INVERTED SUB3) (NORMAL S1) (NORMAL NAD5) (INVERTED NAD6) (NORMAL COB) (NORMAL F) (NORMAL RRNS) (NORMAL E) (NORMAL T) (NORMAL P) (INVERTED Q) (NORMAL N) (NORMAL L1) (INVERTED A) (NORMAL W) (NORMAL C) (INVERTED V) (NORMAL M) (INVERTED D) (NORMAL Y) (NORMAL G) (NORMAL L2) (NORMAL NAD1) (NORMAL I) (NORMAL NAD2) (NORMAL RRNL))

(DEFINE (PROBLEM ARTEMIA-FRANCISCANA-TO-PARACENTROTUS-LIVIDUS)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB3 SUB2 SUB1 Y W V T S2 S1 R Q P N M L2 L1 I G F E
            D C A RRNS RRNL COB NAD6 NAD5 NAD4L NAD3 NAD2 NAD1 COX1)
        (:INIT (NORMAL COX1) (NORMAL L2) (NORMAL SUB2) (NORMAL D)
               (NORMAL SUB1) (NORMAL G) (NORMAL NAD3) (NORMAL A)
               (NORMAL R) (NORMAL N) (NORMAL S1) (NORMAL E)
               (INVERTED F) (INVERTED NAD5) (NORMAL SUB3)
               (INVERTED NAD4L) (NORMAL T) (INVERTED P) (NORMAL NAD6)
               (NORMAL COB) (NORMAL S2) (INVERTED NAD1) (INVERTED L1)
               (INVERTED RRNL) (INVERTED V) (INVERTED RRNS) (NORMAL M)
               (NORMAL NAD2) (NORMAL W) (INVERTED I) (INVERTED Q)
               (INVERTED C) (INVERTED Y) (PRESENT COX1) (PRESENT L2)
               (PRESENT SUB2) (PRESENT D) (PRESENT SUB1) (PRESENT G)
               (PRESENT NAD3) (PRESENT A) (PRESENT R) (PRESENT N)
               (PRESENT S1) (PRESENT E) (PRESENT F) (PRESENT NAD5)
               (PRESENT SUB3) (PRESENT NAD4L) (PRESENT T) (PRESENT P)
               (PRESENT NAD6) (PRESENT COB) (PRESENT S2) (PRESENT NAD1)
               (PRESENT L1) (PRESENT RRNL) (PRESENT V) (PRESENT RRNS)
               (PRESENT M) (PRESENT NAD2) (PRESENT W) (PRESENT I)
               (PRESENT Q) (PRESENT C) (PRESENT Y) (CW Y COX1) (CW C Y)
               (CW Q C) (CW I Q) (CW W I) (CW NAD2 W) (CW M NAD2)
               (CW RRNS M) (CW V RRNS) (CW RRNL V) (CW L1 RRNL)
               (CW NAD1 L1) (CW S2 NAD1) (CW COB S2) (CW NAD6 COB)
               (CW P NAD6) (CW T P) (CW NAD4L T) (CW SUB3 NAD4L)
               (CW NAD5 SUB3) (CW F NAD5) (CW E F) (CW S1 E) (CW N S1)
               (CW R N) (CW A R) (CW NAD3 A) (CW G NAD3) (CW SUB1 G)
               (CW D SUB1) (CW SUB2 D) (CW L2 SUB2) (CW COX1 L2) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL COX1) (NORMAL R) (NORMAL NAD4L)
                    (NORMAL SUB2) (NORMAL SUB1) (INVERTED S2)
                    (NORMAL NAD3) (INVERTED SUB3) (NORMAL S1)
                    (NORMAL NAD5) (INVERTED NAD6) (NORMAL COB)
                    (NORMAL F) (NORMAL RRNS) (NORMAL E) (NORMAL T)
                    (NORMAL P) (INVERTED Q) (NORMAL N) (NORMAL L1)
                    (INVERTED A) (NORMAL W) (NORMAL C) (INVERTED V)
                    (NORMAL M) (INVERTED D) (NORMAL Y) (NORMAL G)
                    (NORMAL L2) (NORMAL NAD1) (NORMAL I) (NORMAL NAD2)
                    (NORMAL RRNL) (CW RRNL COX1) (CW NAD2 RRNL)
                    (CW I NAD2) (CW NAD1 I) (CW L2 NAD1) (CW G L2)
                    (CW Y G) (CW D Y) (CW M D) (CW V M) (CW C V)
                    (CW W C) (CW A W) (CW L1 A) (CW N L1) (CW Q N)
                    (CW P Q) (CW T P) (CW E T) (CW RRNS E) (CW F RRNS)
                    (CW COB F) (CW NAD6 COB) (CW NAD5 NAD6)
                    (CW S1 NAD5) (CW SUB3 S1) (CW NAD3 SUB3)
                    (CW S2 NAD3) (CW SUB1 S2) (CW SUB2 SUB1)
                    (CW NAD4L SUB2) (CW R NAD4L) (CW COX1 R)))
        (:METRIC MINIMIZE (TOTAL-COST)))