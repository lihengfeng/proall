/*************************************************************************
  > File Name: ../base/adler32.h
  > Author: ma6174
  > Mail: 17704623602@163.com 
  > Created Time: Mon Nov  6 14:02:09 2017
 ************************************************************************/
#pragma once
#include<stdint.h>

namespace netxy{
	namespace base{

		uint32_t adler32(const char *data, int32_t len); /* where data is the location of the data in physical memory and*/
	}
}
