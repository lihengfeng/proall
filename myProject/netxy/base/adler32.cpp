/*************************************************************************
	> File Name: adler32.cpp
	> Author: ma6174
	> Mail: 17704623602@163.com 
	> Created Time: Mon Nov 13 10:03:11 2017
 ************************************************************************/

#include<iostream>
using namespace std;

namespace netxy{
	namespace base{

		uint32_t adler32(const char *data, int32_t len) // where data is the location of the data in physical memory and
		{
			const int MOD_ADLER = 65521;

			uint32_t a = 1, b = 0;
			int32_t index;

			/* Process each byte of the data in order */
			for (index = 0; index < len; ++index)
			{
				a = (a + data[index]) % MOD_ADLER;
				b = (b + a) % MOD_ADLER;
			}

			return (b << 16) | a;
	}
	}
}
