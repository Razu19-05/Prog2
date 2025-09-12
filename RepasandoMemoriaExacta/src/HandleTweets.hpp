

#ifndef REPASANDOMEMORIAEXACTA_HANDLETWEETS_HPP
#define REPASANDOMEMORIAEXACTA_HANDLETWEETS_HPP
#include "Functions.hpp"

void loadTweets(const char* ,Tweets &tweets);
void readTweets(ifstream &input,int *bufferDates,char **bufferTweets,int &nTweets) ;
void copyTweets(Tweets &tweets,int *bufferDates,char **bufferTweets,int nTweets) ;

void displayTweets(const char* ,Tweets tweets);

void loadHashtags(const char* ,Tweets &tweets);
void readHashtags(ifstream &input,Tweets &tweets,int *nHashtags) ;
void addHashtag(ifstream &input,char ** &hashtags, int &n) ;
void cutHastags(Tweets &tweets, int ntweets,int *nHashtags) ;
void cut (char** &hashtags,int nHashtags) ;

void displayTweetsComplete(const char* ,Tweets tweets);

#endif //REPASANDOMEMORIAEXACTA_HANDLETWEETS_HPP