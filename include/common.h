#ifndef COMMON_H
#define COMMON_H

//!--------------------------------
//! @brief Used for indicating of appeared error
//!--------------------------------
enum Errors
{
    NOERR = 0,      ///<No errors occured
    INPUTERROR,     ///<Error with input file
    MEMERROR,       ///<Error with memory
    FILERROR        ///<Error with file
};

#endif // COMMON_H
