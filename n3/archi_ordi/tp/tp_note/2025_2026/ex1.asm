; EMRE Ziya 14/07/2002 12212738
.ORIG x3000

; Si le caractère est entre 'A' et 'M' (donc le caractère <= 77), on ajoute 13
; Si le caractère est entre 'N' et 'Z' (donc le caractère > 77), on retire 13

; Preparation du parcours
LEA R1, MESSAGE ; R1 qui pointe sur le début de la chaîne

LOOP
	LDR R0, R1, #0 ; Charger le caractère courant dans R0
	BRz FIN_LOOP ; Si R0 == 0 (fin de chaine) alors on sort

	; Appel de la sous-routine ROT13
	JSR ROOT13 ; R0 est modifié par ROT13

	; Modification en mémoire
	STR R0, R1, #0 ; On écrase le caractère original par le chiffre

	ADD R1, R1, #1 ; On fait avancer le pointeur
	BR LOOP

FIN_LOOP
	LEA R0, MESSAGE
	PUTS
	HALT

; --- DONNEES ---
MESSAGE .STRINGZ "TEST"
NEWLINE .FILL x000A
NEG_M .FILL #-77 ; -'M' puisque 77 est le code ASCII de M

; --- SOUS-ROUTINE ROT13 ---
; Entrée : R0 (caractère majuscule)
; Sortie : R0 (Chiffre)
; Si le caractère <= 'M', on rajoute 13 au caractère sinon on retire 13 au caractère
ROT13
	ST R1, SAVE_R1 ; On sauvegarde R1 afin de l'utiliser pour le calcul

	LD R1, NEG_M ; R1 = -77
	ADD R1, R0, R1 ; R1 = caractère - 'M'

	BRp SUP_M ; Si positif, caractère > 'M' donc on soustrait 13

	; Cas caractère <= 'M' (on ajoute 13)
	ADD R0, R0, #13
	BR FIN_ROT13

SUP_M
	; caractère > 'M' donc on soustrait 13
	ADD R0, R0, #-13

FIN_ROT13
	LD R1, SAVE_R1 ; On restaure R1
	RET

SAVE_R1 .BLKW #1

.END