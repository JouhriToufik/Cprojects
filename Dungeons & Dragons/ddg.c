#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"player.h"
#include"ddg.h"
/**
* Add a player to a DDG.
* \param ddg The DDG.
* \param player The player.
* \return -1 on error (i.e., if the memory allocation is a failure), else 0.
*/
int ddg_add_player(ddg_t *ddg, player_t *player){

  ddg->players = realloc(ddg->players, ((ddg->nplayers)+1) * sizeof(player_t));
  if(ddg->players==NULL){
    printf("Erreur d'allocation\n");
  }
  ddg->players[ddg->nplayers]=player;
  ddg->nplayers++;
  return 0;
}
/**
* Creates a DDG.
* \return NULL on error (i.e., if the memory allocation is a failure), else a DDG.
*/
ddg_t* ddg_create(){
  ddg_t *ddg;
  ddg = (ddg_t*)malloc(sizeof(ddg_t));
  if(ddg==NULL){
    fprintf(stderr, "Erreur lors d'allocation de mémoire \n");
    return NULL;
  }
  else
  {
    ddg->day=0;
    ddg->dmname=NULL;
    ddg->month=0;
    ddg->name= NULL;
    ddg->nplayers=0;
    ddg->players=NULL;
    ddg->year=0;
    return ddg;
  }
}

/**
* Frees a DDG.
* \param ddg The DDG.
*/

void ddg_free(ddg_t *ddg){
  int i;
  xmlFree(ddg->name);
  xmlFree(ddg->dmname);
  for(i=0;i<ddg->nplayers;i++){
    player_free(ddg->players[i]);
  }
  free(ddg->players);
  free(ddg);
}

/**
* Handles the d command for a DDG.
* \param ddg The DDG.
*/

void ddg_handle_d(ddg_t ddg)
{
  printf("0%d - 0%d - %d \n",ddg.day,ddg.month,ddg.year);
}

/**
* Handles the g command for a DDG.
* \param ddg The DDG.
*/

void ddg_handle_g(ddg_t ddg){

  printf("%s, %s, 0%d-0%d-%d, %d players(s)\n",ddg.name,ddg.dmname,ddg.day,ddg.month,ddg.year,ddg.nplayers);

}

/**
* Handles the m command for a DDG.
* \param ddg The DDG.
*/

void ddg_handle_m(ddg_t ddg)
{
  printf("%s\n",ddg.dmname);
}

/**
* Handles the n command for a DDG.
* \param ddg The DDG.
*/

void ddg_handle_n(ddg_t ddg)
{
  printf("%s\n",ddg.name);
}

/**
* Handles the p command for a DDG.
* \param ddg The DDG.
*/

void ddg_handle_p(ddg_t ddg)
{
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_p(*ddg.players[i]);
  }
}

/**
* Handles the pa command for all the players of a DDG.
* \param ddg The DDG.

* \param ac The player armor class.
*/

void ddg_handle_pa(ddg_t ddg, int ac)
{
  int i=0;
    for ( i = 0; i < ddg.nplayers;i++)
  {
    player_handle_pa(*ddg.players[i],ac);
  }
}

/**
* Handles the page command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/

void ddg_handle_page(ddg_t ddg, int ac){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_page(*ddg.players[i], ac);
  }
}
/**
* Handles the pagt command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/
void ddg_handle_pagt(ddg_t ddg, int ac){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_pagt(*ddg.players[i], ac);
  }
}

/**
* Handles the pale command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/

void ddg_handle_pale(ddg_t ddg, int ac){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_pale(*ddg.players[i], ac);
  }
}

/**
* Handles the palt command for all the players of a DDG.
* \param ddg The DDG.
* \param ac The player armor class.
*/

void ddg_handle_palt(ddg_t ddg, int ac){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_palt(*ddg.players[i], ac);
  }
}

/**
* Handles the pc command for all the players of a DDG.
* \param ddg The DDG.
* \param class The player class.
*/
void ddg_handle_pc(ddg_t ddg, const char *class){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_pc(*ddg.players[i], class);
  }
}
/**
* Handles the pcn command for all the players of a DDG.
* \param ddg The DDG.
* \param cname The player character name.
*/
void ddg_handle_pcn(ddg_t ddg, const char *cname){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_pcn(*ddg.players[i], cname);
  }
}
/**
* Handles the ph command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_ph(ddg_t ddg, int hp){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_ph(*ddg.players[i], hp);
  }
}
/**
* Handles the phge command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phge(ddg_t ddg, int hp){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_phge(*ddg.players[i], hp);
  }
}
/**
* Handles the phgt command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phgt(ddg_t ddg, int hp){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_phgt(*ddg.players[i],hp);
  }
}
/**
* Handles the phle command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phle(ddg_t ddg, int hp){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_phle(*ddg.players[i],hp);
  }
}
/**
* Handles the phlt command for all the players of a DDG.
* \param ddg The DDG.
* \param hp The player hit points.
*/
void ddg_handle_phlt(ddg_t ddg, int hp){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_phlt(*ddg.players[i],hp);
  }
}
/**
* Handles the pn command for all the players of a DDG.
* \param ddg The DDG.
* \param name The DDG name.
*/
void ddg_handle_pn(ddg_t ddg, const char *name){
  int i;
  for (i = 0; i < ddg.nplayers;i++)
  {
    player_handle_pn(*ddg.players[i],name);
  }
}
