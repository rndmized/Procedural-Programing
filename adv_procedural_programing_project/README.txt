*******************************************************************************************************************
					What's the purpose of the code?
*******************************************************************************************************************
Custom-surveys Ltd. currently performs surveys in Ireland and 
has requested you to develop a new survey program for them.
This program will create a database which will store the details
of all the surveys. In addition to storing all the survey data 
the application should allow survey statistics to be generated.
Your program should create the database (which for your purpose 
will be implemented as a linked list) and be able to save, restore,
retrieve, add, delete and update survey details.
For each survey, you will store the following details for each 
person that undertakes the survey:
•PPS Number
•First Name
•Second Name
•Address
•Email Address (must contain an @, a full stop and a .com)
•Age Bracket
•Icome Bracket
•Exercise
•Alcohol
•Smoking
The system is password protected and only the correct username and 
password details will allow the user to gain access to the system.
The username and password (6 characters in length) will be stored 
in a login structure which is read in from a login file which holds 
three login records. Ensure that when the user enters in the password 
that it cannot be seen on the screen. (It only shows an * for each 
character. E.g. ******)
Your program should initialise the linked list based on the surveys 
stored in the Surveys.txt file. This file should be updated when the 
user terminates the program.
Your program should provide a menu as follows:
1)Add survey
2)Display all surveys to screen
3)Display Survey Details
4)Update survey
5)Delete survey
6)Generate statistics (a – l) based on the criteria listed in I - III
	a.% of people who smoke
	b.% of people who smoke less than 20 cigarettes per week
	c.% of people who smoke less than 40 cigarettes per week
	d.% of people who smoke greater than 40 cigarettes per week
	e.% of people who never exercise
	f.% of people who exercise less than three times per week
	g.% of people who exercise less than five times per week
	h.% of people who exercise more than five times per week
	i.% of people who do not consume alcohol
	j.% of people who consume less than 2 units of alcohol per week
	k.% of people who consume less than 4 units of alcohol per week
	l.% of people who consume more than 4 units of alcohol per week

I.Age Bracket
II.Income Bracket
III.Gender

7)Print all surveys into a report file.
*******************************************************************************************************************
			What Requirements have been integrated in the code and which ones changed?
*******************************************************************************************************************
All requirements have been fullfilled with the following changes:

- The linked list is saved in the text file every time a change is made: 
  a survey is added, updated or deleted.
- The statistics are displayed based on the criteria but from a to l all at once.

*******************************************************************************************************************
						Known bugs.
*******************************************************************************************************************
- Once you reach the entering password step every key you press will be taken
  into account causing the password to be wrong; Eg, Backspace key counst as entered character...
- Entering long strings cans cause the program to missbehave.

*******************************************************************************************************************
						  Author
*******************************************************************************************************************
This program has been written by Albert Rando for the Advanced Procedural Programming module at GMIT.
Contact:g00330058@gmit.ie