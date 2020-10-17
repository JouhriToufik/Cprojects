#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include"player.h"
#include"ddg.h"
#define NBNBMAX 18
/* ----Parse ddg , la premiere partie de l'xml de balise ddg jusqu'à <dmname> ----*/
void parse_ddg(xmlNodePtr cur ,xmlDocPtr doc,ddg_t *ddg){
  /* déclaration des variables*/
  char *endptr;
  xmlChar *temp;
  /*apres cur = xmlDocGetRootElement(doc);
 dans le main, le pointeur pointe directement sur <ddg>*/
  ddg->name =(char *)xmlGetProp(cur,(const xmlChar *) "name");
  cur=cur->children;
  while (cur!=NULL){

	  if(!xmlStrcmp(cur->name,(const xmlChar *) "date")){
      cur = cur->children;
	    while (cur->next !=NULL)
      {
	       if((!xmlStrcmp(cur->name,(const xmlChar *) "day"))){
           temp=xmlNodeListGetString(doc,cur->children,0);
           ddg->day = strtol((char *)temp,&endptr,10);
           xmlFree(temp);
         }

	       if((!xmlStrcmp(cur->name,(const xmlChar *)"month"))){
           temp= xmlNodeListGetString(doc,cur->children,0);
           ddg->month = strtol((char *)temp,&endptr,10);
           xmlFree(temp);
         }

	       if((!xmlStrcmp(cur->name,(const xmlChar*)"year"))){
          temp = xmlNodeListGetString(doc,cur->children,0);
          ddg->year = strtol((char *)temp,&endptr,10);
          xmlFree(temp);}
          cur=cur->next; /* cur -> next ici sert a bouger le pointeur pour trouver day/month/year */
	      }
	     cur= cur->parent;
	    }
    if(!xmlStrcmp(cur->name,(const xmlChar *) "dmname")){

      ddg->dmname = (char *)xmlNodeListGetString(doc,cur->children,0);
    }
    cur=cur->next;
	}
}

/*----Parse player on recuperer les players et leurs données (2eme partie du fichier xml) ------------------------*/

void parse_player(xmlNodePtr cur,xmlDocPtr doc,ddg_t *ddg){
  /*declaration de variable */

  char *endptr;
	player_t *player; /* pointeur vers structure player_t*/
  xmlChar* temp;
	cur = cur->children;
	while(cur->next != NULL){
		if(!xmlStrcmp(cur->name, (const xmlChar *)"players"))
			break;
		cur = cur->next;
		}
	cur = cur->xmlChildrenNode;/*cur a trouvé <plyaers> puis il va chercher son enfant <player>*/
	while(cur!= NULL)
  {
    player = player_create();
    if(!xmlStrcmp(cur->name, (const xmlChar *)"player"))
    {
      /* allocate new memory*/
      ddg_add_player(ddg,player);
  	  player->name=(char*)xmlGetProp(cur, (const xmlChar *)"name");
			cur=cur->children;
			while(cur->next!= NULL)
      {
        if(!xmlStrcmp(cur->name, (const xmlChar *)"ac")){
          temp =  xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
          player->ac = strtol((char *)temp,&endptr,10);
          xmlFree(temp);
        }
        if(!xmlStrcmp(cur->name, (const xmlChar *)"class")){

          player->class = (char *)xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

        }

				if(!xmlStrcmp(cur->name,(const xmlChar *)"cname")){
          player->cname = (char *)xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

        }


				if(!xmlStrcmp(cur->name, (const xmlChar *) "hp")){
          temp =  xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
          player->hp = strtol((char*)temp,&endptr,10);
          xmlFree(temp);
        }

				if(!xmlStrcmp(cur->name,(const xmlChar *)"money"))
        {
					cur = cur->children;
					while (cur->next !=NULL)
          {
              if(!xmlStrcmp(cur->name,(const xmlChar *)"cp")){
                temp = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                player->cp = strtol((char*)temp,&endptr,10);
                xmlFree(temp);
                }

							if(!xmlStrcmp(cur->name,(const xmlChar *)"gp")){
                temp =xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                player->gp = strtol((char*) temp,&endptr,10);
                xmlFree(temp);
              }

              if(!xmlStrcmp(cur->name,(const xmlChar *)"sp")){
                  temp = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
									player->sp = strtol((char*)temp,&endptr,10);
                  xmlFree(temp);}
              cur = cur->next;
					}
					cur = cur->parent;
				}
        cur = cur->next;
			}/* fin de remplir player*/
      cur = cur->parent; /* quit the the player and go back to players */
			/*fin d'ajout */
		}
		cur = cur->next;/*bouge to next player*/
	}
}
/*------------------------------------------------------------------------------*/
/*gestion de l'écriture de l'utilisature la limiter à 18 et retroune un indice d'erreur pour
  nous servir à sortir du do while*/
  int getinputless18( char *input,char **argv)
  {

    char *aux;
    int i=0;
    do
    {
      aux = fgets(input, NBNBMAX+2, stdin);/* on mets ce qui est ecrit par user dans aux*/
      if (input[strlen(input)-1] == '\n')
      {
        if (aux != NULL)
          aux = NULL;
      }
      i++;
    } while (aux != NULL);/* jusqu'a ce que fgets retourne NULL dans aux */
    if (i > 1)
      fprintf(stderr, "%s :Too many characters for the command\n",argv[0]);
    input[strlen(input) - 1] = '\0';
    return i;
  }

  /* gestion de commande h*/
  void h_handler(){
    printf("d: Prints the DDG date\n");
    printf("g: Prints the DDG\n");
    printf("m: Prints the DDG dungeon master name\n");
    printf("h: Prints this help\n");
    printf("n: Prints the DDG name\n");
    printf("p: Prints the DDG players\n");
    printf("pa AC: Prints the DDG players with the armor class equal to AC\n");
    printf("page AC: Prints the DDG players with the armor class greater than or equal to AC\n");
    printf("pagt AC: Prints the DDG players with the armor class greater than AC\n");
    printf("pale AC: Prints the DDG players with the armor class less than or equal to AC\n");
    printf("palt AC: Prints the DDG players with the armor class less than AC\n");
    printf("pc CLASS: Prints the DDG players with the class containing CLASS\n");
    printf("pcn CNAME: Prints the DDG players with the character name containing CNAME\n");
    printf("ph HP: Prints the DDG players with the hit points equal to HP\n");
    printf("phge HP: Prints the DDG players with the hit points greater than or equal to HP\n");
    printf("phgt HP: Prints the DDG players with the hit points greater than HP\n");
    printf("phle HP: Prints the DDG players with the hit points less than or equal to HP\n");
    printf("phlt HP: Prints the DDG players with the hit points less than HP\n");
    printf("pn NAME: Prints the DDG players with the name containing NAME\n");
    printf("v: Prints the DDGM version\n");
    printf("q: Quits DDGM\n");
  }

  /* gestion de commande v*/

  void v_handler(){
    printf("DDGM (Dungeons and Dragons Game Manager) 20191101 \n");
    printf("Copyright (C) 2019 Toufik Jouhri and Alicx Kamoun.\n");
    printf("Written by Toufik Jouhri <jouhri.toufik@etud.univ-pau.fr> and Alicx Kamoun <alicx.kamoun@etud.univ-pau.fr>\n");

  }

/*--------------------------------------------------------------*/
int main (int argc , char *argv[]){

/* Décalaration des Variables*/

char *endptr=NULL;
char par[NBNBMAX];
char *buf;
int hp,ac;
int i,erreur;
xmlNodePtr cur;
xmlDocPtr doc;
ddg_t *DDG=ddg_create();
buf = malloc(sizeof(char));
/* Nombre d'arguments qui ne doit pas dépasser 2 */

if(argc != 2){
  fprintf(stderr,"Invalid number of arguments \n");
  return 1;
}
/*------------------------------------------*/
doc = xmlParseFile(argv[1]);
if (doc == NULL ) /* DOC == NULL c a d il n'a pas trouver le document ou il n'existe pas.*/
{
  fprintf(stderr,"Document not parsed successfully. \n");
  return 1;
}
/*-------------------------------------------*/
cur = xmlDocGetRootElement(doc);
if (cur == NULL) /* si cur == NULL c-a-d que le document est vide */
{
  fprintf(stderr,"I/O warning : failed to load external entity \"%s\" \n %s: Unable to parse the document",argv[1],argv[0]);
  xmlFreeDoc(doc);
}

/* On parse la premiere partie de l'xml et on remplie le ddg jusqu'à the DDG dungeon master name */
parse_ddg(cur,doc,DDG);
parse_player(cur,doc,DDG);
/***On parse le reste de l'xml et*on remplie les players jusqu'a les avoir tous*/
printf("DDG> " );/* ça commençe par là x) */
erreur = getinputless18(par,argv);/*on recupere ce qui est tapé par l'user */
while(strcmp(par,"q") != 0){
  if(erreur <= 1){
      /* if the user enter h command */
      if (!strcmp(par, "h"))
      h_handler();
    /* handle the h command : show the full menu of commands j'ai choisis
    de le mettre dans une fonction pour éviter trop l'écriture dans le main
    / Pareil pour v_ handler ( versions ).*/
    else if (!strcmp(par, "d"))
      ddg_handle_d( * DDG);

    /*--------- version ------------------------------------------------------------------------------------------------*/
    else if (!strcmp(par, "v"))
      v_handler();
    /*------- n command : print the ddg name -------------------------------------------------------------------------- */
    else if (!strcmp(par, "n"))
      ddg_handle_n( * DDG);
    /* ------the user enter the p command : prints the ddg players------------------------------------------------------*/
    else if (!strcmp(par, "p"))
      ddg_handle_p( * DDG);
    /* --------the user enter the m command : prints the ddg dungeon master name-----------------------------------------*/
    else if (!strcmp(par, "m"))
      ddg_handle_m( * DDG);
    /*prints the DDG */
    else if (!strcmp(par, "g"))
      ddg_handle_g( * DDG);
    /*------- if the user enter pa command -----------------------------------------------------------------------------*/
    else if (strcmp(par, "pa") == 0)
      fprintf(stderr, "%s: Missing parameter for the pa command\n", argv[0]);
    else if ((strstr(par, "pa ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++) {
        buf[i] = buf[i + 1];
      }
      buf[strlen(buf)] = '\0';
      errno = 0;
      ac = strtod((char * ) buf, & endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the pa AC command\n");
      ddg_handle_pa( * DDG, ac);
    }

    /*-----if the user enter page AC command----------------------------------------------------------------------------*/
    else if (strcmp(par, "page") == 0)
      fprintf(stderr, "%s: Missing parameter for the page AC command\n", argv[0]);
    else if ((strstr(par, "page ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      ac = strtod((char * ) buf, & endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the page AC command\n");
      ddg_handle_page( * DDG, ac);
    }
    /*------------------------------ user enter the pagt AC command-----------------------------------------------------------------------------*/
    else if (strcmp(par, "pagt") == 0)
      fprintf(stderr, "%s: Missing parameter for the pagt command\n", argv[0]);
    else if ((strstr(par, "pagt ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++) {
        buf[i] = buf[i + 1];
      }
      buf[strlen(buf)] = '\0';
      errno = 0;
      ac = strtod((char * ) buf, & endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the pagt AC command\n");
      ddg_handle_pagt( * DDG, ac);
    }
    /*----------------------------if the user enter the pale AC command---------------------------------------------------------*/
    else if (strcmp(par, "pale") == 0)
      fprintf(stderr, "%s: Missing parameter for the pale command\n", argv[0]);
    else if ((strstr(par, "pale ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      ac = strtod((char * ) buf, &endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the pale AC command\n");
      ddg_handle_pale( * DDG, ac);
    }
    /*------------------------------if the user enter the palt AC command----------------------------------------------------------*/
    else if (strcmp(par, "palt") == 0)
      fprintf(stderr, "%s: Missing parameter for the palt command\n", argv[0]);
    else if ((strstr(par, "palt ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      ac = strtod((char * ) buf, &endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the palt AC command\n");
      ddg_handle_palt( * DDG, ac);
    }
    /*-----------------------------------if user enter the ph command--------------------------------------------------------------*/
    else if (strcmp(par, "ph") == 0)
      fprintf(stderr, "%s: Missing parameter for the ph HP command\n", argv[0]);
    else if ((strstr(par, "ph ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      hp = strtod((char * ) buf, &endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the ph HP command\n");
      ddg_handle_ph( * DDG, hp);
    }
    /*-------------------------------if user enter the phge command--------------------------------------------------------------*/
    else if (strcmp(par, "phge") == 0)
      fprintf(stderr, "%s: Missing parameter for the phge HP command\n", argv[0]);
    else if ((strstr(par, "phge ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      hp = strtod((char * ) buf, & endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the phge HP command\n");
      ddg_handle_phge( * DDG, hp);
    }

    /*------------------------------if user enter the phgt command------------------------------------------------------------------*/
    else if (strcmp(par, "phgt") == 0)
      fprintf(stderr, "%s: Missing parameter for the phgt HP command\n", argv[0]);
    else if ((strstr(par, "phgt ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      hp = strtod((char * ) buf, & endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the phgt HP command\n");
      ddg_handle_phgt( * DDG, hp);
    }
    /*-------------------------------- if user enter the phle command-------------------------------------------------------------------*/
    else if (strcmp(par, "phle") == 0)
      fprintf(stderr, "%s: Missing parameter for the phle HP command\n", argv[0]);
    else if ((strstr(par, "phle ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      hp = strtod((char * ) buf, &endptr);
      if (errno != 0 || * endptr != '\0')
        fprintf(stderr, "Invalid parameter for the phle HP command\n");
      ddg_handle_phle( * DDG, hp);
    }

    /*------------------------ User enter pcn command :Prints the DDG players with the character name containing CNAME-----------------------*/
    else if (strcmp(par, "pcn") == 0)
      fprintf(stderr, "%s: Missing parameter for the pcn CNAME command\n", argv[0]);
    else if ((strstr(par, "pcn ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++) {
        buf[i] = buf[i + 1];
      }
      buf[strlen(buf)] = '\0';
      ddg_handle_pcn( * DDG, buf);
    }
    /*--------------------------user enter the command : pc CLASS: Prints the DDG players with the class containing CLASS -----------------------*/
    else if (strcmp(par, "pc") == 0)
      fprintf(stderr, "%s: Missing parameter for the pc CLASS command\n", argv[0]);
    else if ((strstr(par, "pc ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      ddg_handle_pc( * DDG, buf);
    }
    /*---------------------------user enter the command : pn NAME: Prints the DDG players with the name containing NAME-------------------------------*/
    else if (strcmp(par, "pn") == 0)
      fprintf(stderr, "%s: Missing parameter for the pn NAME command\n", argv[0]);
    else if ((strstr(par, "pn ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      ddg_handle_pn( * DDG, buf);
    }
/*------------------------------------ if user enter the phlt command-----------------------------------------------------------------*/
    else if (strcmp(par, "phlt") == 0)
      fprintf(stderr, "%s: Missing parameter for the phlt HP command\n", argv[0]);
    else if ((strstr(par, "phlt ") != NULL)) {
      buf = strstr(par, " ");
      for (i = 0; i < strlen(buf); i++)
        buf[i] = buf[i + 1];
      buf[strlen(buf)] = '\0';
      errno = 0;
      hp = strtod((char * ) buf, & endptr);
      ddg_handle_phlt( * DDG, hp);
    }
    /*------------------- if  user tape n'importe quoi =)) --------------------------------------------------------------------------*/
    else
      printf("%s: invalid command \n",argv[0]);
    }
    printf("DDGM> ");
    erreur = getinputless18(par, argv);


}
return 0;
}
