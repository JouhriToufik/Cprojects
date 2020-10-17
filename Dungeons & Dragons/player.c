#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"player.h"

/**
* Creates a player.
* \return NULL on error (i.e., if the memory allocation is a failure), else a player.
*/
player_t *player_create()
{
  player_t *P;
  P = malloc(sizeof(player_t));
  if (P == NULL){
    fprintf(stderr, "Erreur lors d'allocation de mémoire \n");
    return NULL;

  }
  else{
  P->ac=0; /**< The player armor class. */
  P->class=NULL; /**< The player class. */
  P->cname=NULL; /**< The player character name. */
  P->cp=0; /**< The player money (copper pieces, 100 CP = 1 GP). */
  P->gp=0; /**< The player money (gold pieces). */
  P->hp=0; /**< The player hit points. */
  P->name=NULL; /**< The player name. */
  P->sp=0;
  }
  return P;
}

void player_free(player_t *player)
{
  xmlFree(player->name);
  xmlFree(player->cname);
  xmlFree(player->class);
  free(player);
}

void player_handle_p(player_t player)
{
  printf("%s (%s), %s, AC: %d, HP: %d, GP: %.2f (GP: %d, SP: %d, CP: %d) \n",player.name,player.cname,player.class,player.ac,player.hp,(player.gp+((float)player.sp/10)+((float)player.cp/100)),player.gp,player.sp,player.cp);
}

void player_handle_pa(player_t player,int ac){
  if(player.ac == ac)
  {
    player_handle_p(player);
  }

}

void player_handle_page(player_t player, int ac){
  if(player.ac >= ac)
  {
    player_handle_p(player);
  }
}

void player_handle_pagt(player_t player, int ac){
  if(player.ac > ac)
  {
    player_handle_p(player);
  }
}

void player_handle_pale(player_t player, int ac){
if(player.ac <= ac)
    {
      player_handle_p(player);
    }
}

void player_handle_palt(player_t player, int ac){
  if(player.ac < ac)
      {
        player_handle_p(player);
      }
}

void player_handle_pc(player_t player, const char *class){
  if(strstr(player.class,class)!=NULL)
  {
    player_handle_p(player);
  }
}

void player_handle_pcn(player_t player, const char *cname){
  if(strstr(player.cname,cname)!= NULL)
      {
        player_handle_p(player);
      }
}

void player_handle_ph(player_t player, int hp){
  if(player.hp == hp)
      {
        player_handle_p(player);
      }

}

void player_handle_phge(player_t player, int hp){
  if(player.hp >= hp)
      {
        player_handle_p(player);
      }
}

void player_handle_phgt(player_t player, int hp){
  if(player.hp > hp)
      {
        player_handle_p(player);
      }
}

void player_handle_phle(player_t player, int hp){
  if(player.hp <= hp)
      {
        player_handle_p(player);
      }
}

void player_handle_phlt(player_t player, int hp){
  if(player.hp < hp)
      {
        player_handle_p(player);
      }

}

void player_handle_pn(player_t player, const char *name){
  if(strstr(player.name,name)!= NULL)
      {
        player_handle_p(player);
      }
  }
