;; original sequence 1: (1 -32 17 2 23 12 3 20 6 30 7 8 21 31 24 9 -10 -18 11 33 -28 19 14 34 13 25 4 22 -29 26 5 35 -15 -27 -16 -36)
;; original sequence 2: (1 16 26 17 20 2 21 13 6 9 15 28 34 10 7 35 18 14 32 27 36 4 12 23 25 31 5 22 30 29 19 11 24 3 33 8)
;; simplified sequence 1: (1 -32 17 2 23 12 3 20 6 30 7 8 21 31 24 9 -10 -18 11 33 -28 19 14 34 13 25 4 22 -29 26 5 35 -15 -27 -16 -36)
;; simplified sequence 2: (1 16 26 17 20 2 21 13 6 9 15 28 34 10 7 35 18 14 32 27 36 4 12 23 25 31 5 22 30 29 19 11 24 3 33 8)
;; common subsequences: NIL
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL COX1) (INVERTED S2) (NORMAL D) (NORMAL COX2) (NORMAL K) (NORMAL ATP6) (NORMAL COX3) (NORMAL G) (NORMAL NAD3) (NORMAL R) (NORMAL NAD4L) (NORMAL NAD4) (NORMAL H) (NORMAL S1) (NORMAL L1) (NORMAL NAD5) (INVERTED NAD6) (INVERTED E) (NORMAL COB) (NORMAL T) (INVERTED P) (NORMAL F) (NORMAL RRNS) (NORMAL V) (NORMAL RRNL) (NORMAL L2) (NORMAL NAD1) (NORMAL I) (INVERTED Q) (NORMAL M) (NORMAL NAD2) (NORMAL W) (INVERTED A) (INVERTED N) (INVERTED C) (INVERTED Y))
;; sequence 2 (names): ((NORMAL COX1) (NORMAL C) (NORMAL M) (NORMAL D) (NORMAL G) (NORMAL COX2) (NORMAL H) (NORMAL RRNL) (NORMAL NAD3) (NORMAL NAD5) (NORMAL A) (NORMAL P) (NORMAL V) (NORMAL NAD6) (NORMAL NAD4L) (NORMAL W) (NORMAL E) (NORMAL RRNS) (NORMAL S2) (NORMAL N) (NORMAL Y) (NORMAL NAD1) (NORMAL ATP6) (NORMAL K) (NORMAL L2) (NORMAL S1) (NORMAL NAD2) (NORMAL I) (NORMAL R) (NORMAL Q) (NORMAL F) (NORMAL COB) (NORMAL L1) (NORMAL COX3) (NORMAL T) (NORMAL NAD4))

(DEFINE (PROBLEM HUMAN-TO-ASCARIS-SUUM) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS Y W V T S2 S1 R Q P N M L2 L1 K I H G F E D C A RRNS
            RRNL ATP6 COB NAD6 NAD5 NAD4 NAD4L NAD3 NAD2 NAD1 COX3 COX2
            COX1)
        (:INIT (NORMAL COX1) (INVERTED S2) (NORMAL D) (NORMAL COX2)
               (NORMAL K) (NORMAL ATP6) (NORMAL COX3) (NORMAL G)
               (NORMAL NAD3) (NORMAL R) (NORMAL NAD4L) (NORMAL NAD4)
               (NORMAL H) (NORMAL S1) (NORMAL L1) (NORMAL NAD5)
               (INVERTED NAD6) (INVERTED E) (NORMAL COB) (NORMAL T)
               (INVERTED P) (NORMAL F) (NORMAL RRNS) (NORMAL V)
               (NORMAL RRNL) (NORMAL L2) (NORMAL NAD1) (NORMAL I)
               (INVERTED Q) (NORMAL M) (NORMAL NAD2) (NORMAL W)
               (INVERTED A) (INVERTED N) (INVERTED C) (INVERTED Y)
               (PRESENT COX1) (PRESENT S2) (PRESENT D) (PRESENT COX2)
               (PRESENT K) (PRESENT ATP6) (PRESENT COX3) (PRESENT G)
               (PRESENT NAD3) (PRESENT R) (PRESENT NAD4L)
               (PRESENT NAD4) (PRESENT H) (PRESENT S1) (PRESENT L1)
               (PRESENT NAD5) (PRESENT NAD6) (PRESENT E) (PRESENT COB)
               (PRESENT T) (PRESENT P) (PRESENT F) (PRESENT RRNS)
               (PRESENT V) (PRESENT RRNL) (PRESENT L2) (PRESENT NAD1)
               (PRESENT I) (PRESENT Q) (PRESENT M) (PRESENT NAD2)
               (PRESENT W) (PRESENT A) (PRESENT N) (PRESENT C)
               (PRESENT Y) (CW Y COX1) (CW C Y) (CW N C) (CW A N)
               (CW W A) (CW NAD2 W) (CW M NAD2) (CW Q M) (CW I Q)
               (CW NAD1 I) (CW L2 NAD1) (CW RRNL L2) (CW V RRNL)
               (CW RRNS V) (CW F RRNS) (CW P F) (CW T P) (CW COB T)
               (CW E COB) (CW NAD6 E) (CW NAD5 NAD6) (CW L1 NAD5)
               (CW S1 L1) (CW H S1) (CW NAD4 H) (CW NAD4L NAD4)
               (CW R NAD4L) (CW NAD3 R) (CW G NAD3) (CW COX3 G)
               (CW ATP6 COX3) (CW K ATP6) (CW COX2 K) (CW D COX2)
               (CW S2 D) (CW COX1 S2) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL COX1) (NORMAL C) (NORMAL M) (NORMAL D)
                    (NORMAL G) (NORMAL COX2) (NORMAL H) (NORMAL RRNL)
                    (NORMAL NAD3) (NORMAL NAD5) (NORMAL A) (NORMAL P)
                    (NORMAL V) (NORMAL NAD6) (NORMAL NAD4L) (NORMAL W)
                    (NORMAL E) (NORMAL RRNS) (NORMAL S2) (NORMAL N)
                    (NORMAL Y) (NORMAL NAD1) (NORMAL ATP6) (NORMAL K)
                    (NORMAL L2) (NORMAL S1) (NORMAL NAD2) (NORMAL I)
                    (NORMAL R) (NORMAL Q) (NORMAL F) (NORMAL COB)
                    (NORMAL L1) (NORMAL COX3) (NORMAL T) (NORMAL NAD4)
                    (CW NAD4 COX1) (CW T NAD4) (CW COX3 T) (CW L1 COX3)
                    (CW COB L1) (CW F COB) (CW Q F) (CW R Q) (CW I R)
                    (CW NAD2 I) (CW S1 NAD2) (CW L2 S1) (CW K L2)
                    (CW ATP6 K) (CW NAD1 ATP6) (CW Y NAD1) (CW N Y)
                    (CW S2 N) (CW RRNS S2) (CW E RRNS) (CW W E)
                    (CW NAD4L W) (CW NAD6 NAD4L) (CW V NAD6) (CW P V)
                    (CW A P) (CW NAD5 A) (CW NAD3 NAD5) (CW RRNL NAD3)
                    (CW H RRNL) (CW COX2 H) (CW G COX2) (CW D G)
                    (CW M D) (CW C M) (CW COX1 C)))
        (:METRIC MINIMIZE (TOTAL-COST)))