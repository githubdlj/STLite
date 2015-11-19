/********************************************************************
	Time:	  2015/10/21
	Filename: main
	Author:	  dinglj
	
	Purpose:  main,test private_tes && public_test
*********************************************************************/

//#include "public_test.h"
#include "../detail_test/private_test.h"

//////////////////////////////////////////////////////////////////////

int main()
{
    cout << "Hello STLite" << endl;
    
//    public_test();
    private_test();
    
    cout << endl;
    system("pause");
    return true;
}

