;; original sequence 1: (1 2 3 4 5 6 7 8 9 10 11 -60 -59 -58 -57 -56 -53 -52 -51 -50 -49 37 38 39 40 -35 -34 -33 -32 -31 -30 -29 -28 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 54 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 -55 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 5 6 7 8 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (114 113 115 112 -53 110 -35 111 107 108 54 106 -55 109 -97)
;; simplified sequence 2: (114 115 107 112 108 -35 106 113 -55 -54 -53 109 -111 -110 -97)
;; common subsequences: (((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96) . 106) ((12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61) . 107) ((-27 -26 -44 -43 -42 -41 45 46 47 48 -36) . 108) ((-105 -104 -103 -102 -101 -100 -99 -98) . 109) ((-52 -51 -50 -49 37 38 39 40) . 110) ((-34 -33 -32 -31 -30 -29 -28) . 111) ((-60 -59 -58 -57 -56) . 112) ((5 6 7 8) . 113) ((1 2 3 4) . 114) ((9 10 11) . 115))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB9) (NORMAL SUB8) (NORMAL SUB10) (NORMAL SUB7) (INVERTED G53) (NORMAL SUB5) (INVERTED G35) (NORMAL SUB6) (NORMAL SUB2) (NORMAL SUB3) (NORMAL G54) (NORMAL SUB1) (INVERTED G55) (NORMAL SUB4) (INVERTED G97))
;; sequence 2 (names): ((NORMAL SUB9) (NORMAL SUB10) (NORMAL SUB2) (NORMAL SUB7) (NORMAL SUB3) (INVERTED G35) (NORMAL SUB1) (NORMAL SUB8) (INVERTED G55) (INVERTED G54) (INVERTED G53) (NORMAL SUB4) (INVERTED SUB6) (INVERTED SUB5) (INVERTED G97))

(DEFINE (PROBLEM WAHLENBERGIA-TO-LEGOUSIA)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB10 SUB9 SUB8 SUB7 SUB6 SUB5 SUB4 SUB3 SUB2 SUB1
            G97 G55 G54 G53 G35)
        (:INIT (NORMAL SUB9) (NORMAL SUB8) (NORMAL SUB10) (NORMAL SUB7)
               (INVERTED G53) (NORMAL SUB5) (INVERTED G35)
               (NORMAL SUB6) (NORMAL SUB2) (NORMAL SUB3) (NORMAL G54)
               (NORMAL SUB1) (INVERTED G55) (NORMAL SUB4)
               (INVERTED G97) (PRESENT SUB9) (PRESENT SUB8)
               (PRESENT SUB10) (PRESENT SUB7) (PRESENT G53)
               (PRESENT SUB5) (PRESENT G35) (PRESENT SUB6)
               (PRESENT SUB2) (PRESENT SUB3) (PRESENT G54)
               (PRESENT SUB1) (PRESENT G55) (PRESENT SUB4)
               (PRESENT G97) (CW G97 SUB9) (CW SUB4 G97) (CW G55 SUB4)
               (CW SUB1 G55) (CW G54 SUB1) (CW SUB3 G54) (CW SUB2 SUB3)
               (CW SUB6 SUB2) (CW G35 SUB6) (CW SUB5 G35) (CW G53 SUB5)
               (CW SUB7 G53) (CW SUB10 SUB7) (CW SUB8 SUB10)
               (CW SUB9 SUB8) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB9) (NORMAL SUB10) (NORMAL SUB2)
                    (NORMAL SUB7) (NORMAL SUB3) (INVERTED G35)
                    (NORMAL SUB1) (NORMAL SUB8) (INVERTED G55)
                    (INVERTED G54) (INVERTED G53) (NORMAL SUB4)
                    (INVERTED SUB6) (INVERTED SUB5) (INVERTED G97)
                    (CW G97 SUB9) (CW SUB5 G97) (CW SUB6 SUB5)
                    (CW SUB4 SUB6) (CW G53 SUB4) (CW G54 G53)
                    (CW G55 G54) (CW SUB8 G55) (CW SUB1 SUB8)
                    (CW G35 SUB1) (CW SUB3 G35) (CW SUB7 SUB3)
                    (CW SUB2 SUB7) (CW SUB10 SUB2) (CW SUB9 SUB10)))
        (:METRIC MINIMIZE (TOTAL-COST)))