;; original sequence 1: (1 2 3 4 5 6 7 8 -36 -35 -34 -33 -32 -31 -30 -29 -28 -27 -26 -25 -24 -23 -22 -21 -20 -19 -18 -15 -14 -13 -12 -11 -10 -9 40 56 57 58 59 60 37 38 39 -44 -43 -42 -41 45 46 47 48 49 50 51 52 53 16 17 54 55 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 -96 -95 -94 -93 -92 -91 -90 -89 -88 -87 -86 -85 -84 -83 -82 -81 -80 -79 -78 -77 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 8 2 3 4 5 29 30 31 32 33 34 35 36 -56 -55 -54 -53 -52 -51 -50 -28 -27 -26 9 -49 -48 -47 -46 -45 41 42 43 44 37 38 39 40 16 17 18 19 20 21 22 23 24 25 10 11 12 13 14 15 57 58 59 6 7 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; simplified sequence 1: (1 113 119 8 111 117 110 112 -9 40 56 116 60 115 109 114 118 120 107 106 108)
;; simplified sequence 2: (1 8 113 -111 -56 -120 -114 117 9 -109 115 40 118 -110 -112 116 119 60 107 -106 108)
;; common subsequences: (((-96 -95 -94 -93 -92 -91 -90 -89 -88 -87 -86 -85 -84 -83 -82 -81 -80 -79 -78 -77) . 106) ((61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76) . 107) ((-105 -104 -103 -102 -101 -100 -99 -98 -97) . 108) ((-44 -43 -42 -41 45 46 47 48 49) . 109) ((-25 -24 -23 -22 -21 -20 -19 -18) . 110) ((-36 -35 -34 -33 -32 -31 -30 -29) . 111) ((-15 -14 -13 -12 -11 -10) . 112) ((2 3 4 5) . 113) ((50 51 52 53) . 114) ((37 38 39) . 115) ((57 58 59) . 116) ((-28 -27 -26) . 117) ((16 17) . 118) ((6 7) . 119) ((54 55) . 120))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL G1) (NORMAL SUB8) (NORMAL SUB14) (NORMAL G8) (NORMAL SUB6) (NORMAL SUB12) (NORMAL SUB5) (NORMAL SUB7) (INVERTED G9) (NORMAL G40) (NORMAL G56) (NORMAL SUB11) (NORMAL G60) (NORMAL SUB10) (NORMAL SUB4) (NORMAL SUB9) (NORMAL SUB13) (NORMAL SUB15) (NORMAL SUB2) (NORMAL SUB1) (NORMAL SUB3))
;; sequence 2 (names): ((NORMAL G1) (NORMAL G8) (NORMAL SUB8) (INVERTED SUB6) (INVERTED G56) (INVERTED SUB15) (INVERTED SUB9) (NORMAL SUB12) (NORMAL G9) (INVERTED SUB4) (NORMAL SUB10) (NORMAL G40) (NORMAL SUB13) (INVERTED SUB5) (INVERTED SUB7) (NORMAL SUB11) (NORMAL SUB14) (NORMAL G60) (NORMAL SUB2) (INVERTED SUB1) (NORMAL SUB3))

(DEFINE (PROBLEM CODONOPSIS-TO-PLATYCODON)
        (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB15 SUB14 SUB13 SUB12 SUB11 SUB10 SUB9 SUB8 SUB7
            SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 G60 G56 G40 G9 G8 G1)
        (:INIT (NORMAL G1) (NORMAL SUB8) (NORMAL SUB14) (NORMAL G8)
               (NORMAL SUB6) (NORMAL SUB12) (NORMAL SUB5) (NORMAL SUB7)
               (INVERTED G9) (NORMAL G40) (NORMAL G56) (NORMAL SUB11)
               (NORMAL G60) (NORMAL SUB10) (NORMAL SUB4) (NORMAL SUB9)
               (NORMAL SUB13) (NORMAL SUB15) (NORMAL SUB2)
               (NORMAL SUB1) (NORMAL SUB3) (PRESENT G1) (PRESENT SUB8)
               (PRESENT SUB14) (PRESENT G8) (PRESENT SUB6)
               (PRESENT SUB12) (PRESENT SUB5) (PRESENT SUB7)
               (PRESENT G9) (PRESENT G40) (PRESENT G56) (PRESENT SUB11)
               (PRESENT G60) (PRESENT SUB10) (PRESENT SUB4)
               (PRESENT SUB9) (PRESENT SUB13) (PRESENT SUB15)
               (PRESENT SUB2) (PRESENT SUB1) (PRESENT SUB3)
               (CW SUB3 G1) (CW SUB1 SUB3) (CW SUB2 SUB1)
               (CW SUB15 SUB2) (CW SUB13 SUB15) (CW SUB9 SUB13)
               (CW SUB4 SUB9) (CW SUB10 SUB4) (CW G60 SUB10)
               (CW SUB11 G60) (CW G56 SUB11) (CW G40 G56) (CW G9 G40)
               (CW SUB7 G9) (CW SUB5 SUB7) (CW SUB12 SUB5)
               (CW SUB6 SUB12) (CW G8 SUB6) (CW SUB14 G8)
               (CW SUB8 SUB14) (CW G1 SUB8) (IDLE) (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL G1) (NORMAL G8) (NORMAL SUB8)
                    (INVERTED SUB6) (INVERTED G56) (INVERTED SUB15)
                    (INVERTED SUB9) (NORMAL SUB12) (NORMAL G9)
                    (INVERTED SUB4) (NORMAL SUB10) (NORMAL G40)
                    (NORMAL SUB13) (INVERTED SUB5) (INVERTED SUB7)
                    (NORMAL SUB11) (NORMAL SUB14) (NORMAL G60)
                    (NORMAL SUB2) (INVERTED SUB1) (NORMAL SUB3)
                    (CW SUB3 G1) (CW SUB1 SUB3) (CW SUB2 SUB1)
                    (CW G60 SUB2) (CW SUB14 G60) (CW SUB11 SUB14)
                    (CW SUB7 SUB11) (CW SUB5 SUB7) (CW SUB13 SUB5)
                    (CW G40 SUB13) (CW SUB10 G40) (CW SUB4 SUB10)
                    (CW G9 SUB4) (CW SUB12 G9) (CW SUB9 SUB12)
                    (CW SUB15 SUB9) (CW G56 SUB15) (CW SUB6 G56)
                    (CW SUB8 SUB6) (CW G8 SUB8) (CW G1 G8)))
        (:METRIC MINIMIZE (TOTAL-COST)))