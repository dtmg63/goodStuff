#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <math.h>



using namespace std;


void checkStringUpsideDown(string str, string origStr)
{

  //.....Step 1: Break up string into 3 integers
  string str1 = str.substr(0,2);
  string str2 = str.substr(2,2);
  string str3 = str.substr(4,2); //str.length());

  string Ostr1 = origStr.substr(0,2);
  string Ostr2 = origStr.substr(2,2);
  string Ostr3 = origStr.substr(4,2); //str.length());

  //.....Step 2: Check the equation for correctness
  int num1 = atoi(str1.c_str());
  int num2 = atoi(str2.c_str());
  int num3 = atoi(str3.c_str());
  int result = num2-num3;

  int num1_o = atoi(Ostr1.c_str());
  int num2_o = atoi(Ostr2.c_str());
  int num3_o = atoi(Ostr3.c_str());

  bool only2changes = ((num1 - num1_o)==0 ) || ((num2-num2_o)==0) || ((num3-num3_o)==0);

  //....Step 3: Print out the string if correct
  if ( (result - num1) == 0 && only2changes)
  {
    std::cout << Ostr1 << " - " << Ostr2 << " = " << Ostr3  << std::endl;
    std::cout << str1  << " = " << str2 << " - "  << str3   << std::endl << std::endl;
  }

  return;
}



// Function to print permutations of string str
// using next_permute()
void permuteUpsideDown(string str)
{
    int counter = 0;
    string origStr = str;

    // Sort the string in lexicographically ascennding order
     sort(str.begin(), str.end());

    std::cout << "..... Checking Upside down Permutations of " << origStr << " ......" << std::endl;
 
    // Keep printing next permutation while there
    // is next permutation
    do {
       //cout << str << endl;
       counter++;
       checkStringUpsideDown(str, origStr);
    } while (next_permutation(str.begin(), str.end()));

    std::cout << "Finished checking " << counter << " permutations of " << str << std::endl << std::endl;

    return;
}


void checkString(string str, string origStr)
{

  //.....Step 1: Break up string into 3 integers
  string str1 = str.substr(0,2);
  string str2 = str.substr(2,2);
  string str3 = str.substr(4,2); //str.length());

  string Ostr1 = origStr.substr(0,2);
  string Ostr2 = origStr.substr(2,2);
  string Ostr3 = origStr.substr(4,2); //str.length());


  //.....Step 2: Check the 2-digit integer equation for correctness
  int num1 = atoi(str1.c_str());
  int num2 = atoi(str2.c_str());
  int num3 = atoi(str3.c_str());
  int result = num1 - num2;

  int num1_o = atoi(Ostr1.c_str());
  int num2_o = atoi(Ostr2.c_str());
  int num3_o = atoi(Ostr3.c_str());

  bool only2changes = ((num1 - num1_o)==0 ) || ((num2-num2_o)==0) || ((num3-num3_o)==0);

  //....Step 3: Print out the string if correct
  if ( (result - num3) == 0 && only2changes)
  {
    std::cout << Ostr1 << " - " << Ostr2 << " = " << Ostr3  << std::endl;
    std::cout << str1  << " - " << str2  << " = " << str3   << std::endl << std::endl;
  }

  //....Step 4: Check for superscripts when forming the integers
  int a = atoi( (str.substr(0,1)).c_str() );
  int b = atoi( (str.substr(1,1)).c_str() );
  int c = atoi( (str.substr(2,1)).c_str() );
  int d = atoi( (str.substr(3,1)).c_str() );
  int e = atoi( (str.substr(4,1)).c_str() );
  int f = atoi( (str.substr(5,1)).c_str() );

  int num1Exp = (int)pow((float)a, (float)b);
  int num2Exp = (int)pow((float)c, (float)d);
  int num3Exp = (int)pow((float)e, (float)f);

  //std::cout << "checking exponents: " << a << " to the power " << b << " = " << num1Exp << std::endl;

  int val1 = num1Exp - num2;
  int val2 = num1 - num2Exp;
  int val3 = num1Exp - num2Exp;

  bool exp1_a = (val1 == num3);
  bool exp1_b = (val1 == num3Exp);
  bool exp2_a = (val2 == num3);
  bool exp2_b = (val2 == num3Exp);
  bool exp3_a = (val3 == num3);
  bool exp3_b = (val3 == num3Exp);


  bool only1change = ((num1 - num1_o)==0 ) + ((num2-num2_o)==0) + ((num3-num3_o)==0) == 1;
  bool noChanges   = ((num1 - num1_o)==0 ) && ((num2-num2_o)==0) && ((num3-num3_o)==0);

  if ((exp1_a || exp2_a ) && only2changes)
  {
     std::cout << Ostr1 << " - " << Ostr2 << " = " << Ostr3  << std::endl;
     if (exp1_a) std::cout << a << "^" << b << " - " << num2 << " = " << num3 << std::endl << std::endl;
     if (exp2_a) std::cout << num1 << " - " << c << "^" << d << " = " << num3 << std::endl << std::endl;
  }	

// ..... have 2 exponents being used .....
  if ((exp3_a || exp2_b || exp1_b) && (only1change || only2changes ) )
  {
     std::cout << Ostr1 << " - " << Ostr2 << " = " << Ostr3  << std::endl;
     if (exp1_b) std::cout << a << "^" << b << " - " << num2 << " = " << e << "^" << f << std::endl << std::endl;
     if (exp2_b) std::cout << num1 << " - " << c << "^" << d << " = " << e << "^" << f << std::endl << std::endl;
     if (exp3_a) std::cout << a << "^" << b << " - " << c << "^" << d << " = " << num3 << std::endl << std::endl;
  }

// ..... all three numbers have exponents, so this is against the rules
  if (exp3_b && noChanges )
  {
     std::cout << "****** NOT a legal answer, But.......  ******" << std::endl;
     std::cout << Ostr1 << " - " << Ostr2 << " = " << Ostr3  << std::endl;
     std::cout << a << "^" << b << " - " << c << "^" << d << " = " << e << "^" << f << std::endl << std::endl;
  }	


  return;
}



// Function to print permutations of string str
// using next_permute()
void permute(string str)
{
   int counter = 0;
   string origStr = str;

    // Sort the string in lexicographically ascennding order
    sort(str.begin(), str.end());

    std::cout << "..... Checking Permutations of " << origStr << " ......" << std::endl;
 
    // Keep printing next permutation while there
    // is next permutation
    do {
       counter++;
       checkString(str, origStr);
    } while (next_permutation(str.begin(), str.end()));


    std::cout << "Finished checking " << counter << " permutations of " << str << std::endl<< std::endl;
    return;
}

int main()
{

  string origEquation = "65-43=21";
  string origNums     = "654321";
  string change6Nums  = "954321";
  string change2Nums  = "655431";
  string change5Nums  = "643221";
  string changeFlip3  = "924351";
  string change6and2Nums = "955431";
  string change6and5Nums = "922431";

  std::cout << std::endl << std::endl;

  //...... Step 2: Iterate through permutations of the original 6 characters ......
  //...............................................................................

  permute(origNums);
/*
  permute(change6Nums);
  permute(change2Nums);
  permute(change5Nums);
  permute(change6and2Nums);
  permute(change6and5Nums);
  permute(changeFlip3);
  permuteUpsideDown(change6Nums);
*/



  return(0);
}



// Code to save
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/*
//char origNums[7] = "654321";
std::set<char> origSet;
//...... Step 1: Load all of the strings/char arrays ......
//.........................................................
for (int i = 6; i> 0; --i)
{
 //std::string intStr = std::to_string(i+1);
 //origSet.insert(intStr);
 origSet.insert((char) i);
}

//..... Print to screen 
std::cout << "origNums is: " << origNums << std::endl;
std::cout << "origEquation is: " << origEquation << std::endl;


//for (std::set<std::string>::iterator it=origSet.begin(); it!=origSet.end(); ++it)
for (std::set<char>::iterator it=origSet.begin(); it!=origSet.end(); ++it)
{
   //std::cout << ' ' << (int)*it;
   std::cout << ' ' << static_cast<unsigned>(*it);
   std::cout << std::endl;
}
*/

