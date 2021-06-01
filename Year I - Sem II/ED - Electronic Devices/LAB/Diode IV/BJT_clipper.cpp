#include <iostream>

using namespace std;

int main(){
  float Ece = 17.6, Re = 2000, Rc = 2600, Rb1 = 75000, Rb2 = 13000;
  float Vbe0 =  0.6;

  float Ebb = (Rb2/(Rb1 + Rb2))*Ece;
  float Rbb = (Rb1 * Rb2)/(Rb1 + Rb2);
  float Ic_q = (Ebb - Vbe0)/Re;
  float Vce_q = Ece - Ic_q * (Rc + Re);

  cout << Vce_q << ", " << Ic_q;

  // float Ic_q = 0.00075;
  // float Vce_q = 7.5;
  //
  // Re = Ic_q/(Ebb-Vbe0);
  // Rc = (Ece - Vce_q)/Ic_q - Re;
  //
  // cout << Re << ", " << Rc;
}
