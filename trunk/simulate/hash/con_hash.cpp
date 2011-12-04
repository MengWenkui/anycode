#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <set>
#include <string>
#include <list>

typedef std::map<unsigned int, std::string> USMAP;
typedef std::set<std::string> SSET;
typedef std::map<unsigned int, SSET> USSMAP;
typedef std::list<std::string> SLIST;
typedef std::map<std::string, unsigned int> SUMAP;

typedef unsigned int (*HASHFUNC)(const char *str);

class DhtServer {
private:
    USMAP _node_info;            // nodeid to server
    USSMAP _node_slot;           // nodeid to keys   
    HASHFUNC _hash;              // hash function
    int _vnode_num;              // vnode number per server  
public:
    DhtServer(const std::string *servers, int len, HASHFUNC hash, int vnode_num);
    ~DhtServer();
    void put_key(const std::string &key);
    void del_key(const std::string &key);
    std::string get_server(const std::string &key);
    void add_server(const std::string &server);
    void del_server(const std::string &server);
    void print_node_info();
    void print_node_slot();
    void print_node_count();
private:
    void _add_node(const std::string server, int vnode_num);
};


/**
 * @brief add a static node
 *
 * @param server: server ip
 * @param vnode_num: vnode number for this server
 */
void DhtServer::_add_node(const std::string server, int vnode_num)
{
    for(int i = 0; i < vnode_num; i++) {
        char buf[256];
        sprintf(buf, "%s-%010d", server.c_str(), i);
        unsigned int hval = _hash(buf);
        _node_info[hval] = server; 
    }
}


/**
 * @brief construct a DhtServer
 *
 * @param servers: initial server list
 * @param len: server list length
 * @param hash: hash function
 * @param vnode_num: virtual node number for a server
 */
DhtServer::DhtServer(const std::string *servers, int len, HASHFUNC hash, int vnode_num)
{
    _hash = hash;
    _vnode_num = vnode_num;

    for(int i = 0; i < len; i++) {
        _add_node(servers[i], vnode_num);    
    }
}


/**
 * @brief destructor
 */
DhtServer::~DhtServer()
{

}

/**
 * @brief put a key into server
 *
 * @param key: key name
 */
void DhtServer::put_key(const std::string &key)
{
    unsigned int hval = _hash(key.c_str());
    USMAP::iterator iter = _node_info.upper_bound(hval);
    if(iter == _node_info.end() && 0 != _node_info.size()) {
        iter = _node_info.begin();
    }
    
    _node_slot[iter->first].insert(key);
}


/**
 * @brief delete a key from server
 *
 * @param key: key name
 */
void DhtServer::del_key(const std::string &key)
{
    unsigned int hval = _hash(key.c_str());
    USMAP::iterator iter = _node_info.upper_bound(hval);
    if(iter == _node_info.end() && 0 != _node_info.size()) {
        iter = _node_info.begin();
    }

    _node_slot[iter->first].erase(key);
}


/**
 * @brief get server from key
 *
 * @param key: key name
 */
std::string DhtServer::get_server(const std::string &key)
{
    unsigned int hval = _hash(key.c_str());
    USMAP::iterator iter = _node_info.upper_bound(hval);
    if(iter == _node_info.end() && 0 != _node_info.size()) {
        iter = _node_info.begin();
    }
    
    return iter->second;
}

/**
 * @brief add a server to DHT dynamicly
 *
 * @param server
 */
void DhtServer::add_server(const std::string &server)
{
    for(int i = 0; i < _vnode_num; i++) {
        char buf[256];
        sprintf(buf, "%s-%010d", server.c_str(), i);
        unsigned int hval = _hash(buf);

        USSMAP::iterator larger = _node_slot.lower_bound(hval);
        if(larger == _node_slot.end()) {
            larger = _node_slot.begin();
        }
        unsigned int first = _node_slot.begin()->first;

        // already in new server
        if(_node_info[larger->first] == server) {
            continue;
        }

        // transfer recored
        SSET &tset = larger->second;
        SSET::iterator iter = tset.begin();
        for( ; iter != tset.end(); ) {
            int nval = _hash(iter->c_str());
            if(!(nval >= hval || nval < first)) {
                printf("transfer record [%s] from [%s]\n", 
                        iter->c_str(), get_server(iter->c_str()).c_str());
                _node_slot[hval].insert(*iter);
                tset.erase(iter++);
            } else {
                iter++;
            }
        }

        // add server to node_info
        _node_info[hval] = server; 
    }
}

/**
 * @brief delete a server to DHT dynamicly
 *
 * @param server
 */
void DhtServer::del_server(const std::string &server)
{
     for(int i = 0; i < _vnode_num; i++) {
        char buf[256];
        sprintf(buf, "%s-%010d", server.c_str(), i);
        unsigned int hval = _hash(buf);

        USSMAP::iterator larger = _node_slot.upper_bound(hval);
        if(larger == _node_slot.end()) {
            larger = _node_slot.begin();
        }
        
        // transfer record
        SSET::iterator iter = _node_slot[hval].begin();
        SSET::iterator end = _node_slot[hval].end();
        for( ; iter != end; iter++) {
            printf("transfer record [%s] to [%s]\n",
                    iter->c_str(), _node_info[larger->first].c_str());
        }
        larger->second.insert(_node_slot[hval].begin(), _node_slot[hval].end());

        // erase server from node_info
        _node_info.erase(hval);
        _node_slot.erase(hval);
    }
}


/**
 * @brief print vnode to node mapping
 */
void DhtServer::print_node_info()
{
    USMAP::iterator iter = _node_info.begin();
    for( ; iter != _node_info.end(); iter++) {
        printf("[%u-->%s]\n", iter->first, iter->second.c_str());
    }
}


/**
 * @brief print virtual nodes info
 */
void DhtServer::print_node_slot()
{
    USSMAP::iterator iter = _node_slot.begin();
    for( ; iter != _node_slot.end(); iter++) {
        SSET &sset = iter->second;
        
        SSET::iterator iter2 = sset.begin();
        printf("{\n");
        for( ; iter2 != sset.end(); iter2++) {
            printf("[%s %u %u %s]\n", iter2->c_str(), _hash(iter2->c_str()), 
                    iter->first, _node_info[iter->first].c_str());
        }
        printf("}\n");
    }
}

/**
 * @brief print keys in every server
 */
void DhtServer::print_node_count()
{
    SUMAP node_count;
    USSMAP::iterator iter = _node_slot.begin();
    for( ; iter != _node_slot.end(); iter++) {
        std::string &server = _node_info[iter->first];
        if(node_count.end() == node_count.find(server)) {
            node_count[server] = 0;
        }
        node_count[server] += iter->second.size();
    }

    SUMAP::iterator su_iter = node_count.begin();
    for( ; su_iter != node_count.end(); su_iter++) {
        printf("[%s: %u]\n", su_iter->first.c_str(), su_iter->second);
    }

}

unsigned int SDBMHash(const char *str);
unsigned int RSHash(const char *str);
unsigned int JSHash(const char *str);
unsigned int PJWHash(const char *str);
unsigned int ELFHash(const char *str);
unsigned int BKDRHash(const char *str);
unsigned int DJBHash(const char *str);
unsigned int APHash(const char *str);

int main(int argc, char *argv[])
{
    if(3 != argc) {
        printf("./con_hash vnode_num key_num\n");
        return -1;
    }
    
    std::string server_list[] = {"192.168.0.1", "192.168.0.2", "192.168.0.3"};
    int server_num = 3;
    int vnode_num = atoi(argv[1]);
    int key_num = atoi(argv[2]);

    DhtServer ds(server_list, server_num, RSHash, vnode_num);
    
    char buf[64];
    srand((unsigned)time(NULL));
    for(int i = 0; i < key_num; i++) {
        int r1 = rand();
        int r2 = rand();
        sprintf(buf, "%d-%d-%d", r1, i, r2);
        ds.put_key(buf);
    }

    ds.print_node_count();
    ds.add_server("192.168.0.4");

   // ds.print_node_info();
   // ds.print_node_slot();
   ds.print_node_count();

   ds.del_server("192.168.0.4");

   ds.print_node_count();

    return 0;
}


