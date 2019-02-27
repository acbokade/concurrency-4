#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace stickman
{
	/**
	 * Creates a unique pointer for StateRef so that it gets automatically destroyed
	 */
	typedef std::unique_ptr<State> StateRef;

	/**
	 * @brief      Class which is responsible for running a state when it gets loaded
	 */
	class StateMachine
	{
	public:
		/**
		 * @brief      Constructs the object.
		 */
		StateMachine() { }
		/**
		 * @brief      Destroys the object.
		 */
		~StateMachine() { }

		/**
		 * @brief      Marks a state for adding
		 *
		 * @param[in]  newState     The new state which will be added
		 * @param[in]  isReplacing  Indicates if replacing the old state or just pausing it
		 */
		void AddState(StateRef newState, bool isReplacing = true);
		/**
		 * @brief      Marks a  state for removal
		 */
		void RemoveState();
		/**
		 * @brief      This is the function which replaces the states and adds new stats while deleting previous ones. It may also pause or resume states
		 */
		void ProcessStateChanges();

		/**
		 * @brief      Gets the active state which is running
		 *
		 * @return     The active state.
		 */
		StateRef &GetActiveState();

	private:
		/**
		 * Creates a stack of states from which we add or remove
		 */
		std::stack<StateRef> _states;
		/**
		 * The state which we work with 
		 */
		StateRef _newState;

		/**
		 * Variable which marks states for removing
		 */
		bool _isRemoving;
		/**
		 * Variable which marks state for adding or replacing
		 */
		bool _isAdding, _isReplacing;
	};
}