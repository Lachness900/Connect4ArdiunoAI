// Connect 4 Game

/*  Overview
 *   
 *  Plays physical Connect 4 game 
 *  
 *  Can be played human v computer, computer v computer or human v human
 *  Detects wins and draws and shows end game message on the display
*/
 
// My addition to the code was the:
//  decide move function: Line 261 - Line 463
//  Difficulty selection function: 67 - 89
//  readkeypad function: 40 - 56


// debug mode
const bool debug = true; // sends grid state to serial after each turn if true

// menu control
int menu = 0;

// game
int selectorPosition = 1;
int seed = 0;
int difficulty = 4;
  int boardstate = 0;
  byte tempGrid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int win = 0;
void setup() { 
  Serial.begin(9600); 

Serial.println("Arduino Connect4    Press any key");

  // game
seed = random(0,20);

}

char readKeypad(){
  char key = ' ';
   
    while(Serial.available() == 0){};
   int keyInput = Serial.parseInt();
 delay(50);
    if(keyInput == 1) key = '1';
    else if(keyInput == 2) key = '2';
    else if(keyInput == 3) key = '3';
    else if(keyInput == 4) key = '4';
    else if(keyInput == 5) key = '5';
    else if(keyInput == 6) key = '6';
    else if(keyInput == 7) key = '7';
    else if(keyInput == 8) key = '8';
    else if(keyInput == 9) key = '9';
  return key;
}
 
void showMenu(int menu){
  if(menu == 0) Serial.println("Arduino Connect4  Press any key");
  if(menu == 1) Serial.println("1 Play Connect 4,   2 Difficulty Settings");
  if(menu == 11) Serial.println("1 HvC,  2 HvH,   3 CvC,     4 Exit");
  if(menu == 111) Serial.println("1 Human go first,   2 Second,  3 Exit");
  if(menu == 12) Serial.println("1 Difficulty Settings 4 Exit");
  if(menu == 13) Serial.println("1 Difficulty 2 Agression  4 Exit");
}

void Difficulty(){
 char keyPressed = ' ';
  Serial.println("Set new difficulty by entering a number between 1(easiest) - 9(hardest)");
  Serial.println(String("Current difficulty") + difficulty);
   keyPressed = ' ';
    while(keyPressed == ' '){
      keyPressed = readKeypad();
      delay(15);
    }
int key = 0;
    if(keyPressed == '1') key = 1;
    if(keyPressed == '2') key = 2;
    if(keyPressed == '3') key = 3;
    if(keyPressed == '4') key = 4;
    if(keyPressed == '5') key = 5;
    if(keyPressed == '6') key = 6;
    if(keyPressed == '7') key = 7;
    if(keyPressed == '8') key = 8;
    if(keyPressed == '9') key = 9;
int dfficulty = key;
  Serial.println(String("New difficulty = ") + difficulty);
  showMenu(menu);
}

int getHumanMove(byte g[], int p, String colour){
  bool columnAccepted = true;
  char keyPressed = ' ';
  int key = 0;
  
  do{
    columnAccepted = true;
    keyPressed = ' ';
    while(keyPressed == ' '){
      keyPressed = readKeypad();
      delay(15);
    }
    key = 0;
    if(keyPressed == '1') key = 1;
    if(keyPressed == '2') key = 2;
    if(keyPressed == '3') key = 3;
    if(keyPressed == '4') key = 4;
    if(keyPressed == '5') key = 5;
    if(keyPressed == '6') key = 6;
    if(keyPressed == '7') key = 7;

    // exit from game
    if(keyPressed == '9') key = 9;
  
    if(key > 0 && key < 8){
      // check for full column
      if(g[toGrid(key - 1, 5)] != 0){
        Serial.println("Full, try again             " + String("P") + (p + 1) + " " + colour + " 1-7"); 
        columnAccepted = false;
      }
    }
  }while(!columnAccepted && key != 9);
  return key;
}

void resetGrid(byte grid[]){
  for(int i = 0; i < 42; i++){
    grid[i] = 0;
  }
}
int addCounter(byte g[], int p, int c){
  // find row
  int row = 0;
  while(g[toGrid(c, row)] != 0){
    row++;
  }
  // update array
  g[toGrid(c, row)] = p + 1;
  return row;
}

int checkForDraw(byte g[]){
  bool draw = true;
  for(int i = 0; i < 7; i++){
    if(g[toGrid(i, 5)] == 0){
      draw = false;
    }
  }
  return draw;
}

//checks if either player has won
int checkForWin(byte g[], int p, int c, int r){
  p++;
  int win = 0;
  
  if(win == 0) win = checkFor4(g, p, c, r, 3, 6, 0, 2, -1, 1, -2, 2, -3, 3);
  if(win == 0) win = checkFor4(g, p, c, r, 2, 5, 1, 3, -1, 1, -2, 2, 1, -1);
  if(win == 0) win = checkFor4(g, p, c, r, 1, 4, 2, 4, -1, 1, 1, -1, 2, -2);
  if(win == 0) win = checkFor4(g, p, c, r, 0, 3, 3, 5, 1, -1, 2, -2, 3, -3);

  if(win == 0) win = checkFor4(g, p, c, r, 0, 3, 0, 2, 1, 1, 2, 2, 3, 3);
  if(win == 0) win = checkFor4(g, p, c, r, 1, 4, 1, 3, 1, 1, 2, 2, -1, -1);
  if(win == 0) win = checkFor4(g, p, c, r, 2, 5, 2, 4, 1, 1, -1, -1, -2, -2);
  if(win == 0) win = checkFor4(g, p, c, r, 3, 6, 3, 5, -1, -1, -2, -2, -3, -3);

  if(win == 0) win = checkFor4(g, p, c, r, 0, 3, 0, 5, 1, 0, 2, 0, 3, 0);
  if(win == 0) win = checkFor4(g, p, c, r, 1, 4, 0, 5, 1, 0, 2, 0, -1, 0);
  if(win == 0) win = checkFor4(g, p, c, r, 2, 5, 0, 5, 1, 0, -1, 0, -2, 0);
  if(win == 0) win = checkFor4(g, p, c, r, 3, 6, 0, 5, -1, 0, -2, 0, -3, 0);

  if(win == 0) win = checkFor4(g, p, c, r, 0, 6, 3, 5, 0, -1, 0, -2, 0, -3);

  return win;
}

int checkFor4(byte g[], int p, int c, int r, int c1, int c2, int r1, int r2, int sc1, int sr1, int sc2, int sr2, int sc3, int sr3){
  win = 0;
  if(c >= c1 && c <= c2 && r >= r1 && r <= r2 && g[toGrid(c + sc1, r + sr1)] == p && g[toGrid(c + sc2, r + sr2)] == p && g[toGrid(c + sc3, r + sr3)] == p) win = p;
  return win;
}

int toGrid(int column, int row){
  return column + (row * 7);
}

int toColumn(int grid){
  return grid - (toRow(grid) * 7);
}

int toRow(int grid){
  return grid / 7;
}

void sendGrid(byte g[]){
  for(int r = 5; r >= 0; r--){
    for(int c = 0; c < 7; c++){
      Serial.print(g[toGrid(c, r)]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("");
}

/*void boardState(byte g[], int p){
  for(int c = 0; c < 7; c++){
    for(int r = 0; c < 6; r++){
      tempGrid[toGrid(c,r)] = g[c,r];
      checkForWin(tempGrid, p,c,r );
      if(win > 0){
        boardstate += p*2 - 1;
      }
    } 
  }
  return boardstate;
}*/

int decideMove(byte g[], int p){
  int columns[] = {50, 50, 50, 50, 50, 50, 50};
  int win = 0;
  int key = 0;
  int biggest = 0;
  int count = 0;
  int selected = 0;
  int row = 0;
  int p2 = abs(p - 1);


  // mark all full columns with 0s
  for(int i = 0; i < 7; i++){
    if(g[toGrid(i, 5)] != 0){
      columns[i] = 0;
    }
  }

  // add 1000 to winning columns
  for(int i = 0; i < 7; i++){
    if(columns[i] > 0){
      for(int j = 0; j < 42; j++){
        tempGrid[j] = g[j];
      }
      row = addCounter(tempGrid, p, i);
      win = checkForWin(tempGrid, p, i, row);
      if(win > 0){
        columns[i] += 1000;
      }
    }
  }

  // add 150 to columns where the other player wins
  for(int i = 0; i < 7; i++){
    if(columns[i] > 0){
      for(int j = 0; j < 42; j++){
        tempGrid[j] = g[j];
      }
      row = addCounter(tempGrid, p2, i);
      win = checkForWin(tempGrid, p2, i, row);
      if(win > 0){
        columns[i] += 150;
      }
    }
  }


  // check for moves which allow the other player to win on the next turn
  for(int i = 0; i < 7; i++){
    if(columns[i] > 0){
      for(int k = 0; k < 7; k++){
        if(columns[k] > 0){
          for(int j = 0; j < 42; j++){
            tempGrid[j] = g[j];
          }
          row = addCounter(tempGrid, p, i);
          if(i != k || row < 5){ 
            row = addCounter(tempGrid, p2, k);
            win = checkForWin(tempGrid, p2, k, row);
            if(win > 0){
              columns[i] -= 50;
            }
          }
        }
      }
    }
  }
  
  // Add a bais for placing counters in the center
  for(int i = 0; i < 7; i++){
    if(columns[i] > 0){
      if(i == 3){
        columns[i] += 15;
      }
      if(i == 2 || i == 4){
        columns[i] += 10;
      }
      if(i == 1 || i == 5){
        columns[i] += 5;
      }
    }
  }
  
  //Add randomness to the robot for more agression
  for(int i = 0; i < 7; i++){
    if(columns[i] > 0){
      columns[i] += random(2,difficulty*15);
    }
  }
  // find biggest value in columns[]
  for(int i = 0; i < 7; i++){
    if(columns[i] > biggest){
      biggest = columns[i];
    }
  }
  // count biggest in columns[]
  for(int i = 0; i < 7; i++){
    if(columns[i] == biggest){
      count++;
    }
  }
 
  
  // random select a biggest column
  selected = random(count) + 1;
  if(debug){
    Serial.println(String("Player ") + p);
    Serial.println(String("Biggest ") + biggest);
    Serial.println(String("Count ") + count);
    Serial.println(String("Selected ") + selected);
    Serial.println(String("Board State")+ boardstate);
    Serial.println(String("Difficulty")+ difficulty);
  }
  for(int i = 0; i < 7; i++){
    if(columns[i] == biggest){
      selected--;
      if(selected == 0){
        key = i + 1;
      }
    }
  }

  if(debug){
    for(int i = 0; i < 7; i++){
      Serial.print(columns[i]);
      Serial.print(" ");
    }
    Serial.println("");
    Serial.println("");
  }
  
  return key;
}

void playGame(int player1Type, int player2Type){
  randomSeed(seed);
  for(int i = 0; i < 100; i++){
    int dump = random(50);
  }
  
  // type, 1 = human, 2 = computer
  int players[] = {0, 0};
  players[0] = player1Type;
  players[1] = player2Type;

  byte grid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  bool gameEnd = false;
  bool aborted = false;
  int player = 0;
  int key = 0;
  int selectorMove = 0;
  String colour;
  bool draw = false;
  int win = 0;
  int row = 0;
  int column = 0;
  int countDown = 2000;
  char keyPressed = ' ';

  resetGrid(grid);
  
  while(!gameEnd){
    if(player == 0){colour = "Red";}
    else{colour = "Yellow";}

    if(players[player] == 1){
      key = getHumanMove(grid, player, colour);
      Serial.println(String("Player ") + (player + 1) + " " + colour + "     Please select column 1-7     Press 9  to exit");
      if(key == 9){
        gameEnd = true;
        aborted = true;
      }
    }
    else{
      Serial.println(String("Player ") + (player + 1) + " " + colour + "     Deciding move...");
      key = decideMove(grid, player);
      delay(200);
    }
      
    if(key > 0 && key < 8){
      Serial.println("Executing move    Please wait..."); 
      
      column = key - 1;
      row = addCounter(grid, player, column);
      if(debug) sendGrid(grid);
      
      // check for win
      win = checkForWin(grid, player, column, row);
      if(win > 0) gameEnd = true;
      
      // check for draw, all full and no winner
      if(!gameEnd){
        draw = checkForDraw(grid);
        if(draw) gameEnd = true;
      }
      
      player = abs(player - 1);
    }
    // check for abort if not gameEnd
    if(!gameEnd && players[0] == 2 && players[1] == 2){
      Serial.println("Press 1 to abort    Press 2 to continue");

        keyPressed = readKeypad();
        if(keyPressed == '1'){
          Serial.println(keyPressed);
          gameEnd = true;
          aborted = true;
        }
        if(keyPressed == '2'){
          Serial.println("Continuing...");
        }
      
    }
  }
  
  // end game messages
  if(draw){
    Serial.println("Result is a Draw       Press any key");
  }
  if(win == 1){
    Serial.println("Winner P1 Red        Press any key");
  }
  if(win == 2){
    Serial.println("Winner P2 Yellow       Press any key");
  }
  if(aborted) Serial.println("Game aborted        Press any key");
  while(readKeypad() == ' '){
    delay(20);
  }

  showMenu(menu);
}




void processMenuInput(char key){
  if(menu == 0){menu = 1; showMenu(menu);}
  // top level menu
  else if(menu == 1){
    if(key == '1'){menu = 11; showMenu(menu);}
    if(key == '2'){menu = 13; showMenu(menu);}
  }
  // play menu
  else if(menu == 11){
    if(key == '1'){menu = 111; showMenu(menu);}
    if(key == '2'){playGame(1, 1);}
    if(key == '3'){playGame(2, 2);}
    if(key == '4'){menu = 1; showMenu(menu);}
  }
  else if(menu == 111){
    if(key == '1'){Serial.println("Select Column 1-7");playGame(1, 2);}
    if(key == '2'){playGame(2, 1);}
    if(key == '3'){menu = 11; showMenu(menu);}
  }
  // set-up menu
  else if(menu == 13){
    if(key == '1'){Difficulty();};
    if(key == '2'){};
    if(key == '4'){menu = 1; showMenu(menu);}
  }
}

void loop(){ 
  // keypad
  char keyPressed = readKeypad();


  // menu navigation
  if(keyPressed != ' '){
    processMenuInput(keyPressed);
  }

  // game 
  seed++;
  
  delay(50);
} 
