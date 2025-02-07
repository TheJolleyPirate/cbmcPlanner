;; original sequence 1: (1 2 3 4 5 6 7 8 28 -36 -35 -34 -33 -32 -31 -30 -29 -27 -26 40 56 57 58 59 60 37 38 39 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -15 -14 -13 -12 -11 -10 -9 -44 -43 -42 -41 45 46 47 48 -55 -54 -53 -52 -51 -50 -49 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -60 -59 -58 -57 -56 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 90 91 92 93 94 95 96 -55 -54 -53 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; simplified sequence 1: (110 28 121 115 120 40 116 119 107 113 109 118 117 106 112 114 111 108 -97)
;; simplified sequence 2: (110 -113 -106 -116 120 109 121 107 -114 112 111 118 108 28 -115 -40 -119 -117 -97)
;; common subsequences: (((61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76) . 106) ((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16) . 107) ((-105 -104 -103 -102 -101 -100 -99 -98) . 108) ((-44 -43 -42 -41 45 46 47 48) . 109) ((1 2 3 4 5 6 7 8) . 110) ((90 91 92 93 94 95 96) . 111) ((77 78 79 80 81 82 83) . 112) ((-15 -14 -13 -12 -11 -10 -9) . 113) ((84 85 86 87 88 89) . 114) ((-34 -33 -32 -31 -30 -29) . 115) ((56 57 58 59 60) . 116) ((-52 -51 -50 -49) . 117) ((-55 -54 -53) . 118) ((37 38 39) . 119) ((-27 -26) . 120) ((-36 -35) . 121))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB5) (NORMAL G28) (NORMAL SUB16) (NORMAL SUB10) (NORMAL SUB15) (NORMAL G40) (NORMAL SUB11) (NORMAL SUB14) (NORMAL SUB2) (NORMAL SUB8) (NORMAL SUB4) (NORMAL SUB13) (NORMAL SUB12) (NORMAL SUB1) (NORMAL SUB7) (NORMAL SUB9) (NORMAL SUB6) (NORMAL SUB3) (INVERTED G97))
;; sequence 2 (names): ((NORMAL SUB5) (INVERTED SUB8) (INVERTED SUB1) (INVERTED SUB11) (NORMAL SUB15) (NORMAL SUB4) (NORMAL SUB16) (NORMAL SUB2) (INVERTED SUB9) (NORMAL SUB7) (NORMAL SUB6) (NORMAL SUB13) (NORMAL SUB3) (NORMAL G28) (INVERTED SUB10) (INVERTED G40) (INVERTED SUB14) (INVERTED SUB12) (INVERTED G97))

(DEFINE (PROBLEM CYANANTHUS-TO-TRIODANUS)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB16 SUB15 SUB14 SUB13 SUB12 SUB11 SUB10 SUB9 SUB8
            SUB7 SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 G97 G40 G28)
        (:INIT (NORMAL SUB5) (NORMAL G28) (NORMAL SUB16) (NORMAL SUB10)
               (NORMAL SUB15) (NORMAL G40) (NORMAL SUB11)
               (NORMAL SUB14) (NORMAL SUB2) (NORMAL SUB8) (NORMAL SUB4)
               (NORMAL SUB13) (NORMAL SUB12) (NORMAL SUB1)
               (NORMAL SUB7) (NORMAL SUB9) (NORMAL SUB6) (NORMAL SUB3)
               (INVERTED G97) (PRESENT SUB5) (PRESENT G28)
               (PRESENT SUB16) (PRESENT SUB10) (PRESENT SUB15)
               (PRESENT G40) (PRESENT SUB11) (PRESENT SUB14)
               (PRESENT SUB2) (PRESENT SUB8) (PRESENT SUB4)
               (PRESENT SUB13) (PRESENT SUB12) (PRESENT SUB1)
               (PRESENT SUB7) (PRESENT SUB9) (PRESENT SUB6)
               (PRESENT SUB3) (PRESENT G97) (CW G97 SUB5) (CW SUB3 G97)
               (CW SUB6 SUB3) (CW SUB9 SUB6) (CW SUB7 SUB9)
               (CW SUB1 SUB7) (CW SUB12 SUB1) (CW SUB13 SUB12)
               (CW SUB4 SUB13) (CW SUB8 SUB4) (CW SUB2 SUB8)
               (CW SUB14 SUB2) (CW SUB11 SUB14) (CW G40 SUB11)
               (CW SUB15 G40) (CW SUB10 SUB15) (CW SUB16 SUB10)
               (CW G28 SUB16) (CW SUB5 G28) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB5) (INVERTED SUB8) (INVERTED SUB1)
                    (INVERTED SUB11) (NORMAL SUB15) (NORMAL SUB4)
                    (NORMAL SUB16) (NORMAL SUB2) (INVERTED SUB9)
                    (NORMAL SUB7) (NORMAL SUB6) (NORMAL SUB13)
                    (NORMAL SUB3) (NORMAL G28) (INVERTED SUB10)
                    (INVERTED G40) (INVERTED SUB14) (INVERTED SUB12)
                    (INVERTED G97) (CW G97 SUB5) (CW SUB12 G97)
                    (CW SUB14 SUB12) (CW G40 SUB14) (CW SUB10 G40)
                    (CW G28 SUB10) (CW SUB3 G28) (CW SUB13 SUB3)
                    (CW SUB6 SUB13) (CW SUB7 SUB6) (CW SUB9 SUB7)
                    (CW SUB2 SUB9) (CW SUB16 SUB2) (CW SUB4 SUB16)
                    (CW SUB15 SUB4) (CW SUB11 SUB15) (CW SUB1 SUB11)
                    (CW SUB8 SUB1) (CW SUB5 SUB8)))
        (:METRIC MINIMIZE (TOTAL-COST)))