/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2010 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/
#pragma once
#ifndef ANH_ZONESERVER_STATE_MANAGER_H
#define ANH_ZONESERVER_STATE_MANAGER_H

#include "ZoneServer/declspec.h"
#include "ActionState.h"
#include "LocomotionState.h"
#include "PostureState.h"
#include <map>

#define gStateManager ::utils::Singleton<::common::StateManager>::Instance()

// add a map for each type of State here
typedef std::map<int, std::unique_ptr<ActionState>> ActionStateMap;
typedef std::map<int, std::unique_ptr<LocomotionState>> LocomotionStateMap;
typedef std::map<int, std::unique_ptr<PostureState>> PostureStateMap;

class ZONE_API StateManager
{
public:
	/*	@short State Manager is the state machine system that converts the object to and from a state.
	**
	**
	*/
	StateManager();
	~StateManager();

	void setCurrentActionState(CreatureObject* object, ActionState* currState, ActionState* newState);
	void setCurrentLocomotionState(CreatureObject* object, LocomotionState* currState, LocomotionState* newState);
	void setCurrentPostureState(CreatureObject* object, PostureState* currState, PostureState* newState);
	
	//void addLocomotionState(LocomotionState* state);
	//void addPostureState(PostureState* state);

	void removeActionState(Object* object, ActionState* currState);

	ActionStateMap		mActionStateMap;
	PostureStateMap		mPostureStateMap;
	LocomotionStateMap	mLocomotionStateMap;
private:
	void addActionState(Object* object, ActionState* newState);
	ActionStateMap		loadActionStateMap();
	PostureStateMap		loadPostureStateMap();
	LocomotionStateMap	loadLocomotionStateMap();
};
#endif