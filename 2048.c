#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define ARR_SIZE(arr) (sizeof((arr)) / sizeof((arr[0])))

int nDigits(int i);
int shift_num(int num);

void new_game(void);
int quit_game(void);
int check_game_over(void);
int game_over(void);

void init_grid(void);

void draw_numbers(void);
void draw_score(void);
void draw_grid(void);
void draw_all(void);

void spawn_square(void);
void move_grid(int dir);
void move_over(int *a, int *b, int *c, int *d);

// VARIABLES

  /*   a  b  c  d
   * 1 a1 b1 c1 d1
   * 2 a2 b2 c2 d2
   * 3 a3 b3 c3 d3
   * 4 a4 b4 c4 d4
   */

int oa1 = -1, ob1 = -1, oc1 = -1, od1 = -1, 
    oa2 = -1, ob2 = -1, oc2 = -1, od2 = -1,
    oa3 = -1, ob3 = -1, oc3 = -1, od3 = -1,
    oa4 = -1, ob4 = -1, oc4 = -1, od4 = -1;

int a1 = 0, b1 = 0, c1 = 0, d1 = 0,
    a2 = 0, b2 = 0, c2 = 0, d2 = 0,
    a3 = 0, b3 = 0, c3 = 0, d3 = 0,
    a4 = 0, b4 = 0, c4 = 0, d4 = 0;

int WIDTH, HEIGHT;
int buffer;
int score;
int moved = 0;
int need = 1;
int started = 0;

// END VARIABLES

int main() {

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  getmaxyx(stdscr, HEIGHT, WIDTH);
  score = 0;

  unsigned int iseed = (unsigned int)time(NULL);
  srand(iseed);

  if(WIDTH < 35 || HEIGHT < 18) { endwin();
    printf("Please resize your terminal so that it is at least 25x17\n");
    return 0; }

  if(WIDTH < 57) { buffer = 0; }
  else { buffer = 32; }

  started = 0;
  new_game();
  started = 1;

  int c;

  while(1) {
    if(check_game_over()) {
      if(game_over()){ endwin(); return 0; }
      else { new_game(); started = 0; }
    }
    c = getch();
    moved = 0;
    switch(c) {
      case KEY_UP:
        move_grid(0);
        break;
      case 'k':
        move_grid(0);
        break;
      case 'w':
        move_grid(0);
        break;

      case KEY_DOWN:
        move_grid(1);
        break;
      case 'j':
        move_grid(1);
        break;
      case 's':
        move_grid(1);
        break;

      case KEY_LEFT:
        move_grid(2);
        break;
      case 'h':
        move_grid(2);
        break;
      case 'a':
        move_grid(2);
        break;
     
      case KEY_RIGHT:
        move_grid(3);
        break;
      case 'l':
        move_grid(3);
        break;
      case 'd':
        move_grid(3);
        break;
     
       case 'n':
        new_game();
        break;
      case 'q':
        if(quit_game()) {
	  endwin();
	  //printf("%d %d %d %d \n%d %d %d %d \n%d %d %d %d \n%d %d %d %d\n\n%d %d %d %d \n%d %d %d %d \n%d %d %d %d \n%d %d %d %d\n", oa1, ob1, oc1, od1, oa2, ob2, oc2, od2, oa3, ob3, oc3, od3, oa4, ob4, oc4, od4, a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3, a4, b4, c4, d4);
	  return 0;
	}
        break;
    }
    draw_all();
    refresh();
    sleep(0.5);
  }
  endwin();
  return 0;
}

int nDigits(int i) {
  if (i < 0) i = -i;
  if (i == 0) return 0;
  if (i <         10) return 1;
  if (i <        100) return 2;
  if (i <       1000) return 3;
  if (i <      10000) return 4;
  if (i <     100000) return 5;
  if (i <    1000000) return 6;
  if (i <   10000000) return 7;
  if (i <  100000000) return 8;
  if (i < 1000000000) return 9;
  return 10;
}

int shift_num(int num) {
  switch (nDigits(num)) {
  case 0:
    return 0;
    break;
  case 1:
    return 2;
    break;
  case 2:
    return 2;
    break;
  case 3:
    return 1;
    break;
  case 4:
    return 1;
    break;
  case 5:
    return 0;
    break;
  }
}

void new_game() {
  int c;
  if(started) {
    mvprintw(17, 1, "Start a new game? [y/N]");
    c = getch();
      if(c == 'y') { mvprintw(17, 1, "                       "); }
      else { mvprintw(17, 1, "                       "); return; }
  }
  a1 = 0, b1 = 0, c1 = 0, d1 = 0, \
  a2 = 0, b2 = 0, c2 = 0, d2 = 0, \
  a3 = 0, b3 = 0, c3 = 0, d3 = 0, \
  a4 = 0, b4 = 0, c4 = 0, d4 = 0;
  score = 0;

  init_grid();
  draw_all();
  refresh();
}

int quit_game() {
  int c;
  mvprintw(17, 1, "Really quit? [y/N]");
  c = getch();
  if(c == 'y') { mvprintw(17, 1, "                  "); return 1; }
  else { mvprintw(17, 1, "                  "); return 0; }
}

int check_game_over() {
  if( !a1 || !a2 || !a3 || !a4 || \
      !b1 || !b2 || !b3 || !b4 || \
      !c1 || !c2 || !c3 || !c4 || \
      !d1 || !d2 || !d3 || !d4 ) { return 0; }
  else {
    if( a1 == b1 || b1 == c1 || c1 == d1 || \
	a2 == b2 || b2 == c2 || c2 == d2 || \
	a3 == b3 || b3 == c3 || c3 == d3 || \
	a4 == b4 || b4 == c4 || c4 == d4 || \
					    \
	a1 == a2 || a2 == a3 || a3 == a4 || \
	b1 == b2 || b2 == b3 || b3 == b4 || \
	c1 == c2 || c2 == c3 || c3 == c4 || \
	d1 == d2 || d2 == d3 || d3 == d4) { return 0; }
    else { return 1; }
  }
}

int game_over() {
  int c;
  while(1) {
    mvprintw(17, 1, "Game over! New game or quit? [n/q]");
    c = getch();
    if(c == 'n') { mvprintw(17, 1, "                                  ");
      started = 0; return 0; }
    else if(c == 'q') { return 1; }
  }
}

void draw_grid() {
  // Total width: 57 (32 + grid(25))
  // Grid width: 25
  mvprintw(4,  buffer, "+-----+-----+-----+-----+");
  mvprintw(5,  buffer, "|     |     |     |     |");
  mvprintw(6,  buffer, "|     |     |     |     |");
  mvprintw(7,  buffer, "+-----+-----+-----+-----+");
  mvprintw(8,  buffer, "|     |     |     |     |");
  mvprintw(9,  buffer, "|     |     |     |     |");
  mvprintw(10, buffer, "+-----+-----+-----+-----+");
  mvprintw(11, buffer, "|     |     |     |     |");
  mvprintw(12, buffer, "|     |     |     |     |");
  mvprintw(13, buffer, "+-----+-----+-----+-----+");
  mvprintw(14, buffer, "|     |     |     |     |");
  mvprintw(15, buffer, "|     |     |     |     |");
  mvprintw(16, buffer, "+-----+-----+-----+-----+");
}

void init_grid() {
  spawn_square();
  spawn_square();
}

void draw_numbers() {
  // Show a1
  if(a1) { mvprintw(5,  buffer+1+shift_num(a1), "%d", a1); }
  // Show a2
  if(a2) { mvprintw(8,  buffer+1+shift_num(a2), "%d", a2); }
  // Show a3
  if(a3) { mvprintw(11, buffer+1+shift_num(a3), "%d", a3); }
  // Show a4
  if(a4) { mvprintw(14, buffer+1+shift_num(a4), "%d", a4); }

  // Show b1
  if(b1) { mvprintw(5,  buffer+7+shift_num(b1), "%d", b1); }
  // Show b2
  if(b2) { mvprintw(8,  buffer+7+shift_num(b2), "%d", b2); }
  // Show b3
  if(b3) { mvprintw(11, buffer+7+shift_num(b3), "%d", b3); }
  // Show b4
  if(b4) { mvprintw(14, buffer+7+shift_num(b4), "%d", b4); }

  // Show c1
  if(c1) { mvprintw(5,  buffer+13+shift_num(c1), "%d", c1); }
  // Show c2
  if(c2) { mvprintw(8,  buffer+13+shift_num(c2), "%d", c2); }
  // Show c3
  if(c3) { mvprintw(11, buffer+13+shift_num(c3), "%d", c3); }
  // Show c4
  if(c4) { mvprintw(14, buffer+13+shift_num(c4), "%d", c4); }

  // Show d1
  if(d1) { mvprintw(5,  buffer+19+shift_num(d1), "%d", d1); }
  // Show d2
  if(d2) { mvprintw(8,  buffer+19+shift_num(d2), "%d", d2); }
  // Show d3
  if(d3) { mvprintw(11, buffer+19+shift_num(d3), "%d", d3); }
  // Show d4
  if(d4) { mvprintw(14, buffer+19+shift_num(d4), "%d", d4); }
}

void draw_score() {
  mvprintw(1, 4, "                           ");
  mvprintw(1, 4, "Score: %d", score);
}

void draw_all() {
  draw_score();
  draw_grid();
  draw_numbers();
  mvprintw(17, 0, " ");
}

void spawn_square() {
  if(a1 != oa1 || a2 != oa2 || a3 != oa3 || a4 != oa4 || \
     b1 != ob1 || b2 != ob2 || b3 != ob3 || b4 != ob4 || \
     c1 != oc1 || c2 != oc2 || c3 != oc3 || c4 != oc4 || \
     d1 != od1 || d2 != od2 || d3 != od3 || d4 != od4) {
    
    int azero = 0;
    if(!a1){azero++;}
    if(!a2){azero++;}
    if(!a3){azero++;}
    if(!a4){azero++;}
    if(!b1){azero++;}
    if(!b2){azero++;}
    if(!b3){azero++;}
    if(!b4){azero++;}
    if(!c1){azero++;}
    if(!c2){azero++;}
    if(!c3){azero++;}
    if(!c4){azero++;}
    if(!d1){azero++;}
    if(!d2){azero++;}
    if(!d3){azero++;}
    if(!d4){azero++;}

    int *zero[azero];
    int ct = 0;
    if(!a1){zero[ct] = &a1; ct++;}
    if(!a2){zero[ct] = &a2; ct++;}
    if(!a3){zero[ct] = &a3; ct++;}
    if(!a4){zero[ct] = &a4; ct++;}
    if(!b1){zero[ct] = &b1; ct++;}
    if(!b2){zero[ct] = &b2; ct++;}
    if(!b3){zero[ct] = &b3; ct++;}
    if(!b4){zero[ct] = &b4; ct++;}
    if(!c1){zero[ct] = &c1; ct++;}
    if(!c2){zero[ct] = &c2; ct++;}
    if(!c3){zero[ct] = &c3; ct++;}
    if(!c4){zero[ct] = &c4; ct++;}
    if(!d1){zero[ct] = &d1; ct++;}
    if(!d2){zero[ct] = &d2; ct++;}
    if(!d3){zero[ct] = &d3; ct++;}
    if(!d4){zero[ct] = &d4; ct++;}

    *zero[rand() % ARR_SIZE(zero)] = ((rand() % 2)+1)*2;
  }
}

void move_grid(int dir) {
  oa1 = a1;
  oa2 = a2;
  oa3 = a3;
  oa4 = a4;
  ob1 = b1;
  ob2 = b2;
  ob3 = b3;
  ob4 = b4;
  oc1 = c1;
  oc2 = c2;
  oc3 = c3;
  oc4 = c4;
  od1 = d1;
  od2 = d2;
  od3 = d3;
  od4 = d4;

  switch(dir) {
    case 0: // Up
      move_over(&a4, &a3, &a2, &a1);
      move_over(&b4, &b3, &b2, &b1);
      move_over(&c4, &c3, &c2, &c1);
      move_over(&d4, &d3, &d2, &d1);
      break;
    case 1: // Down
      move_over(&d1, &d2, &d3, &d4);
      move_over(&c1, &c2, &c3, &c4);
      move_over(&b1, &b2, &b3, &b4);
      move_over(&a1, &a2, &a3, &a4);
      break;
    case 2: // Left
      move_over(&d1, &c1, &b1, &a1);
      move_over(&d2, &c2, &b2, &a2);
      move_over(&d3, &c3, &b3, &a3);
      move_over(&d4, &c4, &b4, &a4);
      break;
    case 3: // Right
      move_over(&a1, &b1, &c1, &d1);
      move_over(&a2, &b2, &c2, &d2);
      move_over(&a3, &b3, &c3, &d3);
      move_over(&a4, &b4, &c4, &d4);
      break;
  }
  spawn_square();
}

void move_over(int *a, int *b, int *c, int *d) {
  need = 1;
  while(need) { need = 0;
    if(*d == 0 && *c) { *d = *c; *c = 0; need = 1; }
    if(*c == 0 && *b) { *c = *b; *b = 0; need = 1; }
    if(*b == 0 && *a) { *b = *a; *a = 0; need = 1; } }
  if(*d == *c && *d && *c) { *d = *d + *c; score += *d; *c = 0; }
  if(*c == *b && *c && *b) { *c = *c + *b; score += *c; *b = 0; }
  if(*b == *a && *b && *a) { *b = *b + *a; score += *b; *a = 0; }
  need = 1;
  while(need) { need = 0;
    if(*d == 0 && *c) { *d = *c; *c = 0; need = 1; }
    if(*c == 0 && *b) { *c = *b; *b = 0; need = 1; }
    if(*b == 0 && *a) { *b = *a; *a = 0; need = 1; }
  }
}
