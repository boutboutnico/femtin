///
/// \file	state_machine_helper.h
/// \brief	State machine helper.
/// \date	07/04/2014
/// \author	nboutin
///

namespace util
{

class State_Machine_Helper
{
public:
	/// ============================================================================================================
	/// ===	PUBLIC CONSTANTS
	/// ============================================================================================================

	static const ULONG32 FLAGS_DEFAULT = ((ULONG32) 1 << Transition_True::BIT_DEFAULT);

	/// ============================================================================================================
	/// ===	PUBLIC DECLARATIONS
	/// ============================================================================================================

	State_Machine_Helper() :
			flags(FLAGS_DEFAULT)
	{

	}

	UCHAR8 getHighestPriorityTransition(const UCHAR8 start_id, const UCHAR8 n_transition)
	{
		for (UCHAR8 i = start_id; i < n_transition; i++)
		{
			if (flags & (1 << i))
			{
				return i;
			}
		}
		return n_transition;
	}

	void clearAllTransition()
	{
		flags = FLAGS_DEFAULT;
	}

	void setFlag(const UCHAR8 trans_id)
	{
		flags |= 1 << trans_id;
	}

	void resetFlag(const UCHAR8 trans_id)
	{
		flags &= ~(1 << trans_id) | FLAGS_DEFAULT;
	}

private:
	/// ============================================================================================================
	/// ===	PRIVATE ATTRIBUTS
	/// ============================================================================================================

	ULONG32 flags;

};

}
