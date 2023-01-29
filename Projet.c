#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

    //DECLARATIONS ET FONCTIONS GESTION D'ARTICLES
    typedef struct date_peremption {
        int jour;
        int annee;
        int mois;
    } date_peremption;
    typedef struct Article {
        int reference;
        date_peremption DP;
        int quantite;
        int prix;
        int nombre_commande;
    } Article;
    //declaration Pile d'articles
    typedef Article Telm;
    typedef struct EPile *Pile;
    typedef struct EPile {
        Telm  Val;
        Pile Suiv;
    } CelluleP;

    //procedure Ajouter/Empiler article

    void Ajouter(Pile *P, Telm x) {
        Pile V;
        V = malloc(sizeof(CelluleP));
        V->Val = x;
        V->Suiv = *P;
        *P = V;
    }

    //procedure Initpile d'articles

    void Initpile(Pile *P) {
        *P = NULL;
    }
    //procedure Depiler/Supprimer article

    void Depiler(Pile *P, Telm *x) {
        Pile V;
        *x = (*P)->Val;
        V = *P;
        *P = (*P)->Suiv;
        free(V);
    }

    //Fonction Pilevide

    int Pilevide(Pile P) {
        if (P == NULL) return 1;
        else return 0;
    }


    //Affichage global
    void affichageG(Pile P) {
        int i; Pile R; Article X;
        Initpile(&R);
        i = 1;
        printf("_____________________\n");
        printf("\n Affichage global :\n");
        printf("_____________________\n");
        if (Pilevide(P) == 1) {
            printf("\n Il n y'a pas d'articles pour le moment.\n");
        } else {
            while (Pilevide(P) == 0) {
                Depiler(&P, &X);
                Ajouter(&R, X);
                printf("\nArticle N%d :\n", i);
                printf("Reference : %d\n", X.reference);
                printf("Date de peremption : %d-%d-%d\n", X.DP.annee, X.DP.mois, X.DP.jour);
                printf("Quantite : %d (T)\n", X.quantite);
                printf("Prix : %d (DA)\n", X.prix);
                i++;
            }
            while (Pilevide(R) == 0) {
                Depiler(&R, &X);
                Ajouter(&P, X);
            }
        }
    }

    //Affichage produits expires

    void AffichageEx(Pile *P) {
        Pile R; Article X;
        Initpile(&R);
        time_t t;
        t = time(NULL);
        struct tm tm = *localtime(&t);
        int Day = tm.tm_mday;
        int Month = tm.tm_mon + 1;
        int Year =  tm.tm_year + 1900;
        int test = 0;

        if (Pilevide(*P) == 0) {
            printf("_____________________\n");
            printf("\n Listes d'articles expires :\n");
            printf("_____________________\n");
            while (Pilevide(*P) == 0) {
                Depiler(P, &X);
                if (X.DP.annee < Year) {
                    test = 1;
                    printf("\n Produit R%d :\n", X.reference);
                    printf(" date de peremption : %d - %d - %d\n", X.DP.jour, X.DP.mois, X.DP.annee);
                } else if (X.DP.annee == Year && X.DP.mois < Month) {
                    test = 1;
                    printf("\n Produit R%d :\n", X.reference);
                    printf("- date de peremption : %d - %d - %d\n", X.DP.jour, X.DP.mois, X.DP.annee);
                } else if (X.DP.annee == Year && X.DP.mois == Month && X.DP.jour <= Day) {
                    test = 1;
                    printf("\n Produit R%d :\n", X.reference);
                    printf("- date de peremption : %d - %d - %d\n", X.DP.jour, X.DP.mois, X.DP.annee);
                }
                Ajouter(&R, X);
            }
            while (Pilevide(R) == 0) {
                Depiler(&R, &X);
                Ajouter(P, X);
            }
            if (test == 0) {
                printf("\nAucun article n'a expire pour le moment.\n");
            }
        } else {
            printf("\nIl n ya pas d'articles pour le moment.\n");

        }
    }
    //Affichage menu gestion articles

    void AffichageGA() {
        printf("\n\t\t\t\t GESTION DES ARTICLES\n");
        printf("\t\t_______________________________________________________\n");
        printf("\n");
        printf(" 1 - Creer un article.\n");
        printf(" 2 - Modifier un Article.\n");
        printf(" 3 - Rechercher un article.\n");
        printf(" 4 - Liste produits expires.\n");
        printf(" 5 - Affichage global.\n");
        printf(" 6 - Liste en alerte avant peremption.\n");
        printf(" 7 - Suppression article.\n");
        printf(" 8 - Exit.\n");
        printf("\n Saisir un numero : ");
    }

    //DECLARATIONS ET FONCTIONS GESTION DE COMMANDES
    typedef struct date {
        int annee;
        int mois;
        int jour;
    } date;
    typedef struct Commande_Achat_Vente {
        int numero_commande;
        int numero_facture;
        int numero_client;
        date dateAV;
        float MontantTTC;
        float MontantHT;
        int CF;
        int type;
        int reference_article;
    } Commande_Achat_Vente;
    //declaration Pile achat/vente
    typedef Commande_Achat_Vente elm;
    typedef struct PAVPile *AVPile;
    typedef struct PAVPile { elm  Val; AVPile Suiv;} CelluleCP;

    //procedure Ajouter/Empiler
    void AjouterAV(AVPile *P, elm x) {
        AVPile V;
        V = malloc(sizeof(CelluleCP));
        V->Val = x;
        V->Suiv = *P;
        *P = V;
    }

    //procedure Initpile
    void InitpileAV(AVPile *P) {
        *P = NULL;
    }
    //procedure Depiler/Supprimer
    void DepilerAV(AVPile *P, elm *x) {
        AVPile V;
        *x = (*P)->Val;
        V = *P;
        *P = (*P)->Suiv;
        free(V);
    }

    //Fonction Pilevide
    int AVPilevide(AVPile CP) {
        if (CP == NULL) return 1;
        else return 0;
    }
    //Affichage global commande
    void affichageAV(AVPile P) {
        int i; AVPile R; Commande_Achat_Vente X;
        InitpileAV(&R);
        i = 1;
        printf("_____________________\n");
        printf("\n Affichage global :\n");
        printf("_____________________\n");
        if (AVPilevide(P) == 1) { //si la pile est vide
            printf("\n Il n y'a pas de commande pour le moment.\n");
        } else {
            while (AVPilevide(P) == 0) {
                DepilerAV(&P, &X);
                AjouterAV(&R, X);
                printf("\n Item N%d :\n", i);
                printf(" Numero commande : %d\n", X.numero_commande);
                printf(" Numero facture \n", X.numero_facture);
                printf(" Date de commande : %d-%d-%d\n", X.dateAV.jour, X.dateAV.mois, X.dateAV.annee);
                printf(" MontantHT : %f \n", X.MontantHT);
                printf(" MontantTTC : %f \n", X.MontantTTC);
                printf(" client/fournisseur : %d (Client = 0, fournisseur = 1)", X.CF);
                printf(" Type : %d \n", X.type);

                i++;
            }
            while (AVPilevide(R) == 1) { //empiler pour reconstruction
                DepilerAV(&R, &X);
                AjouterAV(&P, X);
            }
        }
    }
    //affichage commande
    void affichecommande(Commande_Achat_Vente X) {
        printf("\n_____________________\n");
        printf("\n AFFICHAGE COMMANDE \n");
        printf("_____________________\n");
        printf("\n - Numero commande : %d\n", X.numero_commande);
        printf(" - Numero facture : %d\n", X.numero_facture);
        printf(" - Date de commande : %d-%d-%d\n", X.dateAV.jour, X.dateAV.mois, X.dateAV.annee);
        printf(" - MontantHT : %f \n", X.MontantHT);
        printf(" - MontantTTC : %f \n", X.MontantTTC);
        printf(" - c/f : %d (C = 0, f = 1)", X.CF);
        printf(" - Type : %d \n", X.type);
    }
    //Affichage menu gestion de commandes
    void AffichageGCC() {
        printf("\n\t\t\t\t MENU COMMANDE\n");
        printf("\t\t_______________________________________________________\n");
        printf("\n");
        printf(" 1 - Inserer une commande.\n");
        printf(" 2 - Modifier une commande.\n");
        printf(" 3 - Rechercher une commande.\n");
        printf(" 4 - Suprimer une commande.\n");
        printf(" 5 - Article le plus vendu\n");
        printf(" 6 - Nombre de commande par entite.\n");
        printf(" 7 - Pires clients.\n");
        printf(" 8 - Affichage Global.\n");
        printf(" 9 - L'Ecart.\n");
        printf(" 10 - Exit.\n");
        printf("\n Saisir un numero : ");
    }
    //DECLARATIONS ET FONCTIONS MENU CLIENT/FOURNISSEUR
    //Menu client/fournisseur
    void menuCF() {
        printf("\n\t\t\t\t MENU CLIENT/FOURNISSEUR\n");
        printf("\t\t_______________________________________________________\n");
        printf("\n");
        printf(" 1 - Creation.\n");
        printf(" 2 - Modification.\n");
        printf(" 3 - Supression.\n");
        printf(" 4 - Exit.\n");
        printf("\n Saisir un numero : ");
    }

    //structure client
    typedef struct clientfournisseur {
        char nom[10];
        char prenom[10];
        int telephone;
        int reference;
        int etat;
        int nombre_commande;
    } clientfournisseur;
    //Pile client
    typedef clientfournisseur celm;
    typedef struct CAVPile *clientfournisseurPile;
    typedef struct CAVPile { celm  Val; clientfournisseurPile Suiv;} CelluleCC;

    //procedure Ajouter/Empiler client
    void AjouterCF(clientfournisseurPile *P, celm x) {
        clientfournisseurPile V;
        V = malloc(sizeof(CelluleCC));
        V->Val = x;
        V->Suiv = *P;
        *P = V;
    }

    //procedure Initpile client
    void InitpileCF(clientfournisseurPile *P) {
        *P = NULL;
    }
    //procedure Depiler/Supprimer client
    void DepilerCF(clientfournisseurPile *P, celm *x) {
        clientfournisseurPile V;
        *x = (*P)->Val;
        V = *P;
        *P = (*P)->Suiv;
        free(V);
    }

    //Fonction Pilevide
    int PilevideCF(clientfournisseurPile P) {
        if (P == NULL) return 1;
        else return 0;
    }
    int main() {
        int numero_saisi, choix;
        int numero_gestion;
        int choixC, CGC, CCF;

        Pile PA;
        AVPile CPA;
        clientfournisseurPile CFP;

        Initpile(&PA); //pile articles
        InitpileAV(&CPA); // pile commandes(achat/vente)
        InitpileCF(&CFP); // pile fournisseur/client

        do {

            printf("\n\t\t_______________________________________________________\n");
            printf("\n\t\t\t\t GESTION DE STOCK\n");
            printf("\t\t_______________________________________________________\n\n");
            printf(" 1 - Gestion d'articles.\n");
            printf(" 2 - Gestion de commandes.\n");
            printf(" 3 - Exit.\n\n");
            printf(" A quoi voulez vous acceder ?\n");
            printf(" Votre choix : ");
            scanf("%d", &numero_gestion);
            switch (numero_gestion) {
            case 1:
                do {
                    /*------ENTÊTE------*/
                    AffichageGA();
                    scanf("%d", &numero_saisi);

                    /*------GESTION ARTICLES------*/

                    switch ( numero_saisi ) {
                    case 1:
                        printf("_____________________\n");
                        printf("\n Creation d'un article :\n");
                        printf("_____________________\n");
                        //creation de l'article
                        Article A;
                        A.nombre_commande = 0;
                        printf("\n entrez la date de peremption de l'article. \n\n");
                        printf(" Annee : ");
                        scanf("%d", &A.DP.annee);
                        if ((A.DP.annee) <= 0) { ///on accepte pas de date negative
                            printf(" Entrez une annee valide : ");
                            scanf("%d", &A.DP.annee);
                        }

                        printf(" Jour :  ");
                        scanf("%d", &A.DP.jour);
                        while ((A.DP.jour) > 31 || (A.DP.jour) < 0) {
                            printf(" Entrez un jour valide (1 - 31) : "); ///les jours sont compris entre 1 et 31
                            scanf("%d", &A.DP.jour);
                        }
                        printf(" mois :  ");
                        scanf("%d", &A.DP.mois);
                        while ((A.DP.mois) > 12 || (A.DP.mois) <= 0) { ///les mois sont compris entre 1 et 12
                            printf(" Entrez un mois valide (1 - 12) : ");
                            scanf("%d", &A.DP.mois);
                        }
                        printf(" Entrez la reference de l'article : ");
                        scanf("%d", &A.reference);

                        printf(" Entrez la quantite de l'article (T) : ");
                        scanf("%d", &A.quantite);

                        printf(" Entrez le prix de l'article (DA) : ");
                        scanf("%d", &A.prix);

                        //remplir la pile d'article
                        Ajouter(&PA, A);
                        break;

                    case 2:

                        printf("_____________________\n");
                        printf("\n Modification d'un article :\n");
                        printf("_____________________\n");
                        int ref;
                        int test = 0;
                        Article ArticleInter;
                        Pile Pinter;
                        Initpile(&Pinter);
                        if (Pilevide(PA) == 1) {
                            printf("\n Il n ya pas d'articles pour le moment.\n");
                        } else {
                            printf("\n Quel article voulez-vous modifier ?\n");
                            printf(" Inserer sa reference : ");
                            scanf("%d", &ref);
                            while (Pilevide(PA) == 0) {
                                Depiler(&PA, &ArticleInter); ///on recherche l'article
                                if ((ArticleInter.reference) == ref) {
                                    test = 1; ///flag est mis a un 1 si on retrouve l'article
                                    printf("\n Que voulez vous modifier?");
                                    printf("\n");
                                    printf(" 1 - date_peremption.\n");
                                    printf(" 2 - quantite.\n");
                                    printf(" 3 - prix.\n");
                                    printf(" 4 - exit.\n");
                                    printf(" Votre choix : ");
                                    scanf("%d", &choix);
                                    switch ( choix ) {
                                    case 1:
                                        printf("\n Inserer une nouvelle date :\n");
                                        printf(" Annee : ");
                                        scanf("%d", &ArticleInter.DP.annee);
                                        while ((ArticleInter.DP.annee) <= 0) {
                                            printf(" Entrez une annee valide : ");
                                            scanf("%d", &ArticleInter.DP.annee);
                                        }
                                        printf(" Jour :  ");
                                        scanf("%d", &ArticleInter.DP.jour);
                                        while ((ArticleInter.DP.jour) > 31 || (ArticleInter.DP.jour) <= 0) {
                                            printf(" Entrez un jour valide (1 - 31) : ");
                                            scanf("%d", &ArticleInter.DP.jour);
                                        }
                                        printf(" mois :  ");
                                        scanf("%d", &ArticleInter.DP.mois);
                                        while ((ArticleInter.DP.mois) > 12 || (ArticleInter.DP.mois) <= 0) {
                                            printf(" Entrez un mois valide (1 - 12) : ");
                                            scanf("%d", &ArticleInter.DP.mois);
                                        }
                                        break;
                                    case 2:
                                        printf("\n Inserer une nouvelle quantite : ");
                                        scanf("%d", &ArticleInter.quantite);
                                        break;
                                    case 3:
                                        printf("\n Inserer le nouveau prix : ");
                                        scanf("%d", &ArticleInter.prix);
                                        break;
                                    }
                                    Ajouter(&Pinter, ArticleInter);
                                } else {
                                    Ajouter(&Pinter, ArticleInter);
                                }
                            }
                            while (Pilevide(Pinter) == 0) {
                                Depiler(&Pinter, &ArticleInter);
                                Ajouter(&PA, ArticleInter);
                            }
                            if (test == 0) {
                                printf("\nL'article n'existe pas.\n");
                            }

                        }
                        break;

                    case 3:
                        printf("_____________________\n");
                        printf("\n Recherche d'un article :\n");
                        printf("_____________________\n");
                        if (Pilevide(PA) == 1) {
                            printf("\n Il n y a pas d'articles pour le moment.\n");
                        } else {
                            int C;
                            test = 0;
                            Initpile(&Pinter);
                            printf("\n Comment voulez vous retrouver votre article ? \n");
                            printf(" 1 - Par reference.\n");
                            printf(" 2 - Par date de peremption.\n");
                            printf(" Votre choix : ");
                            scanf("%d", &C);
                            switch (C) {
                            case 1:
                                printf("\n Entrez la reference de l'article : ");
                                scanf("%d", &ref);
                                Initpile(&Pinter);
                                while (Pilevide(PA) == 0 && test == 0) {
                                    Depiler(&PA, &ArticleInter);
                                    Ajouter(&Pinter, ArticleInter);
                                    if (ArticleInter.reference == ref) {
                                        test = 1; ///si on trouve l'article on arrête la recherche, le flag nous permet d'arreter
                                    }
                                }
                                if (test == 0) {
                                    printf("\n L'article n'existe pas.\n");
                                } else if (test == 1) {
                                    printf("\n - Reference de l'article : %d\n", ArticleInter.reference);
                                    printf(" - Date de peremption : %d-%d-%d \n", ArticleInter.DP.jour, ArticleInter.DP.mois, ArticleInter.DP.annee);
                                    printf(" - Prix de l'article : %d \n", ArticleInter.prix);
                                    printf(" - Quantite de l'article : %d \n", ArticleInter.quantite);
                                }
                                while (Pilevide(Pinter) == 0) {
                                    Depiler(&Pinter, &ArticleInter);
                                    Ajouter(&PA, ArticleInter);
                                }

                                break;
                            case 2:
                                printf("\n Entrez la date de peremption de l'article.\n");
                                int An, Mo, Jo;
                                Initpile(&Pinter);
                                printf(" Annee : ");
                                scanf("%d", &An);
                                printf(" mois : ");
                                scanf("%d", &Mo);
                                printf(" jour : ");
                                scanf("%d", &Jo);
                                test = 0;
                                while (Pilevide(PA) == 0 && test == 0) {
                                    Depiler(&PA, &ArticleInter);
                                    Ajouter(&Pinter, ArticleInter);
                                    if (ArticleInter.reference == ref) {
                                        test = 1;
                                    }
                                }
                                if (test == 0) {
                                    printf("\n L'article n'existe pas.\n");
                                } else if (test == 1) {
                                    printf("\n - Reference de l'article : %d\n", ArticleInter.reference);
                                    printf(" - Date de peremption : %d-%d-%d \n", ArticleInter.DP.jour, ArticleInter.DP.mois, ArticleInter.DP.annee);
                                    printf(" - Prix de l'article : %d \n", ArticleInter.prix);
                                    printf(" - Quantite de l'article : %d \n", ArticleInter.quantite);
                                }
                                while (Pilevide(Pinter) == 0) {
                                    Depiler(&Pinter, &ArticleInter);
                                    Ajouter(&PA, ArticleInter);
                                }


                                break;
                            }

                        }
                        break;
                    case 4:
                        AffichageEx(&PA);
                        break;
                    case 5:
                        affichageG(PA);
                        break;
                    case 6:
                        printf("_____________________\n");
                        printf("\n Listes d'article en alerte avant peremption :\n");
                        printf("_____________________\n");
                        if (Pilevide(PA) == 1) {
                            printf("\nIl n y a pas d'articles pour le moment.\n");
                        } else {
                            time_t t;
                            t = time(NULL);
                            struct tm tm = *localtime(&t);
                            int Day = tm.tm_mday;
                            int Month = tm.tm_mon + 1;
                            int Year =  tm.tm_year + 1900;
                            int test = 0;

                            Article ArticleInter;
                            Pile Pinter;
                            Initpile(&Pinter);

                            while (Pilevide(PA) == 0 && test == 0) {
                                Depiler(&PA, &ArticleInter);
                                Ajouter(&Pinter, ArticleInter);  ///en alerte de peremption = entre 1-31 jours avant peremption
                                if (ArticleInter.DP.annee == Year && ArticleInter.DP.mois == Month && ArticleInter.DP.jour > Day) {
                                    test = 1;
                                }
                            }
                            if (test == 0) {
                                printf("\n Aucun article est en alerte de peremption.\n");
                            } else if (test == 1) {
                                printf("\n - Reference de l'article en alerte de peremption: %d\n", ArticleInter.reference);
                                printf(" - Date de peremption : %d-%d-%d \n", ArticleInter.DP.jour, ArticleInter.DP.mois, ArticleInter.DP.annee);
                                printf(" - %d jours avant peremption.", ArticleInter.DP.jour - Day);
                            }
                            while (Pilevide(Pinter) == 0) {
                                Depiler(&Pinter, &ArticleInter);
                                Ajouter(&PA, ArticleInter);
                            }
                            break;
                        }
                    case 7:
                        printf("\n Entrez la reference de l'article a supprimer : ");
                        scanf("%d", &ref);
                        int test2 = 0;
                        Pile pileinter;
                        Article ArticleInter1;
                        Initpile(&pileinter);
                        if (Pilevide(PA) == 1) {
                            printf("\n Il n y a pas d'articles pour le moment.\n");
                        } else {

                            while (Pilevide(PA) == 0 && test2 == 0) {
                                Depiler(&PA, &ArticleInter1);
                                Ajouter(&pileinter, ArticleInter1);
                                if (ArticleInter1.reference == ref) {
                                    test2 = 1;
                                }
                            }
                            if (test2 == 0) {
                                printf("\n L'article n'existe pas.\n");
                            } else if (test2 == 1) {
                                Depiler(&pileinter, &ArticleInter1); ///on le depile sans empiler a nouveau
                                printf("\n L'article a ete supprime avec succes.\n");
                            }
                            while (Pilevide(pileinter) == 0) {
                                Depiler(&pileinter, &ArticleInter1);
                                Ajouter(&PA, ArticleInter1);
                            }
                        }

                        break;
                    }
                } while (numero_saisi != 8);
                break;
            case 2:
                do {
                    printf("\n\t\t_______________________________________________________\n");
                    printf("\n\t\t\t\t GESTION DE COMMANDE\n");
                    printf("\t\t_______________________________________________________\n\n");
                    printf("\n 1 - Menu commande.\n");
                    printf(" 2 - Menu client/fournisseur.\n");
                    printf(" 3 - Exit.\n");
                    printf(" Votre choix : ");
                    scanf("%d", &choixC);
                    if (choixC == 1) {
                        do {
                            AffichageGCC();
                            scanf("%d", &CCF);
                            switch (CCF) {
                            case 1:
                                printf("_____________________\n");
                                printf("\n Creation commmande :\n");
                                printf("_____________________\n");
                                //creation commande
                                Commande_Achat_Vente C;
                                int ref;
                                int test = 0, type;
                                Article Ainter;
                                Pile Pinter;
                                Initpile(&Pinter);
                                clientfournisseurPile PCFinter;
                                clientfournisseur Einter;
                                InitpileCF(&PCFinter);


                                if (Pilevide(PA) == 1 || PilevideCF(CFP) == 1) { ///si la pile d'articles/fournisseur/clients est vide on ne peux pas creer de commande
                                    printf("\n Il n ya pas d'articles/fournisseur/client pour le moment\n");
                                } else {
                                    printf("\n Entrez la reference de l'article commande : "); ///on cherche l'article dans la pile
                                    scanf("%d", &ref);
                                    while (Pilevide(PA) == 0 && test == 0) {
                                        Depiler(&PA, &Ainter);
                                        if (Ainter.reference == ref) {
                                            test = 1;  ///si on le trouve on met le flag à 1
                                        }
                                        Ajouter(&Pinter, Ainter);
                                    }
                                    if (test == 0) {
                                        printf("\n Cet article n'existe pas.\n"); ///l'article n'existe pas on ne peux pas creer de commande
                                        while (Pilevide(Pinter) == 0) {
                                            Depiler(&Pinter, &Ainter);
                                            Ajouter(&PA, Ainter);
                                        }
                                    } else { ///si il existe on cherche le client/fournisseur
                                        printf(" Entrez la reference du fournisseur/client : ");
                                        int ref2, test2 = 0;
                                        scanf("%d", &ref2);

                                        while (PilevideCF(CFP) == 0) {
                                            DepilerCF(&CFP, &Einter);
                                            AjouterCF(&PCFinter, Einter);
                                            if (Einter.reference == ref2) {
                                                test2 = 1; ///si on trouve le client/fournisseur le flag est mis à 1
                                                type = Einter.etat;
                                            }
                                        }
                                        while (PilevideCF(PCFinter) == 0) {
                                            DepilerCF(&PCFinter, &Einter);
                                            AjouterCF(&CFP, Einter);
                                        }
                                        if (test2 == 0) {
                                            printf("\n Le client/fournisseur n'existe pas.\n"); ///on ne peux pas creer de commande
                                            while (Pilevide(Pinter) == 0) {
                                                Depiler(&Pinter, &Ainter);
                                                Ajouter(&PA, Ainter);
                                            }
                                        } else { ///existance de l'article + existance du client/fournisseur = creation de commande
                                            C.CF = ref2; /// on ajoute la reference du client/fournisseur a la commande
                                            ///on incremente le nombre de commande de l'article



                                            while (Pilevide(Pinter) == 0) { // reremplir la pile
                                                Depiler(&Pinter, &Ainter);
                                                Ajouter(&PA, Ainter);
                                            }

                                            while (Pilevide(PA) == 0) {
                                                Depiler(&PA, &Ainter);
                                                if (Ainter.reference == ref) {
                                                    Ainter.nombre_commande++;
                                                    Ajouter(&PA, Ainter);
                                                    break;
                                                }
                                                Ajouter(&Pinter, Ainter);
                                            }

                                            while (Pilevide(Pinter) == 0) { // reremplir la pile
                                                Depiler(&Pinter, &Ainter);
                                                Ajouter(&PA, Ainter);
                                            }

                                            while (PilevideCF(PCFinter) == 0) {
                                                DepilerCF(&PCFinter, &Einter);
                                                AjouterCF(&CFP, Einter);
                                            }
                                            while (PilevideCF(CFP) == 0) {
                                                DepilerCF(&CFP, &Einter);
                                                if (Einter.reference == ref2) {
                                                    Einter.nombre_commande++;
                                                    AjouterCF(&CFP, Einter);
                                                    break;
                                                }
                                                AjouterCF(&PCFinter, Einter);
                                            }
                                            while (PilevideCF(PCFinter) == 0) {
                                                DepilerCF(&PCFinter, &Einter);
                                                AjouterCF(&CFP, Einter);
                                            }
                                            //////////

                                            C.reference_article = ref; ///on ajoute la reference de l'article commandé à la commande
                                            C.numero_client = Einter.reference;///on affecte la reference du client
                                            printf("\n Entrez la date de commande : \n\n");
                                            printf(" Annee : ");
                                            scanf("%d", &C.dateAV.annee);
                                            if ((C.dateAV.annee) <= 0) {
                                                printf(" Entrez une annee valide : ");
                                                scanf("%d", &C.dateAV.annee);
                                            }

                                            printf(" Jour :  ");
                                            scanf("%d", &C.dateAV.jour);
                                            while ((C.dateAV.jour) > 31 || (C.dateAV.jour) < 0) {
                                                printf(" Entrez un jour valide (1 - 31) : ");
                                                scanf("%d", &C.dateAV.jour);
                                            }
                                            printf(" mois :  ");
                                            scanf("%d", &C.dateAV.mois);
                                            while ((C.dateAV.mois) > 12 || (C.dateAV.mois) < 0) {
                                                printf(" Entrez un mois valide (1 - 12) : ");
                                                scanf("%d", &C.dateAV.mois);
                                            }
                                            printf("\n Entrez le montant HT : ");
                                            scanf("%f", &C.MontantHT);
                                            int calcul;
                                            calcul = C.MontantHT * (0.19);
                                            C.MontantTTC = calcul;
                                            printf(" Entrez le numero de commande : ");
                                            scanf("%d", &C.numero_commande);
                                            printf(" Entrez le numero de facture : ");
                                            scanf("%d", &C.numero_facture);
                                            C.type = type;
                                            AjouterAV(&CPA, C);
                                            printf("\n La commande a ete saisi avec succes.\n");
                                            while (Pilevide(Pinter) == 0) {
                                                Depiler(&Pinter, &Ainter);
                                                Ajouter(&PA, Ainter);
                                            }
                                        }
                                    }

                                }



                                break;
                            case 2:
                                printf("_____________________\n");
                                printf("\n Modification commande :\n");
                                printf("_____________________\n");
                                if (AVPilevide(CPA) == 1) {
                                    printf("\n Il n y a pas de commandes pour l'instant.\n");
                                } else {
                                    int refcmd;
                                    printf("\n Entrez la reference de la commande a modifier : ");
                                    scanf("%d", &refcmd);
                                    Commande_Achat_Vente Cinter;
                                    AVPile Pinter;
                                    InitpileAV(&Pinter);
                                    int test = 0;
                                    while (AVPilevide(CPA) == 0) {
                                        DepilerAV(&CPA, &Cinter);
                                        if (Cinter.numero_commande == refcmd) {
                                            test = 1;
                                        }
                                        AjouterAV(&Pinter, Cinter);
                                    }
                                    if (test == 1) {
                                        printf("\n Que voulez vous modifier?");
                                        printf("\n");
                                        printf(" 1 - date de commande.\n");
                                        printf(" 2 - Montant HT.\n");
                                        printf(" 3 - numero de facture.\n");
                                        printf(" Votre choix : ");
                                        int choix;
                                        scanf("%d", &choix);
                                        switch ( choix ) {
                                        case 1:
                                            printf("\n Inserer une nouvelle date :\n");
                                            printf(" Annee : ");
                                            scanf("%d", &Cinter.dateAV.annee);
                                            while ((Cinter.dateAV.annee) <= 0) {
                                                printf(" Entrez une annee valide : ");
                                                scanf("%d", &Cinter.dateAV.annee);
                                            }
                                            printf(" Jour :  ");
                                            scanf("%d", &Cinter.dateAV.jour);
                                            while ((Cinter.dateAV.jour) > 31 || (Cinter.dateAV.jour) <= 0) {
                                                printf(" Entrez un jour valide (1 - 31) : ");
                                                scanf("%d", &Cinter.dateAV.jour);
                                            }
                                            printf(" mois :  ");
                                            scanf("%d", &Cinter.dateAV.mois);
                                            while ((Cinter.dateAV.mois) > 12 || (Cinter.dateAV.mois) <= 0) {
                                                printf(" Entrez un mois valide (1 - 12) : ");
                                                scanf("%d", &Cinter.dateAV.mois);
                                            }
                                            break;
                                        case 2:
                                            printf("\n Inserer le nouveau montant HT : ");
                                            scanf("%d", &Cinter.MontantHT);
                                            Cinter.MontantTTC = Cinter.MontantHT * 0.19;
                                            break;
                                        case 3:
                                            printf("\n Inserer le nouveau numero facture : ");
                                            scanf("%d", &Cinter.numero_facture);
                                            break;
                                        }

                                    } else if (test == 0) {
                                        printf("\n Cette commande n'existe pas.\n");
                                    }
                                    DepilerAV(&Pinter, &Cinter);
                                    AjouterAV(&CPA, Cinter);
                                }

                                break;
                            case 3:
                                printf("_____________________\n");
                                printf("\n Recherche commande :\n");
                                printf("_____________________\n");
                                if (AVPilevide(CPA) == 1) {
                                    printf("\n Il n y a pas de commande pour l'instant.\n");
                                } else {
                                    AVPile interpile;
                                    InitpileAV(&interpile);
                                    Commande_Achat_Vente interelem;
                                    int rc, test2 = 0, test3 = 0;
                                    printf("\n Comment voulez-vous retrouver votre commande ?\n");
                                    printf(" 1 - reference commande\n");
                                    printf(" 2 - reference client\n");
                                    printf(" Votre choix : ");

                                    scanf("%d", &rc);
                                    switch ( rc ) {
                                    case 1:
                                        printf("\n Entrez le numero de commande : ");
                                        int refc;
                                        scanf("%d", &refc);
                                        while (AVPilevide(CPA) == 0 && test2 == 0) {
                                            DepilerAV(&CPA, &interelem);
                                            AjouterAV(&interpile, interelem);
                                            if (interelem.numero_commande == refc) {
                                                test = 1;
                                            }
                                        }

                                        if (test == 0) {
                                            printf("\n La commande n'existe pas.\n");
                                        } else if (test == 1) {
                                            affichecommande(interelem);
                                        }
                                        while (AVPilevide(interpile) == 0) {
                                            DepilerAV(&interpile, &interelem);
                                            AjouterAV(&CPA, interelem);
                                        }

                                        break;

                                    case 2:
                                        printf("\n Entrez le numero de client : ");
                                        int refcl;
                                        scanf("%d", &refcl);

                                        while ((AVPilevide(CPA) == 0) && (test3 == 0)) {
                                            DepilerAV(&CPA, &interelem);
                                            AjouterAV(&interpile, interelem);
                                            if (interelem.numero_client == refcl) {
                                                test3 = 1;
                                            }
                                        }

                                        if (test3 == 1) {
                                            affichecommande(interelem);
                                        }
                                        if (test3 == 0) {
                                            printf("\n La commande n'existe pas.\n");
                                        }
                                        while (AVPilevide(interpile) == 0) {
                                            DepilerAV(&interpile, &interelem);
                                            AjouterAV(&CPA, interelem);
                                        }

                                        break;
                                    }
                                }

                                break;
                            case 4:
                                printf("_____________________\n");
                                printf("\n Suppression commande :\n");
                                printf("_____________________\n");
                                if (AVPilevide(CPA) == 1) {
                                    printf("\n Il n y a pas de commandes pour le moment.\n");
                                } else {
                                    int refcmd;
                                    printf("\n Entrez la reference de la commande a supprimer : ");
                                    scanf("%d", &refcmd);
                                    Commande_Achat_Vente Cinter2;
                                    AVPile Pinter2;
                                    InitpileAV(&Pinter2);
                                    int test2 = 0;
                                    while (AVPilevide(CPA) == 0) {
                                        DepilerAV(&CPA, &Cinter2);
                                        if (Cinter2.numero_commande == refcmd) {
                                            test2 = 1;
                                        }
                                        AjouterAV(&Pinter2, Cinter2);
                                    }
                                    if (test2 == 1) {
                                        DepilerAV(&Pinter2, &Cinter2);
                                        printf("\n La commande a ete supprime avec succes.\n");
                                    } else if (test2 == 0) {
                                        printf("\n La commande n'existe pas.\n");
                                    }
                                    while (AVPilevide(Pinter2) == 0) {
                                        DepilerAV(&Pinter2, &Cinter2);
                                        AjouterAV(&CPA, Cinter2);
                                    }
                                }
                                break;
                            case 5:
                                printf("_____________________\n");
                                printf("\n Article le plus vendu :\n");
                                printf("_____________________\n");
                                Article articleinter;
                                Pile pileinter;
                                Initpile(&pileinter);
                                int max, refmax;
                                if (Pilevide(PA) == 1) {
                                    printf("\n Il n y a pas d'articles pour le moment.\n");
                                } else {
                                    Depiler(&PA, &articleinter);
                                    Ajouter(&pileinter, articleinter);
                                    max = articleinter.nombre_commande; ///on suppose que le max est le nombre de commande du premier article
                                    refmax = articleinter.reference;
                                    while (Pilevide(PA) == 0) {
                                        Depiler(&PA, &articleinter);
                                        if (articleinter.nombre_commande > max) { ///si le nombre de commande depasse le max, on le remplace
                                            max = articleinter.nombre_commande;
                                            refmax = articleinter.reference;
                                        }
                                        Ajouter(&pileinter, articleinter);
                                    }
                                    while (Pilevide(pileinter) == 0) {
                                        Depiler(&pileinter, &articleinter);
                                        Ajouter(&PA, articleinter);
                                    }
                                    printf("\n L'article de reference %d est le plus vendu.", refmax);
                                    printf(" Il a ete vendu %d fois.\n", max);
                                }
                                break;
                            case 6:
                                printf("_____________________\n");
                                printf("\n Nombre de commande par entite :\n");
                                printf("_____________________\n");
                                if(PilevideCF(CFP) == 1){
                                    printf("\n Il n y a pas de commandes pour l'instant.\n");
                                }
                                else{
                                while (PilevideCF(PCFinter) == 0) {
                                    DepilerCF(&PCFinter, &Einter);
                                    AjouterCF(&CFP, Einter);
                                }
                                while (PilevideCF(CFP) == 0) {
                                    DepilerCF(&CFP, &Einter);
                                    printf("\nClient %s %s nombre de commandes : %d", Einter.nom, Einter.prenom, Einter.nombre_commande);
                                    AjouterCF(&PCFinter, Einter);
                                }
                                while (PilevideCF(PCFinter) == 0) {
                                    DepilerCF(&PCFinter, &Einter);
                                    AjouterCF(&CFP, Einter);
                                }
                                }
                                break;
                            case 7:
                                printf("_____________________\n");
                                printf("\n Pires clients :\n");
                                printf("_____________________\n");
                                if(PilevideCF(CFP) == 1){
                                    printf("\n Il n y a pas de commandes pour l'instant.\n");
                                }
                                else{
                                        test = 0; ///le flag est à 0, si on trouve pas de clients sans commande donc le pire client n'existe pas
                                while (PilevideCF(PCFinter) == 0) {
                                    DepilerCF(&PCFinter, &Einter);
                                    AjouterCF(&CFP, Einter);
                                }
                                while (PilevideCF(CFP) == 0) {
                                    DepilerCF(&CFP, &Einter);
                                    if (Einter.nombre_commande == 0) { ///si le client n'a pas fait de commande c'est le pire client.
                                        test = 1;
                                        printf("\nClient %s %s nombre de commandes : %d", Einter.nom, Einter.prenom, Einter.nombre_commande);
                                    }
                                    AjouterCF(&PCFinter, Einter);
                                }
                                while (PilevideCF(PCFinter) == 0) {
                                    DepilerCF(&PCFinter, &Einter);
                                    AjouterCF(&CFP, Einter);
                                }
                                    if(test == 0){
                                        printf("\n Il n y a pas de pire client.\n");
                                    }
                                }

                                break;
                            case 8:
                                printf("_____________________\n");
                                printf("\n Affichage global :\n");
                                printf("_____________________\n");
                                affichageAV(CPA);
                                break;
                            case 9:
                                printf("_____________________\n");
                                printf("\n L'Ecart:\n");
                                printf("_____________________\n");
                                if(AVPilevide(CPA) == 1){
                                    printf("\n Il n y a pas de commandes pour le moment.\n");
                                }
                                else{
                                        int Achat = 0, Vente = 0;
                                        Commande_Achat_Vente cinter;
                                        AVPile avp;
                                        InitpileAV(&avp);
                                        while(AVPilevide(CPA) == 0){
                                            DepilerAV(&CPA, &cinter);
                                            if(cinter.type == 0){ //si le type est "client"
                                                while(Pilevide(PA) == 0){
                                                    Depiler(&PA, &articleinter);
                                                    Ajouter(&Pinter, articleinter);
                                                }
                                                if(cinter.reference_article == articleinter.reference){ //on cherche l'article
                                                    Vente = Vente + articleinter.prix; //on ajoute le prix au ventes
                                                }
                                                 while(Pilevide(Pinter) == 0){
                                                    Depiler(&Pinter, &articleinter);
                                                    Ajouter(&PA, articleinter);
                                                }
                                            }
                                            else if(cinter.type == 1){ //si le type est "fournisseur"
                                                    while(Pilevide(PA) == 0){
                                                    Depiler(&PA, &articleinter);
                                                    Ajouter(&Pinter, articleinter);
                                                }
                                                if(cinter.reference_article == articleinter.reference){ //on cherche l'article
                                                    Achat = Achat + articleinter.prix; //on ajoute le prix au achats
                                                }
                                                while(Pilevide(Pinter) == 0){
                                                    Depiler(&Pinter, &articleinter);
                                                    Ajouter(&PA, articleinter);
                                                }

                                            }

                                        }
                                        printf("\n L'ecart vaut %d - %d = %d \n", Vente, Achat, Vente-Achat);
                                    }
                                break;
                            }
                        } while (CCF != 10);
                    }
                    if (choixC == 2) {
                        int CF;
                        do {
                            menuCF();
                            scanf("%d", &CF);
                            switch ( CF ) {
                            case 1:
                                printf("_____________________\n");
                                printf("\n CREATION :\n");
                                printf("_____________________\n");
                                clientfournisseur A;
                                printf("\n Types existants : \n");
                                printf("\n 0 - Client.\n");
                                printf(" 1 - Fournisseur.\n");
                                printf(" 2 - divers.\n");
                                printf("\n Entrez le type : ");
                                scanf("%d", &A.etat);
                                while (A.etat > 2 || A.etat < 0) {
                                    printf(" Entrez un type valide : ");
                                    scanf("%d", &A.etat);
                                }
                                printf(" Entrez le nom : ");
                                scanf("%s", &A.nom);
                                printf(" Entrez le prenom : ");
                                scanf("%s", &A.prenom);
                                printf(" Entrez la reference : ");
                                scanf("%d", &A.reference);
                                printf(" Entrez le numero de telephone : ");
                                scanf("%d", &A.telephone);
                                printf("\n Entite ajoute avec succes.\n");
                                A.nombre_commande = 0;
                                AjouterCF(&CFP, A);
                                break;
                            case 2:

                                printf("_____________________\n");
                                printf("\n MODIFICATION :\n");
                                printf("_____________________\n");
                                if (PilevideCF(CFP) == 1) {
                                    printf("\n Il n y a pas d'entites pour l'instant.\n");
                                } else {
                                    int ref, test = 0;
                                    clientfournisseurPile Pileinter;
                                    clientfournisseur Entiteinter;
                                    InitpileCF(&Pileinter);
                                    printf("\n Entrez la reference de l'entite a modifier : ");
                                    scanf("%d", &ref);
                                    while (PilevideCF(CFP) == 0) {
                                        DepilerCF(&CFP, &Entiteinter);
                                        if ((Entiteinter.reference) == ref) {
                                            test = 1;
                                        }
                                        AjouterCF(&Pileinter, Entiteinter);
                                    }
                                    if (test == 0) {
                                        printf("\n L'entite n'existe pas.\n");
                                        while (PilevideCF(Pileinter) == 0) {
                                        }
                                    } else {
                                        int choix;
                                        printf("\n Que voulez vous modifier ?\n");
                                        printf("\n 1 - type\n");
                                        printf(" 2 - nom\n");
                                        printf(" 3 - prenom\n");
                                        printf(" 4 - telephone\n");
                                        printf("\n Votre choix : ");
                                        scanf("%d", &choix);
                                        switch ( choix ) {
                                        case 1:
                                            printf("\n Types existants : \n");
                                            printf("\n 0 - Client.\n");
                                            printf(" 1 - Fournisseur.\n");
                                            printf(" 2 - divers.\n");
                                            printf("\n Entrez le nouveau type: ");
                                            int type;
                                            scanf("%d", &type);
                                            Entiteinter.etat = type;
                                            break;
                                        case 2:
                                            printf("\n Entrez le nouveau nom : ");
                                            scanf("%s", &Entiteinter.nom);
                                            break;
                                        case 3:
                                            printf("\n Entrez le nouveau prenom : ");
                                            scanf("%s", &Entiteinter.prenom);
                                            break;
                                        case 4:
                                            printf("\n Entrez le nouveau numero de telephone : ");
                                            scanf("%d", &Entiteinter.telephone);

                                            break;
                                        }
                                        printf("\n Entite modifie avec succes.\n");
                                    }
                                    while (PilevideCF(Pileinter) == 0) {
                                        DepilerCF(&Pileinter, &Entiteinter);
                                        AjouterCF(&CFP, Entiteinter);
                                    }

                                }
                                break;
                            case 3:
                                printf("_____________________\n");
                                printf("\n SUPRESSION :\n");
                                printf("_____________________\n");
                                int ref, test = 0;
                                clientfournisseurPile Pileinter;
                                clientfournisseur Entiteinter;
                                InitpileCF(&Pileinter);
                                printf("\n Entrez la reference de l'entite a supprimer : ");
                                scanf("%d", &ref);
                                while (PilevideCF(CFP) == 0) {
                                    DepilerCF(&CFP, &Entiteinter);
                                    if ((Entiteinter.reference) == ref) {
                                        test = 1;
                                    }
                                    AjouterCF(&Pileinter, Entiteinter);
                                }
                                if (test == 0) {
                                    printf("\n L'entite n'existe pas.\n");
                                } else {
                                    DepilerCF(&Pileinter, &Entiteinter);
                                    printf("\n L'entite a ete supprime avec succes.\n");
                                }
                                while (PilevideCF(Pileinter) == 0) {
                                    DepilerCF(&Pileinter, &Entiteinter);
                                    AjouterCF(&CFP, Entiteinter);
                                }
                                break;
                            }
                        } while (CF != 4);

                    }
                } while (choixC != 3);
                break;
            }
        } while (numero_saisi = 7 && numero_gestion != 3);


        printf("\n! Fin du programme, merci.\n\n");
        return 0;
    }
