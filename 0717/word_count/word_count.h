#ifndef _WORD_COUNT_
#define _WORD_COUNT_ 

class WordCount
{
    public:
        WordCount(string filename);
        void count()
    private:
        map<string, int> words_;
        set<string> exclude_word_;
        string word_;
};
#endif  /*_WORD_COUNT_*/
