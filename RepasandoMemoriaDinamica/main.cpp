#include "src/HandleTweets.hpp"
#include "structs/Tweets.hpp"
int main() {
    Tweets tweets{};
    loadTweets(tweets,"Data/tweets.csv","Data/hashtags.csv");
    displayTweets(tweets,"Report/reporte.txt");
    return 0;
}   