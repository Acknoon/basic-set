#include "include/Set.h"


int main() {
    Set s1;
    double a = 99;
//    cout << s1.add("cool", 666) << endl;
    cout << s1.add("k1", 2) << endl;
    cout << s1.add("k23", 123) << endl;
    cout << s1.add("k3", 321) << endl;
    cout << s1.add("k2", 1) << endl;
    cout << s1.remove("nothing") << endl;
//    cout << s1.remove("cool") << endl;
    cout << s1.isInSet("k23", a) << '\n';
//    cout << s1.isInSet("cool", a) << '\n';
    cout << s1.isInSet("test", a) << '\n';
    cout << a << "the value of a" << endl;
    cout << s1.sumSet() << "sum of the set" << endl;
    cout << "Hello, World!" << std::endl;
    cout << s1.totWeight() << endl;
    Set s2(s1);
    cout << s2.totWeight() << endl;
    s1.printSet();
    cout << s2.remove("k2") << endl;

    s1 = s1 - s2;
    s1.printSet();

    Set s3;
    cout << s3.add("k1", 666) << endl;
    s3 = s3 | s1;
    s3.printSet();
    cout << s2.add("k5", 7) << endl;
    cout << s2.add("k4", 7) << endl;
    s2.printSet();

    cout << s3.add("k4", 00) << endl;
    s3.printSet();
    s2 = s2 & s3;
    cout << "!" << endl;
    cout << s2.add("k4", 999) << endl;
    s2.printSet();
    cout << "test" << endl;
    s3.printSet();

    return 0;
}
