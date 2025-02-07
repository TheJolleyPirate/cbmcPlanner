;; original sequence 1: (1 16 26 17 20 2 21 13 6 9 15 28 34 10 7 35 18 14 32 27 36 4 12 23 25 31 5 22 30 29 19 11 24 3 33 8)
;; original sequence 2: (1 34 13 24 28 15 10 9 4 7 11 17 16 19 2 36 35 20 21 -29 -25 -27 -12 -30 -18 -14 -26 -6 -32 31 8 -33 -3 22 5 23)
;; simplified sequence 1: (1 16 26 17 20 2 21 13 6 9 15 28 34 10 7 35 18 14 32 27 36 4 12 23 25 31 5 22 30 29 19 11 24 37 8)
;; simplified sequence 2: (1 34 13 24 28 15 10 9 4 7 11 17 16 19 2 36 35 20 21 -29 -25 -27 -12 -30 -18 -14 -26 -6 -32 31 8 -37 22 5 23)
;; common subsequences: (((3 33) . 37))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL COX1) (NORMAL C) (NORMAL M) (NORMAL D) (NORMAL G) (NORMAL COX2) (NORMAL H) (NORMAL RRNL) (NORMAL NAD3) (NORMAL NAD5) (NORMAL A) (NORMAL P) (NORMAL V) (NORMAL NAD6) (NORMAL NAD4L) (NORMAL W) (NORMAL E) (NORMAL RRNS) (NORMAL S2) (NORMAL N) (NORMAL Y) (NORMAL NAD1) (NORMAL ATP6) (NORMAL K) (NORMAL L2) (NORMAL S1) (NORMAL NAD2) (NORMAL I) (NORMAL R) (NORMAL Q) (NORMAL F) (NORMAL COB) (NORMAL L1) (NORMAL SUB1) (NORMAL NAD4))
;; sequence 2 (names): ((NORMAL COX1) (NORMAL V) (NORMAL RRNL) (NORMAL L1) (NORMAL P) (NORMAL A) (NORMAL NAD6) (NORMAL NAD5) (NORMAL NAD1) (NORMAL NAD4L) (NORMAL COB) (NORMAL D) (NORMAL C) (NORMAL F) (NORMAL COX2) (NORMAL Y) (NORMAL W) (NORMAL G) (NORMAL H) (INVERTED Q) (INVERTED L2) (INVERTED N) (INVERTED ATP6) (INVERTED R) (INVERTED E) (INVERTED RRNS) (INVERTED M) (INVERTED NAD3) (INVERTED S2) (NORMAL S1) (NORMAL NAD4) (INVERTED SUB1) (NORMAL I) (NORMAL NAD2) (NORMAL K))

(DEFINE (PROBLEM ASCARIS-SUUM-TO-ALBINARIA-COERULEA)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB1 Y W V S2 S1 R Q P N M L2 L1 K I H G F E D C A
            RRNS RRNL ATP6 COB NAD6 NAD5 NAD4 NAD4L NAD3 NAD2 NAD1 COX2
            COX1)
        (:INIT (NORMAL COX1) (NORMAL C) (NORMAL M) (NORMAL D)
               (NORMAL G) (NORMAL COX2) (NORMAL H) (NORMAL RRNL)
               (NORMAL NAD3) (NORMAL NAD5) (NORMAL A) (NORMAL P)
               (NORMAL V) (NORMAL NAD6) (NORMAL NAD4L) (NORMAL W)
               (NORMAL E) (NORMAL RRNS) (NORMAL S2) (NORMAL N)
               (NORMAL Y) (NORMAL NAD1) (NORMAL ATP6) (NORMAL K)
               (NORMAL L2) (NORMAL S1) (NORMAL NAD2) (NORMAL I)
               (NORMAL R) (NORMAL Q) (NORMAL F) (NORMAL COB)
               (NORMAL L1) (NORMAL SUB1) (NORMAL NAD4) (PRESENT COX1)
               (PRESENT C) (PRESENT M) (PRESENT D) (PRESENT G)
               (PRESENT COX2) (PRESENT H) (PRESENT RRNL) (PRESENT NAD3)
               (PRESENT NAD5) (PRESENT A) (PRESENT P) (PRESENT V)
               (PRESENT NAD6) (PRESENT NAD4L) (PRESENT W) (PRESENT E)
               (PRESENT RRNS) (PRESENT S2) (PRESENT N) (PRESENT Y)
               (PRESENT NAD1) (PRESENT ATP6) (PRESENT K) (PRESENT L2)
               (PRESENT S1) (PRESENT NAD2) (PRESENT I) (PRESENT R)
               (PRESENT Q) (PRESENT F) (PRESENT COB) (PRESENT L1)
               (PRESENT SUB1) (PRESENT NAD4) (CW NAD4 COX1)
               (CW SUB1 NAD4) (CW L1 SUB1) (CW COB L1) (CW F COB)
               (CW Q F) (CW R Q) (CW I R) (CW NAD2 I) (CW S1 NAD2)
               (CW L2 S1) (CW K L2) (CW ATP6 K) (CW NAD1 ATP6)
               (CW Y NAD1) (CW N Y) (CW S2 N) (CW RRNS S2) (CW E RRNS)
               (CW W E) (CW NAD4L W) (CW NAD6 NAD4L) (CW V NAD6)
               (CW P V) (CW A P) (CW NAD5 A) (CW NAD3 NAD5)
               (CW RRNL NAD3) (CW H RRNL) (CW COX2 H) (CW G COX2)
               (CW D G) (CW M D) (CW C M) (CW COX1 C) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL COX1) (NORMAL V) (NORMAL RRNL) (NORMAL L1)
                    (NORMAL P) (NORMAL A) (NORMAL NAD6) (NORMAL NAD5)
                    (NORMAL NAD1) (NORMAL NAD4L) (NORMAL COB)
                    (NORMAL D) (NORMAL C) (NORMAL F) (NORMAL COX2)
                    (NORMAL Y) (NORMAL W) (NORMAL G) (NORMAL H)
                    (INVERTED Q) (INVERTED L2) (INVERTED N)
                    (INVERTED ATP6) (INVERTED R) (INVERTED E)
                    (INVERTED RRNS) (INVERTED M) (INVERTED NAD3)
                    (INVERTED S2) (NORMAL S1) (NORMAL NAD4)
                    (INVERTED SUB1) (NORMAL I) (NORMAL NAD2) (NORMAL K)
                    (CW K COX1) (CW NAD2 K) (CW I NAD2) (CW SUB1 I)
                    (CW NAD4 SUB1) (CW S1 NAD4) (CW S2 S1) (CW NAD3 S2)
                    (CW M NAD3) (CW RRNS M) (CW E RRNS) (CW R E)
                    (CW ATP6 R) (CW N ATP6) (CW L2 N) (CW Q L2)
                    (CW H Q) (CW G H) (CW W G) (CW Y W) (CW COX2 Y)
                    (CW F COX2) (CW C F) (CW D C) (CW COB D)
                    (CW NAD4L COB) (CW NAD1 NAD4L) (CW NAD5 NAD1)
                    (CW NAD6 NAD5) (CW A NAD6) (CW P A) (CW L1 P)
                    (CW RRNL L1) (CW V RRNL) (CW COX1 V)))
        (:METRIC MINIMIZE (TOTAL-COST)))