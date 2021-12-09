#include "CRC8.h"

#include "CRC.h"

String realString = "1123456789";



CRC8 crc;

void setup()
{
  Serial.begin(115200);
  realString = genCRC(realString);
  Serial.println(realString);
  crc.reset(); //MUST reset if need to use more than once
  bool checkIntegrity = checkCRC(realString);
  if (checkIntegrity == true){
    Serial.println("Message is valid!");
  }
  else{
    Serial.println("Message is invalid");
  }
}


void loop()
{
}

String genCRC(String checkString)
{
  char str[24];
  char stringTest[] = "";
  checkString.toCharArray(str, checkString.length()+1); //Converts the string into a char array
  crc.setPolynome(0x07); //Sets the divisor
  crc.add((uint8_t*)str, checkString.length()); //Adds the data to the CRC8 method
  sprintf(stringTest, "%c", crc.getCRC()); //Converts the CRC8 checksum to a char
  checkString += stringTest; //Appends the CRC8 Char code into the string
  return checkString;

 
}

bool checkCRC(String checksumString)
{
  char str[24];
  String msgCheckSum = "";
  char msgCheckSumArray[] = "";
  char newCheckSum[] = "";
  msgCheckSum = checksumString.substring(checksumString.length()-1); //Pulls out the old checksum at the end of submitted string
  msgCheckSum.toCharArray(msgCheckSumArray, msgCheckSum.length()+1); //Cast the old checksum to a new array
  String newCheckSumString = checksumString.substring(0,checksumString.length()-1); //Pulls out the string without checksum
  newCheckSumString.toCharArray(str, newCheckSumString.length()+1); //Converts the new string into a char array
  crc.setPolynome(0x07); //Sets the divisor
  crc.add((uint8_t*)str, newCheckSumString.length()); //Adds the new data to the CRC8 method
  sprintf(newCheckSum, "%c", crc.getCRC()); //Converts the new CRC8 checksum to a char
  
  //Checks if the new Checksum is the same
  if (msgCheckSumArray[0] == newCheckSum[0]){ //If the same, return true
    return true;
  }
  else{ //If not, return false
    return false;
  }

 
}
