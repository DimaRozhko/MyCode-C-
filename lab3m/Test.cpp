#include "List.h"

int main(){
    try{
        List<CFile> catalog;
        catalog.openFile("fileBase.csv");   
        catalog.Print(); 
        CFile* node = new CFile(); 
        node->setAll("fle6598.txt;24/06/1998;146");  
        catalog.push_front(*node);               
        catalog.Print();                            
        catalog.delLowCFile("04/06/2005");                
        catalog.changeNameFile("12e1k65.h", "second.txt");
        catalog.Print();                  
        List<CFile> catalogOut;                 
        List<CFile>::iterator it;
        it = catalog.begin();                       
        catalog.splice(it, catalogOut);                 
        it = catalog.end();                          
        catalog.splice(it, catalogOut);
        node->setAll("qwerty.c;06/08/2018;103");
        it = catalog.find(*node);            
        catalog.splice(it, catalogOut);
        catalogOut.Print();
        catalog.Print();
        it = catalogOut.end();
        catalogOut.splice(it, catalog);                 
        catalogOut.Print();
        catalog.Print();
        cout << "Size -catalogOut-: " << catalogOut.size() << endl;
        cout << "Size -catalog-: " << catalog.size() << endl;
        if(catalogOut.empty() == true)
            cout << "Empty -catalogOut-" << endl;
        else cout << "No empty -catalogOut-" << endl;
        catalogOut.clear();
        catalog.clear();
        if(catalogOut.empty() == true)
            cout << "Empty -catalogOut-" << endl;
        else cout << "No empty -catalogOut-" << endl;  
    }
    catch(runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}