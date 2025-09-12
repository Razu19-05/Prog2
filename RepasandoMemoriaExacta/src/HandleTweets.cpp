#include "HandleTweets.hpp"

void readTweets(ifstream &input,int *bufferDates,char **bufferTweets,int &nTweets) {
    // 20230401,Just saw the most beautiful sunset today!
    while(true) {
        bufferDates[nTweets] = readInt(input);
        if (input.eof()) break;
        input.get();
        bufferTweets[nTweets] = readStr(input,'\n');
        nTweets++;
    }
}

void copyTweets(Tweets &tweets,int *bufferDates,char **bufferTweets,int nTweets) {
    //ReservarMemoria
    tweets.dates = new int[nTweets+1]{};
    tweets.tweets = new char*[nTweets+1]{};
    //Copiar los datos
    for(int i=0;i<nTweets;i++) {
        tweets.dates[i] = bufferDates[i];
        tweets.tweets[i] = bufferTweets[i];
        tweets.tweets[i] = assign_str(bufferTweets[i]);
    }
}

void loadTweets(const char* nombrArch,Tweets &tweets) {
    ifstream input(nombrArch,ios::in);
    if(!input.is_open()) {
        cout << "Error opening file " << nombrArch << endl;
        exit(1);
    }
    //Memoria exacta
    int bufferDates[MAX_TWEETS] {}, nTweets = 0;
    char* bufferTweets[MAX_TWEETS] {};
    readTweets(input,bufferDates,bufferTweets,nTweets);
    copyTweets(tweets,bufferDates,bufferTweets,nTweets);
}

void displayTweets(const char* nombArch,Tweets tweets) {
    ofstream output(nombArch,ios::out);
    output<<"FECHAS"<<setw(40)<<"TWEETS"<<endl;
    for (int i = 0; tweets.dates[i]; i++)
        output<<tweets.dates[i]<<"   "<<left<<tweets.tweets[i]<<right<<endl;
}

void addHashtag(ifstream &input,char ** &hashtags, int &n) {
    hashtags[n] = readStr(input,'\n');
    // cout<<hashtags[n]<<"   "<<endl;
    n++;
}

void readHashtags(ifstream &input,Tweets &tweets,int *nHashtags) {
    // 20230401,#mondaymotivation
    int date, pos;
    while (true) {
        date = readInt(input);
        if (input.eof()) break;
        input.get();
        pos = lookupInt(tweets.dates,date);
        if (pos == -1)continue;
        // cout<<pos<< "  ";
        addHashtag(input,tweets.hashtags[pos],nHashtags[pos]);
    }
}

void cut (char** &hashtags,int nHashtags) {
    if (nHashtags != 0) {
        char** temp = new char*[nHashtags+1]{};
        for (int i = 0; i < nHashtags; i++)
            temp[i] = hashtags[i];
        delete hashtags;
        hashtags = temp;
    }else {
        delete hashtags;
        hashtags = nullptr;
    }
}

void cutHastags(Tweets &tweets, int ntweets,int *nHashtags) {
    for (int i = 0; i<ntweets; i++)
        cut (tweets.hashtags[i],nHashtags[i]);
}

void loadHashtags(const char* nombrArch,Tweets &tweets) {
    ifstream input(nombrArch,ios::in);
    if(!input.is_open()) {
        cout << "Error opening file " << nombrArch << endl;
        exit(1);
    }
    //Memoria exacta
    int ntweets = 0;
    for(int i = 0; tweets.dates[i]; i++) ntweets++;//sacamos la cantidad de tweets que tengo
    int nHashtags[ntweets]{};//es el contador de segundo nivel que va contar los hashtags que tiene cada tweet,empieza de 0
    tweets.hashtags = new char **[ntweets]{};// nivel 1: reservo espacio para hashtags char**
    for (int i = 0; i < ntweets; i++) tweets.hashtags[i] = new char*[MAX_HASHTAGS]{};//reservo espacio en cada arr char*(no es exacto)
    readHashtags(input,tweets,nHashtags);
    // for (int i = 0; i<ntweets; i++) cout << i << "  " << nHashtags[i]<<endl;
    cutHastags(tweets,ntweets,nHashtags);
}

void displayHashtags(ofstream &output,char** hashtags) {
    for (int i = 0; hashtags[i]; i++)
        output<< left << setw(15) << hashtags[i] << right << endl;
    output<<endl;
}

void displayTweetsComplete(const char* nombArch,Tweets tweets) {
    ofstream output(nombArch,ios::out);
    output<<"FECHAS"<<setw(40)<<"TWEETS"<<endl;
    for (int i = 0; tweets.dates[i]; i++) {
        output<<tweets.dates[i]<<"   "<<left<<tweets.tweets[i]<<right<<endl;
        output << "List of Hashtags:" << setw(80) << endl;
        if (tweets.hashtags[i])
            displayHashtags(output,tweets.hashtags[i]);
        else output << left<< "Hashtag not found" <<right<< endl;
    }
}
