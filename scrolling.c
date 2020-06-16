
/** 
   * @file scrolling.c 
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "scrolling.h"

/**
* @brief To initialize the objecs.
* @param perso character 
* @param map first background
* @param wood character
* @param boat object in backgound
* @param map2 second backgound
* @param failed fail image
* @return Nothing
*/
void initialiser(Objet *perso,Objet *map, Objet *wood, Objet *boat, Objet *map2, Objet *failed)
{
  SDL_WM_SetCaption("scrolling", NULL);

  failed->img = IMG_Load("01.png");
  failed->pos.x = 0;
  failed->pos.y = 0;

  map2->img = IMG_Load("backgound.png");
  map2->pos.x = 1000;
  map2->pos.y = 0;
  map2->pos.h = 613;
  map2->pos.w = 1360/2;

  map->img = IMG_Load("backgound.png");
  map->pos.x = 0;
  map->pos.y = 0;
  map->pos.h = 613;
  map->pos.w = 1360/2;

  wood->img = IMG_Load("per1.png");
  wood->pos.x = xperso;
  wood->pos.y = yperso-90;

  perso->img = IMG_Load("per2.png");
  perso->pos.x = 1360/2;
  perso->pos.y = yperso-90;



  boat->img = IMG_Load("boatt.png");
  boat->pos.x = xcollision;
  boat->pos.y = ycollision;
}
/**
* @brief To display objects.
* @param screen 
* @param perso character 
* @param map first background
* @param wood character
* @param boat object in backgound
* @param map2 second backgound
* @return Nothing
*/
void setup(SDL_Surface *screen, Objet *map, Objet *wood, Objet *boat, Objet *map2, Objet *perso)
{
  SDL_Rect pos1,pos2 ;
 pos1.x=0 ;
 pos1.y=0 ;

 pos2.x=1360/2 ;
 pos2.y=0 ;


  SDL_BlitSurface(map->img,&(map->pos), screen,&pos2);
  //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

  SDL_BlitSurface(map2->img, &(map2->pos), screen,&pos1);
  SDL_BlitSurface(wood->img, NULL, screen, &(wood->pos));
  SDL_BlitSurface(perso->img, NULL, screen, &(perso->pos));
/*   if(boat->pos.x >=0)
  SDL_BlitSurface(boat->img, NULL, screen, &(boat->pos)); */
  SDL_Flip(screen);
}
/**
* @brief To display objects.
* @param screen 
* @param perso character 
* @param map first background
* @param wood character
* @param boat object in backgound
* @param map2 second backgound
* @return Nothing
*/
void affichage(SDL_Surface *screen, Objet *boat, Objet *wood, Objet *map, Objet *map2,Objet *perso)
{
   SDL_Rect pos1,pos2 ;
 pos1.x=0 ;
 pos1.y=0 ;

 pos2.x=1360/2 ;
 pos2.y=0 ;
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

  SDL_BlitSurface(map->img, &(map->pos), screen, &pos2);
  SDL_BlitSurface(map2->img, &(map2->pos), screen,&pos1);
  SDL_BlitSurface(wood->img, NULL, screen, &(wood->pos));
  SDL_BlitSurface(perso->img, NULL, screen, &(perso->pos));
/*   if(boat->pos.x >=0)
  {
SDL_BlitSurface(boat->img, NULL, screen, &(boat->pos));
  } */
  
  SDL_Flip(screen) ;
}
/**
* @brief To move background to the right.
* @param screen 
* @param map  background
* @param pod position of backgound
* @param boat object
* @return Nothing
*/
void scrolling_droit(SDL_Surface *screen, Objet *map, SDL_Rect *pos, Objet *boat)
{
  if (map->pos.x <= mapw - 1368)
  {
    map->pos.x += 20;
    boat->pos.x -= 20;
    (pos->x) += 20;
  }
}
/**
* @brief To move background to the left.
* @param screen 
* @param map  background
* @param pod position of backgound
* @param boat object
* @return Nothing
*/
void scrolling_gauche(SDL_Surface *screen, Objet *map, SDL_Rect *pos, Objet *boat)
{
  if (map->pos.x >= 20)
  {
    map->pos.x -= 20;
    boat->pos.x += 20;
    (pos->x) -= 20;
  }
}
/**
* @brief To move background right and left through events.
* @param screen 
* @param perso character 
* @param map first background
* @param wood character
* @param boat object in backgound
* @param map2 second backgound
* @return Nothing
*/
void evenement(SDL_Surface *screen, Objet *boat, Objet *wood, Objet *map, int *running, SDL_Rect *pos, Objet *map2,Objet *perso)
{
  SDL_Event event;

  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    *running = 0;
    break;
  case SDL_KEYDOWN:

    switch (event.key.keysym.sym)

    {

    case SDLK_RIGHT: // Flèche droite

      scrolling_droit(screen, map, pos, boat);
      affichage(screen, boat, wood, map, map2,perso);

      SDL_Flip(screen);

      break;

    case SDLK_LEFT: // Flèche gauche
      scrolling_gauche(screen, map, pos, boat);
      affichage(screen, boat, wood, map, map2,perso);

      SDL_Flip(screen);

      break;
    case SDLK_a: // Flèche gauche
      scrolling_gauche(screen, map2, pos, boat);
      affichage(screen, boat, wood, map, map2,perso);

      SDL_Flip(screen);

      break;
    case SDLK_z: // Flèche gauche
      scrolling_droit(screen, map2, pos, boat);
      affichage(screen, boat, wood, map, map2,perso);

      SDL_Flip(screen);

      break;
    }

    break;
  }
}
/**
* @brief To move character .
* @param objet object
* @param running  loop variable

* @return Nothing
*/
void deplacement_objet(Objet *objet, int *running)
{
  SDL_Event event;

  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    *running = 0;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case SDLK_DOWN:
      objet->pos.y += 2;
      break;
    case SDLK_UP:
      objet->pos.y -= 2;
      break;
    case SDLK_RIGHT:
      if (objet->pos.x < (1368 - objet->img->w))
        objet->pos.x += 7;
      break;
    case SDLK_LEFT:
      objet->pos.x -= 7;
      break;
    }
  }
}

void free_memory(Objet *boat, Objet *wood, Objet *map, Objet *map2)
{
  SDL_FreeSurface(boat->img);
  SDL_FreeSurface(wood->img);
  SDL_FreeSurface(map->img);
  SDL_FreeSurface(map2->img);

  SDL_Quit();
}