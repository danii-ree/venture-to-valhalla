#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <unistd.h>
using namespace std;

/*
****************************************
        Function Definitions  
****************************************
*/

// Function for loading txt files in console
void textLoader(string, bool);

// Function for adding text animation
void textAnimation(string, int);

// Function for showing playerstats
void playerStats(int, int, int, int, int);

// Function for player attack
void attack(int&, int&, int&, bool&);

// function for bifrost attack (adding extra damage to enemy)
void bifrostAttack(int&, int&, int&, bool&);

// function for healing the player
void heal(int&, int&);

// Function for showing enemy Stats
void enemyStats(int, int, string);

// Function for showing boss stats.
void bossStats(int, int, int, int, int);

// Function for player input.
void playerInput(string&);

// Function for checking health.
void gameManager(int&, int&, bool&, vector<bool>&, int&, int&, int&, int, string, bool&, int&, int&, string&);

// function for the enemies attacking
void enemyAttack(int&, int&, int);

// Function for increasing player stats
void increaseStats(int&, int&, int&, int&);

// Function for managing player health of boss
void bossGameManager(int&, vector<bool>, bool&, int&);

// function for clearing the screen
void clearScreen();

/*
****************************************
          Game Functionality
****************************************
*/

// Loading the text from file
void textLoader(string filename, bool animation)
{
  // using ifstream to output the file on the console
  ifstream file;
  string lines;
  file.open(filename);

  // using getline to get all the lines in the console
  getline(file, lines);

  // using file.eof() to loop while it's not the end of while
  while(!file.eof())
    {
      // setting animation to true based on parameter
      if(animation == true)
        textAnimation(lines, 4);
        
      // showing the text with no animations
      else
        cout << lines << endl;
      getline(file, lines);
    }//..end while

  file.close();
}//..end textLoader()

void textAnimation(string text, int speed)
{
  // for loop for setting the animation and using usleep the delay the string characters for smooth effect
  for (int i = 0; i < text.size(); i++)
    {
      // using std::flush for inputting characters individually
      cout << text[i] << flush;

      // usleep for alternating the speed of animation
      usleep(speed * 10000);
      
    }//..end for
  cout << endl;
}//..end textAnimation

// function for showing playerstats
void playerStats(int health, int hitDamage, int bifrostCount, int attackCount, int healthCount)
{            
  cout << "\n\t\t\tPlayer Stats:";
  cout << "\n\t\t\t------------------------------------------" << endl;
  cout << "\t\t\t  Health: " << health << endl;
  cout << "\t\t\t  Hit Damage: " << hitDamage << endl;
  cout << "\t\t\t  Attack: " << attackCount <<  "  Bifröst: " << bifrostCount << "  Heal: " << healthCount << endl;
  cout << "\t\t\t------------------------------------------\n" << endl;
}//..end playerstats

// function for attacking the enemy
void attack(int &hitDamage, int &health, int &attackCount)
{
  // clearing the screen once the function is called
  clearScreen();
  
  // decreasing attack count once the function executes
    if (attackCount > 0)
    {
      cout << "Attacked the enemy " << hitDamage << " pts." << endl;
      health -= hitDamage;
      attackCount--;
    }//..end if

    // outputs when you are out of attacks
    else cout << "You are out of attacks!" << endl;
}

void bifrostAttack(int &hitDamage, int &health, int &bifrostCount)
{
  // initiallizing bifrost damage
  double bifrost = 0.2 * health;

  // clearing the screen once executed
  clearScreen();

  // decreasing the bifrost count once executed
  if (bifrostCount > 0)
  {
    cout << "Bifröst has been applied." << endl;
    hitDamage += bifrost;  
    bifrostCount--;
  }//..end if
    
  else cout << "You are out of Bifröst!" << endl;
}//..end bifrostAttack()

// function for healing the player
void heal(int &health, int &healCount)
{
  //clearing the screen once executed
  clearScreen();

  // decreasing heal count once executed
  if (healCount > 0)
  {
    health += 20;
    cout << "You have been healed" << endl;
    healCount--;
  }//..end if
    
  else cout << "You are out of healing potions!" << endl;
}//..end heal()

//function for showing enemy stats
void enemyStats(int health, int hitDamage, string ascii)
{
  // loading enemy ascii art
  textLoader(ascii, false);
  cout << "\n\t\t\t------------------------------------------" << endl;
  cout << "\t\t\t  Health: " << health  << endl;
  cout << "\t\t\t  Hit Damage: "<< hitDamage << endl;
  cout << "\t\t\t------------------------------------------\n" << endl;
}//..end enemyStats

// function for user input when inputting commands
void playerInput(string &input) {
  cout << "---> ";
  cin >> input;
}

// function for increasing stats which adds up to variables
void increaseStats(int &health, int &bifrostCount, int &attackCount, int &healCount)
{
  health += 40;
  bifrostCount += 2;
  attackCount += 3;
  healCount += 2;
}

// function for managing the game, including health, round, etc.
void gameManager(int &playerHealth, int &enemyHealth, bool &isPlaying, vector<bool> &rounds, int &bifrostCount, int &attackCount, int &healCount, int nextRound, string filename, bool &currentEnemy, bool &nextEnemy, int &nextEnemyHealth, int &nextEnemyHitDamage, string &nextAscii)
{
  // closing the game if player reaches 0 health
  if(playerHealth <= 0)
  {
    cout << "You lost! You have to start everything again." << endl;
    isPlaying = false;
  }//..end if

  // for loop used when the enemy health reaches zero and starting the next round
    for (int i = nextRound; i < nextRound + 1; i++)
      {
        if (enemyHealth <= 0)
        {
          // setting current round to false
           rounds[i] = false;
          
          // loading the next round
           rounds[i + 1] = true;
          // loading the txt file after finishing round
           textLoader(filename, true);

          // loading enemyStats for next round
           enemyStats(nextEnemyHealth, nextEnemyHitDamage, nextAscii);

          // variables for setting the rounds
           currentEnemy = false;
           nextEnemy = true;

          // increasing the stats after each round
           increaseStats(
             playerHealth,
             bifrostCount,
             attackCount,
             healCount
            );
        }//..end if
      }//..end for
}

// function for managing boss variable
void bossGameManager(int &enemyHealth, vector<bool> rounds, bool &isPlaying, int &playerHealth)
{
  // Wrapping the game up when player reaches 0 health
  if(playerHealth <= 0)
  {
    cout << "You lost! But don't worry, you can always try again." << endl;
    isPlaying = false;
  }//..end if

  // loading the final text and finishing the game
  else if (enemyHealth <= 0)
  {
    isPlaying = false;
    textLoader("./text-files/finalboss.txt", true); 
  }//..end else if
  
}//..end bossGameManager()

// function for enemyAttack
void enemyAttack(int &playerHealth, int &enemyHitDamage, int health)
{
  // deducting playerhealth based on enemyDamage
  if(health > 0)
    playerHealth -= enemyHitDamage;

  cout << "The enemy damage was " << enemyHitDamage  << " pts" << endl;
}//..end enemyAttack

// function for clearing the screen
void clearScreen()
{
  // using ANSI escape sequence to clear the screen.
  cout << "\033[2J\033[1;1H";
}