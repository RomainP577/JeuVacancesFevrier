#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lieu
{
    char Lieu_Name[64];
	int LieuExistant;
	char Description[64];
	int GoldGain;
	int HPGain;
	int ID;
};

struct Perso
{
	char Perso_Name[64];
	int HP_Perso;
    int HPMax_Perso;
	int MP_Perso;
	int Att_Perso;
    int Shield;
    char Capacite_Name[16];
};

struct Enemy
{
	char Enemy_Name[64];
	int HP_Enemy;
	int MP_Enemy;
	int Att_Enemy;
    int Enemy_Fight;
};

struct Shop
{
    char Obj_Name[64];
    int Obj_Price;
    int Slot;
    int ID;
    char Effet[64];
};

typedef struct Lieu Lieu;
typedef struct Perso Perso;
typedef struct Enemy Enemy;
typedef struct Shop Shop;

int i;
int j;

int Gold=10;
int Got_Gemme=0;
int Got_Potion=0;

int Access=0;
int HPCost_Light=30;
int HPCost_Heavy=50;
int Day=0;

int In_Fight=0;
int NB_Persos=3;
int NB_Enemy=0;
int Room_Donjon=0;
int Tour_Combat=0;
int Gemme_Debuff=500;

int Target=-1;
int Enemy_Target=0;

int main (){
	
	while (NB_Persos>0)
	{
        
        //Declarations________________________________________________________________________________________________
        
        //day count + display
        Day += 1;
        printf("___Jour %d___ \n", Day);
        
		//vars
		int ChoixLieu;
        int ChoixAction;
		
		//Arrays
		Lieu a_Lieux[4];
		Perso a_Perso[3];
		Enemy a_Enemy[4];
        Shop a_Shop[2];

		//Declaration lieux
		//Lieu example = {"Lieu_Name", Exist, details, Gold, HP, ID};
		Lieu Boutique = {"Boutique", 1, "Lieu1Details", 0, 0, 0};
		Lieu Auberge = {"Auberge", 1, "Lieu1Details", -2, 10, 1};
		Lieu Arene = {"Arene (require 20+ gold)", 1, "Lieu1Details", 26, -12, 2};
		Lieu Donjon = {"Donjon (require 80+ HP)", 1, "Lieu1Details", 14, -20, 3};
		
		//Array lieux
		a_Lieux[0] = Boutique;
		a_Lieux[1] = Auberge;
		a_Lieux[2] = Arene;
		a_Lieux[3] = Donjon;
		
		//Declaration Perso
		//Perso example ={"Perso_Name", HP_Perso, HPMax_Perso, MP_Perso, Att_Perso, Shield, CpacitéName};
		Perso Chevalier = {"Chevalier", 150, 150, 50, 30, 0, "Protection"};
		Perso Archer = {"Archer", 75, 75, 75, 50, 0, "Tir multiple"};
		Perso Pretre = {"Pretre", 100, 100, 100, 40, 0, "Soin"};
		
		//Array Perso
		a_Perso[0] = Chevalier;
		a_Perso[1] = Archer;
		a_Perso[2] = Pretre;
		
		//Declaration Enemy
		//Enemy example ={"Enemy_Name", HP_Perso, MP_Perso, Att_Perso, EnemyFight};
		Enemy Gobelin = {"Gobelin", 100, 30, 15, 0};
        Enemy Squelette = {"Squelette", 100, 30, 20, 0};
		Enemy Troll = {"Troll", 175, 50, 30, 0};
		Enemy Dragon = {"Dragon", 800, 100, 35, 0};
		
		//Array Enemy
		a_Enemy[0] = Gobelin;
		a_Enemy[1] = Squelette;
		a_Enemy[2] = Troll;
		a_Enemy[3] = Dragon;
        
        //Declaration Objets
		//Enemy Objets ={"Obj_Name", Price, slot, ID};
        Shop Potion = {"Potion", 5, 1, 0, "Evite une mort imminente."};
        Shop Gemme = {"Gemme", 30, 1, 1, "Effet inconnu."};
        
        //Array Shop
        a_Shop[0] = Potion;
        a_Shop[1] = Gemme;
        
		
        //prise de direction
        printf("Plusieurs chemins s'offrent a vous.\n");
		for (i=0; i<4; i++)
		{
			if (a_Lieux[i].LieuExistant==1)
			{
				printf("%d = %s \n", a_Lieux[i].ID, a_Lieux[i].Lieu_Name);
			}
		}
		
		//Affichage txt choix lieux
		printf("Ou voulez vous aller ?\n");
		scanf("%d", &ChoixLieu);
		
		/*if (a_Lieux[i].LieuExistant!=1)
		{
			printf("Lieu inexistant");
			scanf("%d", &ChoixLieu);
		}*/
		
        printf("\n");
		printf("Lieu choisi : %d \n", ChoixLieu);
        printf("\n");
		
		//CONDITIONS DEPLACEMENT______________________________________________________________________________________
		if (a_Lieux[ChoixLieu].LieuExistant==1)
		{
			if (ChoixLieu==0)
			{
				printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                printf("Vous entrez dans une boutique poussiereuse.\n");
                
                for (i=0; i<2; i++)
                {
                    if (a_Shop[i].Slot==1)
                    {
                        printf(" %d = %s, %s (%d Or)\n", a_Shop[i].ID, a_Shop[i].Obj_Name, a_Shop[i].Effet, a_Shop[i].Obj_Price);
                    }
                }
                
                printf("Voulez vous acheter quelque chose ? (%d Gold, 2 = Retour)", Gold);
                scanf("%d", &Target);
                
                if (Target==2)
                {
                    Access=1;
                    printf("Vous sortez de la boutique.");
                }
                
                if (Target!=2)
                {
                
                    if (Target==0)
                    {
                        if (a_Shop[0].Obj_Price <= Gold)
                        {
                            printf("Vous achetez %s", a_Shop[Target].Obj_Name);
                            Got_Potion+=1;
                        }
                        else 
                        {
                            printf("Vous n'avez pas assez d'or.\n");
                            printf("Vous sortez de la boutique.\n");
                        }
                    }
                    
                    if (Target==1)
                    {
                        if (a_Shop[1].Obj_Price <= Gold)
                        {
                            printf("Vous achetez %s", a_Shop[Target].Obj_Name);
                            Got_Gemme=1;
                        }
                        else 
                        {
                            printf("Vous n'avez pas assez d'or.\n");
                            printf("Vous sortez de la boutique.\n");
                        }
                    }
                }
			}
            
            if (ChoixLieu==1)
			{
                if (Gold>=2)
                {
                    printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                    printf("Vous vous reposez pour 2 Or et regagnez 10 HP par aventurier.\n");
                    Access=1;
                }
                if (Gold<=2)
                {
                    printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                    printf("Vous n'avez pas d'or pour payer la nuit, vous dormez dehors.\n");
                    Access=0;
                }
				
			}
            
            if (ChoixLieu==2)
            {
                if (Gold>=20)
                {
                    printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                    printf("Vous vous battez pour votre honneur et sortez victorieux.\n");
                    Access=1;
                }
                if (Gold<=20)
                {
                    printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                    printf("Vous n'avez pas d'or pour vous payer votre propre gloire,\n vous assister aux combats depuis les tribunes.\n");
                    Access=0;
                }
            }
			
			if (ChoixLieu==3)
            {
                if (NB_Persos>=2)
                {
                    printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                    printf("Vous entrez dans le donjon.\n");
                    In_Fight=1;
                    
                    if(Room_Donjon==0)
                    {
                        printf("Vous tombez sur une piece vide au premier abord, mais un troll sors de la penombre et vous attaque.");
                        a_Enemy[2].Enemy_Fight = 1; //Troll
                        NB_Enemy+=1;
                    }
                    
                    if(Room_Donjon==1)
                    {
                        printf("Vous descendez les escaliers qui s'enfonce dans le donjon alors qu'un gobelin et un squelette vous bloque le chemin.");
                        a_Enemy[0].Enemy_Fight = 1; //Gobelin
                        a_Enemy[1].Enemy_Fight = 1; //Squelette
                        NB_Enemy+=2;
                    }
                    
                    if(Room_Donjon==2)
                    {
                        printf("Arrives en bas des escaliers, vous entrez dans une grande salle ou un dragon vous attaque.");
                        a_Enemy[3].Enemy_Fight = 1; //Dragon
                        NB_Enemy+=1;
                        
                        if (Got_Gemme==1)
                        {
                            printf("Votre gemme afaiblit le dragon (-%d HP).", Gemme_Debuff);
                            a_Enemy[3].HP_Enemy -= Gemme_Debuff;
                        }
                    }
                }
                if (NB_Persos<=1)
                {
                    printf("Vous etes : %s \n", a_Lieux[ChoixLieu].Lieu_Name);
                    printf("Vous n'avez pas assez d'energie pour vous engouffrez dans un donjon, vous passez votre chemin.\n");
                    Access=0;
                }
            }
			
			printf("\n");
            
            //Combat system___________________________________________________________________________________________
            while (In_Fight == 1)
            {
                printf("\n");
                printf("---------------------------------------\n");
                printf("Vous vous battez contre %d ennemi(s) !\n", NB_Enemy);
                
                //Affichage HP enemy
                for (i=0; i<4; i++)
                {
                    if (a_Enemy[i].Enemy_Fight==1)
                    {
                        printf(" -%s (%d HP)\n", a_Enemy[i].Enemy_Name, a_Enemy[i].HP_Enemy);
                    }
                }
                
                printf("\n");
                
                //Affichage HP persos/ reset shield
                for (i=0; i<3; i++)
                {
                    if (a_Perso[i].HP_Perso>=1)
                    {
                        printf(" -%s (%d HP) | Shield : ", a_Perso[i].Perso_Name, a_Perso[i].HP_Perso);
                    }
                    
                    if (a_Perso[i].Shield <= 0)
                    {
                        printf("Off\n");
                    }
                    
                    if (a_Perso[i].Shield ==1)
                    {
                        a_Perso[i].Shield -=1;
                        printf("On\n");
                    }
                }
                
                printf("\n");
                
                //Compteur de tour
                Tour_Combat += 1;
                printf("_Tour %d_ \n", Tour_Combat);
                
                //Phase d'action
                for (i=0; i<NB_Persos; i++)
                {
                    if (a_Perso[i].HP_Perso>0)
                    {
                        printf("---------------------------------------\n");
                        printf("%s se prepare.\n", a_Perso[i].Perso_Name);
                        printf(" 0 = Attaque\n 1 = Defense\n 2 = Special\n");
                        printf("Que voulez vous faire ?\n");
                        scanf("%d", &ChoixAction);
                        printf("\n");

                        //Attaque
                        if (ChoixAction==0)
                        {
                            printf("Vous choissisez d'attaquer.\n");
                            printf("Vous infligez %d de degats.\n", a_Perso[i].Att_Perso);
                            printf("\n");
                            
                            if (Room_Donjon==0)
                            {
                                a_Enemy[2].HP_Enemy -= a_Perso[i].Att_Perso;
                                //printf(" -%s (%d HP)\n", a_Enemy[2].Enemy_Name, a_Enemy[i].HP_Enemy);
                            }
                            
                            if (Room_Donjon==1)
                            {
                                printf(" 0 = Gobelin\n 1 = Squelette\n");
                                printf("Choississez la cible.\n");
                                scanf("%d", &Target);
                                
                                if (Target == 0)
                                {
                                    a_Enemy[0].HP_Enemy -= a_Perso[i].Att_Perso;
                                }
                                
                                if (Target == 1)
                                {
                                    a_Enemy[1].HP_Enemy -= a_Perso[i].Att_Perso;
                                }
                                //printf(" -%s (%d HP)\n", a_Enemy[0].Enemy_Name, a_Enemy[i].HP_Enemy);
                                //printf(" -%s (%d HP)\n", a_Enemy[1].Enemy_Name, a_Enemy[i].HP_Enemy);
                            }
                            
                            if (Room_Donjon==2)
                            {
                                a_Enemy[3].HP_Enemy -= a_Perso[i].Att_Perso;
                                //printf(" -%s (%d HP)\n", a_Enemy[2].Enemy_Name, a_Enemy[i].HP_Enemy);
                            }
                        }

                        //Defense
                        if (ChoixAction==1)
                        {
                            printf("Vous choissisez de vous protegez.\n");
                            a_Perso[i].Shield = 1;
                        }

                        //Special
                        if (ChoixAction==2)
                        {
                            printf("Vous choissisez d'utiliser votre capacite speciale (%s)\n", a_Perso[i].Capacite_Name);

                            if (i==0)
                            {
                                printf("Chevalier lance une protection.\n");
                                printf(" 0 = Chevalier\n 1 = Archer\n 2 = Pretre\n");
                                printf("Choississez la cible (100% Resist/3tour)\n");
                                scanf("%d", &Target);
                                printf("%s recoit une protection.\n", a_Perso[Target].Perso_Name);
                                a_Perso[Target].Shield = 3;
                            }

                            if (i==1)
                            {
                                printf("Archer lance un tir multiple.\n");
                                
                                if (Room_Donjon==0)
                                {
                                    a_Enemy[2].HP_Enemy -= a_Perso[i].Att_Perso;
                                }
                                
                                if (Room_Donjon==1)
                                {
                                    a_Enemy[0].HP_Enemy -= a_Perso[i].Att_Perso;
                                    a_Enemy[1].HP_Enemy -= a_Perso[i].Att_Perso;
                                }
                                
                                if (Room_Donjon==2)
                                {
                                    a_Enemy[3].HP_Enemy -= a_Perso[i].Att_Perso;
                                }
                            }

                            if (i==2)
                            {
                                printf("Pretre lance un sort de soin.\n");
                                printf(" 0 = Chevalier\n 1 = Archer\n 2 = Pretre\n");
                                printf("Choississez la cible(+50HP)\n");
                                scanf("%d", &Target);
                                printf("%s recoit un sort de soin.\n", a_Perso[Target].Perso_Name);
                                a_Perso[Target].HP_Perso += 50;
                            }
                            
                            //Enemy attack
                            for (j=0; j<4; j++)
                            {
                                if (a_Enemy[j].Enemy_Fight==1)
                                {
                                    //verification perso 1ere ligne
                                    if (a_Perso[Enemy_Target].HP_Perso<=0)
                                    {
                                        Enemy_Target += 1;
                                    }
                                    
                                    a_Perso[Enemy_Target].HP_Perso -= a_Enemy[j].Att_Enemy;
                                    printf("%s inflige %d a %s.\n", a_Enemy[j].Enemy_Name, a_Enemy[j].Att_Enemy, a_Perso[Enemy_Target].Perso_Name);
                                }
                            }
                        }
                    }
                }
                
                //Perso death check
                for (i=0; i<3; i++)
                {
                    if (a_Perso[i].HP_Perso<=0)
                    {
                        if (Got_Potion < 1)
                        {
                            NB_Persos -= 1;
                        }
                        
                        else
                        {
                            printf("Potion utilisée (Restantes : %d)", Got_Potion);
                        }
                    }
                    
                    if (NB_Persos<1)
                    {
                        In_Fight=0;
                    }
                }
                
                //Enemy death check
                for (i=0; i<3; i++)
                {
                    if (a_Enemy[i].HP_Enemy<=0)
                    {
                        a_Enemy[i].Enemy_Fight=0;
                        NB_Enemy -= 1;
                    }
                }
                
                //Donjon progression
                if (NB_Enemy<1)
                {
                    if (Room_Donjon<=1)
                    {
                        In_Fight=0;
                        Room_Donjon+=1;
                        printf("Ennemi(s) detruits, revenez au donjon pour continuer de l'explorer.\n");
                        Access=1;
                    }

                    else if (Room_Donjon>=2)
                    {
                        In_Fight=0;
                        printf("Le Dragon est mort, vous recuperez son butin (100 Gold)\n");
                        Gold += 100;
                        Access=1;
                    }

                }
                printf("Room : %d \n", Room_Donjon);
            }
            
            Tour_Combat=0;
            
            //Reward HP/Gold
			if (Access==1)
			{
				if (Gold>=0)
				{
					Gold += a_Lieux[ChoixLieu].GoldGain;
					if (Gold<0)
					{
						Gold=0;
					}
				}
                
				for (i=0; i<3; i++)
                {
                    if (a_Perso[i].HP_Perso < a_Perso[i].HPMax_Perso)
                    {
                        a_Perso[i].HP_Perso += a_Lieux[ChoixLieu].HPGain;
                    }
                }
			}
			
            //Affichage Gold
			printf("Vous avez %d or \n", Gold);
            printf("\n");
            
			//Affichage HP persos
            for (i=0; i<3; i++)
            {
                if (a_Perso[i].HP_Perso>=0)
                {
                    printf(" -%s (%d HP)\n", a_Perso[i].Perso_Name, a_Perso[i].HP_Perso);
                }
            }
		}
        printf("\n");
	}	
	printf("Votre groupe d'aventure est mort.");
}