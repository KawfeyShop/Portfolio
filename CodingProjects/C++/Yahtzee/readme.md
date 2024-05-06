[Intro]
This is the game yahtzee, it is a single player game in which you try and score as high as you can within 13 rounds, each round consists of 1-3 rolls of 5 dice.

[Build]
Go to source directory file using cd where both CMakeLists.txt and yahtzee.cpp are in the same directory.
Do the following commands to build the file:
cmake -B build -S .
This command creates a folder build in the current directory that puts all the build files in it. 
Next, do one of the following commands:

    $ cmake --build build --target all
This is to build both the yahtzee.exe and the test.exe

    $ cmake --build build --target build_test
This is to build only the test file. 

    $ cmake --build build --target build_yahtzee
This is to build only the Yahtzee file.

    $ cmake --build build --target clean_build
This is to clean the build folder so you can rebuild. 

You're executable(s) should be built. Go to the /build/build/bin file from the root directory to verify. 

[Testing]
	
	Upon building the test application, navigate to the yahtzeeTest.exe file. Open it inside the terminal using ./yahtzeeTest.exe, it will generate a report. This report specifically tells you which test cases pass, and which don't. It also gives a summary at the bottom showing the total test cases, in comparison to how many passed and failed. As well as, total assertions, in comparison to how many passed and failed.

P.S. Professor Decker said that we shouldn't have to have a test case for the game class.  
 

[Statement of Contributions]

	*Jacob = Primarily responsible for the writing of the test cases. Also, helped in setting up catch2. 
	*Logan = Primarily responsible for the cmake file. Ensuring that it worked properly, adding custom targets to build individual files, cleaning it, etc. Added contributions to the readme.txt. Helped in research of ci/cd optional section. Helped in the setup of catch2.  
	*Simon = Primarily responsible for the optional CI/CD implementations. Also, helped in writing some test cases as well as was the primary beneficiary in setting up catch2. 

[How to Play]
Run the YAHTZEE file built
You will be prompted with a desicion after a roll

decide which dice to not roll again

do this a total of twice more
thus ends a round
this will repeat a total of 13 times, each time reporting the score of the player at the end of a round

[Scoring]
In YAHTZEE there are several different ways of scoring, an upper and a lower, these scoring patterns are listed below

Ones, Twos, Threes, Fours, Fives, and Sixes:

The player scores the sum of all dice showing the corresponding number.
For example, if tthe player rolls 1-2-2-4-5, they would score 1 point for each '1' rolled, 4 points for each '2' rolled, and 5 points for each '5' rolled.

Three of a Kind:

If at least three dice show the same value, the player scores the sum of all five dice.
For example, if the player rolls 3-3-3-4-5, they would score 18 points (3 + 3 + 3 + 4 + 5 = 18).

Four of a Kind:

If at least four dice show the same value, the player scores the sum of all five dice.
For example, if the player rolls 2-2-2-2-5, they would score 13 points (2 + 2 + 2 + 2 + 5 = 13).

Full House:

If three dice show one value and the other two dice show a different value, the player scores 25 points.
For example, if the player rolls 2-2-3-3-3 or 4-4-4-6-6, they would score 25 points.

Small Straight:

If four consecutive numbers are rolled, the player scores 30 points.
For example, if the player rolls 1-2-3-4-6 or 2-3-4-5-5, they would score 30 points.

Large Straight:

If five consecutive numbers are rolled, the player sccores 40 points.
For example, if the player rolls 1-2-3-4-5 or 2-3-4-5-6, they would score 40 points.

Yahtzee:

If all five dice show the same value, the player scores 50 points.
For example, if the player rolls 6-6-6-6-6, they would score 50 points.

Chance:

The player can score the sum of all five dice regardless of their values.
This combination is typically used as a backup option when no other combination is applicable.