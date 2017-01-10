/*
	Note:	Borrowed from the Mat Buckland book Programming Game AI by Example
*/

#ifndef _UTILS_H__
#define _UTILS_H__

//returns the minimum of two values
template <class T>
inline T MinOf(const T& a, const T& b)
{
  if (a<b) return a; return b;
}

#endif