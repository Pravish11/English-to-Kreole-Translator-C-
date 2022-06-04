/* SURNAME: Digumber
   NAME: Pravish Kumar
   Student ID: 2011244
   Programme: BSc (Hons) Computer Science L1, Group A
   Module: Computer Programming, ICT 1017Y
   Date: 01 June 2021
   Notes:
   1. Number of mappings : 41 136
      -There were almost 300 sentences in file KM which did not end with a punctuation mark
      -Without these words you would get around 39 000 mappings
   2. Accuracy percentage : 0 %
   3. The program below reads an english and kreole mauricien file
      -It then converts the words into lower case and does mapping as well as finds the frequency of the mappings
      -The vector removeDuplicates removes the duplicate mappings and sort them by frequency
      -The mappings are stored in text file Mapping.txt
   4. Improvement for accuracy:
      -Use a better dataset with more sentences
      -Use sentences such as "This is John","This is Mary" and each time change the name 
      the program will learn the translation of this is and will learn names
   5. Limitations of program:
      It does not ensure whether the program has well read the file for example the file might be empty 
            
*/
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Sentences {

    private:
        //string variable to store one sentence
        string sentence;
        //integer variable to store the number of words in one sentence
        int numWords;
        //boolean variable to store whether a sentence is a question
        bool isQuestion = false;
        //vector of type string to store the words in a sentence
        vector<string> words;

    public:
        Sentences();
        Sentences(string s);
        //get and set method to retrieve a sentence and to change it
        string getSentence();
        void setSentence(string s);
        //method to return the number of words in a sentence
        int getNumWords();
        //method to determine whether a sentence is a question
        bool isSentenceAQuestion();
        //method to return all the words in a sentence (as a vector)
        vector<string> getWords();
        //sentences less than n words
        bool isSentenceLessThan(int n);
        //sentences greater than or equal to n words
        bool isSentenceGreaterThanOrEqualTo(int n);
        ~Sentences();
};

Sentences::Sentences(){}

Sentences::Sentences(string s)
{
    sentence = s;
    numWords = getNumWords();
    isQuestion = isSentenceAQuestion();
}

string Sentences::getSentence(){
    return sentence;
}

void Sentences::setSentence(string s){
    sentence = s;
}

int Sentences::getNumWords(){
    int numChars = sentence.length();
    vector<string> setOfWords;
    string currentWord;
    for(int i=0;i<numChars;i++){
        if(sentence[i] == ' ' && !currentWord.empty()){
            setOfWords.push_back(currentWord);
            currentWord.clear();
        }
    else{
        currentWord += sentence[i];
        }
    }

    return (setOfWords.size() + 1);
}

vector<string> Sentences::getWords(){
    int numChars = sentence.length();
    string currentWord;
    words.clear();

    for(int i=0;i<numChars;i++){
        if(sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'){
            words.push_back(currentWord);
            currentWord.clear();
        }
        else {
            currentWord += sentence[i];
        }
    }

    return words;
}

bool Sentences::isSentenceAQuestion(){
    int numChars = sentence.length();
    if(sentence[numChars-1] == '?')
        isQuestion = true;
    return isQuestion;
}

//sentences less than n words
bool Sentences::isSentenceLessThan(int n){
    int numberWords = getNumWords();

    if(numberWords < n) {
        return true;
    }
    else {
        return false;
    }
}

//sentences greater than or equal to n words
bool Sentences::isSentenceGreaterThanOrEqualTo(int n){
    int numberWords = getNumWords();

    if(numberWords >= n) {
        return true;
    }
    else {
        return false;
    }
}

Sentences::~Sentences(){}

class Words {

    private:
        //string variable to store one word
        string word;
        //integer variable to store the number of characters in one word
        int numCharacters;
        //boolean variable to store whether a word starts with an uppercase character
        bool firstCharacterUpperCase = 0;
        //vector of type char to store the individual characters in a word
        vector<char> characters;

    public:
        Words();
        //get and set method to retrieve a sentence and to change it
        string getWord();
        void setWord(string w);
        //method to return the number of characters (length) in a sentence
        int getNumCharacters();
        //method to determine whether a word starts with an Uppercase character
        bool isFirstCharacterUpperCase();
        //method to return all the words in a sentence (as a vector)
        vector<char> getCharacters();
        ~Words();
};

Words::Words(){}

string Words::getWord(){
    return word;
}

void Words::setWord(string w){
    word = w;
}

int Words::getNumCharacters(){

    return word.length();
}

vector<char> Words::getCharacters(){

    int numChars = word.length();

    for(int i=0;i<numChars;i++){
        characters.push_back(word[i]);
    }

    return characters;
}

bool Words::isFirstCharacterUpperCase(){
    if(isupper(word[0])){
        return 1;
    }
    else {
        return 0;
    }
}

Words::~Words(){}

class Mapping
{
private:
    string translate; //stores the eng word and the kreole word when mapped
    int freq;         //stores frequency of mapping
public:
    Mapping();
    Mapping(string t,int f);
    string gettranslate();
    void settranslate(string t);
    int getfrequency();
    void setfrequency(int f);
    ~Mapping();
};
Mapping::Mapping(){};
Mapping::Mapping(string t,int f)
{
    translate=t;
    freq=f;
}
string Mapping::gettranslate()
{
    return translate;
}
void Mapping::settranslate(string t)
{
    translate=t;
}
int Mapping::getfrequency()
{
    return freq;
}
void Mapping::setfrequency(int f)
{
    freq=f;
}

Mapping::~Mapping(){}

void convertToLower(string& s) //converts to lower case
{
    for (int i=0;i<s.length();i++)
    {
        s[i]=tolower(s[i]);
    }
}
bool sortFrequency(Mapping a,Mapping b)//compares frequency
{
    return (a.getfrequency()>b.getfrequency());
}
int main()
{
    cout<<"MAPPING OF ENGLISH WORDS TO KREOL MORISIEN WORDS"<<endl;

    //SENTENCES
    //vector variable to store the individual words in one sentence
    vector<string> EngwordsFromSentence;

    //vector variable to store all the sentences from the dataset
    vector<string> allEngSentences;

    //temporary string variable to store each sentence from the dataset
    string sentenceFromFile;

    //integer variable to count the number of lines/sentences in the dataset
    int countEngSentence = 0;

    //codes to load the sentences dataset from a text file into a vector
    ifstream infile;
	infile.open ("1000_English_A_040521.txt");
    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        allEngSentences.push_back(sentenceFromFile);
        countEngSentence++;
    }
	infile.close();
   // cout<<"count= "<<countEngSentence<<endl;
    vector<Sentences> sentEnglish(countEngSentence);
	//assign each extracted sentence (from dataset) to one Sentence object
    for(int i=0; i<countEngSentence; i++)
        {
        sentEnglish[i].setSentence(allEngSentences[i]);
    }


    //vector variable to store the individual words in one sentence
    vector<string> KMwordsFromSentence;

    //vector variable to store all the sentences from the dataset
    vector<string> allKMSentences;

    //integer variable to count the number of lines/sentences in the dataset
    int countKMSentence = 0;

    //codes to load the sentences dataset from a text file into a vector
	infile.open ("1000_KM_A_040521.txt");
    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        allKMSentences.push_back(sentenceFromFile);
        countKMSentence++;
    }
	infile.close();
    //cout<<"count= "<<countKMSentence<<endl;
    vector<Sentences> sentKM(countKMSentence);
	//assign each extracted sentence (from dataset) to one Sentence object
    for(int i=0; i<countKMSentence; i++)
        {
        sentKM[i].setSentence(allKMSentences[i]);
    }

    string engword;//stores english word
    string kmword;// stores kreole word
    string storemap;//stores mapping
    vector<string>storeMapping;//vector to store mappings
    for (int i=0;i<countEngSentence;i++)
    {
        EngwordsFromSentence=sentEnglish[i].getWords();
        KMwordsFromSentence = sentKM[i].getWords();
        for (int j=0;j<EngwordsFromSentence.size();j++)
        {
            engword=EngwordsFromSentence[j];
            convertToLower(engword);
            for (int k=0;k<KMwordsFromSentence.size();k++)
            {
                kmword=KMwordsFromSentence[k];
                convertToLower(kmword);
                storemap=engword+" "+kmword; //concatenate eng and kreole word
                storeMapping.push_back(storemap);//stores both in vector ex: I Moi
                
            }
        }
    }
    string currentWord; //variable to store the current eng and kreole word
	Mapping m; //object m
	vector<Mapping>maps; //vector to store the object m
	int fcount=0;
    for (int i=0;i<storeMapping.size();i++)
    {
        currentWord=storeMapping[i];
        for (int j=0;j<storeMapping.size();j++)
        {
            if (currentWord==storeMapping[j])
            {
                fcount=fcount+1;  //count frequencies of mappings
            }
        }
      m.settranslate(currentWord);
      m.setfrequency(fcount);
      maps.push_back(m); //vector maps stores object m with attributes w and fcount
        fcount=0; //Reinitialize the counter for the next set of words
    }
    
    vector<Mapping>removeduplicates(maps.size());//vector which has unique mappings with their respective frequencies
    for(int i=0;i<maps.size();i++)
    {
       removeduplicates[i].settranslate(" "); //initializing the vector
       removeduplicates[i].setfrequency(0);
    }
    ofstream fout;
    fout.open("Mapping.txt"); //file to store mappings
    bool matching=false;//variable to check if word from vector maps is equal to vector in removeduplicates
for (int i=0;i<maps.size();i++)
{
    for (int j=0;j<removeduplicates.size();j++)
    {
        if(maps[i].gettranslate()==removeduplicates[j].gettranslate())//to remove duplicate mappings in the vector removeduplicates
        {
            matching=true;
        }
    }
    if (matching==false)// if matching==false then go to index i in vector remove duplicates and push the value found at i in vector maps
    {
        removeduplicates[i].settranslate(maps[i].gettranslate());
        removeduplicates[i].setfrequency(maps[i].getfrequency());
    }
    matching=false;//re initialize the variable for next set of data
}
sort(removeduplicates.begin(),removeduplicates.end(),sortFrequency);//sorting the vector by frequency
    for (int i=0;i<removeduplicates.size();i++)
    {
        if (removeduplicates[i].getfrequency()!=0) //write only mappings with frequencies > 0 in text file
        {
            fout<<removeduplicates[i].gettranslate()<<" "<<removeduplicates[i].getfrequency()<<"."<<endl;
}
        }


fout.close();

    return 0;
}
