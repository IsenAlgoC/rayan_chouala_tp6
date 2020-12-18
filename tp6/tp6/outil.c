#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom :  chouala                       Prénom :   rayan                            */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		rep->tab[rep->nb_elts] = enr;
		rep->nb_elts += 1;
		trier(rep);
		modif = true;
	}
	else {
		return(ERROR);
	}
	modif = true;


#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {

		SingleLinkedListElem* current = GetElementAt(rep->liste, 0);
		int pos = 0;
		while (!inserted && current != NULL) {
			if (!est_sup(enr, current->pers)) {					//Si un contact est mal positionné par rapport au contact qui suit
				InsertElementAt(rep->liste, pos, enr);
				inserted = true;								//On autorise l'insertion
				rep->nb_elts++;
				rep->est_trie = true;							//On trie la chaine
			}
			else
			{									//Sinon
				current = current->next;		// on associe la valeur d'aprés à current.
				pos++;			// on incrémente la position

			}

		}

	}
#endif

#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */
		if (rep->nb_elts > 1) {
			for (int i = 0; i < (rep->nb_elts - indice); ++i) {
				rep->tab[indice - 1] = rep->tab[indice];
			}
		}
		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem) {

	int ret = DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
}
#endif
#endif


/**********************************************************************/
/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
/* ex Dupont, Jean                 0320304050                         */
/**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("%s,%s                %s\n", enr.nom, enr.prenom, enr.tel);

	// code à compléter ici


} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	printf("|%-20s                 |%-20s                     |%s\n", enr.nom, enr.prenom, enr.tel);
} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici
	int min = 0;
	if (strlen(enr1.nom) > strlen(enr2.nom)) {
		min = strlen(enr2.nom);
	}
	else {
		min = strlen(enr1.nom);
	}
	int i = 0;
	int n = _strcmpi(enr1.nom, enr2.nom);
	if (n == 0) {
		while (n == 0 && i < min) {
			n = _strcmpi(enr1.nom, enr2.nom);                   //je compare d'abord les noms puis si ils ont la meme valeur alors on fait la meme chose pour les prenoms
			++i;
			if (n > 0) {
				return true;
			}
		}
		if (n == 0) {
			i = 0;
			if (strlen(enr1.prenom) > strlen(enr2.prenom)) {
				min = strlen(enr2.prenom);
			}
			else {
				min = strlen(enr1.prenom);
			}
			while (n == 0 && i < min) {
				n = _strcmpi(enr1.prenom, enr2.prenom);
				++i;
				if (n > 0) {
					return true;
				}
			}
		}
	}
	if (n > 0) {
		return true;
	}
	return(false);
}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep) {

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	for (int c = 0; c < rep->nb_elts; ++c) {
		for (int i = 0; i < rep->nb_elts; ++i) {
			if ((est_sup(rep->tab[i], rep->tab[i + 1])) == true) {                       // simple tri a bulle
				Enregistrement inter;
				inter = rep->tab[i];
				rep->tab[i] = rep->tab[i + 1];
				rep->tab[i + 1] = inter;
			}
		}
	}
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;
}

/* fin trier */

 /**********************************************************************/
 /* recherche dans le répertoire d'un enregistrement correspondant au  */
 /*   nom à partir de l'indice ind                                     */
 /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
 /*   un entier négatif si la recherche est négative				    */
 /**********************************************************************/

int rechercher_nom(Repertoire* rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;


#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	ind_fin = rep->nb_elts - 1;
	strcpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);
	for (int j = 0; j < strlen(tmp_nom); ++j) {
		tmp_nom[j] = toupper(tmp_nom[j]);
	}

	int n;
	while ((i <= ind_fin) && (trouve != true)) {

		strcpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);

		for (int j = ind; j < strlen(tmp_nom2); ++j) {
			tmp_nom2[j] = toupper(tmp_nom2[j]);
		}

		n = strcmp(tmp_nom, tmp_nom2);

		if (n == 0) {                                          // compare si le nom entré et le nom lu sont les meme
			trouve = true;
		}
		else {
			++i;
		}

	}


#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste

#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	// compléter code ici
	for (int i = 0; i < strlen(s); ++i) {
		if (48 > s[i] || s[i] > 57) {
			for (int j = 0; j < strlen(s) - i - 1; ++j) {
				s[i + j] = s[i + j + 1];
			}
			int a = 1;
			s[strlen(s) - a] = '\0';
		}
	}
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w");
	if (fic_rep == NULL) return ERROR;

	for (int i = 0; i < rep->nb_elts; i++) {

		int nbDeCar = 4 + strlen(rep->tab[i].nom) + strlen(rep->tab[i].prenom) + strlen(rep->tab[i].tel);  // 4 pour 2*";" et "\n" et "\0"
		char* buffer = (char*)malloc(nbDeCar * sizeof(char));
		if (buffer == NULL) {
			printf("Memoire insuffisante.");
			return ERROR;
		}
		strcpy_s(buffer, nbDeCar, rep->tab[i].nom);
		strcat_s(buffer, nbDeCar, ";");
		strcat_s(buffer, nbDeCar, rep->tab[i].prenom);
		strcat_s(buffer, nbDeCar, ";");
		strcat_s(buffer, nbDeCar, rep->tab[i].tel);
		strcat_s(buffer, nbDeCar, "\n");
		fputs(buffer, fic_rep);
		free(buffer);
	}
	fclose(fic_rep);
	return OK;


#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char* char_nw_line;

	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */