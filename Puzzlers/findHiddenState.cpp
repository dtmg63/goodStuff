#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
//#include <algorithm>
//#include <cstdlib>

using namespace std;


//----------------------------------------------------------------------------------

std::string upperCase(std::string input) 
{
  for (std::string::iterator it = input.begin(); it != input.end(); ++ it)
    *it = toupper((unsigned char)*it);
  return input;
}



//----------------------------------------------------------------------------------

int main()
{
 ifstream worldCapsFile("worldCapitals.txt");
 ifstream statesAndCapsFile("statePlusCapitals.txt");
 
 vector<string> worldCaps;
 vector<string> countries;
 vector<string> stateCaps;
 vector<string> states;
 
 std::stringstream tokenStream;

//....Step 1: Open text file for world Capitals and fill array of strings, removing any blanks.

  if (worldCapsFile.is_open())
  {
    string curLine, countryString, capitolString, token;

    while ( getline(worldCapsFile, curLine) ) 
    {
      // Divide line into two strings
      tokenStream.str(curLine);
      bool odd = true;
      while (getline(tokenStream, token, ','))
        {
            //std::cout << token << std::endl;
            if (odd) 
              countries.push_back(token);
            else
              worldCaps.push_back(token);
              
            odd = !odd;
        }
        tokenStream.clear();
        tokenStream.str("");
    }
    worldCapsFile.close();
    // for (int i=0; i<countries.size(); ++i) std::cout << countries[i] << std::endl;
  } 
  else
  {
    std::cout << "Error opening world caps file" << std::endl;
    worldCapsFile.close();
    statesAndCapsFile.close();
    
    return(0);
  }
  


//....Step 2: Open text file for state and capital and fill arrays of strings, removing any blanks.
  if (statesAndCapsFile.is_open())
  {
    string curLine, stateString, capitolString, token;

    while ( getline(statesAndCapsFile, curLine) ) 
    {
      // Divide line into two strings
      tokenStream.str(curLine);
      bool odd = true;
      while (getline(tokenStream, token, ','))
        {
            //std::cout << token << std::endl;
            if (odd) 
              states.push_back(token);
            else
              stateCaps.push_back(token);
              
            odd = !odd;
        }
        tokenStream.clear();
        tokenStream.str("");
    }
    
    //for (int i=0; i<states.size(); ++i) std::cout << stateCaps[i] << std::endl;
  }
  else
  {
    std::cout << "Error opening states and caps file" << std::endl;
    worldCapsFile.close();
    statesAndCapsFile.close();
  }

//....Step 3: Concatenate every state capital with every world capital and parse for state in between

  string capitalsGlom;
  std::size_t found;
  for (int i = 0; i<stateCaps.size(); ++i)
  {
    for (int j = 0; j<worldCaps.size(); ++j)
    {
      capitalsGlom = upperCase(stateCaps[i]) + upperCase(worldCaps[j]);         
      //std::cout << upperCase(capitalsGlom) << std::endl;
      for (int k = 0; k<stateCaps.size(); ++k)
      {
        found = capitalsGlom.find(upperCase(states[k]));
        if (found != std::string::npos)
        {
          if (upperCase(states[k]).compare("WASHINGTON") != 0 &&
              upperCase(states[k]).compare("INDIANA")    != 0 && 
              upperCase(states[k]).compare("OKLAHOMA") )
              std::cout << "found answer:   " << states[k] << " in: " << capitalsGlom 
                        << " from state: " << states[i] 
                        << " and country: " << countries[j] << std::endl;
        }
      }
    }

  }


//....Step 4: Clean up
    worldCapsFile.close();
    statesAndCapsFile.close();

  return(0);
}
