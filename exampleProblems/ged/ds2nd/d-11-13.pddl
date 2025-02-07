;; original sequence 1: (1 2 3 4 5 6 7 8 28 -36 -35 -34 -33 -32 -31 -30 -29 -27 -26 40 56 57 58 59 60 37 38 39 -25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -15 -14 -13 -12 -11 -10 -9 -44 -43 -42 -41 45 46 47 48 -55 -54 -53 -52 -51 -50 -49 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 -105 -104 -103 -102 -101 -100 -99 -98 -97)
;; original sequence 2: (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105)
;; simplified sequence 1: (109 28 110 116 40 112 115 107 114 113 111 106 108)
;; simplified sequence 2: (109 -107 -116 28 -110 115 40 -114 113 -111 112 106 -108)
;; common subsequences: (((61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96) . 106) ((-25 -24 -23 -22 -21 -20 -19 -18 -17 -16 -15 -14 -13 -12 -11 -10 -9) . 107) ((-105 -104 -103 -102 -101 -100 -99 -98 -97) . 108) ((1 2 3 4 5 6 7 8) . 109) ((-36 -35 -34 -33 -32 -31 -30 -29) . 110) ((-55 -54 -53 -52 -51 -50 -49) . 111) ((56 57 58 59 60) . 112) ((45 46 47 48) . 113) ((-44 -43 -42 -41) . 114) ((37 38 39) . 115) ((-27 -26) . 116))
;; #safe insertions/deletions: 0
;; sequence 1 (names): ((NORMAL SUB4) (NORMAL G28) (NORMAL SUB5) (NORMAL SUB11) (NORMAL G40) (NORMAL SUB7) (NORMAL SUB10) (NORMAL SUB2) (NORMAL SUB9) (NORMAL SUB8) (NORMAL SUB6) (NORMAL SUB1) (NORMAL SUB3))
;; sequence 2 (names): ((NORMAL SUB4) (INVERTED SUB2) (INVERTED SUB11) (NORMAL G28) (INVERTED SUB5) (NORMAL SUB10) (NORMAL G40) (INVERTED SUB9) (NORMAL SUB8) (INVERTED SUB6) (NORMAL SUB7) (NORMAL SUB1) (INVERTED SUB3))

(DEFINE (PROBLEM CYANANTHUS-TO-TOBACCO) (:DOMAIN GENOME-EDIT-DISTANCE)
        (:OBJECTS SUB11 SUB10 SUB9 SUB8 SUB7 SUB6 SUB5 SUB4 SUB3 SUB2
            SUB1 G40 G28)
        (:INIT (NORMAL SUB4) (NORMAL G28) (NORMAL SUB5) (NORMAL SUB11)
               (NORMAL G40) (NORMAL SUB7) (NORMAL SUB10) (NORMAL SUB2)
               (NORMAL SUB9) (NORMAL SUB8) (NORMAL SUB6) (NORMAL SUB1)
               (NORMAL SUB3) (PRESENT SUB4) (PRESENT G28)
               (PRESENT SUB5) (PRESENT SUB11) (PRESENT G40)
               (PRESENT SUB7) (PRESENT SUB10) (PRESENT SUB2)
               (PRESENT SUB9) (PRESENT SUB8) (PRESENT SUB6)
               (PRESENT SUB1) (PRESENT SUB3) (CW SUB3 SUB4)
               (CW SUB1 SUB3) (CW SUB6 SUB1) (CW SUB8 SUB6)
               (CW SUB9 SUB8) (CW SUB2 SUB9) (CW SUB10 SUB2)
               (CW SUB7 SUB10) (CW G40 SUB7) (CW SUB11 G40)
               (CW SUB5 SUB11) (CW G28 SUB5) (CW SUB4 G28) (IDLE)
               (= (TOTAL-COST) 0))
        (:GOAL (AND (NORMAL SUB4) (INVERTED SUB2) (INVERTED SUB11)
                    (NORMAL G28) (INVERTED SUB5) (NORMAL SUB10)
                    (NORMAL G40) (INVERTED SUB9) (NORMAL SUB8)
                    (INVERTED SUB6) (NORMAL SUB7) (NORMAL SUB1)
                    (INVERTED SUB3) (CW SUB3 SUB4) (CW SUB1 SUB3)
                    (CW SUB7 SUB1) (CW SUB6 SUB7) (CW SUB8 SUB6)
                    (CW SUB9 SUB8) (CW G40 SUB9) (CW SUB10 G40)
                    (CW SUB5 SUB10) (CW G28 SUB5) (CW SUB11 G28)
                    (CW SUB2 SUB11) (CW SUB4 SUB2)))
        (:METRIC MINIMIZE (TOTAL-COST)))