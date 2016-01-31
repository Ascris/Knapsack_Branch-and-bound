# Knapsack_Branch-and-bound
Lab Session - Implementation of a branch-and-bound algorithm on the Knapsack problem - Combinatorial Optimization

<h2>Ajouter dans le rapport :</h2>
- comment compiler : make pour algo seul, make debug_full pour avoir des traces, make clean pour nettoyer fichier générés
- à quoi servent les 4 scripts bash, comment les modifier pour changer d'élève
- comment marchent les scripts : lance programme avec paramètres ou appelle script Perl dans dossier resources pour créer fichier mathprog de data (toujours dans dossier resources), si fichier déjà crée, non regénéré, on peut forcer avec make clean.
  - Même indications pour changer d'élève
- comment on a fait le fichier mathprog (.ilp)
- comment on a fait le programme
  - préciser le découpage
  
    Dans un soucis de lisibilité du programme, le fichier .c initial a été séparé en différents fichiers .c (avec headers associés) pour s'y repérer plus facilement.
    Ainsi, les fichiers item.c, queue.c et tree.c contiennent toutes les structures et/ou fonctions associées aux items, aux queues ou aux trees.
    Le fichier knapsack contient les fonctions utiles à la résolution du probleme.
    
  - expliquer ce que l'on a modifié ou seulement déplacé (modifié que ce qu'il y avait à modifier sauf knapsack.c)
  - dire que l'on a ajouté 2 fonctions pour la lecture du fichier, en plus de loadInstance()
  - Expliquer l'algo
  
    En reprenant l'exemple du cours, pour solveRelaxation, nous avons procédé comme ceci :
	-> Grâce à constraint, on sait quel item est déjà dans le sac : on ajoute ces items à x (le tableau de prensence des items que l'on modifie)
	-> On calcule totalPoidsItems, qui va indiquer s'il reste de la place dans le sac ou pas. S'il n'y a plus de place, on retourne 'u' (le probleme est fractionnel)
	-> On parcourt ensuite tous les items pour savoir lequel on ajoute au sac :
		--> Si l'item i à déjà une contrainte appliquée sur lui (constraint = 0 ou 1) alors on ne fait rien
		--> Sinon, l'item doit être traité :
			-> Soit l'item rentre entierement dans le sac et il reste de la place : on ajoute l'item au sac et on l'indique avec x{i]='1'
			-> Soit l'item rentre tout pile dans le sac : on l'ajoute et on retourne 'i', la solution est entière
			-> Soit l'item ne rentre pas dans le sac et on doit fractionner :
				==> On calcule la proportion de l'item qui va dans le sac et on ajoute le profit correspondant dans objx.
				==> L'item n'est pas rentré en entier dans le sac donc x{i]='?', les items suivants ont x[i]='0'
				==> On retourne 'f', le probleme est fractionnel
				
  - Expliquer les problèmes
	Problemes pour comprendre l'articulation du programme , l'interdépendance des fonctions entre elles.
	Problemes pour gérer le cas où l'item est fractionné : cast necessaire
	