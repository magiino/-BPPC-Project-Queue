#ifndef __CHASHMAP_H__
#define __CHASHMAP_H__
/** \file CHashMap.h
 *  \brief CHashMap class header
 *  \details File contain CHashMap class container definition.
 *  \warning Don't modify this file
 *  \author Pety 2017
 *  \version $Revision: 2 $
 *	$Id: CHashMap.h 2 2017-11-06 10:01:25Z petyovsky $
 */

#include <cstddef>
#include <stdexcept>

#include "CPair.h"
#include "ClassInfo.h"
#include "check.h"

/** \brief CHashMap class definition
 *  \details Definition of CHashMap class. There is defined all common methods and member variables.
 */
class CHashMap
	{
public:
	/** \brief TInsert enumerator definition
	 *  \details Definition of TInsert enumerator used as parameter in the Insert method.
	 */
	enum struct TInsert 
		{
		EUniqueKey = 0,				///< Insert and check if key is Unique in the map
		EBeforeFirstKeyDuplicity,	///< Insert as first in the row of same keys
		EAfterLastKeyDuplicity,		///< Insert as last in the row of same keys
		EByPair						///< Insert in the row of same keys after pair with less or same value 
		};  /* enum struct TInsert */

	/** \brief TAt enumerator definition
	 *  \details Definition of TAt enumerator used as parameter in the At methods.
	 */
	enum struct TAt 
		{
		EFirstDuplicity = 0,		///< At returns iterator at first pair in the row of same keys 
		ELastDuplicity				///< At returns iterator at lastt pair in the row of same keys
		};  /* enum struct TAt */
	
private:
	/** \brief TItem structure definiton
	 *  \details Definition of TItem struct which is used as item in the linked list
	 */
	struct TItem
		{
// Simple trick for ASLR of the TItem struct
#ifndef NDEBUG	
		CPair iPair;			///< Pair value
		TItem *iNext;			///< Pointer to the next item in the linked list
#else
		TItem *iNext;			///< Pair value
		CPair iPair;			///< Pointer to the next item in the linked list
#endif
		/** \brief Copy and conversion c'tor for handy initialization of TItem instance
		 *  \param[in] aPair Pair (key, value)
		 *  \param[in] aNext Pointer to the next item in the linked list (can be ommited)
		 */
// Simple trick for ASLR of the TItem struct
#ifndef NDEBUG
		TItem(const CPair &aPair, TItem *aNext = nullptr): iPair(aPair), iNext(aNext)
#else
		TItem(const CPair &aPair, TItem *aNext = nullptr): iNext(aNext), iPair(aPair)
#endif
			{}
		
#ifdef MOVE_SEMANTICS
		/** \brief Move and conversion c'tor for handy initialization of TItem instance
		 *  \param[in] aPair Pair (key, value)
		 *  \param[in] aNext Pointer to the next item in the linked list (can be ommited)
		 */
// Simple trick for ASLR of the TItem struct
#ifndef NDEBUG
		TItem(CPair&& aPair, TItem *aNext = nullptr): iPair(std::move(aPair)), iNext(aNext)
#else
		TItem(CPair&& aPair, TItem *aNext = nullptr): iNext(aNext), iPair(std::move(aPair))
#endif
			{}
#endif /* MOVE_SEMANTICS */
		}; /* struct TItem */

	/** \brief TBucket structure definition
	 *  \details Definition of TBucket struct which is used for storing head and tail pointers to item in the linked list
	 */
	struct TBucket
		{
		TItem *iHead;					///< Pointer to first item in the linked list
		TItem *iTail;					///< Pointer to last item in the linked list
		
		/** \brief Implicit and Conversion c'tor for handy initialization of TBucket instance
		 *  \param[in] aHead Pointer to the first item in the linked list (can be ommited)
		 *  \param[in] aTail Pointer to the last item in the linked list (can be ommited)
		 */
		TBucket(TItem *aHead = nullptr, TItem *aTail = nullptr): iHead(aHead), iTail(aTail)
			{}
		}; /* struct TBucket */

	TBucket *iBucketTable;				///< Array of buckets (main datastructure of HashMap)
	size_t iBucketTableSize;			///< Number of the elements (buckets) in the \p iBucketTable
	size_t iItemCount;					///< Number of the pairs / items stored in the map
 	ClassInfo<CHashMap> iInstanceInfo;	///< Instance of the class info for usage statistics
	
protected:
	/** \brief Hash value calculator
	 *  \param[in] aKey Key value
	 *  \return Hash value (bucket index) calculated from \a aKey and \p iBucketTableSize
	 */
	size_t CalculateHash(const CPair::TKey& aKey) const
		{ return(size_t(aKey) % iBucketTableSize); }

public:
	/** \brief CForwardIterator class definition
	 *  \details Definition of CForwardIterator which act as pointer for traversing thru the all pairs stored in the CHashMap. Every class members are accessible from CHashMap (friend class).
	 */
	class CForwardIterator
		{
		friend class CHashMap;			///< Friend relationship definition with CHashMap instances
		TBucket *iBucketTable;			///< Pointer the CHashMap::iBucketTable copied from assigned CHashMap instance
		size_t iBucketTableSize;		///< Value CHashMap::iBucketTableSize copied from assigned CHashMap instance
		TItem *iPrev;					///< Pointer to the previous TItem in the bucket (or nullptr if \p iAct pointing to the first TItem in the bucket)
		TItem *iAct;					///< Pointer to the actual TItem in the bucket of the map
		size_t iBucketIdx;				///< Bucket (hash) index for actual TItem (pair) currently pointed by iterator

		/** \brief Private conversion c'tor for specific initialization of CForwardIterator instance
		 *  \param[in] aBucketTable Copy of the map's pointer to the array of buckets
		 *  \param[in] aBucketTableSize Copy of the map's number of the elements (buckets) in the \p iBucketTable
		 *  \param[in] aPrev Pointer to the previous TItem
		 *  \param[in] aAct Pointer to the actual TItem (currently pointed by iterator)
		 *  \param[in] aBucketIdx Value of bucket / hash index for actual TItem (currently pointed by iterator)
		 */
		CForwardIterator(TBucket *aBucketTable, size_t aBucketTableSize, TItem *aPrev, TItem *aAct, size_t aBucketIdx):
			iBucketTable(aBucketTable), iBucketTableSize(aBucketTableSize), iPrev(aPrev), iAct(aAct), iBucketIdx(aBucketIdx)
			{}

	public:
		/** \brief Implicit c'tor of CForwardIterator instance
		 *  \details Used for creating empty CForwardIterator instance which is not assigned with any map. Also useful for creation of guaranteed invalid CForwardIterator instances.
		 */
		CForwardIterator(): iBucketTable(nullptr), iBucketTableSize(0), iPrev(nullptr), iAct(nullptr), iBucketIdx(0)
			{}

		/** \brief Iterator pre-increment operator
		 *  \details Shift iterator to the next item / pair in the assigned map and return self
		 *  \return Iterator pointing to the next item / pair
	     *  \attention Operator generate \c std::runtime_error exception when iterator instance is invalid or empty
		 */
		CForwardIterator& operator++();

		/** \brief Iterators equal to comparison operator
		 *  \param[in] aIter Iterator on the left of operator
		 *  \return Result of the equal to comparison of the two iterator (\c true or \c false)
		 */
		bool operator==(const CForwardIterator& aIter) const
			{ return (iAct == aIter.iAct); }
		
		/** \brief Iterators not equal to comparison operator
		 *  \param[in] aIter Iterator on the left of operator
		 *  \return Result of the not equal to comparison of the two iterator (\c true or \c false)
		 */
		bool operator!=(const CForwardIterator& aIter) const
			{ return !(*this == aIter); }

		/** \brief Iterator conversion operator
		 *  \return Operator returns \c true when iterator is valid otherwise returns \c false
		 */
		operator bool() const
			{ return bool(iAct); }

		/** \brief Iterator dereferencing (indirection) operator
		 *  \return Operator returns reference to the pair pointed by iterator
	     *  \attention Operator generate \c std::runtime_error exception when iterator instance is invalid or empty
		 */
		CPair& operator*() const
			{
			if(!iAct)
				throw std::runtime_error("Dereferencing of invalid iterator");
			return(iAct->iPair);
			}

		/** \brief Iterator member of pointer operator
		 *  \return Operator returns pointer to the pair pointed by iterator
		 *  \attention Operator generate \c std::runtime_error exception when iterator instance is invalid or empty
		 */
		CPair* operator->() const
			{
			if(!iAct)
				throw std::runtime_error("Dereferencing of invalid iterator");
			return(&(iAct->iPair));
			}

		}; /* class CForwardIterator */

	/** \brief Implicit (and conversion) c'tor
	 *  \details Create empty map with defined number of buckets
	 *  \param[in] aBucketTableSize Number of Bucket in the internal hash map structures (implicit value is 256)
     *  \attention C'tor generate \c std::length_error exception if \a aBucketTableSize is less than 2
	 */
	CHashMap(size_t aBucketTableSize = 256): iBucketTable(nullptr), iBucketTableSize(aBucketTableSize), iItemCount(0)
		{
		if(aBucketTableSize < 2)
			std::length_error("Bucket table size cannot be zero nor one");
		}

	/** \brief Copy c'tor
	 *  \details Create deep copy of the \a aHashMap the to new map instance
	 *  \param[in] aHashMap Source map used for copying
	 */
	CHashMap(const CHashMap& aHashMap);

	/** \brief Assigment operator for maps
	 *  \details Remove previous content of the map ane made deep copy of \a aHashMap
	 *  \param[in] aHashMap Source map used for copying
	 *  \return Reference to self
	 */
	CHashMap& operator=(const CHashMap& aHashMap);

	/** \brief d'tor
	 *  \details Clear and deallocate all items in the each bucket
	 */
	~CHashMap()
		{ Clear(); }

#ifdef MOVE_SEMANTICS
	/** \brief Default move c'tor
	 *  \details Move content of the one map to the new map instance
	 */
	CHashMap(CHashMap&&) = default;

	/** \brief Default move assignment operator
	 *  \details Move content of the one map to the other map instance
	 */
	CHashMap& operator=(CHashMap&&) = default;

#endif /* MOVE_SEMANTICS */

	/** \brief Insert new pair to the map
	 *  \details Use key and value to create new (copying) pair and insert it into the map
	 *  \param[in] aPair Pair for inserting
	 *  \param[in] aInsertMode Mode of insertion new pair (implicit mode is TInsert::EUniqueKey)
	 *  \return Iterator pointing to the inserted pair
	 *  \attention Method generate \c std::runtime_error exception if insertion mode is \p EUniqueKey and \a aKey in the map already exist
	 */
	CForwardIterator Insert(const CPair& aPair, TInsert aInsertMode = TInsert::EUniqueKey)
		{ return Insert(CPair(aPair), aInsertMode); }
	
	/** \brief Method Insert overload for move semantics
	 *  \details Use key and value to create new (moving) pair and insert it into the map
	 */
	CForwardIterator Insert(CPair&& aPair, TInsert aInsertMode = TInsert::EUniqueKey);
	
	/** \brief Create and return iterator pointing at first pair in the map
	 *  \return Iterator pointing at first pair in the map
	 */
	CForwardIterator begin() const;

	/** \brief Create and return iterator pointing after last pair in the map
	 *  \return Iterator pointing after last pair in the map
	 */
	CForwardIterator end() const
		{ return CForwardIterator(); }

	/** \brief Create and return iterator pointing to pair with required key
	 *  \param[in] aKey Required key
	 *  \param[in] aAtMode Mode of finding required pair (implicit mode is TAt::EFirstDuplicity)
	 *  \return Iterator pointing to the required pair
	 */
	CForwardIterator At(const CPair::TKey& aKey, TAt aAtMode = TAt::EFirstDuplicity) const;

	/** \brief Create and return iterator pointing to the required pair
	 *  \param[in] aPair Required pair (key and value)
	 *  \param[in] aAtMode Mode of finding required pair (implicit mode is TAt::EFirstDuplicity)
	 *  \return Iterator pointing to the required pair
	 */
	CForwardIterator At(const CPair& aPair, TAt aAtMode = TAt::EFirstDuplicity) const;
	
	/** \brief Indexing map by key (subscript operator)
	 *  \param[in] aKey Key value
	 *  \return reference to first pair with required \a aKey
	 *  \attention Method generate \c std::runtime_error exception if \a aKey in the map does not exist
	 */
	CPair& operator[](const CPair::TKey& aKey) const;

	/** \brief Pairs count getter
	 *  \return Number of pairs stored in the CHashMap
	 */
	size_t Count() const
		{ return iItemCount; }

	/** \brief Pair with specific key count getter
	 *  \param[in] aKey Key value
	 *  \return Number of pairs stored in the CHashMap with key equals to \a aKey
	 */
	size_t Count(const CPair::TKey& aKey) const;

	/** \brief Pair with specific pair count getter
	 *  \param[in] aPair Pair value
	 *  \return Number of pairs stored in the CHashMap with key and Value equals to \a aPair
	 */
	size_t Count(const CPair& aPair) const;

	/** \brief Clear content of the map
	 *  \details Deallocate all Item with Pairs, BucketTable and initialize as empty whole Map
	 */
	void Clear();

	/** \brief Erase pair pointed by CForwardIterator
	 *  \details Erase pair of the CHashMap which is pointing by CForwardIterator. \a aIter must point to the pairs in the same map.
	 *  \param[in,out] aIter Iterator pointing to the pair value in the CHashMap. Method update \a aIter after removing Pair to the new valid value.
	 *  \return New valid value of iterator. Iterator now pointing to the pair after removed pair if there exist.
	 *  \attention Method generate \c std::runtime_error exception if \a aIter is invalid iterator (nullptr)
	 *  \attention Method generate \c std::logic_error exception if \a aIter pointing to the different HashMap than is associated with \p this
	 */
	CForwardIterator& Erase(CForwardIterator& aIter);

	/** \brief Method Erase overload for move semantics
	 */
	CForwardIterator&& Erase(CForwardIterator&& aIter)
		{ return std::move(Erase(aIter)); }

	/** \brief InstanceInfo ID getter
	 *  \return Unique instance ID
	 */
	size_t ID() const
		{ return(iInstanceInfo.ID()); }
	
	}; /* class CHashMap */

#endif /* __CHASHMAP_H__ */
