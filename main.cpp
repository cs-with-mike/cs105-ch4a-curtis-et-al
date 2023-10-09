#include "PureLexer.h"

int main(int argc, char *argv[]) {
    PureLexer p("../sample.tk", "../out.sample.curtis.txt");
    while (p.next_token()->type != T_NULL);
}
