#include <iomanip>

using namespace std;
 
/**
   Header file for the Convert class.
*/

class Convert
{
     private:

     public:
          Convert();
         ~Convert();

		 string      decimal_hex(int decimal);
		 int         hex_decimal(string hex);
};
