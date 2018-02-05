/** \file ProjectFunctionalTests.cpp
 *  \brief Functionality unit tests for class CContainer
 *  \details Simple functionality unit tests for class CFronta
 *  \authors
 *  $Id: ProjectFunctionalTests.cpp 3565 2018-01-02 22:25:21Z xmagat01 $
 */

#include "ProjectUnitTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CContainerUnitTests
	{
	TEST_CLASS(CContainerFunctionalTest)
		{
		/** \bugfix[Zad] Chybi hlavicky pro testy. // doplnili sme hlavièku [xlevri01] */
	public:
        // Adam
		TEST_METHOD(CFronta_equal_operator)
		{ 
                CFronta a(2);
                CFronta b(2);
                Assert::IsNotNull(&a, L"Test string values cannot be empty", LINE_INFO());
                Assert::IsTrue(a == b, L"Test string values have to be same", LINE_INFO());
		}
		TEST_METHOD(CFronta_notequal_operator)
		{
				CFronta a(2);
				CFronta b(3);
				Assert::IsNotNull(&a, L"Test string values cannot be empty", LINE_INFO());
				Assert::IsTrue(a != b, L"Test string values cannot be same", LINE_INFO());
		}
		TEST_METHOD(CFronta_graeaterthan_operator)
		{
			CFronta a(3);
			CFronta b(2);
			Assert::IsNotNull(&a, L"Test string values cannot be empty", LINE_INFO());
			Assert::IsTrue(a > b, L"Test string values have to be graeter in a than in b", LINE_INFO());
			Assert::IsTrue(a != b, L"Test string values cannot be same", LINE_INFO());
		}
		TEST_METHOD(CFronta_lessthan_operator)
		{
			CFronta a(2);
			CFronta b(3);
			Assert::IsNotNull(&a, L"Test string values cannot be empty", LINE_INFO());
			Assert::IsTrue(a < b, L"Test string values have to be less in a than in b", LINE_INFO());
			Assert::IsTrue(a != b, L"Test string values cannot be same", LINE_INFO());
		}
		TEST_METHOD(CFronta_IsEmpty)
			{
			size_t allocsize_before = get_alloc_actual_size();
			CFronta fronta1;
			size_t allocsize_after = get_alloc_actual_size();
			Assert::IsTrue(fronta1.IsEmpty() == 1, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			Assert::IsTrue(fronta1.Length() == 0, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			Assert::IsTrue(allocsize_before == allocsize_after, L"Memory leaking", LINE_INFO());
			}
		TEST_METHOD(CFronta_nonmeber_opertor_plus)
			{
			CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = 1 + fronta1;

			Assert::IsFalse(fronta2 > fronta1, L"Instances are equal", LINE_INFO());
			Assert::IsFalse(fronta2 == fronta1, L"Instances are equal", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			}
		TEST_METHOD(CFronta_Lenght)
			{
			CValue val1(CValue::TestStringValue0());
			CValue val2(CValue::TestStringValue1());
			size_t allocsize_before = get_alloc_actual_size();
			CFronta tmp;
			size_t allocsize_after = get_alloc_actual_size();
			tmp.EnQueue(val1);
			tmp.EnQueue(val2);

			Assert::IsTrue(tmp.Length() == 2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			CValue tmpVal = tmp.DeQueue();
			Assert::IsFalse(tmp.Length() == 2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			tmp.DeQueue();
			tmp.DeQueue();
			Assert::IsTrue(tmp.Length() == 0, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			Assert::IsTrue(allocsize_before == allocsize_after, L"Memory leaking", LINE_INFO());
			}
        // Marek
        TEST_METHOD(CFronta_dtor)
        {
            size_t allocsize_before = get_alloc_actual_size();
            ptrdiff_t living_before = ClassInfo<CValue>::Living();
            CFronta fronta;
            fronta.~CFronta();
            ptrdiff_t living_after = ClassInfo<CValue>::Living();
            size_t allocsize_after = get_alloc_actual_size();
            Assert::IsTrue(living_before == living_after, L"Wrong number of instances", LINE_INFO());
            Assert::AreEqual(allocsize_before, allocsize_after, L"Memory leaking", LINE_INFO());
        }
        TEST_METHOD(CFronta_ctor_conv_cstring)
        {
            size_t allocsize_before = get_alloc_actual_size();
            ptrdiff_t living_before = ClassInfo<CValue>::Living();
            CFronta tmp1(CValue::TestStringValues());
            CFronta tmp2(CValue::TestStringValues());
            ptrdiff_t living_after = ClassInfo<CValue>::Living();
            size_t allocsize_after = get_alloc_actual_size();
            Assert::AreNotEqual(allocsize_before, allocsize_after, L"Memory leaking", LINE_INFO());
            Assert::IsTrue(living_before != living_after, L"Wrong number of instances", LINE_INFO());
            Assert::IsTrue(tmp1.DeQueue() == tmp2.DeQueue(), L"Values should be equal", LINE_INFO());
            Assert::IsTrue(tmp1.DeQueue() == tmp2.DeQueue(), L"Values should be equal", LINE_INFO());
            Assert::IsTrue(tmp1 == tmp2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_ctor_array)
        {
            CValue array1[2]{CValue(), CValue()};
            CValue array2[1]{CValue()};
            size_t allocsize_before = get_alloc_actual_size();
            CFronta tmp1(array1, 2);
            CFronta tmp2(array2, 1);
            size_t allocsize_after = get_alloc_actual_size();
            Assert::IsTrue(allocsize_before < allocsize_after, L"Memory leaking", LINE_INFO());
            Assert::IsTrue(tmp1 != tmp2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsTrue(tmp1.DeQueue() == tmp2.DeQueue(), L"Values should be equal", LINE_INFO());
            Assert::IsFalse(tmp1 < tmp2, L"Wrong number of elements in CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_stream_operators)
        {
            CValue tmpVal(CValue::TestValue1());
            CFronta tmp1(tmpVal);
            CFronta tmp2;

            std::stringstream ss;
            ss << tmp1;
            ss >> tmp2;

            Assert::IsTrue(tmp1 == tmp2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsFalse(tmp2.DeQueue() == CValue(), L"CFronta has no elements", LINE_INFO());
            Assert::AreNotEqual(tmp1.ID(), tmp2.ID(), L"IDs cannot be same", LINE_INFO());
        }
        TEST_METHOD(CFronta_operator_plusEqual)
        {
            CFronta tmp1(CValue::TestStringValues());
            CFronta tmp2(CValue::TestStringValues());
            size_t length = tmp1.Length() + tmp2.Length();
            Assert::IsTrue(tmp1 == tmp2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            tmp1 += tmp2;
            Assert::IsFalse(tmp1 == tmp2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsTrue(tmp1.Length() == length, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsTrue(tmp2.Back() == tmp1.Back(), L"Wrong last element in CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_operator_minus)
        {
            CFronta tmp1(CValue::TestStringValues());
            CFronta tmp2(CValue::TestStringValues());
            size_t length = tmp1.Length() + tmp2.Length();
            CFronta tmp = tmp1 - tmp2;
            Assert::IsTrue(tmp.Front() == tmp2.Front(), L"Wrong first element in CFronta", LINE_INFO());
            Assert::IsTrue(tmp.Back() == tmp1.Back(), L"Wrong last element in CFronta", LINE_INFO());
            Assert::IsTrue(tmp.Length() == length, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_operator_plus)
        {
            CFronta tmp1(CValue::TestStringValues());
            CFronta tmp2(CValue::TestStringValues());
            size_t length = tmp1.Length() + tmp2.Length();
            CFronta tmp = tmp1 + tmp2;
            Assert::IsTrue(tmp.Front() == tmp1.Front(), L"Wrong first element in CFronta", LINE_INFO());
            Assert::IsTrue(tmp.Back() == tmp2.Back(), L"Wrong last element in CFronta", LINE_INFO());
            Assert::IsTrue(tmp.Length() == (size_t)length, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_operator_equal)
        {
            CFronta tmp1(CValue::TestStringValues());
            CFronta tmp2(CValue::TestStringValues());
            tmp1 = tmp2;
            Assert::IsTrue(tmp1.Length() == tmp2.Length(), L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsTrue(tmp1.Front() == tmp2.Front(), L"Wrong first element in CFronta", LINE_INFO());
            Assert::IsTrue(tmp1.Back() == tmp2.Back(), L"Wrong last element in CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_conversion_operator)
        {
            CFronta tmp1(CValue::TestStringValues());
            Assert::IsTrue(bool(tmp1), L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            tmp1.Clear();
            Assert::IsFalse(bool(tmp1), L"Wrong number of CValue instances inside CFronta", LINE_INFO());
        }
        TEST_METHOD(CFronta_enqueue_dequeue)
        {
            CValue val1(CValue::TestStringValue0());
            CValue val2(CValue::TestStringValue1());
            CValue val3(CValue::TestValue0());
            size_t allocsize_before = get_alloc_actual_size();
            CFronta tmp;
            size_t allocsize_after = get_alloc_actual_size();
            tmp.EnQueue(val1);
            tmp.EnQueue(val2);

            Assert::IsTrue(tmp.Length() == 2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            CValue tmpVal = tmp.DeQueue();
            Assert::IsFalse(tmp.Length() == 2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsTrue(tmpVal == val1, L"Wrong values in CValues instances", LINE_INFO());
            tmp.EnQueue(val3);
            Assert::IsTrue(tmp.Length() == 2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            tmp.DeQueue();
            tmp.DeQueue();
            Assert::IsTrue(tmp.Length() == 0, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
            Assert::IsTrue(allocsize_before == allocsize_after, L"Memory leaking", LINE_INFO());
        }
        TEST_METHOD(CFronta_usage)
        {
            CFronta tmp;
            CFronta tmp1(2);

            Assert::IsTrue(tmp.Usage() == 0, L"Wrong usage value", LINE_INFO());
            Assert::IsTrue(tmp.Usage() < tmp1.Usage(), L"Wrong usage value", LINE_INFO());
            CValue a = tmp1.DeQueue();
            tmp.EnQueue(a);
            Assert::IsTrue(tmp.Usage() == tmp1.Usage(), L"Wrong usage value", LINE_INFO());
            Assert::AreNotEqual(tmp.ID(), tmp1.ID(), L"IDs cannot be same", LINE_INFO());
        }
        TEST_METHOD(CFronta_clear)
        {
            size_t allocsize_before = get_alloc_actual_size();
            CFronta tmp1(CValue::TestStringValues());
            CFronta tmp2(CValue::TestStringValues());

            tmp1.Clear();
            Assert::IsTrue(tmp1.Length() == 0, L"Fronta should be clear.", LINE_INFO());
            Assert::IsTrue(tmp1.Usage() == 0, L"Usage should be 0.", LINE_INFO());
            Assert::IsTrue(tmp2.Length() > tmp1.Length(), L"Wrong length in fronta.", LINE_INFO());
            tmp2.Clear();
            Assert::IsTrue(tmp2.Length() == tmp1.Length(), L"Wrong length in fronta.", LINE_INFO());
            size_t allocsize_after = get_alloc_actual_size();
            Assert::IsTrue(allocsize_before == allocsize_after, L"Memory leaking", LINE_INFO());
        }
        // Jan
		TEST_METHOD(CFronta_prefix_operator_minus)
			{
			CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = -fronta1;

			Assert::IsTrue(fronta1 == fronta2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			Assert::IsFalse(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should not be same", LINE_INFO());
			Assert::IsTrue(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should be equal", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			}
		TEST_METHOD(CFronta_prefix_operator_plusplus)
			{
            CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = fronta1;
		    ++fronta1;

		
			Assert::IsTrue(fronta1.Back() == fronta1.Back(), L"CValues should not be same", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::IsFalse(fronta1 < fronta2, L"Instances are equal", LINE_INFO());
			}
		TEST_METHOD(CFronta_prefix_operator_minusminus)
			{
            CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = fronta1;
			--fronta1;
			Assert::IsTrue(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should be equal", LINE_INFO());
			Assert::IsTrue(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should be equal", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			Assert::IsFalse(fronta2 < fronta1, L"Instances are equal", LINE_INFO());
			}
		TEST_METHOD(CFronta_prefix_operator_tilde)
			{
            CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = ~fronta1;

			Assert::IsTrue(fronta1.Front() == fronta2.Back(), L"CValues should be equal", LINE_INFO());
			Assert::IsTrue(fronta2.Front() == fronta1.Back(), L"CValues should be equal", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			}
		TEST_METHOD(CFronta_reverz)
			{
            CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = Reverz(fronta1);

			Assert::IsTrue(fronta1 == fronta2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			Assert::IsFalse(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should not be same", LINE_INFO());
			Assert::IsTrue(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should be equal", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			}
		TEST_METHOD(CFronta_Conversion_ctor)
			{
			size_t allocsize_before = get_alloc_actual_size();
			ptrdiff_t living_before = ClassInfo<CValue>::Living();
			CFronta fronta1(CValue::TestStringValues());
			ptrdiff_t living_after = ClassInfo<CValue>::Living();
			size_t allocsize_after = get_alloc_actual_size();
			Assert::IsNotNull(&fronta1, L"Test string values cannot be empty", LINE_INFO());
			Assert::IsTrue(allocsize_before < allocsize_after, L"Memory leaking", LINE_INFO());
			Assert::IsTrue(living_before != living_after, L"Wrong number of instances", LINE_INFO());
			}
		TEST_METHOD(CFronta_implicit_ctor)
			{
			size_t allocsize_before = get_alloc_actual_size();
			
			CFronta fronta1;
			
			size_t allocsize_after = get_alloc_actual_size();
			Assert::IsNotNull(&fronta1, L"Test string values can be empty", LINE_INFO());
			Assert::IsTrue(allocsize_before == allocsize_after, L"Memory leaking", LINE_INFO());
			Assert::IsTrue(fronta1.Front() == fronta1.Back(), L"Wrong number of instances", LINE_INFO());
			}
		TEST_METHOD(CFronta_Reverz)
			{
			CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2 = fronta1;
			Reverz(fronta2);

			Assert::IsTrue(fronta1 == fronta2, L"Wrong number of CValue instances inside CFronta", LINE_INFO());
			Assert::IsTrue(fronta1.DeQueue() == fronta2.DeQueue(), L"CValues should be equal", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			}
		TEST_METHOD(CFronta_instanceinfo)
			{
			CFronta fronta1(CValue::TestStringValues());
			CFronta fronta2(CValue::TestStringValues());
			size_t ID1 = fronta1.ID();
			size_t ID2 = fronta2.ID();
			Assert::IsTrue(ID2 != 0, L"Test string values cannot be empty", LINE_INFO());
			Assert::IsTrue(ID1 != 0, L"Test string values cannot be empty", LINE_INFO());
			Assert::AreNotEqual(fronta1.ID(), fronta2.ID(), L"IDs cannot be same", LINE_INFO());
			}
		};  /* TEST_CLASS(CFrontaFunctionalTest) */
	} /* namespace CFrontaFunctionalTest */
