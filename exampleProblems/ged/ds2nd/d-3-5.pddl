;; original sequence 1: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -53 -52 -51 -50 -49 -39 -38 -37 28 29 30 31 32 33 34 35 40 26 27 -44 -43 -42 -41 45 46 47 48 -36 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 -55 -54 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96 5 6 7 8 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (112 111 107 -53 113 114 110 35 40 116 108 106 115 109 -97)
;; simplified sequence 2: (112 107 -116 108 -35 106 111 115 -53 109 110 -40 114 -113 -97)
;; common subsequences: (((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 91 92 93 94 95 96) . 106) ((9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56) . 107) ((-44 -43 -42 -41 45 46 47 48 -36) . 108) ((-105 -104 -103 -102 -101 -100 -99 -98) . 109) ((28 29 30 31 32 33 34) . 110) ((5 6 7 8) . 111) ((1 2 3 4) . 112) ((-52 -51 -50 -49) . 113) ((-39 -38 -37) . 114) ((-55 -54) . 115) ((26 27) . 116))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB7) (NORMAL SUB6) (NORMAL SUB2) (INVERTED G53) (NORMAL SUB8) (NORMAL SUB9) (NORMAL SUB5) (NORMAL G35) (NORMAL G40) (NORMAL SUB11) (NORMAL SUB3) (NORMAL SUB1) (NORMAL SUB10) (NORMAL SUB4) (INVERTED G97))
;; sequence 2 (names): ((NORMAL SUB7) (NORMAL SUB2) (INVERTED SUB11) (NORMAL SUB3) (INVERTED G35) (NORMAL SUB1) (NORMAL SUB6) (NORMAL SUB10) (INVERTED G53) (NORMAL SUB4) (NORMAL SUB5) (INVERTED G40) (NORMAL SUB9) (INVERTED SUB8) (INVERTED G97))

(DEFINE (PROBLEM ADENOPHORA-TO-LEGOUSIA) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB11 SUB10 SUB9 SUB8 SUB7 SUB6 SUB5 SUB4 SUB3 SUB2
            SUB1 G97 G53 G40 G35)
        (:INIT (NORMAL SUB7) (NORMAL SUB6) (NORMAL SUB2) (INVERTED G53)
               (NORMAL SUB8) (NORMAL SUB9) (NORMAL SUB5) (NORMAL G35)
               (NORMAL G40) (NORMAL SUB11) (NORMAL SUB3) (NORMAL SUB1)
               (NORMAL SUB10) (NORMAL SUB4) (INVERTED G97)
               (PRESENT SUB7) (PRESENT SUB6) (PRESENT SUB2)
               (PRESENT G53) (PRESENT SUB8) (PRESENT SUB9)
               (PRESENT SUB5) (PRESENT G35) (PRESENT G40)
               (PRESENT SUB11) (PRESENT SUB3) (PRESENT SUB1)
               (PRESENT SUB10) (PRESENT SUB4) (PRESENT G97)
               (CW G97 SUB7) (CW SUB4 G97) (CW SUB10 SUB4)
               (CW SUB1 SUB10) (CW SUB3 SUB1) (CW SUB11 SUB3)
               (CW G40 SUB11) (CW G35 G40) (CW SUB5 G35) (CW SUB9 SUB5)
               (CW SUB8 SUB9) (CW G53 SUB8) (CW SUB2 G53)
               (CW SUB6 SUB2) (CW SUB7 SUB6) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB7) (NORMAL SUB2) (INVERTED SUB11)
                    (NORMAL SUB3) (INVERTED G35) (NORMAL SUB1)
                    (NORMAL SUB6) (NORMAL SUB10) (INVERTED G53)
                    (NORMAL SUB4) (NORMAL SUB5) (INVERTED G40)
                    (NORMAL SUB9) (INVERTED SUB8) (INVERTED G97)
                    (CW G97 SUB7) (CW SUB8 G97) (CW SUB9 SUB8)
                    (CW G40 SUB9) (CW SUB5 G40) (CW SUB4 SUB5)
                    (CW G53 SUB4) (CW SUB10 G53) (CW SUB6 SUB10)
                    (CW SUB1 SUB6) (CW G35 SUB1) (CW SUB3 G35)
                    (CW SUB11 SUB3) (CW SUB2 SUB11) (CW SUB7 SUB2)))
        (:METRIC MINIMIZE (TOTAL-COST)))