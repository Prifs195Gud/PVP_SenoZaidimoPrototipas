#include "pch.h"
#include "CppUnitTest.h"
#include "../PVP_SenoZaidimoPrototipas/Vectors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(testPlus)
		{
			Vector2 vector1(1.,2.);
			Vector2 vector2(3., 5.);
			Vector2 result = vector1 + vector2;
			Assert::AreEqual(4, (int)result.x);
		}

		TEST_METHOD(testMinus)
		{
			Vector2 vector1(1., 2.);
			Vector2 vector2(3., 5.);
			Vector2 result = vector1 - vector2;
			Assert::AreEqual(-2, (int)result.x);
		}

		TEST_METHOD(testMultiply)
		{
			Vector2 vector1(1., 2.);
			double x = 5;
			Vector2 result = vector1 * x;
			Assert::AreEqual(10, (int)result.y);
		}

		TEST_METHOD(testEqual)
		{
			Vector2 vector1(1., 2.);
			Vector2 vector2(1., 2.);
			bool result = vector1 == vector2;
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(testMagnitude)
		{
			Vector2 vector1(3., 4.);
			double result = vector1.Magnitude();
			Assert::AreEqual(5., result);
		}

		TEST_METHOD(testNormalize)
		{
			Vector2 vector1(3., 4.);
			Vector2 result = vector1.Normalize();
			Assert::AreEqual(0.8, result.y);
		}
	};
}
