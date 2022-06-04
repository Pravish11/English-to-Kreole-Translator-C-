/* SURNAME: Digumber
   NAME: Pravish Kumar
   Programme: BSc (Hons) Computer Science L1
   Module: Computer Programming, ICT 1017Y
   Date: 01 June 2021
   Notes:
   1. The program below reads mapping file and store them in a vector
   2. It then reads 1000 english sentences from a file and store them in a vector
   3. It takes the fist sentence, breaks them in words and search each english word in the mapping vector
      IF found it then compares the frequency
      The corresponding eng word with the highest frequency will give the kreole word
      The translated sentences are output in text file Translated.txt
   4. The program accuracy will check if the manually translated sentences matches the automatically translated   
   */
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ostream>
#include <fstream>
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
    string eng;
    string km;
    string frequency;//stores frequency of string datatype
    int freq;//stores frequency of int datatype
public:
    Mapping();
    Mapping(string e,string k,string f);
    string geteng();
    void seteng(string e);
    string getkm();
    void setkm(string k);
    int getfrequency();//returns frequency as integer
    void setfrequency(string f);//takes frequency as string
    ~Mapping();
};
Mapping::Mapping(){};
Mapping::Mapping(string e,string k,string f)
{
    eng=e;
    km=k;
    frequency=f;
}
string Mapping::geteng()
{
    return eng;
}
void Mapping::seteng(string e)
{
    eng=e;
}
string Mapping::getkm()
{
    return km;
}
void Mapping::setkm(string k)
{
    km=k;
}
int Mapping::getfrequency()
{
    freq=stoi(frequency);
    return freq;
}
void Mapping::setfrequency(string f)
{
    frequency=f;
}
Mapping::~Mapping(){}

void convertToLower(string& s) //converts to lower case
{
    for (int i=0;i<s.length();i++)
    {
        s[i]=tolower(s[i]);
    }
}
int main()
{
    cout<<"***English to Kreol Moricien Translator***"<<endl;
    vector<string> wordsFromSentence;//separates eng word  km word and frequency
    string sentenceFromFile;//variable to store line
    vector<string>allSentences;//stores each line from mapping file ex: I Mo 100
    int countSentence=0;
    ifstream infile;
    infile.open("Mapping.txt");//opens file which contains mapping with frequency

    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        allSentences.push_back(sentenceFromFile);//read the file and place each line in vector allSentences
        countSentence++;
    }
	infile.close();

    //creating a vector of objects of type sentences
    vector<Sentences> s(countSentence);
    int index=0;
    Mapping m;
    vector<Mapping>maps;//vector to store eng word, kreole word and frequency
    string temp;//variable to store temporary data

    //assign each extracted sentence (from dataset) to one Sentence object
    for(int i=0; i<countSentence; i++){
        s[i].setSentence(allSentences[i]);
    }
    for(int i=0; i<countSentence; i++){

        wordsFromSentence = s[i].getWords();//words from sentence will have the eng word the kreole word and the frequency
        
        for(int i=0; i<wordsFromSentence.size(); i++){
           temp=wordsFromSentence[i];
           if (i==0)//wordsFromSentence[0] contains english words only
           {
               m.seteng(temp);
           }
           if (i==1)//wordsFromSentence[1] contains kreole words
            {
               m.setkm(temp);
           }
           if(i==2)//wordsFromSentence[2] contains frequencies
           {
               m.setfrequency(temp);
           }

       }
       maps.push_back(m);
    }
    
    allSentences.clear();//clear the vector
countSentence=0;
infile.open("1000_English_A_110521_Test.txt");//reads the test file

    while(!infile.eof()) {
        getline(infile,sentenceFromFile);
        allSentences.push_back(sentenceFromFile);//puts the sentences in vector allSentences
        countSentence++;
    }
	infile.close();
vector<Sentences> sentEng(countSentence);
for (int i=0;i<countSentence;i++)
{
    sentEng[i].setSentence(allSentences[i]);
}
int highestfreq=0;
string krol;//variable to store the kreole word
string translatedsentence="";
vector<string> engword;
ofstream fout;
fout.open("Translated.txt");//file which contains the translation of the english sentences
for (int a=0;a<countSentence;a++){
    engword = sentEng[a].getWords();//takes first sentences in test file and returns the words
    for(int i=0;i<engword.size();i++)
    {
        temp=engword[i];//store the current word in vector engword
        convertToLower(temp);
        for (int j=0;j<maps.size();j++)
        {
            if (temp==maps[j].geteng())//checks the word in vector english
            {
                if(maps[j].getfrequency()>=highestfreq)//if found then checks if frequency >maximum
                {
                    highestfreq=maps[j].getfrequency();//stores highestfreqeuncy
                    krol= maps[j].getkm();//stores the kreole word
                }
            }
        }
        highestfreq=0;//re initialize after checking all frequencies of corresponding word
        translatedsentence=translatedsentence+' '+krol;
    }
    fout<<translatedsentence<<"."<<endl;//output translated sentence in file
    translatedsentence.clear();

}
fout.close();

    return 0;
}
