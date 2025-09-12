
#ifndef REPASANDOMEMORIADINAMICA_HANDLETWEETS_HPP
#define REPASANDOMEMORIADINAMICA_HANDLETWEETS_HPP
#include "Utils.hpp"
#include "../structs/Tweets.hpp"

void loadTweets(Tweets &tweets,const char* fileNametweets,const char* fileNamehashtags);
void displayTweets(const Tweets tweets,const char* fileNameReport);

#endif //REPASANDOMEMORIADINAMICA_HANDLETWEETS_HPP