
#include "plugins/phpbb_auth/phpbb_session_provider.h"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>

#include <glog/logging.h>

using namespace anh::database;
using namespace plugins::phpbb_auth;
using namespace std;
using namespace swganh::connection;


PhpbbSessionProvider::PhpbbSessionProvider(
    DatabaseManagerInterface* database_manager,
    string table_prefix)
    : MysqlSessionProvider(database_manager)
    , database_manager_(database_manager)
    , table_prefix_(table_prefix)
{}

uint64_t PhpbbSessionProvider::GetPlayerId(uint32_t account_id)
{
    uint64_t player_id = FindPlayerByReferenceId_(account_id);

    if (player_id == 0)
    {
        CreatePlayerAccount_(account_id);
        player_id = FindPlayerByReferenceId_(account_id);
    }

    return player_id;
}

bool PhpbbSessionProvider::CreatePlayerAccount_(uint64_t account_id)
{
	bool success = false;
    try 
    {
        string sql = "call sp_CreatePlayerAccount(?);";
        auto conn = database_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt64(1, account_id);
        auto rows_updated = statement->executeUpdate();
        if (rows_updated > 0)
            success = true;
    } 
    catch(sql::SQLException &e) 
    {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }

    return success;
}
    
uint64_t PhpbbSessionProvider::FindPlayerByReferenceId_(uint64_t account_id)
{
    uint64_t player_id = 0;

    try {
        string sql = "select id from player_account where reference_id = ?";
        auto conn = database_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt(1, account_id);
        auto result_set = statement->executeQuery();
        
        if (result_set->next()) {
            player_id = result_set->getUInt64("id");
            
        } else {
            DLOG(WARNING) << "No Player Id found for account_id: " << account_id << endl;
        }

    } catch(sql::SQLException &e) {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }

    return player_id;
}
