#include "text_corrector.h"
#include "get_config.h"

int main(int argc, const char *argv[])
{
    //MakeDictCn md;
//    MakeDicEn md("in.txt");
    //TextCorrector tc("a.txt");
    GetConfig gc;
    gc.readConfig("config.txt");
    return 0;
}
