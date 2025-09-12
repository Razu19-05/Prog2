

#ifndef REPASANDOMEMORIADINAMICA_TWEETS_HPP
#define REPASANDOMEMORIADINAMICA_TWEETS_HPP
struct Tweets {
    int * dates;
    char ** tweets;
    char *** hashtags;
    int capacity;
    int nTweets;
};

#endif //REPASANDOMEMORIADINAMICA_TWEETS_HPP