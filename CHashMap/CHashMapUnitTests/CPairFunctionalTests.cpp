/** \file CPairFunctionalTests.cpp
 *  \brief Functionality unit tests for class CPair
 *  \details Simple functionality unit tests for class CPair
 *  \warning Don't modify this file
 *  \author Richter
 *  $Id: CPairFunctionalTests.cpp 1763 2017-12-11 15:25:59Z xkunaj01 $
 */

#include "CPairUnitTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPairUnitTests
	{
	TEST_CLASS(CPairFunctionalTests)
		{
	public:
		// neni nejlepsi testovat vice metod naraz - ale jinak to nejde (?)
		// CPair(TKey aKey, const CValue& aValue) 
		// TKey Key() const
		// CValue Value() const
		TEST_METHOD(CPairCtor_KeyValue_and_Getters)
			{
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CPair>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
				{
				const CValue val0(CValue::TestValue0());
				const CValue val1(CValue::TestValue1());
				const CPair::TKey key0 = 0;
				const CPair::TKey key1 = 100;

				CPair cp00(key0, val0), cp01(key0, val1), cp10(key1, val0), cp11(key1, val1);

				living_after = ClassInfo<CPair>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(val0 == cp00.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(val1 == cp01.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(val0 == cp10.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(val1 == cp11.Value(), L"Wrong value", LINE_INFO());

				Assert::IsTrue(key0 == cp00.Key(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(key1 == cp10.Key(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(key0 == cp01.Key(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(key1 == cp11.Key(), L"Wrong value", LINE_INFO());

				Assert::IsTrue(living_before + 4 == living_after, L"Wrong number of instances", LINE_INFO());
				Assert::IsTrue(cp01.ID() > cp00.ID(), L"Wrong ClassInfo ID initialization", LINE_INFO());
				Assert::IsTrue(cp10.ID() > cp01.ID(), L"Wrong ClassInfo ID initialization", LINE_INFO());
				Assert::IsTrue(cp11.ID() > cp10.ID(), L"Wrong ClassInfo ID initialization", LINE_INFO());

				if(KCValue_allocate)
					Assert::IsTrue(allocsize_before < allocsize_after, L"No memory allocation", LINE_INFO());
				else
					Assert::IsTrue(allocsize_before == allocsize_after, L"Memory allocated", LINE_INFO());
				}
			ptrdiff_t living_after2 = ClassInfo<CPair>::Living();
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after2, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after2, L"Memory leaking", LINE_INFO());
			}

		// size_t ID() const
		TEST_METHOD(CPair_ID)
			{
			// TODO: Your test code here
			std::ostringstream oss;
			oss << "(#99," << CValue::TestStringValue1() << ')';
			const CValue val(CValue::TestValue0());
			const CPair::TKey key = 0;
			size_t living_before = ClassInfo<CPair>::Total();
				{
				CPair cp0(key, val);
				CPair cp1(key, val), cp2(oss.str().c_str()), cp3(oss.str().c_str()), cp4(key, val);

				Assert::AreEqual(living_before, cp0.ID(), L"Wrong ClassInfo ID initialization", LINE_INFO());
				Assert::IsTrue(cp1.ID() == cp0.ID() + 1, L"Wrong ClassInfo ID initialization", LINE_INFO());
				Assert::IsTrue(cp2.ID() == cp1.ID() + 1, L"Wrong ClassInfo ID initialization", LINE_INFO());
				Assert::IsTrue(cp3.ID() == cp2.ID() + 1, L"Wrong ClassInfo ID initialization", LINE_INFO());
				Assert::IsTrue(cp4.ID() == cp3.ID() + 1, L"Wrong ClassInfo ID initialization", LINE_INFO());
				/*/
					// pro jistotu testy upravim pro paralelni beh testu
					Assert::IsTrue(cp0.ID() >= living_before, L"Wrong ClassInfo ID initialization", LINE_INFO());
					Assert::IsTrue(cp1.ID() > cp0.ID() , L"Wrong ClassInfo ID initialization", LINE_INFO());
					Assert::IsTrue(cp2.ID() > cp1.ID() , L"Wrong ClassInfo ID initialization", LINE_INFO());
					Assert::IsTrue(cp3.ID() > cp2.ID() , L"Wrong ClassInfo ID initialization", LINE_INFO());
					Assert::IsTrue(cp4.ID() > cp3.ID() , L"Wrong ClassInfo ID initialization", LINE_INFO());
					//*/
				}
			}

		// void SetValue(const CValue& aValue)
		TEST_METHOD(CPair_Value_Setter)
			{
			// TODO: Your test code here
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CPair>::Living();
			ptrdiff_t living_after;

			size_t allocsize_after;
				{
				const CValue val0(CValue::TestValue0());
				const CValue val1(CValue::TestValue1());
				const CPair::TKey key0 = 0;
				const CPair::TKey key1 = 100;

				CPair cp00(key0, val0), cp11(key1, val1);

				living_after = ClassInfo<CPair>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(val0 == cp00.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(val1 == cp11.Value(), L"Wrong value", LINE_INFO());

				Assert::IsTrue(key0 == cp00.Key(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(key1 == cp11.Key(), L"Wrong value", LINE_INFO());

				cp00.SetValue(val1);
				cp11.SetValue(val0);

				Assert::IsTrue(val1 == cp00.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(val0 == cp11.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(key0 == cp00.Key(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(key1 == cp11.Key(), L"Wrong value", LINE_INFO());

				Assert::IsTrue(living_before + 2 == living_after, L"Wrong number of instances", LINE_INFO());

				if(KCValue_allocate)
					Assert::IsTrue(allocsize_before < allocsize_after, L"No memory allocation", LINE_INFO());
				else
					Assert::IsTrue(allocsize_before == allocsize_after, L"Memory allocated", LINE_INFO());
				}
			ptrdiff_t living_after2 = ClassInfo<CPair>::Living();
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after2, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after2, L"Memory leaking", LINE_INFO());
			}


		//CPair(const char *aStr) 
		TEST_METHOD(CPair_ctor_conv_cstring)
			{
			// TODO: Your test code here
			std::ostringstream oss1, oss0;
			oss0 << "(#99," << CValue::TestStringValue0() << ')';
			oss1 << "(#50," << CValue::TestStringValue1() << ')';
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CPair>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
				{
				const CPair val0(oss0.str().c_str());
				const CPair val1(oss1.str().c_str());

				living_after = ClassInfo<CPair>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(CValue::TestValue0() == val0.Value().Value(), L"Value isn't same", LINE_INFO());
				Assert::IsTrue(CValue::TestValue1() == val1.Value().Value(), L"Value isn't same", LINE_INFO());
				Assert::IsTrue(CPair::TKey(99) == val0.Key(), L"Value isn't same", LINE_INFO());
				Assert::IsTrue(CPair::TKey(50) == val1.Key(), L"Value isn't same", LINE_INFO());
				Assert::IsFalse(val0.Value() == val1.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(living_before + 2 == living_after, L"Wrong number of instances", LINE_INFO());
				Assert::IsTrue(val1.ID() > val0.ID(), L"Wrong ClassInfo ID initialization", LINE_INFO());

				if(KCValue_allocate)
					Assert::IsTrue(allocsize_before < allocsize_after, L"No memory allocation", LINE_INFO());
				else
					Assert::IsTrue(allocsize_before == allocsize_after, L"Memory allocated", LINE_INFO());
				}
			ptrdiff_t living_after2 = ClassInfo<CValue>::Living();
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after2, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after2, L"Memory leaking", LINE_INFO());

			}

		// friend std::ostream& operator<<(std::ostream& aOstr, const CPair& aPair)
		TEST_METHOD(CPair_operators_stream_format_compatibility)
			{
			std::ostringstream oss1, oss0;
			oss0 << "(#99," << CValue::TestStringValue0() << ')';
			oss1 << "(#50," << CValue::TestStringValue1() << ')';
			const CPair val0(oss0.str().c_str());
			const CPair val1(oss0.str().c_str());

			std::stringstream ss0;
			ss0 << val0;
			std::stringstream ss1;
			ss1 << val1;

			size_t allocsize_before = get_alloc_actual_size();
			const CPair val1_t(ss1.str().c_str());
			size_t allocsize_after1 = get_alloc_actual_size();
			const CPair val0_t(ss0.str().c_str());
			size_t allocsize_after2 = get_alloc_actual_size();

			Assert::AreNotEqual(val0_t.ID(), val0.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::AreNotEqual(val1_t.ID(), val1.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::IsTrue(val0_t.Value() == val0.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(val1_t.Value() == val1.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(val0_t.Key() == val0.Key(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(val1_t.Key() == val1.Key(), L"Value isn't same", LINE_INFO());

			if(KCValue_allocate)
				{
				Assert::IsTrue(allocsize_before < allocsize_after1, L"No memory allocation", LINE_INFO());
				Assert::IsTrue(allocsize_after1 < allocsize_after2, L"No memory allocation", LINE_INFO());
				}
			else
				{
				Assert::IsTrue(allocsize_before == allocsize_after1, L"Memory allocated", LINE_INFO());
				Assert::IsTrue(allocsize_after1 == allocsize_after2, L"Memory allocated", LINE_INFO());
				}
			}

		};  /* TEST_CLASS(CPairUnitTest) */
	} /* namespace CPairUnitTests */
