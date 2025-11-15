/* type d'ennemi */
typedef enum
  {
    SI_TYPE_SQUID = 1,
    SI_TYPE_CRAB,
    SI_TYPE_OCTOPUS,
  }Si_Type;

typedef struct Invaders Invaders;
typedef struct Tank Tank;
typedef struct Si Si;

struct Invaders
{
  int x;
  int y;
  int direction; /* +-1 */
  int firing; /* is fire ? */
  int bomb_x;
  int bomb_y;
};

struct Tank
{
  int x;
  int firing;
  int shoot_x;
  int shoot_y;
  int destroyed;
  int destroyed_count;
};

struct Si
{
  int window_width;
  int window_height;
  int pixel_size;
  int nbr_players;
  int score_1;
  int life_1;
  int score_2;
  int life_2;
  int score_highest;
  Tank tank;
  Invaders invaders;
};

/* crée un pointeur vers la structure Si. On passe en paramètre
 * les dimensions de la fenêtre et la taille de pixel */
Si *si_new(int window_width, int window_height, int pixel_size);

/* Détruit les ressources */
void si_del(Si *si);

/* renvoie la matrice */
char *si_get_matrix(void);

/* renvoie le nombre d’ennemis restant dans la matrice */
int si_matrix_count(void);

/* renvoie le nombre de points en fonction de l’ennemi */
int si_get_points(Si_Type t);

/* renvoie le nombre de joueurs */
int si_get_nbr_players(Si *si);


/* tank */


/* teste si le tank peut se déplacer vers le haut. SI c’est possible,
   met à jour la coordonnée y du tir du Tank.*/
int si_tank_shoot_can_move_up(Si *si);

/* renvoie 1 si le tank est touché, 0 sinon */
int si_tank_is_hit(Si *si);


/* invaders */


/* Détermine dans quelle colonnnede la matrice, choisie aléatoirement,
la bombe est lachée. Met à jour les coordonn\’ees de la bombe
dans Invaders. */
void si_invaders_get_column(Si *si);

/*
* Renvoie 1 si la bombe peut se déplacer vers le bas, 0 sinon.
* Met à jour la coordonnéee y de la bombe.
*/
int si_invaders_bomb_can_move_down(Si *si);

/*
* Renvoie 1 si les ennemis peuvent se déplacer vers la gauche, 0 sinon.
* Met à jour la position de la matrice.
*/
int si_invaders_can_move_left(Si *si);

/*
* Renvoie 1 si les ennemis peuvent se déplacer vers la droite, 0 sinon.
* Met à jour la position de la matrice.
*/
int si_invaders_can_move_right(Si *si);

/*
* Renvoie 1 si un ennemi est touché par le tir du tank, 0 sinon.
* Met à jour la matrice.
*/
int si_invader_is_hit(Si *si);
