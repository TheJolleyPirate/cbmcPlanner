;; original sequence 1: (1 2 3 4 5 6 7 8 -36 -35 -34 -33 -32 -31 -30 -29 -28 -27 -26 -25 -24 -23 -22 -21 -20 -19 -18 -15 -14 -13 -12 -11 -10 -9 40 56 57 58 59 60 37 38 39 -44 -43 -42 -41 45 46 47 48 49 50 51 52 53 16 17 54 55 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 -96 -95 -94 -93 -92 -91 -90 -89 -88 -87 -86 -85 -84 -83 -82 -81 -80 -79 -78 -77 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 90 91 92 93 94 95 96 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (110 120 114 119 109 113 40 116 118 108 117 53 122 121 106 112 115 111 107 -97)
;; simplified sequence 2: (110 -113 -106 -116 119 108 120 109 -122 115 -111 -112 -121 -53 107 -114 -40 -118 117 -97)
;; common subsequences: (((61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76) . 106) ((-105 -104 -103 -102 -101 -100 -99 -98) . 107) ((-44 -43 -42 -41 45 46 47 48) . 108) ((-25 -24 -23 -22 -21 -20 -19 -18) . 109) ((1 2 3 4 5 6 7 8) . 110) ((-83 -82 -81 -80 -79 -78 -77) . 111) ((-96 -95 -94 -93 -92 -91 -90) . 112) ((-15 -14 -13 -12 -11 -10 -9) . 113) ((-34 -33 -32 -31 -30 -29 -28) . 114) ((-89 -88 -87 -86 -85 -84) . 115) ((56 57 58 59 60) . 116) ((49 50 51 52) . 117) ((37 38 39) . 118) ((-27 -26) . 119) ((-36 -35) . 120) ((54 55) . 121) ((16 17) . 122))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB5) (NORMAL SUB15) (NORMAL SUB9) (NORMAL SUB14) (NORMAL SUB4) (NORMAL SUB8) (NORMAL G40) (NORMAL SUB11) (NORMAL SUB13) (NORMAL SUB3) (NORMAL SUB12) (NORMAL G53) (NORMAL SUB17) (NORMAL SUB16) (NORMAL SUB1) (NORMAL SUB7) (NORMAL SUB10) (NORMAL SUB6) (NORMAL SUB2) (INVERTED G97))
;; sequence 2 (names): ((NORMAL SUB5) (INVERTED SUB8) (INVERTED SUB1) (INVERTED SUB11) (NORMAL SUB14) (NORMAL SUB3) (NORMAL SUB15) (NORMAL SUB4) (INVERTED SUB17) (NORMAL SUB10) (INVERTED SUB6) (INVERTED SUB7) (INVERTED SUB16) (INVERTED G53) (NORMAL SUB2) (INVERTED SUB9) (INVERTED G40) (INVERTED SUB13) (NORMAL SUB12) (INVERTED G97))

(DEFINE (PROBLEM CODONOPSIS-TO-TRIODANUS)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB17 SUB16 SUB15 SUB14 SUB13 SUB12 SUB11 SUB10 SUB9
            SUB8 SUB7 SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 G97 G53 G40)
        (:INIT (NORMAL SUB5) (NORMAL SUB15) (NORMAL SUB9)
               (NORMAL SUB14) (NORMAL SUB4) (NORMAL SUB8) (NORMAL G40)
               (NORMAL SUB11) (NORMAL SUB13) (NORMAL SUB3)
               (NORMAL SUB12) (NORMAL G53) (NORMAL SUB17)
               (NORMAL SUB16) (NORMAL SUB1) (NORMAL SUB7)
               (NORMAL SUB10) (NORMAL SUB6) (NORMAL SUB2)
               (INVERTED G97) (PRESENT SUB5) (PRESENT SUB15)
               (PRESENT SUB9) (PRESENT SUB14) (PRESENT SUB4)
               (PRESENT SUB8) (PRESENT G40) (PRESENT SUB11)
               (PRESENT SUB13) (PRESENT SUB3) (PRESENT SUB12)
               (PRESENT G53) (PRESENT SUB17) (PRESENT SUB16)
               (PRESENT SUB1) (PRESENT SUB7) (PRESENT SUB10)
               (PRESENT SUB6) (PRESENT SUB2) (PRESENT G97)
               (CW G97 SUB5) (CW SUB2 G97) (CW SUB6 SUB2)
               (CW SUB10 SUB6) (CW SUB7 SUB10) (CW SUB1 SUB7)
               (CW SUB16 SUB1) (CW SUB17 SUB16) (CW G53 SUB17)
               (CW SUB12 G53) (CW SUB3 SUB12) (CW SUB13 SUB3)
               (CW SUB11 SUB13) (CW G40 SUB11) (CW SUB8 G40)
               (CW SUB4 SUB8) (CW SUB14 SUB4) (CW SUB9 SUB14)
               (CW SUB15 SUB9) (CW SUB5 SUB15) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB5) (INVERTED SUB8) (INVERTED SUB1)
                    (INVERTED SUB11) (NORMAL SUB14) (NORMAL SUB3)
                    (NORMAL SUB15) (NORMAL SUB4) (INVERTED SUB17)
                    (NORMAL SUB10) (INVERTED SUB6) (INVERTED SUB7)
                    (INVERTED SUB16) (INVERTED G53) (NORMAL SUB2)
                    (INVERTED SUB9) (INVERTED G40) (INVERTED SUB13)
                    (NORMAL SUB12) (INVERTED G97) (CW G97 SUB5)
                    (CW SUB12 G97) (CW SUB13 SUB12) (CW G40 SUB13)
                    (CW SUB9 G40) (CW SUB2 SUB9) (CW G53 SUB2)
                    (CW SUB16 G53) (CW SUB7 SUB16) (CW SUB6 SUB7)
                    (CW SUB10 SUB6) (CW SUB17 SUB10) (CW SUB4 SUB17)
                    (CW SUB15 SUB4) (CW SUB3 SUB15) (CW SUB14 SUB3)
                    (CW SUB11 SUB14) (CW SUB1 SUB11) (CW SUB8 SUB1)
                    (CW SUB5 SUB8)))
        (:METRIC MINIMIZE (TOTAL-COST)))