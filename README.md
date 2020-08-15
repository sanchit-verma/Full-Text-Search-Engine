# Search Engine Project
A Full-text unigram search engine implemented in c++.
## Project Author - 
- Sanchit Verma
## Aim
The aim of this project is to build a prototype of a search engine which works on Student database and retrieve the details based on query.This search engine takes user student database in json format.
This search engine is full text search engine unlike exact value search in Data Base Management System.

**Here without using the concept of _machine learning_ , aim was to make it a better search engine by applying word similarity like jump and leap are same and stemming like jumping to jump etc**.
We have student document in Json format which is used as database for searching.Our main purpose is to create an object of Student File, and using Json Parser we access complete information of file in to main memory.Json Parser reads the document in byte by byte fashion. Depending on the byte it will call the appropriate handler.
The Student pages has been taken as object and following operations are performed,
- Split the text into tokens
- Remove the stop words
- Stem the words
- Maintain where each word has occurred (using Hash Map/Unordered_map(C++ STL)) like a key-value pair.
We put word as the key and an array of integer as value. The array at each index contains count of that word present in various attributes of object.
Now we are performing inverted indexing to know which student's data need to be printed.Here also, we are going to maintain a kind of Hash Map containing words as key and value as set of all documents in which it is present along with a set-Bit and a Term Frequency (TF).
## Term Frequency(TF)
It is a numerical statistics that is intended to reflect how important the word is to the document in the collection. 
On the basis of term frequency we give priority to document which contains that particular word.

         Term Frequency(TF) : 1+log(total weight)


###### Disadvantage of TF :
Let say, we need to search “the brown” so we will be searching documents with “the” and documents with “brown” and show up. Here we are using **one-gram/Unigram** concept only. We are not using bi-gram, tri-gram etc. Now the frequency of the word “the” is relatively higher than other words. So documents even with less number of the word “brown” will also be shown up which in not of our interest.

###### Solution:
We will reduce the weightage of words like “the”, “an” etc. (I mean frequently occurring words) and we will increase the weightage of the words which occurs less frequently.

## Inverted Documents Frequency (IDF): 

        IDF = log (total number of docs /Number of documents word occurs)

If the word has occurred less number of time than IDF value will be more and vice-versa. Now in final list we will have both IDF and TF. We will be showing the result on the basis of TF and IDF. IDF for a word is single number representing in the entire documents while TF is for each page.
## Project Structure and Implementation Overview
**Include**  - Important directory containing major implementation and all kind of header files required to run the project.
###### Include
- *Dataclass* - Contains class of student having necessry attributes to be loaded from document to main memory.
- *Parsers* - Contains Json Parser Library file and Handler. Hander manages all the data parsed by parser and store it inside Unordered Map.
- *Text Preprocess* - All necessary preprocess like removing special characters and tokenisation of words and filteration of stopwords along with Port stemming algorithm library to stem words are managed.
- *ParseDBinfo* - File that packs the entire project and generates a collection(i.e. Set) of Information that is utilised for searching purpose.

**Data** - 
Contains all the database files containing data in Json format that is parsed and extracted data is searched by user.

**SRC** -
Contains the source file or a sample file that can use the ParseDBinfo file and generate the necessary Front-end Interaction with the user. It can be modified as per requirement.
