/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "swganh/login/providers/mysql_account_provider.h"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>

#include <glog/logging.h>

#include "anh/database/database_manager.h"


using namespace swganh::login;
using namespace providers;
using namespace swganh::login;
using namespace std;

MysqlAccountProvider::MysqlAccountProvider(anh::database::DatabaseManagerInterface* db_manager)
    : AccountProviderInterface()
    , db_manager_(db_manager) {}

MysqlAccountProvider::~MysqlAccountProvider() {}

shared_ptr<Account> MysqlAccountProvider::FindByUsername(string username) {
    shared_ptr<Account> account = nullptr;

    try {
        string sql = "select id, username, password, salt, enabled from account where username = ?";
        auto conn = db_manager_->getConnection("galaxy_manager");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setString(1, username);
        auto result_set = statement->executeQuery();
        
        if (result_set->next()) {
            account = make_shared<Account>(true);

            account->account_id(result_set->getInt("id"));
            account->username(result_set->getString("username"));
            account->password(result_set->getString("password"));
            account->salt(result_set->getString("salt"));
            if (result_set->getInt("enabled") == 1) {
                account->Enable();
            } else {
                account->Disable();
            }

            account->algorithm("sha1");
        } else {
            DLOG(WARNING) << "No account information found for user: " << username << endl;
        }

    } catch(sql::SQLException &e) {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }

    return account;
}
uint32_t MysqlAccountProvider::FindBySessionKey(const string& session_key) {
    uint32_t account_id = 0;

     try {
        string sql = "select account from account_session where session_key = ?";
        auto conn = db_manager_->getConnection("galaxy_manager");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setString(1, session_key);
        auto result_set = statement->executeQuery();
        
        if (result_set->next()) {
            account_id = result_set->getInt("account");
            
        } else {
            DLOG(WARNING) << "No account found for session_key: " << session_key << endl;
        }

    } catch(sql::SQLException &e) {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
     return account_id;
}
bool MysqlAccountProvider::CreateAccountSession(uint32_t account_id, const std::string& session_key) {
    bool success = false;
    try {
        string sql = "INSERT INTO account_session(account, session_key) VALUES(?,?);";
        auto conn = db_manager_->getConnection("galaxy_manager");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt64(1, account_id);
        statement->setString(2, session_key);
        auto rows_updated = statement->executeUpdate();
        if (rows_updated > 0)
            success = true;

    } catch(sql::SQLException &e) {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }

    return success;
}

bool MysqlAccountProvider::AutoRegisterAccount(std::string username, std::string password) {
    bool success = false;
    try {
        string sql = "call sp_CreateAccount(?,?,?);";
        auto conn = db_manager_->getConnection("galaxy_manager");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setString(1, username);
        statement->setString(2, password);
        statement->setString(3, "");
        auto results = unique_ptr<sql::ResultSet>(statement->executeQuery());
        if (results->next())
		{
			if (CreatePlayerAccount(results->getUInt64(1)))
				success = true;
		}
    } catch(sql::SQLException &e) {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }

    return success;
}
bool MysqlAccountProvider::CreatePlayerAccount(uint64_t account_id)
{
	bool success = false;
    try {
        string sql = "call sp_CreatePlayerAccount(?);";
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt64(1, account_id);
        auto rows_updated = statement->executeUpdate();
        if (rows_updated > 0)
            success = true;
    } catch(sql::SQLException &e) {
        DLOG(ERROR) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        DLOG(ERROR) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }

    return success;
}