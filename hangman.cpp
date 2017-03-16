//Challenge: Create a hangman puzzle program
//Player gets 175% as many guesses as there are letters in the word.

#include <iostream>
#include <fstream>
#include <ctime>
//#include <iomanip>
#include <vector>
//#include <typeinfo>
//#include <cmath>
#include <string>
#include <algorithm>




using namespace std;

void checkForOnlyLetters(string g, char &oL);
void menuCoutBlock(string clue);
void findDeleteLetters(string g, string &abc);
void bubbleSortLetters(string &lets);
int randomInteger();
void noFail ();

int main()
{
	ifstream inWords;
	inWords.open("corncob_caps.txt", ios::in);
	vector<string> wordVector;
		if (inWords.is_open())								//make sure input file opened properly
		{		while(!inWords.eof())					//put every word listed in the file into an array to make program speedy
				{	string word = "";
					getline(inWords, word);
					wordVector.push_back(word);
				}//end for

			int scoreBoard[2][2] = {	{0,0},
										{0,0} };

				while (true) 									//make the game run until a sentinel value calls break;
				{	int randNum = randomInteger();
					
					
						#ifdef WIN32  //unix for some reason compiles a whitespace character at the end of this string
							string answer = wordVector.at(randNum);
						#else 
							string answer = wordVector.at(randNum);
							answer.erase(answer.length() - 1, 1);
						#endif
					
					
					string answerClue = "";
					answerClue.assign(answer.length(), '-');
					
					menuCoutBlock(answerClue);
					
					cout << answer << endl;
					
					bool ifOne = false;
					bool ifTwo = false;
					bool ifThree = false;
					bool ifFour = false;
					int firstNumOfGuesses = (answer.length() * 1.25);
					string usedLetters = "";
					int testPass = 0;
					string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
						for (int numOfGuesses = firstNumOfGuesses; numOfGuesses > 0; --numOfGuesses)
						{	string guess = "";	
							char fullGuess = ' ';
							char goodGuess = 'N';
							
							
								while (guess == "")
								{	++testPass;
									guess = ""; 
								 	getline(cin, guess);
									transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
									char onlyLetters = 'Y'; //set to Y - if unaltered, indicates that menu-call has not ocurred
									
										if (guess == "!END")//checks for sentinel value
										{	inWords.close();
											return 0;
										}//end returnIF
										
										if (guess == "!MENU")
										{	menuCoutBlock(answerClue);
																						
											guess = "";//ensures it will ask for another guess without registering '!' as the guess
											onlyLetters = 'M';//prevents onlyLetters error from triggering, 'M' for menu
										}//end menuIF
										
										if(guess == "!WORD")
										{	cout 
											<< endl << "Okay! If you guess the full word you win! If you don't, you lose! Enter the full word below!"
											<< endl;
											onlyLetters = ' ';
												while (onlyLetters != 'Y')
												{	getline(cin, guess);
													transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
													
														if (guess == "!END")
														{	inWords.close();
															return 0;
														}// end returnIF

													checkForOnlyLetters(guess, onlyLetters)	;
																											
														if (guess.length() > answer.length())
														{	cout
															<< endl << "Guess is too Long! The word is " << answer.length() << " letters!"
															<< endl;
																if (onlyLetters == 'L')
																{	cout
																	<< endl << "You took the long route again! Now Ascii's neck will be longer..."
																	<< endl;
																	break;
																}
																else
																{	onlyLetters = 'L';
																}//end inner l_onlyLettersIF
														}
														else if (guess.length() < answer.length())
														{	cout
															<< endl << "Guess is too Short! The word is " << answer.length() << " letters!"
															<< endl;
															
																if (onlyLetters == 'H')
																{	cout
																	<< endl << "Not again! Now Ascii will have a short drop and a sudden stop..."
																	<< endl;
																	break;
																}
																else
																{
																onlyLetters = 'H';
																}//end inner h_onlyLettersIF
														}
														else if (onlyLetters != 'N')
														{	onlyLetters = 'Y';
														}//end all_onlyLettersIF									
												}//end y_onlyLettersWHILE
											
											cout << guess << endl;
												if (guess != answer)
												{	cout
													<< endl << "Oh no! The correct answer is " + answer + "! You lose!"
													<< endl << endl;
													fullGuess = 'N';
													++scoreBoard[1][1];		//losses by full guess
												}
												else
												{	cout
													<< endl << "That's right! You win! The answer is " + answer + "!"
													<< endl << endl;
													fullGuess = 'Y';
													++scoreBoard[0][1];		//wins by full guess
												}//end inner if
											onlyLetters = 'W';//prevents onlyLetters error from triggering, 'W' for word guess
										}
										
										if (guess == "!SCORE")//checks for score call
										{	cout 
											<< endl
											<< "You've won " << scoreBoard[0][0] << " times by letter guess."
											<< endl
											<< "You've won " << scoreBoard[0][1] << " times by full word guess."
											<< endl
											<< "You've lost " << scoreBoard[1][0] << " times by letter guess."
											<< endl
											<< "You've lost " << scoreBoard[1][1] << " times by full word guess."
											<< endl << endl;
											
											guess = "";//ensures it will ask for another guess without registering '!' as the guess
											onlyLetters = 'S';//ensures an onlyLetters error isn't triggered, 'S' for score exception
										}
										
										if (onlyLetters == 'Y')
										{	checkForOnlyLetters(guess, onlyLetters);
											
											if (onlyLetters == 'N') //if non-letters are detected, triggers error
											{	cout
												<< endl << "Only letters are allowed!"
												<< endl;
												guess = "";
											}
											else 
											{		for (int pong = answer.length(); pong > -1; pong --) //replace each dash with a correct letter
													{		if (answer.substr(pong, 1) == guess.substr(0,1))
															{	answerClue.replace(pong, 1, guess.substr(0,1));
																goodGuess = 'Y';
															}//end if
													}//end pongFor
											}//end n_onlyLettersIF
											
										}// end y_onlyLettersIF
								}//end invalidGuessWHILE	
							
							
								
								if (fullGuess == 'Y')
								{	break;//breaks out of numOfGuessesFOR
								}
								else if (fullGuess == 'N')
								{
									cout	<< "                                          "
									<< endl << "                  -----                   "
									<< endl << "                  |  \\|                   "
									<< endl << "                  |   |                   "
									<< endl << "              b   |   |  d                "
									<< endl << "            /*|)  &   | /|)               "
									<< endl << "            _/^\\ <|>?_|\\_/\\_              "
									<< endl << "___________/    |( )        \\_____________"
									<< endl << "          Ascii has been Hung!            "
									<< endl << endl;
									break;
								}
								
							usedLetters.append(guess.substr(0,1));
							findDeleteLetters(guess.substr(0,1), alphabet);
							bubbleSortLetters(usedLetters);
								
								
								if (goodGuess == 'Y')
								{	numOfGuesses += 1;
								}//end goodGuessIF
								
								
								if (answerClue == answer)
								{	cout
									<< endl << "You have guessed the final letters! The answer is " + answer + '!'
									<< endl << endl;
									++scoreBoard[0][0];		//wins by letter guess
									break;//breaks numOfGuessesFOR
								}
								else if (numOfGuesses == 1)
								{ cout
									<< endl << "That was your last guess! The answer was " + answer + '!'
									<< endl << endl;
									++scoreBoard[1][0];		//losses by letter guess
								}
								else
								{	cout
									<< endl << answerClue
									<< endl << "You have " << numOfGuesses-1 << " guesses left."
									<< endl;
								}//end winLoseIF
								
								
								
								if (numOfGuesses == firstNumOfGuesses && ifOne == false)
								{	cout	<< "                                          "
									<< endl << "                  -----                   "
									<< endl << "                  |  \\|                   "
									<< endl << "                  |   |                   "
									<< endl << "                  8   |                   "
									<< endl << "                      |/      b   o   d   "
									<< endl << "            __________|_____  |>-d|b-<|   "
									<< endl << "___________/                \\_/\\_/^\\_/\\___"
									<< endl;
									ifOne = true;
								}
								else if (numOfGuesses >= (firstNumOfGuesses / 3) * 2 && numOfGuesses < firstNumOfGuesses && ifTwo == false)//if greater than 2/3 but less than 100%
								{	cout	<< "                                          "
									<< endl	<< "                  -----                   "
									<< endl	<< "                  |  \\|                   "
									<< endl	<< "                  |   |                   "
									<< endl	<< "                  8   |  b                "
									<< endl	<< "                      |/ |>-,  o   d      "
									<< endl	<< "            __________|__/\\_ \\d|b-<|      "
									<< endl	<< "___________/                \\_/^\\_/\\______"
									<< endl;
									ifTwo = true;
								}
								else if (numOfGuesses >= (firstNumOfGuesses / 3) && numOfGuesses < (firstNumOfGuesses / 3) * 2 && ifThree == false)//if > than 1/3 but < 2/3
								{	cout	<< "                                          "
									<< endl << "                  -----                   "
									<< endl << "                  |  \\|                   "
									<< endl << "                  |   |                   "
									<< endl << "                  8 b |  o                "
									<< endl << "                    |>x/d|b--, d          "
									<< endl << "            ________/\\|_/^\\_  \"|          "
									<< endl << "___________/                \\_/\\__________"
									<< endl;
									ifThree = true;
								}
								else if ((numOfGuesses == 2 && ifFour == false) || (numOfGuesses > 1 && numOfGuesses < (firstNumOfGuesses / 3) && ifFour == false))//if greater than 1 but less than 1/3
								{	cout	<< "                                          "
									<< endl << "                  -----                   "
									<< endl << "                  |  \\|                   "
									<< endl << "                  |   |                   "
									<< endl << "            \\ b   8   |  d                "
									<< endl << "             *|) <|>  |/-|)               "
									<< endl << "            _/^\\_/^\\?_|_/^\\_              "
									<< endl << "___________/                \\_____________"
									<< endl;
									ifFour = true;
								}
								else if (numOfGuesses == 1)
								{	cout	<< "                                          "
									<< endl << "                  -----                   "
									<< endl << "                  |  \\|                   "
									<< endl << "                  |   |                   "
									<< endl << "              b   |   |  d                "
									<< endl << "            /*|)  &   | /|)               "
									<< endl << "            _/^\\ <|>?_|\\_/\\_              "
									<< endl << "___________/    |( )        \\_____________"
									<< endl << "          Ascii has been Hung!            "
									<< endl << endl;
								}
						}//end outer numOfGuessesFor
				}//end trueWhile
		}//if
		else
		{	cout << "Error! Words file could not be found." << endl;
		}//end openIf
		
	inWords.close();
	
	return 0;
}

void checkForOnlyLetters(string g, char &oL)
{
	for (int ping = g.length()-1; ping > -1; ping --)
	{		if (g.substr(ping, 1) > "Z" || g.substr(ping, 1) < "A")
			{	oL = 'N';
				cout
				<< endl << "Word must be only letters!"
				<< endl;
				break;
			}//end n_onlyLettersIF
	}//end pingFor

}

void menuCoutBlock(string clue)
{
	cout << "This is Hangman! Guess the letters in the following " << clue.length() << " letter word to save Mr. Ascii! "
	<< endl 
	<< endl << "Type    !word     to guess the full word."
	<< endl 
	<< endl << "Type    !score  to get win/loss stats."
	<< endl 
	<< endl << "Type    !end     to end."
	<< endl 
	<< endl << "Type    !menu     to repeat this menu!"
	<< endl << clue
	<< endl;
}

void findDeleteLetters(string g, string &abc)
{	char ch = g[0];
		while (abc.find(ch, 0) != std::string::npos)
		{	abc.erase(abc.find(ch, 0), 1);
		}
	cout 
	<< endl << "Available letters: " << abc;
	//http://www.cplusplus.com/reference/string/string/rfind/
	//delete any g found in abc, cout abc
}

void bubbleSortLetters(string &lets)
{	char sntnl = 'N';
	while(sntnl == 'N')
	{	sntnl = 'Y';
		for (int i = lets.length() - 1; i > 0; --i)
		{	if (lets.substr(i,1) < lets.substr(i-1,1))
			{	string plH = lets.substr(i,1);
				lets.replace(i, 1, lets, i-1 ,1);
				lets.replace(i-1, 1, plH, 0, 1);
				sntnl = 'N';
			}//end if
		}//end for
	}//end while
	cout
	<< endl << "     Used letters: " << lets
	<< endl;
}

int randomInteger()
{	srand(static_cast<int>(time(0)));
	int rndmInt = 0 + rand() % (58108 - 0 + 0);
	return rndmInt;
}

using namespace std;
void noFail ()
{
	cin.clear();
	cin.ignore(65536,'\n');
}