#        ENGG1340-Group-119
>Chi ben incomincia, è alla metà dell'opera.
>
>A good beginning is half done. 
>
>--- Quinto Orazio Flacco
##          Problem Statement:  
Learning English as a second language, we profoundly understand the difficulty to memorize tens of thousands of vocabularies. A traditional way to memorize vocabularies is to study the dictionary, but during this tedious process you can easily get lost and bored.The efficiency of memorizing those unrelated words is relatively low. Therefore, our project aims to help users learn new words effectively and systematically. You will no longer be bothered by the boring alphabetical order, our app will introduce new words tailored to the user, and users can even choose words from different subjects that we have stored in the “database”.

## Problem Setting:  
### In user's view:  
1. Choose the category of vocabulary he/she want to memorize.
2. After the category is chosen, user can decide whether to continue the last process.
3. During operation, user will be asked to answer multiple choice questions.
4. Whether the user's answer is right or not, the programme will show the detial about that word.
5. The user will come across new words as well as words that have popuped before.
6. No matter in which way user exit the program, accidentally or by command, they can always come back and resume last learning progress.
7. User can go back to home page whenever they want.  
### In developer's view:  
1. Design interface.
2. Sort the word list of non-mastered word in a properly ranking method.
3. Evaluate user's cognition of a word by giving mutiple choice questions.
4. Using dynamic memory allocation to minimize run time memory.
5. Store meanings and properties of the words in the database.
5. Preserve running datas in files and update them in real time.
6. Determine which word to popup next based on a rule subject to "Ebbinghaus forgetting curve".
## Functionalities and Features
We successfully solve all the problem settings. Therefore user is expected to enjoy all the functions we mentioned in [Problem Setting>In user's view](https://github.com/Ericcsr/ENGG1340-Group-119/blob/master/README.md#in-users-view).

More advanced features are waiting to be discovered by you! Or you can [click here](http://) to check them.
## Input/Output Specifications
### Input :abc:
You will mainly be dealing with multiple choice questions where only entering int or char leading each option is fine. What's more, you can always enter `#home` to go back to homepage. 
### Output :abc:
New messages will appear right after your input, no new window will popup.
## Compilation and Execution Instructions
This project is only guaranteed to work in Linux.os. Clone the master brunch to your local path and open this directory in terminal. Enter `make wordmemor` to compile and `./wordmemor` to execute the project! While the programme is running , just follow the instructions and enjoy the process of exploring English words!
## Advanced Features
### Change Interface
Open "screenplay.cpp", by simply changing the value of "WIDTH" in the macro defination part, you can change the size of the interface to fit your screen.
### Switch Between Categories
While you are learning a particular category, you can jump to another category when feeling bored. For example, say, you are learning business words, you can go to home page and start to learn sports terms. However, you do not need to worry that your footprint in business might be lost, we have already save it for you. 

You can learn about the logic of this function in the following program chart.
![image]()
### Add New Words
Also, you can enlarge the database by extend the (category).txt, be careful to write in the form of "word@choice@details@9@"
