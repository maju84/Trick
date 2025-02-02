
/* 
 * $Id: Threads.cpp 3577 2014-06-25 20:04:57Z alin $
 */

#include <iostream>
#include <sstream>
#include <stdio.h>

#include "sim_services/Executive/include/Threads.hh"
#include "sim_services/Message/include/message_proto.h"

Trick::Threads::Threads(int in_id , bool in_rt_nap) :
 enabled(true) ,
 thread_id(in_id) ,
 curr_time_tics(0) ,
 amf_cycle(0.0) ,
 amf_cycle_tics(0) ,
 amf_next_tics(0) ,
 curr_job(NULL) ,
 rt_nap(in_rt_nap) ,
 process_type(PROCESS_TYPE_SCHEDULED) ,
 child_complete(false) ,
 frame_trigger(0) ,
 running(false) ,
 rt_semaphores(true) ,
 shutdown_wait_async(false) {
    pthread_cond_init(&go_cv, NULL);
    pthread_mutex_init(&go_mutex, NULL);

    std::stringstream oss ;
    oss << "Child_" << in_id ;
    name = oss.str() ;
}

void Trick::Threads::set_pthread_id(pthread_t in_pthread_id) {
    pthread_id = in_pthread_id ;
}

void Trick::Threads::set_enabled( bool in_enabled ) {
    enabled = in_enabled ;
}

void Trick::Threads::clear_scheduled_queues() {
    job_queue.clear() ;
    top_of_frame_queue.clear() ;
    end_of_frame_queue.clear() ;
}

void Trick::Threads::dump( std::ostream & oss ) {
    oss << "Trick::Threads (" << name << ")" << std::endl ;
    oss << "    process_type = " ;
    switch ( process_type ) {
        case PROCESS_TYPE_SCHEDULED: oss << "scheduled" << std::endl ; break ;
        case PROCESS_TYPE_ASYNC_CHILD: oss << "asynchronous" << std::endl ; break ;
        case PROCESS_TYPE_AMF_CHILD: oss << "asynchronous must finish with amf_cycle = " << amf_cycle << std::endl ; break ;
    }
    oss << "    number of scheduled jobs = " << job_queue.size() << std::endl ;
    Trick::ThreadBase::dump(oss) ;
}
