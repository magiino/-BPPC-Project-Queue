/** \file CValueFunctionalTests.cpp
 *  \brief Functionality unit tests for class CValue
 *  \details Simple functionality unit tests for class CValue
 *  \warning Don't modify this file
 *  \author Pety
 *  $Id: CValueFunctionalTests.cpp 827 2017-12-02 14:13:11Z xmagat01 $
 */

#include "CValueUnitTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CValueUnitTests
	{
	TEST_CLASS(CValueFunctionalTests)
		{
	public:

		TEST_METHOD(CValue_TestValues)
			{
			Assert::IsFalse(CValue::TestValue0() == CValue::TestValue1(), L"Test values cannot be same", LINE_INFO());
			std::string stringval0(CValue::TestStringValue0());
			std::string stringval1(CValue::TestStringValue1());
			Assert::IsFalse(stringval0 == stringval1, L"Test string values cannot be same", LINE_INFO());
			CValue::TestValueRandom();	// just call randomized Test value factory
			CValue::TestStringValueRandom();	// just call randomized Test string value factory
			}

		TEST_METHOD(CValue_ctor_implicit)
			{
			size_t alloc_count_before = get_alloc_count();
			size_t dealloc_count_before = get_dealloc_count();
			size_t realloc_count_before = get_realloc_count();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			CValue val0;
			ptrdiff_t living_after = ClassInfo<CValue>::Living();
			size_t alloc_count_after = get_alloc_count();
			size_t dealloc_count_after = get_dealloc_count();
			size_t realloc_count_after = get_realloc_count();
			Assert::IsTrue(CValue::TestValue0() == val0.Value(), L"Wrong init value", LINE_INFO());
			Assert::IsTrue(living_before + 1 == living_after, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(alloc_count_before, alloc_count_after, L"Implicit c'tor allocate", LINE_INFO());
			Assert::AreEqual(dealloc_count_before, dealloc_count_after, L"Implicit c'tor deallocate", LINE_INFO());
			Assert::AreEqual(realloc_count_before, realloc_count_after, L"Implicit c'tor reallocate", LINE_INFO());
			CValue val1;
			Assert::IsTrue(val1.ID() > val0.ID(), L"Wrong ClassInfo ID initialization", LINE_INFO());
			}

		TEST_METHOD(CValue_ctor_conv)
			{
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
				{
				const CValue val0(CValue::TestValue0());
				const CValue val1(CValue::TestValue1());
				
				living_after = ClassInfo<CValue>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(CValue::TestValue0() == val0.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(CValue::TestValue1() == val1.Value(), L"Wrong value", LINE_INFO());
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

		TEST_METHOD(CValue_ctor_copy)
			{
			const CValue val0(CValue::TestValue0());
			const CValue val1(CValue::TestValue1());
			Assert::IsTrue(CValue::TestValue0() == val0.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(CValue::TestValue1() == val1.Value(), L"Value isn't same", LINE_INFO());

			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
				{
				CValue val0_t(val0);
				CValue val1_t(val1);

				living_after = ClassInfo<CValue>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(living_before + 2 == living_after, L"Wrong number of instances", LINE_INFO());

				if (KCValue_allocate)
					Assert::IsTrue(allocsize_before < allocsize_after, L"No memory allocation", LINE_INFO());
				else
					Assert::IsTrue(allocsize_before == allocsize_after, L"Memory allocated", LINE_INFO());

				Assert::AreNotEqual(val0_t.ID(), val0.ID(), L"IDs cannot be same", LINE_INFO());
				Assert::AreNotEqual(val1_t.ID(), val1.ID(), L"IDs cannot be same", LINE_INFO());

				Assert::IsTrue(val0_t.Value() == val0.Value(), L"Wrong value", LINE_INFO());
				Assert::IsTrue(val1_t.Value() == val1.Value(), L"Wrong value", LINE_INFO());
				Assert::IsFalse(val0_t.Value() == val1_t.Value(), L"Wrong value", LINE_INFO());
				}
			ptrdiff_t living_after2 = ClassInfo<CValue>::Living();
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after2, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after2, L"Memory leaking", LINE_INFO());
			}

		TEST_METHOD(CValue_ctor_conv_cstring)
			{
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
				{
				const CValue val0(CValue::TestStringValue0());
				const CValue val1(CValue::TestStringValue1());
				
				living_after = ClassInfo<CValue>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(CValue::TestValue0() == val0.Value(), L"Value isn't same", LINE_INFO());
				Assert::IsTrue(CValue::TestValue1() == val1.Value(), L"Value isn't same", LINE_INFO());
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

		TEST_METHOD(CValue_dtor)
			{
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			CValue val(CValue::TestValue0());
			val.~CValue();
			ptrdiff_t living_after = ClassInfo<CValue>::Living();
			size_t allocsize_after = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after, L"Memory leaking", LINE_INFO());
			}

		TEST_METHOD(CValue_ctor_conv_cstring_format_compatibility)
			{
			const CValue val0(CValue::TestStringValue0());
			const CValue val1(CValue::TestStringValue1());
			Assert::IsTrue(CValue::TestValue0() == val0.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(CValue::TestValue1() == val1.Value(), L"Value isn't same", LINE_INFO());

			std::stringstream ss0;
			ss0 << val0;
			std::stringstream ss1;
			ss1 << val1;

			size_t allocsize_before = get_alloc_actual_size();
			const CValue val1_t(ss1.str().c_str());
			size_t allocsize_after1 = get_alloc_actual_size();
			const CValue val0_t(ss0.str().c_str());
			size_t allocsize_after2 = get_alloc_actual_size();

			Assert::AreNotEqual(val0_t.ID(), val0.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::AreNotEqual(val1_t.ID(), val1.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::IsTrue(val0_t.Value() == val0.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(val1_t.Value() == val1.Value(), L"Value isn't same", LINE_INFO());
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

		TEST_METHOD(CValue_operators_stream_format_compatibility)
			{
			const CValue val0(CValue::TestStringValue0());
			const CValue val1(CValue::TestStringValue1());
			Assert::IsTrue(CValue::TestValue0() == val0.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(CValue::TestValue1() == val1.Value(), L"Value isn't same", LINE_INFO());

			std::stringstream ss;
			ss << val0;
			ss << val1;
			CValue val0_t, val1_t;
			size_t allocsize_before = get_alloc_actual_size();
			ss >> val0_t;
			size_t allocsize_after1 = get_alloc_actual_size();
			ss >> val1_t;
			size_t allocsize_after2 = get_alloc_actual_size();

			Assert::AreNotEqual(val0_t.ID(), val0.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::AreNotEqual(val1_t.ID(), val1.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::IsTrue(val0_t.Value() == val0.Value(), L"Value isn't same", LINE_INFO());
			Assert::IsTrue(val1_t.Value() == val1.Value(), L"Value isn't same", LINE_INFO());

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

		TEST_METHOD(CValue_setter)
			{
			CValue val;
			size_t allocsize_before = get_alloc_actual_size();
			val.SetValue(CValue::TestValue1());
			size_t allocsize_after1 = get_alloc_actual_size();
			Assert::IsTrue(val.Value() == CValue::TestValue1(), L"Value isn't same", LINE_INFO());

			if(KCValue_allocate)
				Assert::IsTrue(allocsize_before < allocsize_after1, L"No memory allocation", LINE_INFO());
			else
				Assert::IsTrue(allocsize_before == allocsize_after1, L"Memory allocated", LINE_INFO());

			val.SetValue(CValue::TestValue0());
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(val.Value() == CValue::TestValue0(), L"Value isn't same", LINE_INFO());

			if(KCValue_allocate)
				Assert::IsTrue(allocsize_before < allocsize_after2, L"No memory allocation", LINE_INFO());
			else
				Assert::IsTrue(allocsize_before == allocsize_after2, L"Memory allocated", LINE_INFO());
			}

		TEST_METHOD(CValue_operator_unary_minus)
			{
			const CValue val0(CValue::TestValue1());
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			CValue val1(-val0);
			CValue val2(-val1);
			size_t allocsize_after1 = get_alloc_actual_size();
			ptrdiff_t living_after = ClassInfo<CValue>::Living();

			if(KCValue_allocate)
				Assert::IsTrue(allocsize_before < allocsize_after1, L"No memory allocation", LINE_INFO());
			else
				Assert::IsTrue(allocsize_before == allocsize_after1, L"Memory allocated", LINE_INFO());

			Assert::IsTrue(living_before + 2 == living_after, L"Wrong number of instances", LINE_INFO());
			Assert::IsTrue(val0.Value() != val1.Value(), L"Value is same", LINE_INFO());
			Assert::IsTrue(val1.Value() != val2.Value(), L"Value is same", LINE_INFO());
			Assert::IsTrue(val0.Value() == val2.Value(), L"Value isn't same", LINE_INFO());
			}

		TEST_METHOD(CValue_operator_equal)
			{
			const CValue val1_0(CValue::TestValue0()), val2_0(CValue::TestValue0());
			const CValue val3_1(CValue::TestValue1()), val4_1(CValue::TestValue1());

			Assert::IsTrue(val1_0.ID() < val2_0.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val2_0.ID() < val3_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val3_1.ID() < val4_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());

			Assert::IsTrue(val1_0 == val1_0, L"Must be true", LINE_INFO());
			Assert::IsTrue(val3_1 == val4_1, L"Must be true", LINE_INFO());

			Assert::IsTrue(val1_0 == val2_0, L"Must be true", LINE_INFO());
			Assert::IsTrue(val2_0 == val1_0, L"Must be true", LINE_INFO());

			Assert::IsTrue(val3_1 == val4_1, L"Must be true", LINE_INFO());
			Assert::IsTrue(val3_1 == val4_1, L"Must be true", LINE_INFO());

			Assert::IsFalse(val1_0 == val3_1, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 == val1_0, L"Must be false", LINE_INFO());

			Assert::IsFalse(val2_0 == val4_1, L"Must be false", LINE_INFO());
			Assert::IsFalse(val4_1 == val2_0, L"Must be false", LINE_INFO());
			}

		TEST_METHOD(CValue_operator_not_equal)
			{
			const CValue val1_0(CValue::TestValue0()), val2_0(CValue::TestValue0());
			const CValue val3_1(CValue::TestValue1()), val4_1(CValue::TestValue1());

			Assert::IsTrue(val1_0.ID() < val2_0.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val2_0.ID() < val3_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val3_1.ID() < val4_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());

			Assert::IsFalse(val1_0 != val1_0, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 != val4_1, L"Must be false", LINE_INFO());

			Assert::IsFalse(val1_0 != val2_0, L"Must be false", LINE_INFO());
			Assert::IsFalse(val2_0 != val1_0, L"Must be false", LINE_INFO());

			Assert::IsFalse(val3_1 != val4_1, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 != val4_1, L"Must be false", LINE_INFO());

			Assert::IsTrue(val1_0 != val3_1, L"Must be true", LINE_INFO());
			Assert::IsTrue(val3_1 != val1_0, L"Must be true", LINE_INFO());

			Assert::IsTrue(val2_0 != val4_1, L"Must be true", LINE_INFO());
			Assert::IsTrue(val4_1 != val2_0, L"Must be true", LINE_INFO());
			}

		TEST_METHOD(CValue_operator_greater_than)
			{
			const CValue val1_0(CValue::TestValue0()), val2_0(CValue::TestValue0());
			const CValue val3_1(CValue::TestValue1()), val4_1(CValue::TestValue1());

			Assert::IsTrue(val1_0.ID() < val2_0.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val2_0.ID() < val3_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val3_1.ID() < val4_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());

			Assert::IsFalse(val1_0 < val1_0, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 < val4_1, L"Must be false", LINE_INFO());

			Assert::IsFalse(val1_0 < val2_0, L"Must be false", LINE_INFO());
			Assert::IsFalse(val2_0 < val1_0, L"Must be false", LINE_INFO());

			Assert::IsFalse(val3_1 < val4_1, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 < val4_1, L"Must be false", LINE_INFO());

			Assert::IsTrue(val1_0 < val3_1, L"Must be true", LINE_INFO());
			Assert::IsFalse(val3_1 < val1_0, L"Must be false", LINE_INFO());

			Assert::IsTrue(val2_0 < val4_1, L"Must be true", LINE_INFO());
			Assert::IsFalse(val4_1 < val2_0, L"Must be false", LINE_INFO());
			}

		TEST_METHOD(CValue_operator_less_than)
			{
			const CValue val1_0(CValue::TestValue0()), val2_0(CValue::TestValue0());
			const CValue val3_1(CValue::TestValue1()), val4_1(CValue::TestValue1());

			Assert::IsTrue(val1_0.ID() < val2_0.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val2_0.ID() < val3_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());
			Assert::IsTrue(val3_1.ID() < val4_1.ID(), L"Wrong ClassInfo ID", LINE_INFO());

			Assert::IsFalse(val1_0 > val1_0, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 > val4_1, L"Must be false", LINE_INFO());

			Assert::IsFalse(val1_0 > val2_0, L"Must be false", LINE_INFO());
			Assert::IsFalse(val2_0 > val1_0, L"Must be false", LINE_INFO());

			Assert::IsFalse(val3_1 > val4_1, L"Must be false", LINE_INFO());
			Assert::IsFalse(val3_1 > val4_1, L"Must be false", LINE_INFO());

			Assert::IsFalse(val1_0 > val3_1, L"Must be false", LINE_INFO());
			Assert::IsTrue(val3_1 > val1_0, L"Must be true", LINE_INFO());

			Assert::IsFalse(val2_0 > val4_1, L"Must be false", LINE_INFO());
			Assert::IsTrue(val4_1 > val2_0, L"Must be true", LINE_INFO());
			}

		TEST_METHOD(CValue_assignment_to_empty)
			{
			const CValue cval(CValue::TestValue1());
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
			{
			CValue val;
			val = cval;

			living_after = ClassInfo<CValue>::Living();
			allocsize_after = get_alloc_actual_size();
			Assert::IsTrue(living_before + 1 == living_after, L"Wrong number of instances", LINE_INFO());
			Assert::AreNotEqual(val.ID(), cval.ID(), L"IDs cannot be same", LINE_INFO());

			if(KCValue_allocate)
				Assert::IsTrue(allocsize_before < allocsize_after, L"No memory allocation", LINE_INFO());
			else
				Assert::IsTrue(allocsize_before == allocsize_after, L"Memory allocated", LINE_INFO());

			Assert::IsTrue(val.Value() == cval.Value(), L"Must be true", LINE_INFO());

			}
			ptrdiff_t living_after2 = ClassInfo<CValue>::Living();
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after2, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after2, L"Memory leaking", LINE_INFO());
			}

		TEST_METHOD(CValue_assignment_to_existing)
			{
			const CValue cval(CValue::TestValue1());
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			ptrdiff_t living_after;
			size_t allocsize_after;
				{
				CValue val(-cval);
				val = cval;

				living_after = ClassInfo<CValue>::Living();
				allocsize_after = get_alloc_actual_size();
				Assert::IsTrue(living_before + 1 == living_after, L"Wrong number of instances", LINE_INFO());
				Assert::AreNotEqual(val.ID(), cval.ID(), L"IDs cannot be same", LINE_INFO());

				if(KCValue_allocate)
					Assert::IsTrue(allocsize_before < allocsize_after, L"No memory allocation", LINE_INFO());
				else
					Assert::IsTrue(allocsize_before == allocsize_after, L"Memory allocated", LINE_INFO());

				Assert::IsTrue(val.Value() == cval.Value(), L"Must be true", LINE_INFO());

				}
			ptrdiff_t living_after2 = ClassInfo<CValue>::Living();
			size_t allocsize_after2 = get_alloc_actual_size();
			Assert::IsTrue(living_before == living_after2, L"Wrong number of instances", LINE_INFO());
			Assert::AreEqual(allocsize_before, allocsize_after2, L"Memory leaking", LINE_INFO());
			}

		}; /* TEST_CLASS(CValueFunctionalTests) */

	} /* namespace CValueUnitTests */
