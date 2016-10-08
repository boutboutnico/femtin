
#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

// ====================================================================================================================
// ===	INCLUDES
// ====================================================================================================================
#include "state.h"
#include "transition.h"

// ====================================================================================================================
// ===	NAMESPACES
// ====================================================================================================================

/// \namespace	util
///	\brief		Contains utilitary classes.
namespace util
{

// ====================================================================================================================
// ===	CLASS
// ====================================================================================================================

/// \class	I_State_Machine
///	\brief	State machine Interface.
/// \date	17/04/2017
/// \author	nboutin & bpayen
/// \code
///
/// static const uint8_t N_STATE = 3;
/// static const uint8_t N_TRANSITION = 3;
///
/// State s_on;
/// State s_off;
/// State s_error;
///
/// Transition t_on;
/// Transition t_off;
/// Transition t_error;
///
/// /// State start is s_off
/// State_Machine<N_STATE, N_TRANSITION> state_machine(s_off);
///
/// ///  Transition t_error define with highest priority
/// state_machine.setTransitionPriority(t_error);
///
/// state_machine.add(s_on, s_off, t_off);
/// state_machine.add(s_on, s_on, t_on);
/// state_machine.add(s_on, s_error, t_error);
///
/// state_machine.add(s_off, s_on, t_on);
/// state_machine.add(s_off, s_off, t_off);
/// state_machine.add(s_off, s_error, t_error);
///
/// ///  Go to s_on
/// state_machine.fireTransition(t_on);
///
/// ///  Go to s_off
/// state_machine.fireTransition(t_off);
///
/// ///  Post 3 transitions
/// state_machine.postTransition(t_on);
/// state_machine.postTransition(t_off);
/// state_machine.postTransition(t_error);
///
/// ///  Go to s_error because it has the highest priority.
/// state_machine.update();
///
/// \endcode
class I_State_Machine
{
public:
	// ============================================================================================================
	// ===	PUBLIC INTERFACE
	// ============================================================================================================
	///
	/// \brief	Add element state machine
	/// \param	src : source state
	/// \param	trans : transition
	/// \param	dst : destination state
	///
	virtual bool add(State& src, State& dst, Transition& trans) = 0;

	///
	/// \brief	Delete transition
	/// \param	trans : transition to remove
	/// \return	true if transition is removed
	///
	virtual bool remove(Transition& trans) = 0;

	///
	/// \brief	Post transition
	/// \param	trans : transition post
	///
	virtual void postTransition(Transition& trans) = 0;

	///
	/// \brief	Update state machine
	///
	virtual void update() = 0;

	///
	/// \brief	Execute transition
	/// \param	trans : transition to execute
	///
	virtual void fireTransition(Transition& trans) = 0;

	///
	/// \brief	Restart state machine
	///
	virtual void restart() = 0;
};

// ====================================================================================================================
// ===	CLASS
// ====================================================================================================================

/// \class	State_Machine
///	\brief	State machine implementation.
/// \date	17/04/2017
/// \author	nboutin & bpayen
template<uint8_t n_state, uint8_t n_transition>
class State_Machine: public I_State_Machine
{
public:
	// ============================================================================================================
	// ===	PUBLIC CONSTANTS
	// ============================================================================================================
	static const uint32_t FLAGS_DEFAULT = ((uint32_t) 1 << Transition_True::BIT_DEFAULT);	///< Flags default value

	// ============================================================================================================
	// ===	PUBLIC DECLARATIONS
	// ============================================================================================================
	///
	/// \brief	Default constructor
	/// \param	start : start state
	/// \param	is_transition_true_used : indicate if transition is used
	///
	State_Machine(State& start, const bool is_transition_true_used = false)
		: m_uc_i_state_add(0), m_uc_i_trans_add(0), m_pcl_state_start(&start), m_pcl_state_current(&start),
		  m_ul_flags(FLAGS_DEFAULT)
	{
		if (is_transition_true_used == true)
		{
			m_uc_i_trans_add = 1; // id 0 reserved for transition_true, highest priority
		}

		memset(m_ptcl_state_dest, 0x00, sizeof(State*) * n_state * n_transition);
	}

	/// \brief		State_Machine set transition priority
	/// 			First transition set will have the highest priority.
	/// \warning	Should be used before add ad it will also set a priority.
	/// \param		[in] trans	Transition to set priority.
	bool setTransitionPriority(Transition& trans)
	{
		// Return
		return (generateId(trans));
	}

	/// \brief		Define relation between states and a transition.
	/// \warning	Transition priority is set in the order of the first call in add.
	///	\see		setTransitionPriority()
	///	\param		[in] src	Source state from which "trans" come from.
	/// \param		[in] dst	Desination state to which "trans" go to.
	/// \param		[in] trans	Directionnal link from "src" to "dst".
	virtual bool add(State& src, State& dst, Transition& trans)
	{
		// Declaration
		bool b_result = true;

		b_result &= generateId(src);
		b_result &= generateId(dst);
		b_result &= generateId(trans);

		if (b_result == true)
		{
			m_ptcl_state_dest[src.getId()][trans.getId()] = &dst;

			// Return
			return (true);
		}
		else
		{
			// Return
			return (false);
		}
	}

	///
	/// \brief	Remove the transition requested
	/// \param	trans : transition to remove
	/// \return	true if success
	///
	virtual bool remove(Transition& trans)
	{
		if (trans.getId() < n_transition)
		{
			for (uint8_t s = 0; s < n_state; s++)
			{
				m_ptcl_state_dest[s][trans.getId()] = NULL;
			}

			// Return
			return (true);
		}
		else
		{
			// Return
			return (false);
		}
	}

	/// \brief		Post a transition and immediately compute its effects on state machine
	///				according to current_state and transition table.
	/// \warning	Must not be called in OnEnter and in OnExit State define functions.
	/// \param		[in] trans	Transition to execute.
	virtual void fireTransition(Transition& trans)
	{
		setFlag(trans.getId());
		update(trans.getId());
	}

	/// \brief	Post a transition to the state_machine but does not compute next state.
	/// \param	[in] trans	Transition to post.
	virtual void postTransition(Transition& trans)
	{
		setFlag(trans.getId());
	}

	/// \brief	Compute next state according to posted transition and current state.
	///			Should be call periodically.
	virtual void update()
	{
		/// Loop on flags from the highest priority to the lowest
		uint8_t trans_id = getHighestPriorityTransition();

		while (trans_id < n_transition)
		{
			if (update(trans_id) == true)
			{
				/// Move to a new state so check Transition priority from beginning
				trans_id = getHighestPriorityTransition();
			}
			else
			{
				/// Search for next highest transition
				trans_id = getHighestPriorityTransition(++trans_id);
			}
		}
	}

	///
	/// \brief	Restart state machine
	///
	virtual void restart()
	{
		clearAllTransition();
		m_pcl_state_current = m_pcl_state_start;
	}

	///
	/// \brief	Clear all transition
	///
	void clearAllTransition()
	{
		m_ul_flags = FLAGS_DEFAULT;
	}

private:
	// ============================================================================================================
	// ===	PRIVATE DECLARATIONS
	// ============================================================================================================
	///
	/// \brief	Provides the transition of the highest priority
	/// \param	start_id : transition identifier to start search
	/// \return	Transition with the highest priority
	///
	uint8_t getHighestPriorityTransition(const uint8_t start_id = 0) const
	{
		for (uint8_t i = start_id; i < n_transition; i++)
		{
			if (m_ul_flags & (1 << i))
			{
				// Return transition i
				return (i);
			}
		}
		// Return the last transition
		return (n_transition);
	}

	///
	/// \brief	Update state machine
	/// \param	trans_id : current transition identifier
	/// \return	true if success
	//
	bool update(const uint8_t trans_id)
	{
		// Declaration
		uint8_t s = m_pcl_state_current->getId();
		uint8_t t = trans_id;

		if (m_ptcl_state_dest[s][t] != NULL)
		{
			/// On exit for current_state
			m_pcl_state_current->onExit();

			/// On transition
			/// if (trans.Execute() == false) return false;

			/// On enter for new state
			if (m_ptcl_state_dest[s][t]->onEnter() == false)
			{
				// Return
				return (false);
			}

			/// Save new current state
			m_pcl_state_current = m_ptcl_state_dest[s][t];

			m_ptcl_state_dest[s][t]->inState();

			resetFlag(trans_id);

			// Return
			return (true);
		}

		// Return
		return (false);
	}

	///
	/// \brief	Set internal flag
	/// \param	trans_id : transition to set
	///
	void setFlag(const uint8_t trans_id)
	{
		m_ul_flags |= 1 << trans_id;
	}

	///
	/// \brief	Reset internal flag
	/// \param	trans_id : transition to reset
	///
	void resetFlag(const uint8_t trans_id)
	{
		m_ul_flags &= ~(1 << trans_id) | FLAGS_DEFAULT;
	}

	///
	/// \brief	Generate state identifier
	/// \param	state : state input
	/// \return	true if success
	///
	bool generateId(State& state)
	{
		if (state.getId() == State::ID_DEFAULT)
		{
			if (m_uc_i_state_add < n_state)
			{
				state.setId(m_uc_i_state_add++);
			}
			else
			{
				// Return error
				return (false);
			}
		}

		// Return
		return (true);
	}

	///
	/// \brief	Generate transition identifier
	/// \param	trans : transition input
	/// \return	true if success
	///
	bool generateId(Transition& trans)
	{
		if (trans.getId() == Transition::ID_DEFAULT)
		{
			if (m_uc_i_trans_add < n_transition)
			{
				trans.setId(m_uc_i_trans_add++);
			}
			else
			{
				// Return error
				return (false);
			}
		}

		// Return
		return (true);
	}

	// ============================================================================================================
	// ===	PRIVATE ATTRIBUTS
	// ============================================================================================================
	uint8_t m_uc_i_state_add;							///< State identifier
	uint8_t m_uc_i_trans_add;							///< Transition identifier
	State* m_pcl_state_start;							///< Pointer of start state

	State* m_pcl_state_current;							///< Pointer of current state
	uint32_t m_ul_flags;									///< Internal flags state machine

	State* m_ptcl_state_dest[n_state][n_transition];	///< List of state & transition

#ifdef TEST_INTEGR
	friend class ti_state_machine;
#endif
};

}	// Namespace util


#endif	// STATE_MACHINE_H_

// ====================================================================================================================
// ===	END OF FILE
// ====================================================================================================================
