;; original sequence 1: (1 27 2 17 36 20 3 29 10 11 35 12 30 21 9 19 18 28 33 7 8 16 26 14 34 13 24 15 32 25 4 22 23 6 31 5)
;; original sequence 2: (1 17 2 12 -19 -9 -21 -8 -7 33 -32 -11 -10 28 -4 -25 -24 -13 -34 -14 -26 -16 -36 -35 -29 -20 -18 3 23 15 30 27 22 6 31 5)
;; simplified sequence 1: (1 27 2 17 36 20 3 29 42 35 12 30 39 18 28 33 41 37 15 32 40 22 23 38)
;; simplified sequence 2: (1 17 2 12 -39 -41 33 -32 -42 28 -40 -37 -36 -35 -29 -20 -18 3 23 15 30 27 22 38)
;; common subsequences: (((16 26 14 34 13 24) . 37) ((6 31 5) . 38) ((21 9 19) . 39) ((25 4) . 40) ((7 8) . 41) ((10 11) . 42))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL COX1) (NORMAL N) (NORMAL COX2) (NORMAL D) (NORMAL Y) (NORMAL G) (NORMAL COX3) (NORMAL Q) (NORMAL SUB6) (NORMAL W) (NORMAL ATP6) (NORMAL R) (NORMAL SUB3) (NORMAL E) (NORMAL P) (NORMAL T) (NORMAL SUB5) (NORMAL SUB1) (NORMAL A) (NORMAL S2) (NORMAL SUB4) (NORMAL I) (NORMAL K) (NORMAL SUB2))
;; sequence 2 (names): ((NORMAL COX1) (NORMAL D) (NORMAL COX2) (NORMAL ATP6) (INVERTED SUB3) (INVERTED SUB5) (NORMAL T) (INVERTED S2) (INVERTED SUB6) (NORMAL P) (INVERTED SUB4) (INVERTED SUB1) (INVERTED Y) (INVERTED W) (INVERTED Q) (INVERTED G) (INVERTED E) (NORMAL COX3) (NORMAL K) (NORMAL A) (NORMAL R) (NORMAL N) (NORMAL I) (NORMAL SUB2))

(DEFINE (PROBLEM LUMBRICUS-TERRESTRIS-TO-KATHARINA-TUNICATA)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 Y W T S2 R Q P N K I G
            E D A ATP6 COX3 COX2 COX1)
        (:INIT (NORMAL COX1) (NORMAL N) (NORMAL COX2) (NORMAL D)
               (NORMAL Y) (NORMAL G) (NORMAL COX3) (NORMAL Q)
               (NORMAL SUB6) (NORMAL W) (NORMAL ATP6) (NORMAL R)
               (NORMAL SUB3) (NORMAL E) (NORMAL P) (NORMAL T)
               (NORMAL SUB5) (NORMAL SUB1) (NORMAL A) (NORMAL S2)
               (NORMAL SUB4) (NORMAL I) (NORMAL K) (NORMAL SUB2)
               (PRESENT COX1) (PRESENT N) (PRESENT COX2) (PRESENT D)
               (PRESENT Y) (PRESENT G) (PRESENT COX3) (PRESENT Q)
               (PRESENT SUB6) (PRESENT W) (PRESENT ATP6) (PRESENT R)
               (PRESENT SUB3) (PRESENT E) (PRESENT P) (PRESENT T)
               (PRESENT SUB5) (PRESENT SUB1) (PRESENT A) (PRESENT S2)
               (PRESENT SUB4) (PRESENT I) (PRESENT K) (PRESENT SUB2)
               (CW SUB2 COX1) (CW K SUB2) (CW I K) (CW SUB4 I)
               (CW S2 SUB4) (CW A S2) (CW SUB1 A) (CW SUB5 SUB1)
               (CW T SUB5) (CW P T) (CW E P) (CW SUB3 E) (CW R SUB3)
               (CW ATP6 R) (CW W ATP6) (CW SUB6 W) (CW Q SUB6)
               (CW COX3 Q) (CW G COX3) (CW Y G) (CW D Y) (CW COX2 D)
               (CW N COX2) (CW COX1 N) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL COX1) (NORMAL D) (NORMAL COX2)
                    (NORMAL ATP6) (INVERTED SUB3) (INVERTED SUB5)
                    (NORMAL T) (INVERTED S2) (INVERTED SUB6) (NORMAL P)
                    (INVERTED SUB4) (INVERTED SUB1) (INVERTED Y)
                    (INVERTED W) (INVERTED Q) (INVERTED G) (INVERTED E)
                    (NORMAL COX3) (NORMAL K) (NORMAL A) (NORMAL R)
                    (NORMAL N) (NORMAL I) (NORMAL SUB2) (CW SUB2 COX1)
                    (CW I SUB2) (CW N I) (CW R N) (CW A R) (CW K A)
                    (CW COX3 K) (CW E COX3) (CW G E) (CW Q G) (CW W Q)
                    (CW Y W) (CW SUB1 Y) (CW SUB4 SUB1) (CW P SUB4)
                    (CW SUB6 P) (CW S2 SUB6) (CW T S2) (CW SUB5 T)
                    (CW SUB3 SUB5) (CW ATP6 SUB3) (CW COX2 ATP6)
                    (CW D COX2) (CW COX1 D)))
        (:METRIC MINIMIZE (TOTAL-COST)))