/*
 * $Id: MonteCarlo_master_file_io.cpp $
 */

#include <sys/stat.h>
#include <libgen.h>

#include "sim_services/MonteCarlo/include/MonteCarlo.hh"
#include "sim_services/Message/include/message_proto.h"
#include "sim_services/CommandLineArguments/include/command_line_protos.h"

/** @par Detailed Design: */
int Trick::MonteCarlo::construct_run_directory() {
    /** <ul><li> Construct the run directory. */
    run_directory = command_line_args_get_user_output_dir();
    if (run_directory.empty()) {
    	std::string run_base_directory = command_line_args_get_output_dir();
    	if (run_base_directory.empty()) {
    		if (verbosity >= ERROR) {
    			message_publish(MSG_ERROR, "Monte [Master] Could not get the output directory.\n") ;
    	    }
    	    return -1;
    	}
    	std::size_t path_separator_pos = run_base_directory.find_last_of("/");
    	if (path_separator_pos != std::string::npos) {
    		// "/" is included
    		run_base_directory = run_base_directory.substr(0, path_separator_pos + 1);
    	} else {
    		run_base_directory = "";
    	}

        run_directory = basename((char *)command_line_args_get_output_dir());
        if (run_directory.empty()) {
            if (verbosity >= ERROR) {
                message_publish(MSG_ERROR, "Monte [Master] Could not get the run directory name.\n") ;
            }
            return -1;
        }
        run_directory = run_base_directory + "MONTE_" + run_directory;
    }

    if  (access(run_directory.c_str(), F_OK) != 0) {
        if (mkdir(run_directory.c_str(), 0775) != 0) {
            message_publish(MSG_ERROR, "Monte Error while trying to create directory %s.\n", run_directory.c_str()) ;
            return -1;
        }
    }
    return 0 ;
}

int Trick::MonteCarlo::open_file(std::string file_name, FILE** file_ptr) {

    if ((*file_ptr = fopen(file_name.c_str(), "w")) == NULL) {
        if (verbosity >= ERROR) {
            message_publish(MSG_ERROR, "Monte [Master] Could not open %s for writing.\n", file_name.c_str()) ;
        }
        return -1;
    }
    return 0;
}

void Trick::MonteCarlo::write_to_run_files(std::string file_name) {

    /** <li> Write the number of runs. */
    fprintf(run_header_file, "trick.mc_set_num_runs(%d)\n", num_runs);

    /** <li> Write the variables. */
    fprintf(run_data_file, "#run_num ");
    for (std::vector<std::string>::size_type i = 0; i < variables.size(); ++i) {
        if (variables[i]->unit.empty()) {
            fprintf(run_header_file, "\nvar%zu = trick.MonteVarFile(\"%s\", \"%s\", %zu)\n",
              i, variables[i]->name.c_str(), file_name.c_str(), i + 2);
        }
        else {
            fprintf(run_header_file, "\nvar%zu = trick.MonteVarFile(\"%s\", \"%s\", %zu, \"%s\")\n",
              i, variables[i]->name.c_str(), file_name.c_str(), i + 2, variables[i]->unit.c_str());
        }
        fprintf(run_header_file, "trick_sys.sched.add_variable(var%zu)\n", i);
        fprintf(run_data_file, "%s  ", variables[i]->name.c_str());
    }

    fprintf(run_data_file, "\n");
}
