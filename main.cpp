// tesasdfting github on brand new machine

// libraries necessary for game functionality
#include <iostream>
#include "gameMechanic.h"
#include <ctime>
#include <vector>
#include <fstream>
#include <unistd.h>
using namespace std;

// This is where the player stats variables go
struct Player {
  int health;
  int damage;
  int bifrostCount;
  int attackCount;
  int healCount;
};

// This is where the enemy stats variables go
struct Enemy {
  int health;
  int damage;
  int randDamage;
  string ascii; 
  bool isPresent;
};

// Function for implementing full attacking mechanism
void attackMechanic(Player &player, Enemy &enemy, Enemy &enemy2,  bool &isPlaying, vector<bool> &rounds, int startRound, string filename)
{

  // calling the attack function
  attack(
    player.damage, 
    enemy.health,
    player.attackCount
  );

  // waiting for 1 second
  sleep(1);

  // calling the enemyAttack function
  enemyAttack(
    player.health, 
    enemy.damage,
    enemy.health
  );

  // Calling the game manager
  gameManager(
    player.health, 
    enemy.health,
    isPlaying, 
    rounds,
    player.bifrostCount, 
    player.attackCount, 
    player.healCount,
    startRound,
    filename,
    enemy.isPresent,
    enemy2.isPresent,
    enemy2.health, 
    enemy2.damage, 
    enemy2.ascii
  );
}

// function for bifrost mechanic
void bifrostMechanic(int &health, int &randDamage, int &enemyHealth, int &bifrostCount, int &playerDamage)
{
  // calling the bifrost attack function
  bifrostAttack(
    playerDamage, 
    enemyHealth, 
    bifrostCount
  );

  // waiting for 1 second
  sleep(1);

  // calling the enemy attack function
  enemyAttack(
    health, 
    randDamage,
    enemyHealth
    );
}

int main() {

  // vector of strings for running commands on the program
  vector<string> commands {
    "stats", "enemystats", "help",
    "exit", "quit", "bifrost",
    "attack", "heal", "clear"
  };
  
  // vector booleans for level status
  vector<bool> rounds {false, false, false, false};

  // boolean for controlling the while loop
  bool isPlaying = true;

  // setting initial randomized number
  srand(time(0));

  // setting random damage 
  int randDamage = rand() % 51;
  
  // player stats along with variables
  Player player;
  player.health = 100;
  player.damage = 13;
  player.bifrostCount = 2;
  player.attackCount = 4;
  player.healCount = 2;

  // Enemy stats for first enemy
  Enemy draugrEnemy;
  draugrEnemy.health = 100;
  draugrEnemy.damage = 16;
  draugrEnemy.ascii = "./text-files/draugr.txt";
  draugrEnemy.isPresent = false;

  // enemy stats for second enemy
  Enemy einherjarEnemy;
  einherjarEnemy.health = 130;
  einherjarEnemy.damage = 26;
  einherjarEnemy.ascii = "./text-files/einherjar.txt";
  einherjarEnemy.isPresent = false;

  // enemy stats for third enemy
  Enemy bjornEnemy;
  bjornEnemy.health = 170;
  bjornEnemy.damage = 37;
  bjornEnemy.ascii = "./text-files/bjorn.txt";
  bjornEnemy.isPresent = false;
  
  // FinalBoss stats for the last enemy;
  Enemy boss;
  boss.health = 200;
  boss.damage = 50;
  boss.ascii = "./text-files/tyr.txt";
  boss.isPresent = false;

  // user inputs
  string input;
  int fightChoice;

  // This when the logo starts.
  textLoader("./text-files/logo.txt", false);
  sleep(1);

  // Loading the story.txt file which begins the story
  textLoader("./text-files/story.txt", true);

  // Menu for choosing starting or exiting
  cout << "\n1. Start your fight" << endl;
  cout << "2. exit.\n" << endl;
  cout << "Choose your fight: ";
  cin >> fightChoice;

  // switch case to make the menu functional
  switch(fightChoice)
    {
      case 1: 
        rounds[0] = true;
      break;
      case 2:
        isPlaying = false;
        break;
    }//..end switch

  // while loop for when the user inputs invalid choice
  while (fightChoice > 2 || fightChoice < 0)
    {
      cout << "\nInvalid choice! Please try again." << endl;
      cout << "Choose your fight: ";
      cin >> fightChoice;
    }//..end while

  // if statement for when the round starts
  if (rounds[0] == true)
  {
    // this boolean helps with checking the rounds in the game
    draugrEnemy.isPresent = true;

    //loading the instruction once the round starts
    textLoader("./text-files/instructions.txt", false);
    
    enemyStats(
      draugrEnemy.health, 
      draugrEnemy.damage, 
      draugrEnemy.ascii
      ); 
  }//..end if

  // loop for running the game.
  while (isPlaying)
    {
    // setting the random damages inside the loop
    draugrEnemy.randDamage = draugrEnemy.damage + randDamage;
    einherjarEnemy.randDamage = einherjarEnemy.damage + randDamage;
    bjornEnemy.randDamage = bjornEnemy.damage + randDamage;
    boss.randDamage = boss.damage + randDamage;


    // calling the player input function
    playerInput(input);

    // if statement for running player stats
    if(input == commands[0])
      playerStats(
        player.health,
        player.damage,
        player.bifrostCount,
        player.attackCount, 
        player.healCount
      );

    // if statement for running enemy stats which differs round to round
    else if (input == commands[1])
    {
      // bring up stats for first enemy
        if (rounds[0]) 
          enemyStats(
            draugrEnemy.health, 
            draugrEnemy.damage,
            draugrEnemy.ascii
          );
          
      // bring up stats for second enemy
        else if (rounds[1]) 
          enemyStats(
            einherjarEnemy.health, 
            einherjarEnemy.damage,
            einherjarEnemy.ascii
          );
          
        // bring up stats for 3rd enemy
        else if (rounds[2]) 
          enemyStats(
            bjornEnemy.health,
            bjornEnemy.damage, 
            bjornEnemy.ascii
          );
          
        // show stats for final boss
        else
          enemyStats(
            boss.health, 
            boss.damage,
            boss.ascii
          );
    }//..end else if

    // running the help command to bring instructions  
    else if (input == commands[2])
      textLoader("./text-files/instructions.txt", false);
    
    // running the quit or exit command   
    else if (input == commands[3] || input == commands[4])
    {
        textAnimation("Valhalla is at your disposal!", 4);
        break;
    }//..end else if

    // running the bifrost command for applying extra damage
    else if (input == commands[5])
    {

      // running the attack command when the first enemy is present
      if (draugrEnemy.isPresent) 
        bifrostMechanic(
          player.health,
          draugrEnemy.randDamage, 
          draugrEnemy.health, 
          player.bifrostCount, 
          player.damage
        );
      // running the attack command when the second enemy is present
      else if (einherjarEnemy.isPresent) 
        bifrostMechanic(
          player.health,
          einherjarEnemy.randDamage, 
          einherjarEnemy.health, 
          player.bifrostCount, 
          player.damage
        );

      // running the attack command when the third enemy is present
      else if (bjornEnemy.isPresent) 
        bifrostMechanic(
          player.health,
          bjornEnemy.randDamage, 
          bjornEnemy.health, 
          player.bifrostCount, 
          player.damage
        );
    
    // running the attack command when the final enemy is present
      else if (boss.isPresent) 
        bifrostMechanic(
          player.health,
          boss.randDamage, 
          boss.health, 
          player.bifrostCount, 
          player.damage
        );

      // waiting for 1 second
      sleep(1);
    }//..end else if

   // running attack command based on input
    else if (input == commands[6])
    {
     // running attack mechanic function when first enemy is present 
      if (draugrEnemy.isPresent) 
         attackMechanic(
           player,
           draugrEnemy,
           einherjarEnemy,
           isPlaying,
           rounds,
           0,
           "./text-files/round1.txt"
          ); 

      // running attack mechanic function when second enemy is present 
      else if (einherjarEnemy.isPresent) 
        attackMechanic(
         player,
         einherjarEnemy,
         bjornEnemy,
         isPlaying,
         rounds,
         1,
         "./text-files/round2.txt"
        );
      // running attack mechanic function when third enemy is present 
      else if (bjornEnemy.isPresent)
        attackMechanic(
         player,
         bjornEnemy,
         boss,
         isPlaying,
         rounds,
         2,
         "./text-files/round3.txt"
        );
      // running attack mechanic function when the boss enemy is present 
      else if (boss.isPresent) 
      {
        attack(player.damage, boss.health, player.attackCount);
        enemyAttack(player.health, boss.damage, boss.health);
        bossGameManager(boss.health, rounds, isPlaying, player.health);
      }//..end else if
      
      sleep(1);
      
    }//..end else if

    // running the heal command when the user inputs 'heal'
    else if (input == commands[7])
    {
        heal(player.health, player.healCount);
        sleep(1);
        playerStats(
          player.health,
          player.damage,
          player.bifrostCount,
          player.attackCount, 
          player.healCount
        );
    }//..ense else if

    // running the clear command when the user inputs 'clear' 
    else if (input == commands[8])
        clearScreen();
    // invalid command when the user doesn't enter the right input
    else
      cout << "Invalid command! type 'help' to learn the commands" << endl;
    
  }//..end while

}