# Knapsack_Branch-and-bound
Lab Session - Implementation of a branch-and-bound algorithm on the Knapsack problem - Combinatorial Optimization

<h2>Ajouter dans le rapport :</h2>
  
    Dans un soucis de lisibilité du programme, le fichier .c initial a été séparé en différents fichiers .c (avec headers associés).
    Les structures et fonctions déjà présentes dans le fichier original n'ont pas été modifiées, seulement ordonnées. Les structures sont dans des .h et les fonctions dans des .c . Nous avons ajouté la signature des fonctions dans les fichiers .h, avec les structures correspondantes auquelles elles s'appliquent.
    Ainsi, les fichiers item.c, queue.c et tree.c contiennent toutes les structures et/ou fonctions associées aux items, aux queues ou aux trees.
    Le fichier knapsack.c contient les fonctions utiles à la résolution du probleme. Deux fonctions utiles à la lecture de fichier dans loadInstance ont été ajoutées dans knapsack.
    Les fichiers others.h et others.c contiennent une fonction printdebug, affichant avec le même format qu'un printf (attribut de compilation pour gcc ajouté dans le .h afin de contrôler le respect de ce format) seulement si une variable préprocesseur DEBUG a pour valeur 1. Sinon la fonction printdebug n'a aucun effet. La variable DEBUG est définie lors de la compilation, l'option 'debug_full' du Makefile permet ainsi d'afficher un suivi du programme lors de son exécution, mais ralentit fortement celle-ci.

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
	
Instructions de compilation :
- Utiliser la commande make dans un terminal compile le programme.
- L'option du Makefile 'debug_full' permet d'avoir les traces complètes lors de l'exécution.
- 'make clean' permet de nettoyer fichier générés

Instructions d'exécution :
- Programme C :
	- Lancer les scripts DAVID_Florian.sh et GARNIER_Antoine.sh depuis permet de lancer l'exécution du programme avec le fichier .txt correspondant à l'étudiant.
	- Pour utiliser d'autres fichiers, on peut soit copier un des scripts et modifier la ligne où le 'STUDENT_NAME' est définie,  avec le nom d'un fichier qui aura été placé dans le dossier 'resources' au prélable (sans l'extension, qui doit être '.txt'), ou appeler directement le programme en ligne de commande avec le nom du fichier en paramètre.
- GLPSOL :
	- Lancer les scripts glpsol_knapsack_DAVID.sh et glpsol_knapsack_GARNIER.sh depuis permet de lancer l'exécution du solver glpsol sur avec le fichier .txt correspondant à l'étudiant. Ces scripts lancent le solver avec un fichier .ilp, contenant les parmètres et contraintes du problème, et un fichier .ilp avec les données sur lesquelles travailler.
	- Ces scripts vérifient qu'il existe de fichier ilp contenant les données (fichier contenant la partie 'data;' du problème) pour l'élève. Si ce fichier n'existe pas (il doit avoir un nom de la forme "[STUDENT_Name].data.ilp"), un script Perl prenant en paramètres le nom fichier texte et un nom de fichier de sortie est exécuté et génère le fichier de données à utiliser.
	- Pour utiliser d'autres fichiers texte, on peut ici aussi modifier le 'STUDENT_NAME' dans le script, avec le nom d'un fichier qui aura été placé dans le dossier 'resources'.
	- Les fichiers générés pas l'exécution de ces scripts peuvent être effacé avec l'exécution de 'make clean'.
				
Problèmes rencontrés :
	- Compréhension de l'articulation du programme , l'interdépendance des fonctions entre elles.
	-> Comment implémenter l'algorithme dans programme déjà commencé par une autre personne.
	- Gestion du cas où l'item est fractionné : cast necessaire
	- Compréhension du la structure d'un fichier Mathprog
	- Conversion d'un fichier texte en fichier de données Mathprog
	
