/*
  PURPOSE:                     (Monte carlo structures)
  REFERENCE:                   (Trick Users Guide)
  ASSUMPTIONS AND LIMITATIONS: (None)
  PROGRAMMERS:                 ((Keith Vetter) (LinCom) (7/2003))
*/

/*
 * $Id: MonteVar.hh $
 */

#ifndef _MONTEVAR_HH_
#define _MONTEVAR_HH_

#include <string>

namespace Trick {

    /**
     * Abstract base class for Monte Carlo variables.
     *
     * @author Alex Lin
     * @author Donna Panter
     * @author Derek Bankieris
     *
     * @date August 2010
     */
    class MonteVar {

        public:
        /** Name. */
        std::string name;  /**< \n trick_units(--) */

        /** Units. */
        std::string unit;  /**< \n trick_units(--) */

        /** Value. */
        std::string value; /**< \n trick_units(--) */

        /** Destructor. */
        virtual ~MonteVar() {};

        /** Class MonteCarlo is a friend so it can use the get_next_value method.
         *  The get_next_value method needs to be protected so users cannot use it in the input file
         */
        friend class MonteCarlo ;

        protected:
        /**
         * Gets this variable's next value.
         *
         * @return the next value
         */
        virtual std::string get_next_value() = 0;

    };

};
#endif
