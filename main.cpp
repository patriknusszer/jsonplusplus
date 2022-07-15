#include <iostream>
#include "jvalue.h"
#include "jarray.h"
#include "jobject.h"
#include "jconvert.h"
#include "memtrace.h"
 
using namespace std;
 
int main(int argc, const char * argv[]) {
    {
        string cfg = "{ \"szia\" : 500, \"hali\" : [ 120, { \"key\" : \"value\", \"obj\" : { \"subkey\" : 14.5 } } ] }";
        jindentcfg c;
        jvalue jv = jvalue(cfg);
        cout << "1. JSON konfiguracio hiba nelkul beolvasva!" << endl;
        jobject o = jconvert::to_jobject(jv);
        cout << "2. jvalue hiba nelkul atkonvertalva valódi altipusara!" << endl;
        jarray ja = jconvert::to_jarray(o["hali"]);
        cout << "3. objektumbol gyermek sikresen lekerve!" << endl;
        ja.del(0);
        cout << "4. 'hali' kulcsban levo tombbol 0. indexu elem sikeresen kitorolve!" << endl;
        cout << jconvert::to_double(o["szia"]);
        cout << "5. objektumbol double sikeresen lekerve!" << endl;
        o["szia"] = 450;
        cout << "6. 'szia' kulcsban sikeres megvaltozott az ertek!" << endl;
        cout << endl << o.to_string(c);
        cout << "7. a futasideju modositasoknak megfelel a kiirt objektum!" << endl;
    }
 
    return 0;
}