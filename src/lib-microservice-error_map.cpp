// =-=-=-=-=-=-=-
// irods includes

#define MAKE_IRODS_ERROR_MAP
#include "rodsErrorTable.h"
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
    msParam_t*      errorSymbol,
    msParam_t*      errorNumber,
    ruleExecInfo_t* rei 
    )
{
    const auto & name_map = irods_error_map_construction::irods_error_name_map;
    const auto & error_map = irods_error_map_construction::irods_error_map;

    int x = std::numeric_limits<int>::min();

    const char *s, *t;
    if ( ( s = parseMspForStr(errorSymbol ) ) == NULL) {
        rodsLog( LOG_ERROR,"null errorSymbol param '%s'",errorSymbol);
        return USER__NULL_INPUT_ERR;
    }
    if ( ( t = parseMspForStr(errorNumber ) ) == NULL) {
        rodsLog( LOG_ERROR,"null errorNumber param '%s'",errorNumber);
        return USER__NULL_INPUT_ERR;
    }
    if (std::strlen(s)) {  //--> nonzero length errorSymbol param, store str(errnum(errorSymbol)) into errorNumber
        try {
            x = name_map.at(s) ;
        }
        catch(...)
        {
            //
        }
        auto s = std::to_string( x );
        fillStrInMsParam( errorNumber, s.c_str());
    }
    else {
        std::string errorSymbol_list, errorNumber_list ;
        const char *z=nullptr, sep[] = "\n";
        for (auto i = error_map.rbegin();  i != error_map.rend(); i++) {
           auto f1 = i->first;
           auto f1s = std::to_string(f1);
           auto f2 = i->second.c_str();
           if (0==std::strlen(t) || 0==std::strcmp(f1s.c_str(),t)) {
             if (z) { errorSymbol_list += z; errorNumber_list += z; }
             z = sep;
             errorSymbol_list += f2;
             errorNumber_list += f1s;
           }
        }
        fillStrInMsParam(errorSymbol, errorSymbol_list.c_str());
        fillStrInMsParam(errorNumber, errorNumber_list.c_str());
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

