#include "src/HandleTweets.hpp"
#include "structs/Structs.hpp"

int main() {
    Tweets tweets;
    loadTweets("Data/tweets.csv",tweets);
    displayTweets("Reporte/ReporteTweets.txt",tweets);
    loadHashtags("Data/hashtags.csv",tweets);
    displayTweetsComplete("Reporte/ReporteCompleto.txt",tweets);

    return 0;
}