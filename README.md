# MOIRON_PADILLA

## Space Invaders — Projet C 

Ce projet consiste en le développement du jeu Space Invaders en langage C. Les principaux éléments développés étaient les personnages, le char, les envahisseurs et l'UFO. Différentes fonctions et structures ont été utilisées pour contrôler les mouvements des éléments, détecter les collisions et gérer les modifications visuelles pendant la partie.

La bibliothèque SDL a été utilisée pour la partie graphique du projet, permettant le rendu des graphismes, la modification de la structure des fenêtres et l'affichage final des différents éléments du jeu.

Le dossier include/ contient les fichiers d’en-tête utilisées dans le projet, inclus dans les fichiers source avec #include. Le dossier src/ regroupe les fichiers source qui implémentent la logique du jeu.

## Compilation

Le projet se compile avec
gcc -g -O2 -Wall -Wextra -o si src/*.c $(pkg-config --cflags --libs sdl2)
