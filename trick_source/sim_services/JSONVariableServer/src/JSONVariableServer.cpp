
#include <iostream>
#include <pwd.h>
#include <sstream>

#include "sim_services/JSONVariableServer/include/JSONVariableServer.hh"
#include "sim_services/JSONVariableServer/include/JSONVariableServerThread.hh"
#include "trick_utils/comm/include/tc_proto.h"
#include "sim_services/Message/include/message_proto.h"

Trick::JSONVariableServer::JSONVariableServer() :
 Trick::ThreadBase("JSONVarServLis"),
 enabled(true),
 port(0),
 user_port_requested(false),
 listen_dev()
{
    char hname[80];
    gethostname(hname , (size_t) 80 ) ;
    source_address = std::string(hname) ;
    strcpy(listen_dev.client_tag, "<empty>");
    tc_error(&listen_dev, 0);
}

Trick::JSONVariableServer::~JSONVariableServer() {
    if ( listen_dev.hostname != NULL ) {
        free(listen_dev.hostname) ;
    }
    if ( listen_dev.error_handler != NULL ) {
        free(listen_dev.error_handler) ;
    }
}

const char * Trick::JSONVariableServer::get_hostname() {
    return listen_dev.hostname;
}

unsigned short Trick::JSONVariableServer::get_port() {
    return port;
}

void Trick::JSONVariableServer::set_port(unsigned short in_port) {
    port = in_port;
    user_port_requested = true ;
}

void Trick::JSONVariableServer::set_source_address(const char * address) {
    if ( address == NULL ) {
        source_address = std::string("") ;
    } else {
        source_address = std::string(address) ;
    }
    user_port_requested = true ;
}

std::string Trick::JSONVariableServer::get_source_address() {
    return source_address ;
}

/*
@details
-# call tc_init to initialize the listen device
 -# save the port number if tc_init was successful
*/
int Trick::JSONVariableServer::init_listen_device() {
    int ret;

    ret = tc_init(&listen_dev);
    if (ret == TC_SUCCESS) {
        port = listen_dev.port ;
    } else {
        fprintf(stderr, "ERROR: Could not establish listen port for Variable Server. Aborting.\n");
        ret = -1 ;
    }
    return ret ;
}

/*
@details
-# if enabled
 -# move listen device to user specified address and port.
 -# create listening thread
*/
int Trick::JSONVariableServer::init() {
    int ret = 0 ;
    if ( enabled ) {
        ret = check_and_move_listen_device() ;
        if ( ret == 0 ) {
            create_thread() ;
        }
    } else {
        tc_disconnect(&listen_dev) ;
    }
    return ret ;
}

/*
@details
-# If the source address or port number does not match the current listen device
 -# disconnect current listen device
 -# initialize listen device with new source address and port
*/
int Trick::JSONVariableServer::check_and_move_listen_device() {
    int ret ;

    if ( source_address.compare(listen_dev.hostname) or port != listen_dev.port ) {
        /* The user has requested a different source address or port in the input file */
        tc_disconnect(&listen_dev) ;
        ret = tc_init_with_connection_info(&listen_dev, AF_INET, SOCK_STREAM, source_address.c_str(), port) ;
        if (ret != TC_SUCCESS) {
            message_publish(MSG_ERROR, "ERROR: Could not establish variable server source_address %s: port %d. Aborting.\n",
             source_address.c_str(), port);
            return -1 ;
        }
    }
    return 0 ;
}

/*
@details
-# Loop forever for new connections
 -# create a new VariableServerThread when new conection found
 -# create new VariableServerThread thread
*/
void * Trick::JSONVariableServer::thread_body() {

    fd_set rfds;
    struct timeval timeout_time = { 2, 0 };

    while (1) {
        FD_ZERO(&rfds);
        FD_SET(listen_dev.socket, &rfds);
        timeout_time.tv_sec = 2 ;
        select(listen_dev.socket + 1, &rfds, NULL, NULL, &timeout_time);

        if (FD_ISSET(listen_dev.socket, &rfds)) {
            Trick::JSONVariableServerThread * vst = new Trick::JSONVariableServerThread(&listen_dev) ;
            vst->copy_cpus(get_cpus()) ;
            vst->create_thread() ;
        }
    }

    return NULL ;
}

/*
@details
-# If the user specified an address and port
 -# disconnect the current listen port
 -# initialize listen port to new address and port
-# else print message of current port number of listen device
*/
int Trick::JSONVariableServer::restart() {

    int ret ;

    if ( user_port_requested ) {
        printf("user_port_requested set %d", port) ;
        tc_disconnect(&listen_dev) ;
        ret = tc_init_with_connection_info(&listen_dev, AF_INET, SOCK_STREAM, source_address.c_str(), port) ;
        if (ret != TC_SUCCESS) {
            message_publish(MSG_ERROR, "ERROR: Could not establish listen port %d for Variable Server. Aborting.\n", port);
            return (-1);
        }
    } else {
        struct sockaddr_in s_in;
        int s_in_size =  sizeof(s_in) ;
        getsockname( listen_dev.socket , (struct sockaddr *)&s_in, (socklen_t *)&s_in_size) ;
        printf("restart JSON variable server message port = %d\n" , ntohs(s_in.sin_port)) ;
        port = listen_dev.port = ntohs(s_in.sin_port);
    }

    return 0 ;
}

void Trick::JSONVariableServer::dump( std::ostream & oss ) {
    oss << "Trick::JSONVariableServer (" << name << ")" << std::endl ;
    oss << "    enabled = " << enabled << std::endl ;
    oss << "    source_address = " << source_address << std::endl ;
    oss << "    port = " << port << std::endl ;
    oss << "    user_port_requested = " << user_port_requested << std::endl ;
    Trick::ThreadBase::dump(oss) ;
}

