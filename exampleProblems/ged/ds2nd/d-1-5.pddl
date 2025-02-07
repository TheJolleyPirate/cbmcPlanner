;; original sequence 1: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -53 -52 -51 -50 -49 37 38 39 40 -35 -34 -33 -32 -31 -30 -29 -28 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 -55 -54 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 5 6 7 8 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (113 112 107 -53 110 -35 111 108 106 114 109 -97)
;; simplified sequence 2: (113 107 108 -35 106 112 114 -53 109 -111 -110 -97)
;; common subsequences: (((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96) . 106) ((9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56) . 107) ((-27 -26 -44 -43 -42 -41 45 46 47 48 -36) . 108) ((-105 -104 -103 -102 -101 -100 -99 -98) . 109) ((-52 -51 -50 -49 37 38 39 40) . 110) ((-34 -33 -32 -31 -30 -29 -28) . 111) ((5 6 7 8) . 112) ((1 2 3 4) . 113) ((-55 -54) . 114))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB8) (NORMAL SUB7) (NORMAL SUB2) (INVERTED G53) (NORMAL SUB5) (INVERTED G35) (NORMAL SUB6) (NORMAL SUB3) (NORMAL SUB1) (NORMAL SUB9) (NORMAL SUB4) (INVERTED G97))
;; sequence 2 (names): ((NORMAL SUB8) (NORMAL SUB2) (NORMAL SUB3) (INVERTED G35) (NORMAL SUB1) (NORMAL SUB7) (NORMAL SUB9) (INVERTED G53) (NORMAL SUB4) (INVERTED SUB6) (INVERTED SUB5) (INVERTED G97))

(DEFINE (PROBLEM TRACHELIUM-TO-LEGOUSIA) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB9 SUB8 SUB7 SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 G97 G53
            G35)
        (:INIT (NORMAL SUB8) (NORMAL SUB7) (NORMAL SUB2) (INVERTED G53)
               (NORMAL SUB5) (INVERTED G35) (NORMAL SUB6) (NORMAL SUB3)
               (NORMAL SUB1) (NORMAL SUB9) (NORMAL SUB4) (INVERTED G97)
               (PRESENT SUB8) (PRESENT SUB7) (PRESENT SUB2)
               (PRESENT G53) (PRESENT SUB5) (PRESENT G35)
               (PRESENT SUB6) (PRESENT SUB3) (PRESENT SUB1)
               (PRESENT SUB9) (PRESENT SUB4) (PRESENT G97)
               (CW G97 SUB8) (CW SUB4 G97) (CW SUB9 SUB4)
               (CW SUB1 SUB9) (CW SUB3 SUB1) (CW SUB6 SUB3)
               (CW G35 SUB6) (CW SUB5 G35) (CW G53 SUB5) (CW SUB2 G53)
               (CW SUB7 SUB2) (CW SUB8 SUB7) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB8) (NORMAL SUB2) (NORMAL SUB3)
                    (INVERTED G35) (NORMAL SUB1) (NORMAL SUB7)
                    (NORMAL SUB9) (INVERTED G53) (NORMAL SUB4)
                    (INVERTED SUB6) (INVERTED SUB5) (INVERTED G97)
                    (CW G97 SUB8) (CW SUB5 G97) (CW SUB6 SUB5)
                    (CW SUB4 SUB6) (CW G53 SUB4) (CW SUB9 G53)
                    (CW SUB7 SUB9) (CW SUB1 SUB7) (CW G35 SUB1)
                    (CW SUB3 G35) (CW SUB2 SUB3) (CW SUB8 SUB2)))
        (:METRIC MINIMIZE (TOTAL-COST)))