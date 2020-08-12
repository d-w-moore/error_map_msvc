// =-=-=-=-=-=-=-
// irods includes

#define MAKE_IRODS_ERROR_MAP 1
//#include "rodsErrorTable.h"
#include "irods_error.hpp"
#include "irods_ms_plugin.hpp"

#include "icatHighLevelRoutines.hpp"
#include "rcMisc.h"

#include "irods_re_structs.hpp"

// =-=-=-=-=-=-=-
// stl includes

#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <limits>
#include <cstring>
#include <sys/time.h>
#include <regex.h>

#include "boost/format.hpp"


int msierror_map(
    msParam_t*      first,
    msParam_t*      second,
    ruleExecInfo_t* rei 
    )
{
    const auto & name_map = irods_error_map_construction::irods_error_name_map;
    const auto & error_map = irods_error_map_construction::irods_error_map;

    int x = std::numeric_limits<int>::min();

    const char *s, *t;
    if ( ( s = parseMspForStr(first ) ) == NULL) {
        rodsLog( LOG_ERROR,"null first param '%s'",first);
        return USER__NULL_INPUT_ERR;
    }
    if ( ( t = parseMspForStr(second ) ) == NULL) {
        rodsLog( LOG_ERROR,"null second param '%s'",second);
        return USER__NULL_INPUT_ERR;
    }
    if (std::strlen(s)) {  //--> nonzero length first param, store str(errnum(first)) into second
        try {
            x = name_map.at(s) ;
        }
        catch(...)
        {
            //
        }
        auto s = std::to_string( x );
        fillStrInMsParam( second, s.c_str());
    }
    else {
        std::string first_list, second_list ;
        const char *z=nullptr, sep[] = "\n";
        for (auto i = error_map.rbegin();  i != error_map.rend(); i++) {
           auto f1 = i->first;
           auto f1s = std::to_string(f1);
           auto f2 = i->second.c_str();
           if (0==std::strlen(t) || 0==std::strcmp(f1s.c_str(),t)) {
             if (z) { first_list += z; second_list += z; }
             z = sep;
             first_list += f2;
             second_list += f1s;
           }
        }
        fillStrInMsParam(first, first_list.c_str());
        fillStrInMsParam(second, second_list.c_str());
    }

    rei->status = 0;
    return 0;
}

extern "C"
irods::ms_table_entry* plugin_factory() {
    irods::ms_table_entry* msvc = new irods::ms_table_entry(2);
    msvc->add_operation<
        msParam_t*,
        msParam_t*,
        ruleExecInfo_t*>("msierror_map",
                         std::function<int(
                             msParam_t*,
                             msParam_t*,
                             ruleExecInfo_t*)>(msierror_map));
    return msvc;
}

