/*
	ShiftBriteHughesy.pp - A library to run shiftbrites
	Created by Ashley J. Hughes, 17 May 2010.
	Based on a post found @ http://macetech.com/blog/node/54
*/
#include "WProgram.h"
#include "ShiftBriteHughesy.h"

ShiftBriteHughesy::ShiftBriteHughesy()
{
	_dPin = 10;
	_lPin = 11;
	_ePin = 12;
	_cPin = 13;
	
	pinMode(_dPin, OUTPUT);
	pinMode(_lPin, OUTPUT);
	pinMode(_ePin, OUTPUT);
	pinMode(_cPin, OUTPUT);

	digitalWrite(_lPin, LOW);
	digitalWrite(_ePin, LOW);
}

void ShiftBriteHughesy::_SB_SendPacket() 
{
  _SB_CommandPacket = _SB_CommandMode & B11;
  _SB_CommandPacket = (_SB_CommandPacket << 10)  | (_SB_BlueCommand & 1023);
  _SB_CommandPacket = (_SB_CommandPacket << 10)  | (_SB_RedCommand & 1023);
  _SB_CommandPacket = (_SB_CommandPacket << 10)  | (_SB_GreenCommand & 1023);

  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket >> 24);
  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket >> 16);
  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket >> 8);
  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket);

  delay(1); // adjustment may be necessary depending on chain length
  digitalWrite(_lPin,HIGH); // latch data into registers
  delay(1); // adjustment may be necessary depending on chain length
  digitalWrite(_lPin,LOW);
}

void ShiftBriteHughesy::sendColour(int r, int g, int b)
{

    _SB_CommandMode = B00;
    _SB_RedCommand = r;
    _SB_GreenCommand = g;
    _SB_BlueCommand = b;
    _SB_SendPacket();
}