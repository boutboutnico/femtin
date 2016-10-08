

#ifndef STATE_H_
#define STATE_H_

// ====================================================================================================================
// ===	INCLUDES
// ====================================================================================================================
#include "sp2_common.h"
#include "timer.h"
#include "thread.h"

// ====================================================================================================================
// ===	NAMESPACES
// ====================================================================================================================

///
/// \namespace	util
///	\brief		Contains utilitary classes.
///
namespace util
{

// ====================================================================================================================
// ===	CLASS
// ====================================================================================================================
template<uint8_t n_state, uint8_t n_transition> class State_Machine;

// ====================================================================================================================
// ===	CLASS
// ====================================================================================================================

/// \class	I_State
///	\brief	State interface.
/// \date	17/04/2014
/// \author	nboutin
class I_State
{
public:
	// ============================================================================================================
	// ===	PUBLIC DECLARATIONS
	// ============================================================================================================
	///
	/// \brief	Called each time we enter the state from another state
	/// \return	TRUE if success, FALSE otherwise.
	///
	virtual bool onEnter() = 0;

	///
	/// \brief	Called each time we exit the state for another state.
	///
	virtual void onExit() = 0;

	///
	/// \brief	Called each time a transition lead to this state.
	///
	virtual void inState() = 0;
};

// ====================================================================================================================
// ===	CLASS
// ====================================================================================================================

/// \class	State
///	\brief	Model a state in State_Machine.
/// \date	17/04/2014
/// \author	nboutin
class State: public I_State
{
	/// Only State_Machine can change a State id.
	template<uint8_t n_state, uint8_t n_transition> friend class State_Machine;

public:
	// ============================================================================================================
	// ===	PUBLIC CONSTANTS
	// ============================================================================================================
	static const uint8_t ID_DEFAULT = 0xFF;	///< Default identifier

	// ============================================================================================================
	// ===	PUBLIC DECLARATIONS
	// ============================================================================================================
	///
	/// \brief	Default constructor
	///
	State()
		: m_uc_id(ID_DEFAULT)
	{
	}

	///
	/// \brief	Enter state
	/// \return	true if success
	///
	virtual bool onEnter();

	///
	/// \brief	Exit state
	/// \return	true if success
	///
	virtual void onExit();

	///
	/// \brief	In state execution
	///
	virtual void inState();

	///
	/// \brief	Provides state identifier
	/// \return	Identifier
	///
	uint8_t getId() const
	{
		// Return
		return (m_uc_id);
	}

#ifdef __DBG_STATE // For debug state
	/// Set a name to a state so debug is easier.

	static const uint8_t NAME_LENGTH = 24;

	template<uint8_t Len>
	void setName(const CHAR8 (&name)[Len])
	{
		if (Len <= NAME_LENGTH)
		{
			strncpy(s_name, &name[0], sizeof(CHAR8) * Len);
		}
	}
	CHAR8 s_name[NAME_LENGTH];
#endif

private:
	// ============================================================================================================
	// ===	PRIVATE DECLARATIONS
	// ============================================================================================================
	///
	/// \brief	Set identifier
	/// \param	iu8_id : identifier
	///
	/// TODO protection, only accessible from State_Machine, use friend key word.
	void setId(const uint8_t iu8_id)
	{
		m_uc_id = iu8_id;
	}

	// ============================================================================================================
	// ===	PRIVATE ATTRIBUTS
	// ============================================================================================================
	uint8_t m_uc_id;
};

// ====================================================================================================================
// ===	CLASS
// ====================================================================================================================

/// \class	State_Timed
///	\brief	Model a state with a timeout.
/// \date	17/04/2014
/// \author	nboutin
//class State_Timed: public State
//{
//public:
//	// ============================================================================================================
//	// ===	PUBLIC DECLARATIONS
//	// ============================================================================================================
//	///
//	/// \brief	Default constructor
//	/// \param	icl_timer : timer
//	/// \param	ius_duration_ms : duration time out
//	///
//	State_Timed(OS::OS_Timer& icl_timer, const uint16_t ius_duration_ms)
//		: 	m_cl_os_tim(icl_timer),
//			TIMER_DURATION_MS(ius_duration_ms)
//	{
//	}
//
//	///
//	/// \brief	Enter in state
//	/// \return	true
//	///
//	virtual bool onEnter()
//	{
//		m_cl_os_tim.stop();
//		m_cl_os_tim.change(OS::ms_to_tick_os(TIMER_DURATION_MS));
//		m_cl_os_tim.start();
//		return true;
//	}
//
//	///
//	/// \brief	Exit state
//	///
//	virtual void onExit()
//	{
//		m_cl_os_tim.stop();
//	}
//
//private:
//	// ============================================================================================================
//	// ===	PRIVATE ATTRIBUTS
//	// ============================================================================================================
//	OS::OS_Timer& m_cl_os_tim;			///< Timer management
//	const uint16_t TIMER_DURATION_MS;	///< Timer duration for state timed
//};

}

#endif	// STATE_H_

// ====================================================================================================================
// ===	END OF FILE
// ====================================================================================================================
