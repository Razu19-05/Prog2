#include "HandleTweets.hpp"

void openFileRead(ifstream &input,const char* fileNametweets) {
    input.open(fileNametweets,ios::in);
    if(!input.is_open()) {
        cout << "Error opening file " << fileNametweets << endl;
        exit(1);
    }
}

int readInt (ifstream &input) {
    int a;
    input >> a;
    return a;
}
char * readStr(ifstream &input, char delim) {
    char buffer[200], *cad;
    input.getline(buffer, 100, delim);
    cad = new char[strlen(buffer) + 1];
    strcpy(cad, buffer);
    return cad;
}

void reservarMemoriaIncremento(Tweets &tweets) {
    tweets.capacity += INCREMENTO;
    if (tweets.dates==nullptr and tweets.tweets == nullptr) {
        //espacio para el primer elemento
        tweets.dates = new int[tweets.capacity]{};
        tweets.tweets = new char*[tweets.capacity]{};
        tweets.nTweets = 1;
    }else {
        int *auxDates = new int[tweets.capacity]{};
        char **auxTweets = new char*[tweets.capacity]{};
        for (int i = 0; i < tweets.nTweets; i++) {
            auxDates[i]=tweets.dates[i];
            auxTweets[i]=tweets.tweets[i];
        }
        delete tweets.dates;
        delete tweets.tweets;
        tweets.dates = auxDates;
        tweets.tweets = auxTweets;
    }
}

void loadTweetsIncremental(Tweets &tweets,const char* fileNametweets) {
    ifstream input;
    openFileRead(input,fileNametweets);
    // 20230401,Just saw the most beautiful sunset today!
    int date;
    char *tweet = nullptr;
    //iniciamos las varibles
    tweets.tweets = nullptr;
    tweets.dates = nullptr;
    tweets.capacity = 0;
    tweets.nTweets = 0;
    while (true) {
        date = readInt (input);
        if (input.eof())break;
        input.get();
        tweet = readStr(input,'\n');
        if (tweets.capacity == tweets.nTweets) reservarMemoriaIncremento(tweets);
        tweets.dates[tweets.nTweets - 1] = date;
        tweets.tweets[tweets.nTweets - 1] = tweet;
        cout<<tweets.dates[tweets.nTweets - 1]<<"  "<<tweets.tweets[tweets.nTweets - 1]<<endl;
        tweets.nTweets++;
    }
}

int lookupInt(int date,int* dates) {
    for (int i = 0;dates[i];i++) if (dates[i] == date) return i;
    return -1;
}

void reservarMemoriaIncremento(char **&hashtags, int &cantidad, int &capacidad) {
    capacidad += INCREMENTO;
    if (hashtags == nullptr) {
        hashtags = new char*[capacidad]{};
        cantidad = 1;
    }else {
        char **auxHashtags = new char*[capacidad]{};
        for (int i = 0; i < cantidad; i++)
            auxHashtags[i] = hashtags[i];
        delete hashtags;
        hashtags = auxHashtags;
    }
}

void addHashtags(ifstream &input,char **&hashtags,int &cantidad, int &capacidad) {
    char * hashtag;
    hashtag = readStr(input,'\n');
    if (cantidad == capacidad)
        reservarMemoriaIncremento(hashtags,cantidad,capacidad);
    hashtags[cantidad - 1] = hashtag;
    cout<<hashtags[cantidad - 1]<<"  "<<endl;
    cantidad++;
}

void loadHashtagsIncremental(Tweets &tweets,const char*fileNamehashtags) {
    ifstream input;
    openFileRead(input,fileNamehashtags);
    // 20230401,#mondaymotivation
    int date,pos;
    int cantidades[MAXHASHTAGS]{}, capacidad[MAXHASHTAGS]{};
    tweets.hashtags = new char**[tweets.nTweets+1]{};
    while (true) {
        date = readInt(input);
        if (input.eof())break;
        input.get();
        pos = lookupInt(date,tweets.dates);
        if (pos == -1 )continue;
        addHashtags(input,tweets.hashtags[pos],cantidades[pos],capacidad[pos]);
    }
}

void loadTweets(Tweets &tweets,const char* fileNametweets,const char* fileNamehashtags) {
    loadTweetsIncremental(tweets,fileNametweets);
    loadHashtagsIncremental(tweets,fileNamehashtags);
}

void displayHashtags(ofstream &output, char **hashtags_tweet) {
    for (int i = 0; hashtags_tweet[i]; i++)
        output << right << setw(15) << hashtags_tweet[i] << endl;
    output << endl;
}

void displayTweets(int *dates, char **tweets, char ***hashtags,ofstream &output) {
    output << "DATES" << setw(80) << "TWEETS" << endl;
    for (int i = 0; dates[i]; i++) {
        output << dates[i] << setw(100) << tweets[i] << endl;
        output << "List of Hashtags:" << setw(80) << endl;
        if (hashtags[i])
            displayHashtags(output, hashtags[i]);
        else
            output << "WE COULDN'T FIND ANY HASHTAGS!" << endl;
    }
}

void displayTweets(const Tweets tweets,const char* fileNameReport) {
    ofstream output (fileNameReport,ios::out);
    displayTweets(tweets.dates,tweets.tweets,tweets.hashtags,output);
}