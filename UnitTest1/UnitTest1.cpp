#include "pch.h"
#include "CppUnitTest.h"
#include "../PKR 5.3A/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int i = 1;
			Student s[i];
			char FileName[6] = "H.dat";
			s[0].spec = CS;
			s[0].physics = 5;
			s[0].math = 5; 
			s[0].informatik = 5;
			Assert::AreEqual(5., avgGrade(s, 0));
		}
	};
}
