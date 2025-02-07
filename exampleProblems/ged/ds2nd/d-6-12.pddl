;; original sequence 1: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61 -56 -55 -54 -53 -60 -59 -58 -57 -27 -26 -44 -43 -42 -41 45 46 47 48 -36 -35 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -89 -88 -87 -86 -85 -84 77 78 79 80 81 82 83 90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98 28 29 30 31 32 33 34 -40 -39 -38 -37 49 50 51 52 -97)
;; original sequence 2: (1 8 2 3 4 5 29 30 31 32 33 34 35 36 -56 -55 -54 -53 -52 -51 -50 -28 -27 -26 9 -49 -48 -47 -46 -45 41 42 43 44 37 38 39 40 16 17 18 19 20 21 22 23 24 25 10 11 12 13 14 15 57 58 59 6 7 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; simplified sequence 1: (1 115 120 8 9 112 106 114 -60 118 119 109 121 108 113 110 107 28 111 116 49 117 -97)
;; simplified sequence 2: (1 8 115 111 -121 114 -117 -28 119 9 -49 -109 -116 -108 112 -118 120 60 -106 110 -113 107 -97)
;; common subsequences: (((-76 -75 -74 -73 -72 -71 -70 -69 -68 -67 -66 -65 -64 -63 -62 -61) . 106) ((90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98) . 107) ((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16) . 108) ((-44 -43 -42 -41 45 46 47 48) . 109) ((77 78 79 80 81 82 83) . 110) ((29 30 31 32 33 34) . 111) ((10 11 12 13 14 15) . 112) ((-89 -88 -87 -86 -85 -84) . 113) ((-56 -55 -54 -53) . 114) ((2 3 4 5) . 115) ((-40 -39 -38 -37) . 116) ((50 51 52) . 117) ((-59 -58 -57) . 118) ((-27 -26) . 119) ((6 7) . 120) ((-36 -35) . 121))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL G1) (NORMAL SUB10) (NORMAL SUB15) (NORMAL G8) (NORMAL G9) (NORMAL SUB7) (NORMAL SUB1) (NORMAL SUB9) (INVERTED G60) (NORMAL SUB13) (NORMAL SUB14) (NORMAL SUB4) (NORMAL SUB16) (NORMAL SUB3) (NORMAL SUB8) (NORMAL SUB5) (NORMAL SUB2) (NORMAL G28) (NORMAL SUB6) (NORMAL SUB11) (NORMAL G49) (NORMAL SUB12) (INVERTED G97))
;; sequence 2 (names): ((NORMAL G1) (NORMAL G8) (NORMAL SUB10) (NORMAL SUB6) (INVERTED SUB16) (NORMAL SUB9) (INVERTED SUB12) (INVERTED G28) (NORMAL SUB14) (NORMAL G9) (INVERTED G49) (INVERTED SUB4) (INVERTED SUB11) (INVERTED SUB3) (NORMAL SUB7) (INVERTED SUB13) (NORMAL SUB15) (NORMAL G60) (INVERTED SUB1) (NORMAL SUB5) (INVERTED SUB8) (NORMAL SUB2) (INVERTED G97))

(DEFINE (PROBLEM ASYNEUMA-TO-PLATYCODON) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB16 SUB15 SUB14 SUB13 SUB12 SUB11 SUB10 SUB9 SUB8
            SUB7 SUB6 SUB5 SUB4 SUB3 SUB2 SUB1 G97 G60 G49 G28 G9 G8
            G1)
        (:INIT (NORMAL G1) (NORMAL SUB10) (NORMAL SUB15) (NORMAL G8)
               (NORMAL G9) (NORMAL SUB7) (NORMAL SUB1) (NORMAL SUB9)
               (INVERTED G60) (NORMAL SUB13) (NORMAL SUB14)
               (NORMAL SUB4) (NORMAL SUB16) (NORMAL SUB3) (NORMAL SUB8)
               (NORMAL SUB5) (NORMAL SUB2) (NORMAL G28) (NORMAL SUB6)
               (NORMAL SUB11) (NORMAL G49) (NORMAL SUB12)
               (INVERTED G97) (PRESENT G1) (PRESENT SUB10)
               (PRESENT SUB15) (PRESENT G8) (PRESENT G9) (PRESENT SUB7)
               (PRESENT SUB1) (PRESENT SUB9) (PRESENT G60)
               (PRESENT SUB13) (PRESENT SUB14) (PRESENT SUB4)
               (PRESENT SUB16) (PRESENT SUB3) (PRESENT SUB8)
               (PRESENT SUB5) (PRESENT SUB2) (PRESENT G28)
               (PRESENT SUB6) (PRESENT SUB11) (PRESENT G49)
               (PRESENT SUB12) (PRESENT G97) (CW G97 G1) (CW SUB12 G97)
               (CW G49 SUB12) (CW SUB11 G49) (CW SUB6 SUB11)
               (CW G28 SUB6) (CW SUB2 G28) (CW SUB5 SUB2)
               (CW SUB8 SUB5) (CW SUB3 SUB8) (CW SUB16 SUB3)
               (CW SUB4 SUB16) (CW SUB14 SUB4) (CW SUB13 SUB14)
               (CW G60 SUB13) (CW SUB9 G60) (CW SUB1 SUB9)
               (CW SUB7 SUB1) (CW G9 SUB7) (CW G8 G9) (CW SUB15 G8)
               (CW SUB10 SUB15) (CW G1 SUB10) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL G1) (NORMAL G8) (NORMAL SUB10)
                    (NORMAL SUB6) (INVERTED SUB16) (NORMAL SUB9)
                    (INVERTED SUB12) (INVERTED G28) (NORMAL SUB14)
                    (NORMAL G9) (INVERTED G49) (INVERTED SUB4)
                    (INVERTED SUB11) (INVERTED SUB3) (NORMAL SUB7)
                    (INVERTED SUB13) (NORMAL SUB15) (NORMAL G60)
                    (INVERTED SUB1) (NORMAL SUB5) (INVERTED SUB8)
                    (NORMAL SUB2) (INVERTED G97) (CW G97 G1)
                    (CW SUB2 G97) (CW SUB8 SUB2) (CW SUB5 SUB8)
                    (CW SUB1 SUB5) (CW G60 SUB1) (CW SUB15 G60)
                    (CW SUB13 SUB15) (CW SUB7 SUB13) (CW SUB3 SUB7)
                    (CW SUB11 SUB3) (CW SUB4 SUB11) (CW G49 SUB4)
                    (CW G9 G49) (CW SUB14 G9) (CW G28 SUB14)
                    (CW SUB12 G28) (CW SUB9 SUB12) (CW SUB16 SUB9)
                    (CW SUB6 SUB16) (CW SUB10 SUB6) (CW G8 SUB10)
                    (CW G1 G8)))
        (:METRIC MINIMIZE (TOTAL-COST)))