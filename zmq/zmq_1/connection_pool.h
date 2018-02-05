//
// Created by jiang on 16-11-30.
//

#ifndef PROJECT_CONNECTION_POOL_H
#define PROJECT_CONNECTION_POOL_H

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <pthread.h>
#include <list>

using namespace std;

class ConnPool {
private:
    int curSize; //当前已建立的数据库连接数量
    int maxSize; //连接池中定义的最大数据库连接数
    string username;
    string password;
    string url;
    string database;
    list<sql::Connection*> connList; //连接池的容器队列
    pthread_mutex_t lock; //线程锁
    static ConnPool *connPool;
    sql::Driver*driver;

    sql::Connection* CreateConnection(); //创建一个连接
    void InitConnection(int iInitialSize); //初始化数据库连接池
    void DestoryConnection(sql::Connection *conn); //销毁数据库连接对象
    void DestoryConnPool(); //销毁数据库连接池
    ConnPool(string url, string user, string password, string database, int maxSize); //构造方法
public:
    ~ConnPool();
    sql::Connection* GetConnection(); //获得数据库连接
    void ReleaseConnection(sql::Connection *conn); //将数据库连接放回到连接池的容器中
    static ConnPool *GetInstance(string url, string user, string password, string database); //获取数据库连接池对象
};

ConnPool *ConnPool::connPool = NULL;

//连接池的构造函数
ConnPool::ConnPool(string url, string userName, string password, string database, int maxSize) {
    this->maxSize = maxSize;
    this->curSize = 0;
    this->username = userName;
    this->password = password;
    this->url = url;
    this->database = database;
    try {
        this->driver = sql::mysql::get_driver_instance();
    } catch (sql::SQLException&e) {
        LOG(INFO)<<"驱动连接出错\n";
    } catch (std::runtime_error&e) {
        LOG(INFO)<<"运行出错了\n";
    }
    pthread_mutex_init(&lock,NULL);
    this->InitConnection(2);
}

//获取连接池对象，单例模式
ConnPool*ConnPool::GetInstance(string url, string user, string password, string database) {
    if (connPool == NULL) {
        connPool = new ConnPool(url, user, password, database, 50);
    }
    return connPool;
}

//初始化连接池，创建最大连接数的一半连接数量
void ConnPool::InitConnection(int iInitialSize) {
    sql::Connection* conn;
    pthread_mutex_lock(&lock);
    for (int i = 0; i < iInitialSize; i++) {
        conn = this->CreateConnection();
        if (conn) {
            connList.push_back(conn);
            ++(this->curSize);
        } else {
            LOG(INFO)<<"创建CONNECTION出错\n";
        }
    }
    pthread_mutex_unlock(&lock);
}

//创建连接,返回一个Connection
sql::Connection* ConnPool::CreateConnection() {
    sql::Connection *conn;
    sql::ConnectOptionsMap connection_properties;
    connection_properties["hostName"] = this->url;
    connection_properties["userName"] = this->username;
    connection_properties["password"] = this->password;
    connection_properties["schema"] = this->database;
    connection_properties["OPT_CONNECT_TIMEOUT"] = 10; // set timeout 10 seconds
    connection_properties["OPT_READ_TIMEOUT"] = 10; // set timeout 10 seconds
    connection_properties["OPT_WRITE_TIMEOUT"] = 10; // set timeout 10 seconds
    connection_properties["OPT_RECONNECT"] = true;
    try {
//        conn = driver->connect(this->url, this->username, this->password); //建立连接
//        conn->setSchema(this->database);
        conn = driver->connect(connection_properties); //重连，可能会卡死
        return conn;
    } catch (sql::SQLException &e) {
        LOG(INFO)<<"创建连接出错\n";
        return NULL;
    } catch (std::runtime_error &e) {
        LOG(INFO)<<"运行时出错\n";
        return NULL;
    }
}

//在连接池中获得一个连接
sql::Connection* ConnPool::GetConnection() {
    sql::Connection* con;
    pthread_mutex_lock(&lock);

    if (connList.size() > 0) {   //连接池容器中还有连接
        con = connList.front(); //得到第一个连接
        connList.pop_front();   //移除第一个连接
        if (con->isClosed()) {   //如果连接已经被关闭，删除后重新建立一个
            delete con;
            con = this->CreateConnection();
        }
        //如果连接为空，则创建连接出错
        if (con == NULL) {
            --curSize;
        }
        pthread_mutex_unlock(&lock);
        return con;
    } else {
        if (curSize < maxSize) { //还可以创建新的连接
            con = this->CreateConnection();
            if (con) {
                ++curSize;
                pthread_mutex_unlock(&lock);
                return con;
            } else {
                pthread_mutex_unlock(&lock);
                return NULL;
            }
        } else { //建立的连接数已经达到maxSize
            pthread_mutex_unlock(&lock);
            return NULL;
        }
    }
}

//回收数据库连接
void ConnPool::ReleaseConnection(sql::Connection * conn) {
    if (conn) {
        pthread_mutex_lock(&lock);
        connList.push_back(conn);
        pthread_mutex_unlock(&lock);
    }
}

//连接池的析构函数
ConnPool::~ConnPool() {
    this->DestoryConnPool();
}

//销毁连接池,首先要先销毁连接池的中连接
void ConnPool::DestoryConnPool() {
    list<sql::Connection*>::iterator icon;
    pthread_mutex_lock(&lock);
    for (icon = connList.begin(); icon != connList.end(); ++icon) {
        this->DestoryConnection(*icon); //销毁连接池中的连接
    }
    curSize = 0;
    connList.clear(); //清空连接池中的连接
    pthread_mutex_unlock(&lock);
}

//销毁一个连接
void ConnPool::DestoryConnection(sql::Connection* conn) {
    if (conn) {
        try {
            conn->close();
        } catch (sql::SQLException&e) {
            perror(e.what());
        } catch (std::exception&e) {
            perror(e.what());
        }
        delete conn;
    }
}

#endif //PROJECT_CONNECTION_POOL_H
