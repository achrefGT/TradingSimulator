#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

using namespace std;

template<class T>
class Test {
public:
    static void runTest(T valeur,T valeurAttendue, string nomTest) {
        valeur == valeurAttendue ? cout << "Test reussi : " << nomTest << endl : cout << "Test echoue : " << nomTest << endl;
    }
};
#endif // TEST_H_INCLUDED