/*
 * $Id: montecarlo_c_intf.c $
 */

#include "sim_services/MonteCarlo/include/MonteCarlo.hh"
#include "sim_services/CommandLineArguments/include/CommandLineArguments.hh"
#include "trick_utils/comm/include/tc_proto.h"

extern Trick::MonteCarlo *the_mc;
extern Trick::CommandLineArguments *the_cmd_args;

extern "C" void mc_set_enabled(int enabled) {
    if ( the_mc != NULL ) {
        the_mc->set_enabled(enabled);
    }
}

extern "C" int mc_get_enabled() {
    if ( the_mc != NULL ) {
        return the_mc->get_enabled();
    }
    return 0 ;
}

extern "C" void mc_set_dry_run(int dry_run) {
    if ( the_mc != NULL ) {
        the_mc->set_dry_run(dry_run);
    }
}

extern "C" int mc_get_dry_run() {
    if ( the_mc != NULL ) {
        return the_mc->get_dry_run();
    }
    return 0 ;
}

extern "C" int mc_is_slave() {
    if ( the_mc != NULL ) {
        return the_mc->is_slave();
    }
    return 0 ;
}

extern "C" void mc_set_localhost_as_remote(int localhost_as_remote) {
    if ( the_mc != NULL ) {
        the_mc->set_localhost_as_remote(localhost_as_remote);
    }
}

extern "C" int mc_get_localhost_as_remote() {
    if ( the_mc != NULL ) {
        return the_mc->get_localhost_as_remote();
    }
    return 0 ;
}

extern "C" void mc_set_custom_slave_dispatch(int custom_slave_dispatch) {
    if ( the_mc != NULL ) {
        the_mc->set_custom_slave_dispatch(custom_slave_dispatch);
    }
}

extern "C" int mc_get_custom_slave_dispatch() {
    if ( the_mc != NULL ) {
        return the_mc->get_custom_slave_dispatch();
    }
    return 0 ;
}

extern "C" void mc_set_timeout(double timeout) {
    if ( the_mc != NULL ) {
        the_mc->set_timeout(timeout);
    }
}

extern "C" double mc_get_timeout() {
    if ( the_mc != NULL ) {
        return the_mc->get_timeout();
    }
    return 0.0 ;
}

extern "C" void mc_set_max_tries(unsigned int max_tries) {
    if ( the_mc != NULL ) {
        the_mc->set_max_tries(max_tries);
    }
}

extern "C" unsigned int mc_get_max_tries() {
    if ( the_mc != NULL ) {
        return the_mc->get_max_tries();
    }
    return 0 ;
}

extern "C" void mc_set_user_cmd_string(const char *user_cmd_string) {
    if ( the_mc != NULL ) {
        the_mc->set_user_cmd_string(std::string(user_cmd_string ? user_cmd_string : ""));
    }
}

extern "C" const char *mc_get_user_cmd_string() {
    if ( the_mc != NULL ) {
        return the_mc->get_user_cmd_string().c_str();
    }
    return NULL ;
}

extern "C" void mc_set_custom_pre_text(const char *custom_pre_text) {
    if ( the_mc != NULL ) {
        the_mc->set_custom_pre_text(std::string(custom_pre_text ? custom_pre_text : ""));
    }
}

extern "C" const char *mc_get_custom_pre_text() {
    if ( the_mc != NULL ) {
        return the_mc->get_custom_pre_text().c_str();
    }
    return NULL ;
}

extern "C" void mc_set_custom_post_text(const char *custom_post_text) {
    if ( the_mc != NULL ) {
        the_mc->set_custom_post_text(std::string(custom_post_text ? custom_post_text : ""));
    }
}

extern "C" const char *mc_get_custom_post_text() {
    if ( the_mc != NULL ) {
        return the_mc->get_custom_post_text().c_str();
    }
    return NULL ;
}

extern "C" void mc_set_verbosity(int verbosity) {
    if ( the_mc != NULL ) {
        the_mc->set_verbosity((Trick::MonteCarlo::Verbosity)verbosity);
    }
}

extern "C" int mc_get_verbosity() {
    if ( the_mc != NULL ) {
        return the_mc->get_verbosity();
    }
    return 0 ;
}

extern "C" void mc_set_num_runs(unsigned int num_runs) {
    if ( the_mc != NULL ) {
        the_mc->set_num_runs(num_runs);
    }
}

extern "C" unsigned int mc_get_num_runs() {
    if ( the_mc != NULL ) {
        return the_mc->get_num_runs();
    }
    return 0 ;
}

extern "C" unsigned int mc_get_num_results() {
    if ( the_mc != NULL ) {
        return the_mc->get_num_results();
    }
    return 0 ;
}

extern "C" unsigned int mc_get_slave_id() {
    if ( the_mc != NULL ) {
        return the_mc->get_slave_id();
    }
    return 0 ;
}

extern "C" void mc_add_range(unsigned int start, unsigned int end) {
    if ( the_mc != NULL ) {
        the_mc->add_range(start, end);
    }
}

extern "C" void mc_add_slave(const char *machine_name) {
    if ( the_mc != NULL ) {
        the_mc->add_slave(std::string(machine_name ? machine_name : ""));
    }
}

extern "C" void mc_start_slave(unsigned int id) {
    if ( the_mc != NULL ) {
        the_mc->start_slave(id);
    }
}

extern "C" void mc_stop_slave(unsigned int id) {
    if ( the_mc != NULL ) {
        the_mc->stop_slave(id);
    }
}

extern "C" void mc_write(char *buffer, int size) {
    if ( the_mc != NULL ) {
        TCDevice *data_conn = the_mc->get_data_connection_device();
        tc_write(data_conn, buffer, size) ;
    }
}

extern "C" void mc_read(char *buffer, int size) {
    if ( the_mc != NULL ) {
        TCDevice *data_conn = the_mc->get_data_connection_device();
        tc_read(data_conn, buffer, size) ;
    }
}

extern "C" TCDevice* mc_get_connection_device() {
    if ( the_mc != NULL ) {
        return (the_mc->get_data_connection_device());
    }
    return NULL ;
}

extern "C" unsigned int mc_get_current_run() {
    if ( the_mc != NULL ) {
        return the_mc->get_current_run();
    }
    return 0 ;
}

extern "C" void mc_set_current_run(int run_num) {
    if ( the_mc != NULL ) {
        the_mc->set_current_run(run_num);
    }
}

extern "C" void mc_set_listen_device_port(int port_number) {
    if ( the_mc != NULL ) {
        the_mc->set_listen_device_port(port_number);
    }
}

extern "C" void mc_set_data_listen_device_port(int port_number) {
    if ( the_mc != NULL ) {
        the_mc->set_data_listen_device_port(port_number);
    }
}

extern "C" void mc_set_connection_device_port(int port_number) {
    if ( the_mc != NULL ) {
        the_mc->set_connection_device_port(port_number);
    }
}

extern "C" void mc_set_data_connection_device_port(int port_number) {
    if ( the_mc != NULL ) {
        the_mc->set_data_connection_device_port(port_number);
    }
}

extern "C" int mc_get_listen_device_port() {
    if ( the_mc != NULL ) {
        return the_mc->get_listen_device_port();
    }
    return -1 ;
}

extern "C" int mc_get_data_listen_device_port() {
    if ( the_mc != NULL ) {
        return the_mc->get_data_listen_device_port();
    }
    return -1 ;
}

extern "C" int mc_get_connection_device_port() {
    if ( the_mc != NULL ) {
        return the_mc->get_connection_device_port();
    }
    return -1 ;
}

extern "C" int mc_get_data_connection_device_port() {
    if ( the_mc != NULL ) {
        return the_mc->get_data_connection_device_port();
    }
    return -1 ;
}

