/**
 * @file    Misc.h
 * @brief   Entities common to all projects.
 * @ingroup MISC
 */

#ifndef __MISC_H__
#define __MISC_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


///////////////////////////////////////////////////////////
//         Modules declaration block for doxygen         //
///////////////////////////////////////////////////////////

/** @defgroup  MISC             Entities common to all projects */
/** @defgroup  DATA_STRUCTURES  Fundamental data structures     */


///////////////////////////////////////////////////////////
//         Modules declaration block for doxygen         //
///////////////////////////////////////////////////////////

/** An input parameter in a function or method. */
#define IN

/** An output parameter in a function or method. */
#define OUT

/** An optional parameter in a function or method/ */
#define OPTIONAL


///////////////////////////////////////////////////////////
//                    Return statuses                    //
///////////////////////////////////////////////////////////

/**
 * @brief Status returned by functions and methods.
 *
 * @details The status is uint64_t with the following structure:
 *
 *          0x00000000
 *            ||  |
 *            Error bit (1 bit), if 1, then error
 *             |  |
 *             |  Line (16 bit)
 *             |
 *             Status code (12 bit)
 */
typedef uint32_t STATUS_CODE;


/** Successful status. */
#define SC_SUCCESS 0x00000000U

/** The most significant bit indicates an error. */
#define SC_ERROR_BIT 0x80000000U

#define SC_INVALID_PARAMETER (SC_ERROR_BIT | 0x00010000)
#define SC_NOT_ENOUGH_MEMORY (SC_ERROR_BIT | 0x00020000)
#define SC_UNSUCCESSFUL      (SC_ERROR_BIT | 0x00030000)


/** Sets the return status to the desired state(StatusCode). */
#define SET_SC(StatusCode) \
   status = (0x0000FFFF & __LINE__) | StatusCode

/** Returns true if the status code(StatusCode) is an error. */
#define SC_ERROR(StatusCode) ((int32_t)StatusCode < 0)


///////////////////////////////////////////////////////////
//                  Encapsulation in C                   //
///////////////////////////////////////////////////////////

/** Unique protocol structure ID. Formed using macro STRUCT_ID_64.*/
typedef uint64_t STRUCT_ID;


#define STRUCT_ID_16(A, B) ((A) | ((B) << 8))

#define STRUCT_ID_32(A, B, C, D) \
   (STRUCT_ID_16(A, B) | (STRUCT_ID_16(C, D) << 16))

/**
 * Generates a STRUCT_ID. The first 8 letters of the protocol name
 * must be given as input. For correct operation, similar protocol
 * names should be avoided.
 */
#define STRUCT_ID_64(A, B, C, D, E, F, G, H) \
   (STRUCT_ID_32(A, B, C, D) | ((uint64_t)STRUCT_ID_32(E, F, G, H) << 32))


/**
 * By pointer to the protocol(This), get the field(Field) of the
 * structure that implements it(ClassName).
 */
#define GET_STRUCT_FIELD(This, ClassName, Field)                    \
   (This != NULL) ?                                                 \
   ((ClassName*)((char*)This - (char*)&(((ClassName*)0)->Field))) : \
   (ClassName*)NULL


/**
 *  By pointer to the protocol(This), get the pointer to the
 *  structure(ClassName) that implements it.
 */
#define GET_THIS(This, ClassName)                               \
   ClassName* this = GET_STRUCT_FIELD(This, ClassName, VTable); \
   if (NULL == this) { SET_SC(SC_INVALID_PARAMETER); break; }   \
   if (this->StructureId != ClassName ## _STRUCT_ID)            \
   { SET_SC(SC_INVALID_PARAMETER); break; }

#endif // __MISC_H__