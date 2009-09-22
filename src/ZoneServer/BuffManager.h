/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2008 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_BUFFMANAGER_H
#define ANH_BUFFMANAGER_H

#define	 gBuffManager	BuffManager::getSingletonPtr()
// WTF This is already defined where it should be.... in the message lib
// #define	 gMessageLib	MessageLib::getSingletonPtr()

//======================================================================================================================
#include "DatabaseManager/DatabaseCallback.h"
#include "BuffEvent.h"
#include "Worldmanager.h"
#include "Utils/EventHandler.h"

//======================================================================================================================
class Database;
class DatabaseCallback;
class DatabaseResult;
class CreatureObject;
class PlayerObject;
class QueryContainerBase;
struct buffAsyncContainer;

enum BMQuery
{
	BMQuery_Null			= 0,
	BMQuery_Buffs			= 1,
	BMQuery_Buff_Attributes	= 2,
	BMQuery_Delete			= 3,
	BMQuery_Safe_Async		= 4,
};
//======================================================================================================================
//======================================================================================================================
class BuffManager : public DatabaseCallback, public Anh_Utils::EventHandler
{
	friend class CreatureObject;
public:

	~BuffManager(void);
	BuffManager(Database* database);

	static		BuffManager*	Init(Database* database);
	static		BuffManager*	getSingletonPtr() { return mSingleton; }

	void		handleDatabaseJobComplete(void* ref,DatabaseResult* result);
	void		SaveBuffs(PlayerObject* playerObject, uint64 currenttime);
	bool		SaveBuffsAsync(WMAsyncContainer* asyncContainer,DatabaseCallback* callback, PlayerObject* playerObject, uint64 currenttime);
	void		LoadBuffs(PlayerObject* playerObject, uint64 currenttime);
	void		LoadBuffAttributes(buffAsyncContainer* envelope);
	void		InitBuffs(PlayerObject* Player);

private:
	
	void		LoadBuffsFromResult(buffAsyncContainer* asyncContainer, DatabaseResult* result);
	void		LoadBuffAttributesFromResult(buffAsyncContainer* asyncContainer, DatabaseResult* result);
				
	
	bool		AddBuffToDB(WMAsyncContainer* asyncContainer,DatabaseCallback* callback, Buff* buff, uint64 currenttime);
	void		AddBuffToDB(Buff* buff, uint64 currenttime);


	static		BuffManager*	mSingleton;
	Database*	mDatabase;
	static bool mInsFlag;
};

#endif //ANH_BUFFMANAGER_H