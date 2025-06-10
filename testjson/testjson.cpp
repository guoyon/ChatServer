#include "json.hpp"
using json = nlohmann::json;

#include <vector>
#include <iostream>
#include <string>

using namespace std;

void func1()
{
    json js;
    js["id"] = {1,2,3,4,5};
    js["name"] = "guoyongqi";
    js["msg"]["gg"] = "hello world";
    js["msg"]["yy"] = "hello china";
    cout << js << endl;
}

string func2()
{
    json js;
    js["id"] = {1,2,3,4,5};
    js["name"] = "guoyongqi";
    js["msg"]["gg"] = "hello world";
    js["msg"]["yy"] = "hello china";
    //cout << js << endl;
    return js.dump();
}

int main()
{
    //func1();
    string revbuf = func2();
    json jsbuf = json::parse(revbuf);
    cout << jsbuf["id"] << endl;
    return 0;
}