#ifndef __CLASSINFO_H__
#define __CLASSINFO_H__
/** \file ClassInfo.h
 *  \brief ClassInfo class header
 *  \details File contain ClassInfo definition with 64bit counter support.
 *  \warning Don't modify this file
 *  \author Pety 2017
 *  $Id: ClassInfo.h 1 2017-11-06 09:45:38Z petyovsky $
 */

#include <cstddef>	// due size_t and ptrdiff_t (unsigned and int better equivalent for x64 platform)

/** \brief ClassInfo class template
 *  \tparam	T The class name of type that want to keep statistical information
 *  \details Definition of ClassInfo class template. There is defined all common methods and member variables.
 */
template <typename T>
	class ClassInfo
		{
		const size_t iID;					///< Constant value for simple runtime instance identification and debuging
		static size_t iTotalCounter;		///< Summary count of all created instances
		static ptrdiff_t iLivingCounter;	///< Counter of actually existing instances
#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
		friend T;							///< Set Template argument class as friend. So no one (only class) have access to the private methods of ClassInfo instances. C++11 feature.
#else
	public:
#endif
	//c'tors
#define CLASSINFO_IMPLICIT_CTOR_BODY :iID(iTotalCounter++) {iLivingCounter++;}
#if (__cplusplus >= 201103L) || (_MSC_VER >= 1800)
	#define CLASSINFO_IMPLICIT_CTOR_BODY_DELEGATED :ClassInfo() {}
#else
	#define CLASSINFO_IMPLICIT_CTOR_BODY_DELEGATED CLASSINFO_IMPLICIT_CTOR_BODY
#endif
		
		/** \brief Implicit c'tor
		 *  \details Initialise iID and increment counters.
		 */
		ClassInfo() CLASSINFO_IMPLICIT_CTOR_BODY

		/** \brief Copy c'tor
		 *  \details Initialise iID and increment counters.
		 */
		ClassInfo(const ClassInfo &) CLASSINFO_IMPLICIT_CTOR_BODY_DELEGATED
		
	//d'tor
		/** \brief d'tor
		 *  \details Decrement Living instance counter only.
		 */
		~ClassInfo()
			{ iLivingCounter--; }

		/** \brief Assigment operator
		 *  \return Just return self
		 */
		ClassInfo& operator=(const ClassInfo &)
			{ return(*this); }

#define MOVE_SEMANTICS
#ifdef MOVE_SEMANTICS
		
		/** \brief Move c'tor!
		 *  \details Initialise new iID and increment counters.
		 */
		ClassInfo(ClassInfo &&) CLASSINFO_IMPLICIT_CTOR_BODY_DELEGATED
		
		/** \brief Move operator
		 *  \details Initialise new iID and increment counters.
		 *  \return Just return self
		 */
		ClassInfo& operator=(ClassInfo &&)
			{ return(*this); }

#endif /* MOVE_SEMANTICS */

		/** \brief ID getter
		 *  \return Unique instance ID
		 */
		size_t ID() const
			{ return(iID); }

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
	public:
#endif
	// counters getters
		/** \brief Getter for actual count of all created instances
		 *  \return Actual count of all created instances
		 */
		static size_t Total()
			{ return(iTotalCounter); }
		
		/** \brief Getter for count of actually existing instances
		 *  \return Count of actually existing instances
		 */
		static ptrdiff_t Living()
			{ return(iLivingCounter); }
		
		}; /* class ClassInfo */

template <typename T>
	size_t ClassInfo<T>::iTotalCounter = 0;

template <typename T>
	ptrdiff_t ClassInfo<T>::iLivingCounter = 0;

#endif /* __CLASSINFO_H__ */
