#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;

//stage
char stage[24][71] = {
{"#####################################################################"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||    X        X                                     X       X      ||"},
{"||        @        @                         @         @            ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                                                  ||"},
{"||                                 ^                                ||"},
{"||                                 A                                ||"}, 
{"#####################################################################"}};

//functions
 
void printstage();
void gotoxy(int, int);
void left();
void right();
void shoot();
void projectileleft();
void projectileright();
void enemyshooting(); //bullets affecting the player movement and shooting mechanics  
void boss();
void moveupperenemies();
void load();   //loading the stage
void store();  //storing the updated stage

//files
fstream loadstage, storestage;

//coordinates
bool gamerunning = true;
int enemyprojectilex[100];
int enemyprojectiley[100];
int spaceshipy = 35;
int spaceshipx = 22;
int projectiley = 35;
int projectilex = 21;

//upper oscillating enemies coordinates 
int enemy29y = 4;
int enemy29x = 1;
int enemy30y = 12;
int enemy30x = 1;
int enemy31y = 30;
int enemy31x = 1;
int enemy32y = 46;
int enemy32x = 1;
int enemy33y = 55;
int enemy33x = 1;

//lower shooting enemies coordinates
int enemy34y = 10;
int enemy34x = 14;
int enemy35y = 19;
int enemy35x = 14;
int enemy36y = 45;
int enemy36x = 14;
int enemy37y = 55;
int enemy37x = 14;

//boss components coordinates
int enemy38y = 27;
int enemy38x = 3;
int enemy39y = 37;
int enemy39x = 3;
int enemy40y = 28;
int enemy40x = 4;
int enemy41y = 30;
int enemy41x = 4;
int enemy42y = 32;
int enemy42x = 4;
int enemy43y = 34;
int enemy43x = 4;
int enemy44y = 36;
int enemy44x = 4;
int enemy45y = 28;
int enemy45x = 5;
int enemy46y = 32;
int enemy46x = 5;
int enemy47y = 36;
int enemy47x = 5;
int enemy48y = 28;
int enemy48x = 6;
int enemy49y = 32;
int enemy49x = 6;
int enemy50y = 36;
int enemy50x = 6;
int enemy51y = 32;
int enemy51x = 7;

int rng;
int lives = 3;
int score = 0;

int main() {
  system("cls");
  system("color 40"); //setting the color to red
  load();
  printstage();
  gotoxy(spaceshipy, spaceshipx);
  cout << "A";

    while (gamerunning) {
    srand(time(0));
    Sleep(5);
    moveupperenemies();
    boss();
    enemyshooting();
    store();

    if (GetAsyncKeyState(VK_LEFT)) { //players movements 

      if (GetAsyncKeyState(VK_SPACE)) {
        shoot();
      }

      left();
      projectileleft();
    } else if (GetAsyncKeyState(VK_RIGHT)) {

      if (GetAsyncKeyState(VK_SPACE)) {
        shoot();
      }

      right();
      projectileright();
    } else if (GetAsyncKeyState(VK_SPACE)) {
      shoot();
    } else if (GetAsyncKeyState(VK_ESCAPE)) {
      gamerunning = false;
      cout << "Game over,Your Score :" << score << endl;
      cout << "Your lives : 3/" << lives;

    } else if (lives <= 0) {
      gamerunning = false;
      cout << "Game over,Your Score :" << score << endl;
      cout << "Your lives : 3/" << lives;
    }

  }

}

void printstage() {  //prints the stage

  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 71; j++) {
    cout << stage[i][j];
    }
    cout << endl;
  }

}

void left() {

  if (stage[spaceshipx][spaceshipy - 1] == ' ') {
    stage[spaceshipx][spaceshipy] = ' ';
    gotoxy(spaceshipy, spaceshipx);
    cout << " ";
    spaceshipy = spaceshipy - 1;
    gotoxy(spaceshipy, spaceshipx);
    cout << "A";
  }

}

void right() {
  if (stage[spaceshipx][spaceshipy + 1] == ' ') {

    stage[spaceshipx][spaceshipy] = ' ';
    gotoxy(spaceshipy, spaceshipx);
    cout << " ";
    spaceshipy = spaceshipy + 1;
    gotoxy(spaceshipy, spaceshipx);
    cout << "A";
  }

}

void shoot() {

  int bullet = spaceshipx - 2;
  int bulletdirection = spaceshipy;
  stage[bullet][bulletdirection] = '|';
  gotoxy(bulletdirection, bullet);
  cout << "|";

  while (stage[bullet][bulletdirection] != '#') {  //shooting process
    Sleep(15);
    stage[bullet][bulletdirection] = ' ';
    gotoxy(bulletdirection, bullet);
    cout << " ";
    bullet--;
    if (stage[bullet][bulletdirection] == ' ') {
      stage[bullet][bulletdirection] = '|';
      gotoxy(bulletdirection, bullet);
      cout << "|";
    } else if (stage[bullet][bulletdirection] == '@' || stage[bullet][bulletdirection] == 'X' || stage[bullet][bulletdirection] == '0' || stage[bullet][bulletdirection] == '$' || stage[bullet][bulletdirection] == '%' || stage[bullet][bulletdirection] == '*' || stage[bullet][bulletdirection] == '|') {
      stage[bullet][bulletdirection] = '|';
      gotoxy(bulletdirection, bullet);
      cout << "|";
      score = score + 10;
	  gotoxy(80,12);
	  cout<<"Score :"<<score<<endl;
    }

  }

}

void gotoxy(int x, int y) {
  COORD coordinates;
  coordinates.X = x;
  coordinates.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void projectileleft() {
  if (stage[projectilex][projectiley - 1] == ' ') {
    stage[projectilex][projectiley] = ' ';
    gotoxy(projectiley, projectilex);
    cout << " ";
    projectiley = projectiley - 1;
    gotoxy(projectiley, projectilex);
    cout << "^";
  }
}
 
void projectileright() {  //moving the projectile with the space ship
  if (stage[projectilex][projectiley + 1] == ' ') {
    stage[projectilex][projectiley] = ' ';
    gotoxy(projectiley, projectilex);
    cout << " ";
    projectiley = projectiley + 1;
    gotoxy(projectiley, projectilex);
    cout << "^";
  }
}

void moveupperenemies() {
  rng = rand() % 4 + 1;   //using rng generator to determine the enemies movements 
  Sleep(20);

  if (rng == 1) {

    if (stage[enemy29x][enemy29y - 1] == ' ') {
      stage[enemy29x][enemy29y] = ' ';
      gotoxy(enemy29y, enemy29x);
      cout << " ";
      enemy29y--;
      stage[enemy29x][enemy29y] = '0';
      gotoxy(enemy29y, enemy29x);
      cout << "0";
    }

    if (stage[enemy30x][enemy30y - 1] == ' ') {
      stage[enemy30x][enemy30y] = ' ';
      gotoxy(enemy30y, enemy30x);
      cout << " ";
      enemy30y--;
      stage[enemy30x][enemy30y] = '0';
      gotoxy(enemy30y, enemy30x);
      cout << "0";
    }

    if (stage[enemy31x][enemy31y - 1] == ' ') {
      stage[enemy31x][enemy31y] = ' ';
      gotoxy(enemy31y, enemy31x);
      cout << " ";
      enemy31y--;
      stage[enemy31x][enemy31y] = '0';
      gotoxy(enemy31y, enemy31x);
      cout << "0";
    }

    if (stage[enemy32x][enemy32y - 1] == ' ') {
      stage[enemy32x][enemy32y] = ' ';
      gotoxy(enemy32y, enemy32x);
      cout << " ";
      enemy32y--;
      stage[enemy32x][enemy32y] = '0';
      gotoxy(enemy32y, enemy32x);
      cout << "0";
    }

    if (stage[enemy33x][enemy33y - 1] == ' ') {
      stage[enemy33x][enemy33y] = ' ';
      gotoxy(enemy33y, enemy33x);
      cout << " ";
      enemy33y--;
      stage[enemy33x][enemy33y] = '0';
      gotoxy(enemy33y, enemy33x);
      cout << "0";
    }

  } else if (rng == 2) {

    if (stage[enemy29x][enemy29y + 1] == ' ') {
      stage[enemy29x][enemy29y] = ' ';
      gotoxy(enemy29y, enemy29x);
      cout << " ";
      enemy29y++;
      stage[enemy29x][enemy29y] = '0';
      gotoxy(enemy29y, enemy29x);
      cout << "0";
    }

    if (stage[enemy30x][enemy30y + 1] == ' ') {
      stage[enemy30x][enemy30y] = ' ';
      gotoxy(enemy30y, enemy30x);
      cout << " ";
      enemy30y++;
      stage[enemy30x][enemy30y] = '0';
      gotoxy(enemy30y, enemy30x);
      cout << "0";
    }

    if (stage[enemy31x][enemy31y + 1] == ' ') {
      stage[enemy31x][enemy31y] = ' ';
      gotoxy(enemy31y, enemy31x);
      cout << " ";
      enemy31y++;
      stage[enemy31x][enemy31y] = '0';
      gotoxy(enemy31y, enemy31x);
      cout << "0";
    }

    if (stage[enemy32x][enemy32y + 1] == ' ') {
      stage[enemy32x][enemy32y] = ' ';
      gotoxy(enemy32y, enemy32x);
      cout << " ";
      enemy32y++;
      stage[enemy32x][enemy32y] = '0';
      gotoxy(enemy32y, enemy32x);
      cout << "0";
    }

    if (stage[enemy33x][enemy33y + 1] == ' ') {
      stage[enemy33x][enemy33y] = ' ';
      gotoxy(enemy33y, enemy33x);
      cout << " ";
      enemy33y++;
      stage[enemy33x][enemy33y] = '0';
      gotoxy(enemy33y, enemy33x);
      cout << "0";
    }

  }
}

void enemyshooting() {
  rng = rand() % 6 + 1;  //using rng generator to determine which enemies shoot  
  Sleep(20);

  if (rng == 1) {
    Sleep(20);
    enemyprojectilex[2] = enemy35x + 1;
    enemyprojectiley[2] = enemy35y;
    stage[enemyprojectilex[2]][enemyprojectiley[2]] = '*';
    gotoxy(enemyprojectiley[2], enemyprojectilex[2]);
    cout << "*";
    while (stage[enemyprojectilex[2]][enemyprojectiley[2]] != '#') {
      Sleep(20);
      stage[enemyprojectilex[2]][enemyprojectiley[2]] = ' ';
      gotoxy(enemyprojectiley[2], enemyprojectilex[2]);
      cout << " ";
      enemyprojectilex[2]++;
      if (stage[enemyprojectilex[2]][enemyprojectiley[2]] == ' ') {
        stage[enemyprojectilex[2]][enemyprojectiley[2]] = '*';
        gotoxy(enemyprojectiley[2], enemyprojectilex[2]);
        cout << "*";
      } else if (stage[enemyprojectilex[2]][enemyprojectiley[2]] == 'A' || stage[enemyprojectilex[2]][enemyprojectiley[2]] == '^') {
        lives = lives - 1;
      }
    }

    Sleep(20);
    enemyprojectilex[3] = enemy34x + 1;
    enemyprojectiley[3] = enemy34y;
    stage[enemyprojectilex[3]][enemyprojectiley[3]] = '*';
    gotoxy(enemyprojectiley[3], enemyprojectilex[3]);
    cout << "*";
    while (stage[enemyprojectilex[3]][enemyprojectiley[3]] != '#') {
      Sleep(20);
      stage[enemyprojectilex[3]][enemyprojectiley[3]] = ' ';
      gotoxy(enemyprojectiley[3], enemyprojectilex[3]);
      cout << " ";
      enemyprojectilex[3]++;
      if (stage[enemyprojectilex[3]][enemyprojectiley[3]] == ' ') {
        stage[enemyprojectilex[3]][enemyprojectiley[3]] = '*';
        gotoxy(enemyprojectiley[3], enemyprojectilex[3]);
        cout << "*";
      } else if (stage[enemyprojectilex[3]][enemyprojectiley[3]] == 'A' || stage[enemyprojectilex[3]][enemyprojectiley[3]] == '^') {
        lives = lives - 1;
      }
    }

  } else if (rng == 2) {
    Sleep(20);
    enemyprojectilex[4] = enemy36x + 1;
    enemyprojectiley[4] = enemy36y;
    stage[enemyprojectilex[4]][enemyprojectiley[4]] = '|';
    gotoxy(enemyprojectiley[4], enemyprojectilex[4]);
    cout << "|";
    while (stage[enemyprojectilex[4]][enemyprojectiley[4]] != '#') {
      Sleep(20);
      stage[enemyprojectilex[4]][enemyprojectiley[4]] = ' ';
      gotoxy(enemyprojectiley[4], enemyprojectilex[4]);
      cout << " ";
      enemyprojectilex[4]++;
      if (stage[enemyprojectilex[4]][enemyprojectiley[4]] == ' ') {
        stage[enemyprojectilex[4]][enemyprojectiley[4]] = '|';
        gotoxy(enemyprojectiley[4], enemyprojectilex[4]);
        cout << "|";
      } else if (stage[enemyprojectilex[4]][enemyprojectiley[4]] == 'A' || stage[enemyprojectilex[4]][enemyprojectiley[4]] == '^') {
        lives = lives - 1;
      }
    }

    Sleep(20);
    enemyprojectilex[5] = enemy37x + 1;
    enemyprojectiley[5] = enemy37y;
    stage[enemyprojectilex[5]][enemyprojectiley[5]] = '|';
    gotoxy(enemyprojectiley[5], enemyprojectilex[5]);
    cout << "|";
    while (stage[enemyprojectilex[5]][enemyprojectiley[5]] != '#') {
      Sleep(20);
      stage[enemyprojectilex[5]][enemyprojectiley[5]] = ' ';
      gotoxy(enemyprojectiley[5], enemyprojectilex[5]);
      cout << " ";
      enemyprojectilex[5]++;
      if (stage[enemyprojectilex[5]][enemyprojectiley[5]] == ' ') {
        stage[enemyprojectilex[5]][enemyprojectiley[5]] = '|';
        gotoxy(enemyprojectiley[5], enemyprojectilex[5]);
        cout << "|";
      } else if (stage[enemyprojectilex[5]][enemyprojectiley[5]] == 'A' || stage[enemyprojectilex[5]][enemyprojectiley[5]] == '^') {
        lives = lives - 1;
      }
    }

  }
}

void boss() {
  rng = rand() % 4 + 1;  //using rng generator to shoot and oscillate the tip of the mouth of the enemy boss
  Sleep(20);   

  if (rng == 1) {

    stage[enemy38x][enemy38y] = ' ';   //moving all parts of the enemy boss 
    gotoxy(enemy38y, enemy38x);
    cout << " ";
    enemy38y--;
    if (stage[enemy38x][enemy38y] == ' ') {
      stage[enemy30x][enemy38y] = '%';
      gotoxy(enemy38y, enemy38x);
      cout << "%";
    }

    stage[enemy39x][enemy39y] = ' ';
    gotoxy(enemy39y, enemy39x);
    cout << " ";
    enemy39y--;
    if (stage[enemy39x][enemy39y] == ' ') {
      stage[enemy39x][enemy39y] = '%';
      gotoxy(enemy39y, enemy39x);
      cout << "%";
    }

    stage[enemy40x][enemy40y] = ' ';
    gotoxy(enemy40y, enemy40x);
    cout << " ";
    enemy40y--;
    if (stage[enemy40x][enemy40y] == ' ') {
      stage[enemy40x][enemy40y] = '%';
      gotoxy(enemy40y, enemy40x);
      cout << "%";
    }

    stage[enemy41x][enemy41y] = ' ';
    gotoxy(enemy41y, enemy41x);
    cout << " ";
    enemy41y--;
    if (stage[enemy41x][enemy41y] == ' ') {
      stage[enemy41x][enemy41y] = '*';
      gotoxy(enemy41y, enemy41x);
      cout << "*";
    }

    stage[enemy42x][enemy42y] = ' ';
    gotoxy(enemy42y, enemy42x);
    cout << " ";
    enemy42y--;
    if (stage[enemy42x][enemy42y] == ' ') {
      stage[enemy42x][enemy42y] = '*';
      gotoxy(enemy42y, enemy42x);
      cout << "*";
    }

    stage[enemy43x][enemy43y] = ' ';
    gotoxy(enemy43y, enemy43x);
    cout << " ";
    enemy43y--;
    if (stage[enemy43x][enemy43y] == ' ') {
      stage[enemy43x][enemy43y] = '*';
      gotoxy(enemy43y, enemy43x);
      cout << "*";
    }

    stage[enemy44x][enemy44y] = ' ';
    gotoxy(enemy44y, enemy44x);
    cout << " ";
    enemy44y--;
    if (stage[enemy44x][enemy44y] == ' ') {
      stage[enemy44x][enemy44y] = '%';
      gotoxy(enemy44y, enemy44x);
      cout << "%";
    }

    stage[enemy45x][enemy45y] = ' ';
    gotoxy(enemy45y, enemy45x);
    cout << " ";
    enemy45y--;
    if (stage[enemy45x][enemy45y] == ' ') {
      stage[enemy45x][enemy45y] = '0';
      gotoxy(enemy45y, enemy45x);
      cout << "0";
    }

    stage[enemy46x][enemy46y] = ' ';
    gotoxy(enemy46y, enemy46x);
    cout << " ";
    enemy46y--;
    if (stage[enemy46x][enemy46y] == ' ') {
      stage[enemy46x][enemy46y] = '|';
      gotoxy(enemy46y, enemy46x);
      cout << "|";
    }

    stage[enemy47x][enemy47y] = ' ';
    gotoxy(enemy47y, enemy47x);
    cout << " ";
    enemy47y--;
    if (stage[enemy47x][enemy47y] == ' ') {
      stage[enemy47x][enemy47y] = '0';
      gotoxy(enemy47y, enemy47x);
      cout << "0";
    }

    stage[enemy48x][enemy48y] = ' ';
    gotoxy(enemy48y, enemy48x);
    cout << " ";
    enemy48y--;
    if (stage[enemy48x][enemy48y] == ' ') {
      stage[enemy48x][enemy48y] = '$';
      gotoxy(enemy48y, enemy48x);
      cout << "$";
    }

    stage[enemy49x][enemy49y] = ' ';
    gotoxy(enemy49y, enemy49x);
    cout << " ";
    enemy49y--;
    if (stage[enemy49x][enemy49y] == ' ') {
      stage[enemy49x][enemy49y] = '*';
      gotoxy(enemy49y, enemy49x);
      cout << "*";
    }

    stage[enemy50x][enemy50y] = ' ';
    gotoxy(enemy50y, enemy50x);
    cout << " ";
    enemy50y--;
    if (stage[enemy50x][enemy50y] == ' ') {
      stage[enemy50x][enemy50y] = '%';
      gotoxy(enemy50y, enemy50x);
      cout << "%";
    }

    stage[enemy51x][enemy51y] = ' ';
    gotoxy(enemy51y, enemy51x);
    cout << " ";
    enemy51y--;
    if (stage[enemy51x][enemy51y] == ' ') {
      stage[enemy51x][enemy51y] = '|';
      gotoxy(enemy51y, enemy51x);
      cout << "|";
    }

    Sleep(20);
    enemyprojectilex[0] = enemy51x + 1;
    enemyprojectiley[0] = enemy51y;
    stage[enemyprojectilex[0]][enemyprojectiley[0]] = '|';   //shooting from the tip of the mouth
    gotoxy(enemyprojectiley[0], enemyprojectilex[0]);
    cout << "|";
    while (stage[enemyprojectilex[0]][enemyprojectiley[0]] != '#') {
      Sleep(20);
      stage[enemyprojectilex[0]][enemyprojectiley[0]] = ' ';
      gotoxy(enemyprojectiley[0], enemyprojectilex[0]);
      cout << " ";
      enemyprojectilex[0]++;
      if (stage[enemyprojectilex[0]][enemyprojectiley[0]] == ' ') {
        stage[enemyprojectilex[0]][enemyprojectiley[0]] = '|';
        gotoxy(enemyprojectiley[0], enemyprojectilex[0]);
        cout << "|";
      } else if (stage[enemyprojectilex[0]][enemyprojectiley[0]] == 'A') {
        lives = lives - 1;
      }

    }

  } else if (rng == 2) {

    stage[enemy38x][enemy38y] = ' ';   //moving all the parts of the enemy boss in opposite direction
    gotoxy(enemy38y, enemy38x);    
    cout << " ";
    enemy38y++;
    if (stage[enemy38x][enemy38y] == ' ') {
      stage[enemy30x][enemy38y] = '%';
      gotoxy(enemy38y, enemy38x);
      cout << "%";
    }

    stage[enemy39x][enemy39y] = ' ';
    gotoxy(enemy39y, enemy39x);
    cout << " ";
    enemy39y++;
    if (stage[enemy39x][enemy39y] == ' ') {
      stage[enemy39x][enemy39y] = '%';
      gotoxy(enemy39y, enemy39x);
      cout << "%";
    }

    stage[enemy40x][enemy40y] = ' ';
    gotoxy(enemy40y, enemy40x);
    cout << " ";
    enemy40y++;
    if (stage[enemy40x][enemy40y] == ' ') {
      stage[enemy40x][enemy40y] = '%';
      gotoxy(enemy40y, enemy40x);
      cout << "%";
    }

    stage[enemy41x][enemy41y] = ' ';
    gotoxy(enemy41y, enemy41x);
    cout << " ";
    enemy41y++;
    if (stage[enemy41x][enemy41y] == ' ') {
      stage[enemy41x][enemy41y] = '*';
      gotoxy(enemy41y, enemy41x);
      cout << "*";
    }

    stage[enemy42x][enemy42y] = ' ';
    gotoxy(enemy42y, enemy42x);
    cout << " ";
    enemy42y++;
    if (stage[enemy42x][enemy42y] == ' ') {
      stage[enemy42x][enemy42y] = '*';
      gotoxy(enemy42y, enemy42x);
      cout << "*";
    }

    stage[enemy43x][enemy43y] = ' ';
    gotoxy(enemy43y, enemy43x);
    cout << " ";
    enemy43y++;
    if (stage[enemy43x][enemy43y] == ' ') {
      stage[enemy43x][enemy43y] = '*';
      gotoxy(enemy43y, enemy43x);
      cout << "*";
    }

    stage[enemy44x][enemy44y] = ' ';
    gotoxy(enemy44y, enemy44x);
    cout << " ";
    enemy44y++;
    if (stage[enemy44x][enemy44y] == ' ') {
      stage[enemy44x][enemy44y] = '%';
      gotoxy(enemy44y, enemy44x);
      cout << "%";
    }

    stage[enemy45x][enemy45y] = ' ';
    gotoxy(enemy45y, enemy45x);
    cout << " ";
    enemy45y++;
    if (stage[enemy45x][enemy45y] == ' ') {
      stage[enemy45x][enemy45y] = '0';
      gotoxy(enemy45y, enemy45x);
      cout << "0";
    }

    stage[enemy46x][enemy46y] = ' ';
    gotoxy(enemy46y, enemy46x);
    cout << " ";
    enemy46y++;
    if (stage[enemy46x][enemy46y] == ' ') {
      stage[enemy46x][enemy46y] = '|';
      gotoxy(enemy46y, enemy46x);
      cout << "|";
    }

    stage[enemy47x][enemy47y] = ' ';
    gotoxy(enemy47y, enemy47x);
    cout << " ";
    enemy47y++;
    if (stage[enemy47x][enemy47y] == ' ') {
      stage[enemy47x][enemy47y] = '0';
      gotoxy(enemy47y, enemy47x);
      cout << "0";
    }

    stage[enemy48x][enemy48y] = ' ';
    gotoxy(enemy48y, enemy48x);
    cout << " ";
    enemy48y++;
    if (stage[enemy48x][enemy48y] == ' ') {
      stage[enemy48x][enemy48y] = '$';
      gotoxy(enemy48y, enemy48x);
      cout << "$";
    }

    stage[enemy49x][enemy49y] = ' ';
    gotoxy(enemy49y, enemy49x);
    cout << " ";
    enemy49y++;
    if (stage[enemy49x][enemy49y] == ' ') {
      stage[enemy49x][enemy49y] = '*';
      gotoxy(enemy49y, enemy49x);
      cout << "*";
    }

    stage[enemy50x][enemy50y] = ' ';
    gotoxy(enemy50y, enemy50x);
    cout << " ";
    enemy50y++;
    if (stage[enemy50x][enemy50y] == ' ') {
      stage[enemy50x][enemy50y] = '%';
      gotoxy(enemy50y, enemy50x);
      cout << "%";
    }

    stage[enemy51x][enemy51y] = ' ';
    gotoxy(enemy51y, enemy51x);
    cout << " ";
    enemy51y++;
    if (stage[enemy51x][enemy51y] == ' ') {
      stage[enemy51x][enemy51y] = '|';
      gotoxy(enemy51y, enemy51x);
      cout << "|";
    }

    Sleep(20);
    enemyprojectilex[1] = enemy51x + 1;
    enemyprojectiley[1] = enemy51y;
    stage[enemyprojectilex[1]][enemyprojectiley[1]] = '*';
    gotoxy(enemyprojectiley[1], enemyprojectilex[1]);
    cout << "*";
    while (stage[enemyprojectilex[1]][enemyprojectiley[1]] != '#') {    //enemy boss shooting
      Sleep(20);
      stage[enemyprojectilex[1]][enemyprojectiley[1]] = ' ';
      gotoxy(enemyprojectiley[1], enemyprojectilex[1]);
      cout << " ";
      enemyprojectilex[1]++;
      if (stage[enemyprojectilex[1]][enemyprojectiley[1]] == ' ') {
        stage[enemyprojectilex[1]][enemyprojectiley[1]] = '*';
        gotoxy(enemyprojectiley[1], enemyprojectilex[1]);
        cout << "*";
      } else if (stage[enemyprojectilex[1]][enemyprojectiley[1]] == 'A' || stage[enemyprojectilex[1]][enemyprojectiley[1]] == '^') {
        lives = lives - 1;
      }

    }

  }
}

void load() {   //loading the stage from the file

  loadstage.open("stage.txt", ios:: in );
  string line;
  int row = 0;
  while (!loadstage.eof()) {
    getline(loadstage, line);
    for (int col = 0; col < 71; col++) {
      stage[row][col] = line[col];
    }
    row++;
  }
  loadstage.close();
}

void store() {   //storing the update stage in the file 

  storestage.open("store.txt", ios::out);
  for (int row = 0; row < 24; row++) {
    for (int col = 0; col < 71; col++) {
      storestage << stage[row][col];
    }
    storestage << endl;
  }
  storestage << "Lives :" << lives << endl;
  storestage << "Score :" << score << endl;
  storestage.close();
}