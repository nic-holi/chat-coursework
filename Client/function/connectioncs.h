#ifndef CONNECTIONCS_H
#define CONNECTIONCS_H

#include <string>
#include <list>
#include <qdebug.h>
#include "dataType/ClientInfo.h"
#include "system.h"
#include <QMessageBox>
#include <qtextbrowser.h>
#include <set>
using namespace std;

string conn_login(string username, string password);        // Connect interface and communication, handle login events
string conn_register(string username, string password);     // Handle registration events
#endif // CONNECTIONCS_H
