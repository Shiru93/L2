Sur la page de cours se trouve une démo live pour fusionner deux loop devices
avec LVM :

    https://sysadmin2526.netlib.re/cours/asciinema/loop_lvm.html

Récupérez le fichier source de la démo, observez son contenu et essayez de
deviner son fonctionnement.

Comme vous pouvez le voir, les timestamps des évènements d'affichage sont
donnés avec une une précision d'un millionnième de seconde, ce qui permet un
rendu visuel très précis de ce qu'a tapé son auteur. La dynamique de frappe au
clavier peut être utilisée comme donnée biométrique permettant d'identifier
l'auteur de la démo. Afin de le protéger, on peut essayer de baisser la
précision, tout en gardant un rendu visuel raisonnable.


Mettez dans un fichier nommé ./sandbox/kiss_lo.cast une version modifiée du
fichier source de la démo de sorte que les timestamps des évènements
d'affichage soient tronqués avec une une précision d'un dixième de seconde.


AVERTISSEMENT : la situation donne un prétexte pour pratiquer du traitement de
texte en ligne de commande. Elle n'est absolument pas suffisante pour protéger
l'auteur du fichier d'une analyse de dynamique de frappe. En effet, les
hésitations sont encore perceptibles, les fautes de frappes ne sont pas
corrigées, etc. Il est très difficile d'anonymiser le style d'un texte rédigé
par une personne humaine.

