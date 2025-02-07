;; original sequence 1: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -56 -55 -54 -53 -60 -59 -58 -57 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; original sequence 2: (1 2 3 4 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 5 6 7 8 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (113 112 107 -56 114 111 108 109 90 110 106)
;; simplified sequence 2: (113 107 111 -56 108 -90 109 110 112 114 106)
;; common subsequences: (((-105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97) . 106) ((9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61) . 107) ((-27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16) . 108) ((-89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83) . 109) ((91 92 93 94 95 96) . 110) ((-60 -59 -58 -57) . 111) ((5 6 7 8) . 112) ((1 2 3 4) . 113) ((-55 -54 -53) . 114))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB8) (NORMAL SUB7) (NORMAL SUB2) (INVERTED G56) (NORMAL SUB9) (NORMAL SUB6) (NORMAL SUB3) (NORMAL SUB4) (NORMAL G90) (NORMAL SUB5) (NORMAL SUB1))
;; sequence 2 (names): ((NORMAL SUB8) (NORMAL SUB2) (NORMAL SUB6) (INVERTED G56) (NORMAL SUB3) (INVERTED G90) (NORMAL SUB4) (NORMAL SUB5) (NORMAL SUB7) (NORMAL SUB9) (NORMAL SUB1))

(DEFINE (PROBLEM ASYNEUMA-TO-LEGOUSIA) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB9 SUB8 SUB7 SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 G90 G56)
        (:INIT (NORMAL SUB8) (NORMAL SUB7) (NORMAL SUB2) (INVERTED G56)
               (NORMAL SUB9) (NORMAL SUB6) (NORMAL SUB3) (NORMAL SUB4)
               (NORMAL G90) (NORMAL SUB5) (NORMAL SUB1) (PRESENT SUB8)
               (PRESENT SUB7) (PRESENT SUB2) (PRESENT G56)
               (PRESENT SUB9) (PRESENT SUB6) (PRESENT SUB3)
               (PRESENT SUB4) (PRESENT G90) (PRESENT SUB5)
               (PRESENT SUB1) (CW SUB1 SUB8) (CW SUB5 SUB1)
               (CW G90 SUB5) (CW SUB4 G90) (CW SUB3 SUB4)
               (CW SUB6 SUB3) (CW SUB9 SUB6) (CW G56 SUB9)
               (CW SUB2 G56) (CW SUB7 SUB2) (CW SUB8 SUB7) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB8) (NORMAL SUB2) (NORMAL SUB6)
                    (INVERTED G56) (NORMAL SUB3) (INVERTED G90)
                    (NORMAL SUB4) (NORMAL SUB5) (NORMAL SUB7)
                    (NORMAL SUB9) (NORMAL SUB1) (CW SUB1 SUB8)
                    (CW SUB9 SUB1) (CW SUB7 SUB9) (CW SUB5 SUB7)
                    (CW SUB4 SUB5) (CW G90 SUB4) (CW SUB3 G90)
                    (CW G56 SUB3) (CW SUB6 G56) (CW SUB2 SUB6)
                    (CW SUB8 SUB2)))
        (:METRIC MINIMIZE (TOTAL-COST)))