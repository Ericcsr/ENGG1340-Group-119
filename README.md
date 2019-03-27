# ENGG1340-Group-119
Introduction:  
Learning English as a second language, we profoundly understand the difficulty to memorize tens of thousands of vocabularies. A traditional way to memorize vocabularies is to study the dictionary, but you may easily get bored when you can concisely predict and recite the first few words in every dictionary. Most of us will possibly give up before proceeding to last few letters like ‘s’ or ‘t’. Therefore, our product is designed to help users learn new words effectively and systematically. You will no longer be bothered by the boring alphabetical order, instead, our app will introduce new words tailored to the user, and users can even choose from 5 subjects of words that we previously stored in the “database”.

Problem Setting:  
In user view:  
1. Choose the category of vocabulary he/she want to memorize.
2. If the category is chosen, user can choose mode learning or reviewing mode of the program.
3. In learning mode user is required to input description of the word (Or multiple choices).
4. From time to time user will come across vocabularies that has shown up but fail to memorize.
5. In revision mode user will be required to deal with didn't mastered words only.
6. No matter user choose to end the program or exit the program accidentally
   user can click and resume last learning progress.
7. User can exit to the menu of choosing mode or category whenever they like.
In developer's view:  
1. Design interface.
2. Sort the word list of non-mastered word in a properly ranked method.
3. Insert the previous non-master words from mentioned list to a linked list of
   word pending to pop up from time to time.
4. Manage the current memory and use dynamic memory method as well as file IO to 
   save clean away some data and saved them into files.
5. Use some data as the condition of current learning procedure, and update them in real time.
6. Use the word extract and matching as well as restricted input explanation format to judge if user input satisfied description of a word.
