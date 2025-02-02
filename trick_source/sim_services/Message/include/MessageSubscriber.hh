/* 
 * $Id: MessageSubscriber.hh 3553 2014-06-11 19:26:39Z alin $
 */


/**
 * @file MessageSubscriber.hh
 */

#ifndef _MESSAGESUBSCRIBER_HH_
#define _MESSAGESUBSCRIBER_HH_

#include <streambuf>
#include <iostream>
#include <string>

namespace Trick {

	/**
	 * This class defines a message subscriber that can subscribe to a MessagePublisher.
	 */
    class MessageSubscriber {

        public:
            MessageSubscriber() ;

            /** Toggle to enable/disable this message subscriber.\n */
            bool enabled ;       /**< trick_units(--) */

            /** Toggle to enable/disable adding color to message.\n */
            bool color ;         /**< trick_units(--) */

            /** Name of the subscriber\n */
            std::string name ;         /**< trick_units(--) */

            /**
             @brief Enable (default) or disable this message subscriber, so that it outputs the messages it receives.
             @param yes_no - true to enable, false to disable
             @return always 0
             */
            int set_enabled(bool yes_no) ;

            /**
             @brief Enable/disable adding color to messages.
             @param yes_no - true to enable, false to disable
             @return always 0
             */
            int set_color(bool yes_no) ;

            /**
             @brief The destructor.
             */
            virtual ~MessageSubscriber() {} ;

            /**
             @brief Get a message and send to output. This gets called every time when the message publisher
             that this subscriber subscribes to publishes a message. Actual output done in the derived class.
             @param level - received message level
             @param header - received message header
             @param message - received message text
             */
            virtual void update( unsigned int level , std::string header, std::string message ) = 0 ;

    } ;

}

#endif

