; EMRE Ziya 14/07/2002 12212738
.ORIG x3000

; Initialisation de la pile
LD R6, ADRESS_PILE

; Test avec la valeur 13
LD R0, TEST_VAL
JSR FREC

HALT

TEST_VAL .FILL #13
ADRESS_PILE .FILL xFE00 ; Adresse de base de la pile

; --- SOUS-ROUTINE FREC ---
; Entree : R0 (n)
; Sortie : R0 (F(n))
; F(n) = n si n < 10
; F(n) = (n mod 10) + F(n/10) sinon
FREC
    ADD R6, R6, #-1
    STR R7, R6, #0 ; Push R7
    ADD R6, R6, #-1
    STR R1, R6, #0 ; Push R1

    ; Case base : n < 10 ?
    ADD R1, R0, #-10
    BRn FREC_FIN ; Si n-10 < 0, alors n < 10, on retourne n

    ; Cas Récursif 
    JSR DIV10 ; R0 = Reste (n mod 10), R1 = Quotient (n/10)

    ADD R6, R6, #-1
    STR R0, R6, #0 ; Push Reste

    ADD R0, R1, #0 ; R0 = Quotient

    JSR FREC ; Appel récursif 

    LDR R1, R6, #0
    ADD R6, R6, #1

    ADD R0, R0, R1 

FREC_FIN
    LDR R1, R6, #0 
    ADD R6, R6, #1
    LDR R7, R6, #0
    ADD R6, R6, #1
    RET

        ;; R0 contient n
        ;; Sortie : R1 = quotient = n/10

DIV10:
        AND R1, R1, #0     ; quotient = 0
DIV10_LOOP:       
        ADD R2, R0, #-10   ; 
        ;; tester R0 < 10
        BRn DIV10_END        ; si négatif -> fini (car R0 < 10)
        ADD R0, R2, #0     ; sinon R0 = R0 - 10
        ADD R1, R1, #1     ; quotient++
        BR DIV10_LOOP:
DIV10_END:        
        RET

.END