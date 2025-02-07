;; original sequence 1: (1 2 3 4 5 6 7 8 9 10 49 50 51 52 53 28 29 30 31 32 33 34 35 -40 -39 -38 -37 -60 -59 -58 -57 -56 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 54 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -90 -89 -88 -87 -86 -85 77 78 79 80 81 82 83 84 91 92 93 94 95 96 -55 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 90 91 92 93 94 95 96 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (109 117 53 113 35 116 115 106 107 54 108 -90 114 112 84 111 110 -97)
;; simplified sequence 2: (109 106 115 107 -35 108 114 -84 112 90 111 -54 -53 110 113 116 117 -97)
;; common subsequences: (((11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61) . 106) ((-27 -26 -44 -43 -42 -41 45 46 47 48 -36) . 107) ((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16) . 108) ((1 2 3 4 5 6 7 8 9 10) . 109) ((-105 -104 -103 -102 -101 -100 -99 -98) . 110) ((91 92 93 94 95 96 -55) . 111) ((77 78 79 80 81 82 83) . 112) ((28 29 30 31 32 33 34) . 113) ((-89 -88 -87 -86 -85) . 114) ((-60 -59 -58 -57 -56) . 115) ((-40 -39 -38 -37) . 116) ((49 50 51 52) . 117))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB4) (NORMAL SUB12) (NORMAL G53) (NORMAL SUB8) (NORMAL G35) (NORMAL SUB11) (NORMAL SUB10) (NORMAL SUB1) (NORMAL SUB2) (NORMAL G54) (NORMAL SUB3) (INVERTED G90) (NORMAL SUB9) (NORMAL SUB7) (NORMAL G84) (NORMAL SUB6) (NORMAL SUB5) (INVERTED G97))
;; sequence 2 (names): ((NORMAL SUB4) (NORMAL SUB1) (NORMAL SUB10) (NORMAL SUB2) (INVERTED G35) (NORMAL SUB3) (NORMAL SUB9) (INVERTED G84) (NORMAL SUB7) (NORMAL G90) (NORMAL SUB6) (INVERTED G54) (INVERTED G53) (NORMAL SUB5) (NORMAL SUB8) (NORMAL SUB11) (NORMAL SUB12) (INVERTED G97))

(DEFINE (PROBLEM MERCIERA-TO-TRIODANUS) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB12 SUB11 SUB10 SUB9 SUB8 SUB7 SUB6 SUB5 SUB4 SUB3
            SUB2 SUB1 G97 G90 G84 G54 G53 G35)
        (:INIT (NORMAL SUB4) (NORMAL SUB12) (NORMAL G53) (NORMAL SUB8)
               (NORMAL G35) (NORMAL SUB11) (NORMAL SUB10) (NORMAL SUB1)
               (NORMAL SUB2) (NORMAL G54) (NORMAL SUB3) (INVERTED G90)
               (NORMAL SUB9) (NORMAL SUB7) (NORMAL G84) (NORMAL SUB6)
               (NORMAL SUB5) (INVERTED G97) (PRESENT SUB4)
               (PRESENT SUB12) (PRESENT G53) (PRESENT SUB8)
               (PRESENT G35) (PRESENT SUB11) (PRESENT SUB10)
               (PRESENT SUB1) (PRESENT SUB2) (PRESENT G54)
               (PRESENT SUB3) (PRESENT G90) (PRESENT SUB9)
               (PRESENT SUB7) (PRESENT G84) (PRESENT SUB6)
               (PRESENT SUB5) (PRESENT G97) (CW G97 SUB4) (CW SUB5 G97)
               (CW SUB6 SUB5) (CW G84 SUB6) (CW SUB7 G84)
               (CW SUB9 SUB7) (CW G90 SUB9) (CW SUB3 G90) (CW G54 SUB3)
               (CW SUB2 G54) (CW SUB1 SUB2) (CW SUB10 SUB1)
               (CW SUB11 SUB10) (CW G35 SUB11) (CW SUB8 G35)
               (CW G53 SUB8) (CW SUB12 G53) (CW SUB4 SUB12) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB4) (NORMAL SUB1) (NORMAL SUB10)
                    (NORMAL SUB2) (INVERTED G35) (NORMAL SUB3)
                    (NORMAL SUB9) (INVERTED G84) (NORMAL SUB7)
                    (NORMAL G90) (NORMAL SUB6) (INVERTED G54)
                    (INVERTED G53) (NORMAL SUB5) (NORMAL SUB8)
                    (NORMAL SUB11) (NORMAL SUB12) (INVERTED G97)
                    (CW G97 SUB4) (CW SUB12 G97) (CW SUB11 SUB12)
                    (CW SUB8 SUB11) (CW SUB5 SUB8) (CW G53 SUB5)
                    (CW G54 G53) (CW SUB6 G54) (CW G90 SUB6)
                    (CW SUB7 G90) (CW G84 SUB7) (CW SUB9 G84)
                    (CW SUB3 SUB9) (CW G35 SUB3) (CW SUB2 G35)
                    (CW SUB10 SUB2) (CW SUB1 SUB10) (CW SUB4 SUB1)))
        (:METRIC MINIMIZE (TOTAL-COST)))