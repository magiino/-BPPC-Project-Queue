/** \file CHashMap.cpp
 *  \brief CHashMap class implementation
 *  \details File contain CHashMap class container implementation.
 *  \authors Pety 2017
 *  $Id: CHashMap.cpp 1637 2017-12-10 02:37:41Z xmagat01 $
 */

#include "CHashMap.h"

// ****************************************************************************
// ************************ CHashMap::CForwardIterator ************************
// ****************************************************************************

CHashMap::CForwardIterator& CHashMap::CForwardIterator::operator++()
	{
	if (!iAct)
		throw std::runtime_error("Incrementing of invalid iterator");
	if (iAct != iBucketTable[iBucketIdx].iTail)
	{
		iPrev = iAct;
		iAct = iAct->iNext;
	}
	else
	{
		do
		{
			++iBucketIdx;
			if (iBucketIdx >= iBucketTableSize)
			{
				iAct = nullptr;
				return(*this);
			}
			iPrev = nullptr;
			iAct = iBucketTable[iBucketIdx].iHead;
		} 
		while (!iAct);
	}
	return(*this);
	}  /* CHashMap::CForwardIterator::operator++() */

// ****************************************************************************
// ********************************* CHashMap *********************************
// ****************************************************************************

CHashMap::CHashMap(const CHashMap& aHashMap): iBucketTable(nullptr), iBucketTableSize(aHashMap.iBucketTableSize), iItemCount(0)
	{
	if (!aHashMap.Count())
		return;
	iBucketTable = new TBucket[iBucketTableSize];
	for (CForwardIterator it = aHashMap.begin(); it != aHashMap.end(); ++it)
		Insert(*it, TInsert::EAfterLastKeyDuplicity);


	}  /* CHashMap::CHashMap(aHashMap) */

CHashMap& CHashMap::operator=(const CHashMap& aHashMap)
	{
	if(this == &aHashMap)
		return(*this);
	Clear();

	iBucketTable = new TBucket[aHashMap.iBucketTableSize];
	iBucketTableSize = aHashMap.iBucketTableSize;

	for (CForwardIterator it = aHashMap.begin(); it != aHashMap.end(); ++it)
		Insert(*it, TInsert::EAfterLastKeyDuplicity);
	//aj takto to ide
	//for(CPair& pair:aHashMap)
	//	Insert(pair, TInsert::EAfterLastKeyDuplicity);

		return(*this);

	}  /* CHashMap::operator=(aHashMap) */

CHashMap::CForwardIterator CHashMap::Insert(CPair&& aPair, TInsert aInsertMode)
	{
		if (!iBucketTable)
			iBucketTable = new TBucket[iBucketTableSize];

		size_t idx = CalculateHash(aPair.Key());
		if (!iBucketTable[idx].iHead)
		{
			iBucketTable[idx].iHead = iBucketTable[idx].iTail = new TItem(std::move(aPair));
			++iItemCount;
			return(CForwardIterator(iBucketTable, iBucketTableSize, nullptr, iBucketTable[idx].iHead, idx));
		}

		// Try to insert Pair as last TItem
		if ((aInsertMode == TInsert::EUniqueKey) && (iBucketTable[idx].iTail->iPair.Key() == aPair.Key()))
			throw std::runtime_error("Pair with this key in the map already exist"); // Error trying insert duplicity

		if ((iBucketTable[idx].iTail->iPair.Key() < aPair.Key()) ||
			((aInsertMode == TInsert::EAfterLastKeyDuplicity) && (iBucketTable[idx].iTail->iPair.Key() == aPair.Key())) ||
			((aInsertMode == TInsert::EByPair) && (iBucketTable[idx].iTail->iPair.Key() == aPair.Key()) && (iBucketTable[idx].iTail->iPair.Value() < aPair.Value()))
			)
		{
			TItem *act = new TItem(std::move(aPair));
			TItem *prev = iBucketTable[idx].iTail;
			iBucketTable[idx].iTail->iNext = act;
			iBucketTable[idx].iTail = act;
			++iItemCount;
			return(CForwardIterator(iBucketTable, iBucketTableSize, prev, act, idx));
		}

		TItem *prev = nullptr;
		TItem *act = iBucketTable[idx].iHead;
		for (; (act != iBucketTable[idx].iTail) && (act->iPair.Key() < aPair.Key()); prev = act, act = act->iNext);

		if ((aInsertMode == TInsert::EUniqueKey) && (act->iPair.Key() == aPair.Key()))
			throw std::runtime_error("Pair with this key in the map already exist"); //Error trying insert duplicity

		if ((aInsertMode == TInsert::EAfterLastKeyDuplicity) && (iBucketTable[idx].iHead->iPair.Key() == aPair.Key()))
			for (; (act != iBucketTable[idx].iTail) && (act->iPair.Key() == aPair.Key()); prev = act, act = act->iNext);

		else if ((aInsertMode == TInsert::EByPair) && (iBucketTable[idx].iHead->iPair.Key() == aPair.Key()))
			for (; (act != iBucketTable[idx].iTail) && (act->iPair.Key() == aPair.Key()) && (act->iPair.Value() < aPair.Value()); prev = act, act = act->iNext);

		TItem *item = new TItem(std::move(aPair), act);
		if (prev)
			prev->iNext = item;
		else
			iBucketTable[idx].iHead = item;

		++iItemCount;
		return(CForwardIterator(iBucketTable, iBucketTableSize, prev, item, idx));
	}  /* CHashMap::Insert(aPair) */



CHashMap::CForwardIterator CHashMap::begin() const
	{
	if(Count() == 0 || !iBucketTable)
		return CForwardIterator();
	for (size_t idx = 0; idx < iBucketTableSize; ++idx)
	{
		if (iBucketTable[idx].iHead)
		{
			return CForwardIterator(iBucketTable, iBucketTableSize, nullptr, iBucketTable[idx].iHead, idx);
		}
	}

	return CForwardIterator();
	}  /* CHashMap::begin() */

CHashMap::CForwardIterator CHashMap::At(const CPair::TKey& aKey, TAt aAtMode) const
	{
	if (!Count() || !iBucketTable)
		return CForwardIterator();

	size_t idx = CalculateHash(aKey);
	TItem *act = iBucketTable[idx].iHead;

	if (!act)
		return CForwardIterator();

	TItem *prev = nullptr;

	for (; (act->iPair.Key() < aKey) && (act != iBucketTable[idx].iTail); prev = act, act = act->iNext);
	
	if (act->iPair.Key() != aKey)
		return CForwardIterator();

	if (aAtMode == TAt::ELastDuplicity)
	{
		TItem *nxt = act->iNext;
		while ((nxt) && (nxt->iPair.Key() == aKey))
		{
			prev = act;
			act = nxt;
			nxt = nxt->iNext;
		}
	}
	return(CForwardIterator(iBucketTable, iBucketTableSize, prev, act, idx));

	}  /* CHashMap::At(aKey) */

CHashMap::CForwardIterator CHashMap::At(const CPair& aPair, TAt aAtMode) const
	{
	CForwardIterator it = At(aPair.Key());
	if (!it)
		return CForwardIterator();
	
	for (; (it) && (it->Key() == aPair.Key()); ++it)
	{
		if (it->Value() == aPair.Value())
			break;
	}

	if ((!it) || ((it->Key() != aPair.Key() && (it->Value() != aPair.Value()))))
	{
		return(CForwardIterator());
	}
	
	if (aAtMode == TAt::ELastDuplicity)
	{
		CForwardIterator nxt = it;
		for (++nxt; (nxt) && (nxt->Key() == aPair.Key()); ++nxt)
		{
		if (nxt->Value() == aPair.Value())
			it = nxt;
		}
	}

	return (it);
	}  /* CHashMap::At(aPair) */

CPair& CHashMap::operator[](const CPair::TKey& aKey) const
	{
	CForwardIterator it = At(aKey);
	if (!it)
		throw std::runtime_error("Key does not exist");

	return(*it);
	}  /* CHashMap::operator[](aKey) */

size_t CHashMap::Count(const CPair::TKey& aKey) const
	{
	size_t count = 0;

	for (CForwardIterator it = At(aKey); it && (it->Key() == aKey); ++count, ++it);
	return count;
	}  /* CHashMap::Count(aKey) */

size_t CHashMap::Count(const CPair& aPair) const
	{
	size_t count = 0;
	for (CForwardIterator it = At(aPair.Key()); it && (it->Key() == aPair.Key()); ++it)
		if(it->Value() == aPair.Value())
			++count;
	
	return count;
	}  /* CHashMap::Count(aPair) */

void CHashMap::Clear()
	{
	if (!iBucketTable)
		return;
	for (size_t idx = 0; idx < iBucketTableSize; ++idx)
	{
		TItem*act = iBucketTable[idx].iHead;
		while (act)
		{
			TItem*next = act->iNext;
			delete act;
			act = next;
		}
		iBucketTable[idx].iHead = iBucketTable[idx].iTail = nullptr;
	}
	delete[] iBucketTable;
	iBucketTable = nullptr;
	iItemCount = 0;
	}  /* CHashMap::Clear() */

CHashMap::CForwardIterator& CHashMap::Erase(CHashMap::CForwardIterator& aIter)
	{
	if (!aIter)
	{
		throw std::runtime_error("Cannot erase pair by invalid iterator");
	}
	if ((aIter.iBucketTable != iBucketTable) || (aIter.iBucketTableSize != iBucketTableSize))
	{
		throw std::runtime_error("Mismatch instances of iterator and map");
	}

	TItem *act = aIter.iAct;
	TItem *prev = aIter.iPrev;
	size_t idx = aIter.iBucketIdx;
	++aIter;

	if (iBucketTable[idx].iTail == act)
		iBucketTable[idx].iTail = prev;
	
	if (aIter.iPrev == act)
		aIter.iPrev = prev;

	if (prev)
		prev->iNext = act->iNext;
	else
		iBucketTable[idx].iHead = act->iNext;
	
	--iItemCount;
	
	delete act;
	return aIter;
	}  /* CHashMap::Erase(aIter) */
