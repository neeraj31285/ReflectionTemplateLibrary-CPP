
#include <complex>

#include "Complex.h"


std::string reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr;
}

std::string reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr;
}

namespace complex
{
	static double g_imgNumber;
	static double g_realNumber;

	double getMagnitude()
	{
		std::complex<double> z(g_realNumber, g_imgNumber);
		return std::abs(z);
	}

	void setReal(double pNum) {
		g_realNumber = pNum;
	}

	void setImaginary(double pNum) {
		g_imgNumber = pNum;
	}
}

std::string getComplexNumAsString()
{
	return std::to_string(complex::g_realNumber) + "i" + (std::to_string(complex::g_imgNumber));
}