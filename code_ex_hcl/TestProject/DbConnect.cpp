#include <sql.h>
#include <string>
#include <string.h>
#include <sqlext.h>
#include <windows.h>
#include <tchar.h>
#include <iostream>


class DbConnect {

public:
	DbConnect();
	int connect();

private:

	std::string login;
	std::string password;
	std::string server;
	std::string database;
	std::string	m_Sql;

	long		m_LoginTimeout;
	HDBC		m_Hdbc;
	HENV		m_Henv;
	HSTMT		m_Hstmt;


};

DbConnect::DbConnect() {
	login = "";
	password = "";
	server = "";
	database = "C:\\CQ.Data\\HCL2.0\\HCL2.0_m.mdb";
	m_Hdbc = SQL_NULL_HDBC;
	m_Hstmt = SQL_NULL_HSTMT;
	m_Henv = SQL_NULL_HENV;
	m_LoginTimeout = 60; //in sec.

}

int DbConnect::connect() {
	RETCODE rc;

	try {
		rc = SQLAllocEnv(&m_Henv);
		rc = SQLAllocConnect(m_Henv, &m_Hdbc);
		rc = SQLSetConnectOption(m_Hdbc, SQL_ODBC_CURSORS, SQL_CUR_USE_DRIVER);

		const int connect_string_output_max = 1024;
		SQLTCHAR connect_string_output[connect_string_output_max];
		SWORD connect_string_output_len;
		LPCTSTR connect_string = L"DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\CQ.Data\\HCL2.0\\HCL2.0_m.mdb";
		int retries = 3;

		while (retries-- >= 0) {

			try {
				rc = SQLDriverConnect(m_Hdbc,
					NULL,
					(SQLTCHAR*)connect_string,
					_tcslen(connect_string),
					connect_string_output,
					connect_string_output_max,
					&connect_string_output_len,
					SQL_DRIVER_NOPROMPT);
			}
			catch (...) {
				std::cout << "Exception1\n";
			}
		}
	}
	catch (...) {
		std::cout << "Exception2\n";
	}

}