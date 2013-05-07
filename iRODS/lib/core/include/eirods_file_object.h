/* -*- mode: c++; fill-column: 132; c-basic-offset: 4; indent-tabs-mode: nil -*- */

#ifndef __EIRODS_FILE_OBJECT_H__
#define __EIRODS_FILE_OBJECT_H__

// =-=-=-=-=-=-=-
// irods includes
#include "fileCreate.h"
#include "initServer.h"

// =-=-=-=-=-=-=-
// eirods includes
#include "eirods_first_class_object.h"
#include "eirods_physical_object.h"

// =-=-=-=-=-=-=-
// stl includes
#include <vector>

namespace eirods {

    class file_object : public first_class_object {
    public:
        // =-=-=-=-=-=-=-
        // Constructors
        file_object();
        file_object( const file_object& );
        file_object( rsComm_t* _comm,
                     const std::string& _logical_name,
                     const std::string& _filename,
                     const std::string& _resc_hier,
                     int _fd,
                     int _mode,
                     int _flags);
        file_object( rsComm_t* _comm,
                     const dataObjInfo_t* _dataObjInfo);
        
        // =-=-=-=-=-=-=-
        // Destructor
        virtual ~file_object();

        // =-=-=-=-=-=-=-
        // Operators
        virtual file_object& operator=( const file_object& );

        /// @brief Comparison operator
        virtual bool operator==( const file_object& _rhs ) const;
        
        // =-=-=-=-=-=-=-
        // plugin resolution operation
        virtual error resolve( resource_manager&, resource_ptr& );

        // =-=-=-=-=-=-=-
        // Accessors
        inline size_t                         size()           const { return size_;           }
        inline int                            repl_requested() const { return repl_requested_; }
        inline std::vector< physical_object > replicas()       const { return replicas_;       }
        inline bool                           in_pdmo()        const { return in_pdmo_;        }
        inline const keyValPair_t&            cond_input()     const { return cond_input_;     }
        
        // =-=-=-=-=-=-=-
        // Mutators
        inline void size( size_t _v )        { size_           = _v; }
        inline void repl_requested( int _v ) { repl_requested_ = _v; }
        inline void in_pdmo( bool _v )       {
            in_pdmo_        = _v;
        }
        inline void replicas( const std::vector< physical_object >& _v ) {
            replicas_ = _v;
        }
        inline void cond_input( const keyValPair_t& _cond_input ) { replKeyVal(&_cond_input, &cond_input_); }
        
    protected:
        // =-=-=-=-=-=-=-
        // Attributes
        // NOTE :: These are not guaranteed to be properly populated right now
        //      :: that will need be done later when these changes are pushed 
        //      :: higher in the original design
        size_t                         size_;           // size of the file in bytes
        int                            repl_requested_; // requested replica number
        bool                           in_pdmo_;        // flag indicating the current operations are occurring from within a pdmo
                                                        // call
        std::vector< physical_object > replicas_;       // structures holding replica info initialized by factory fcn from
                                                        // dataObjInfoHead
        keyValPair_t                  cond_input_;      // input keywords
        
    }; // class file_object

    // =-=-=-=-=-=-=-
    // factory function which will take a dataObjInfo pointer and create a file_object
    error file_object_factory( rsComm_t*,      // server network connection  
                               dataObjInp_t*,  // incoming data object request struct
                               file_object& ); // out var for file object
    // =-=-=-=-=-=-=-
    // function which will inform eirods as to which server to select for a given operation
    error resource_redirect( const std::string&,   // operation in question
                             rsComm_t*,            // server network connection  
                             dataObjInp_t*,        // incoming data object request struct
                             std::string&,         // chosen resource hierarchy string
                             rodsServerHost_t*&  , // svr2svr conn if redirecting
                             int& );               // local / remote flag


}; // namespace eirods

#endif // __EIRODS_FILE_OBJECT_H__



