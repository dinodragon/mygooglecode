#include "header.h"

void ParaInfo()
{
  BOOL fResult;
  int aMouseInfo[3];       // array for mouse information

  // Get the current mouse speed. 

  fResult = SystemParametersInfo(
    SPI_GETMOUSE,   // get mouse information 
    0,              // not used 
    &aMouseInfo,    // holds mouse information
    0);             // not used 

  // Double it. 

  if( fResult )
  {
    aMouseInfo[2] = 2 * aMouseInfo[2]; 

    // Change the mouse speed to the new value. 

    SystemParametersInfo(
      SPI_SETMOUSE,      // set mouse information
      0,                 // not used 
      aMouseInfo,        // mouse information 
      SPIF_SENDCHANGE);  // update win.ini 
  }
}