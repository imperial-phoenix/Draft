/**
 * @file    Common.h
 * @brief   Entities common to all projects.
 * @ingroup MISC
 */

#ifndef __MISC_H__
#define __MISC_H__

#include <stddef.h>
#include <stdint.h>


///////////////////////////////////////////////////////////
//         Modules declaration block for doxygen         //
///////////////////////////////////////////////////////////

/** @defgroup MISC            Entities common to all projects */
/** @defgroup DATA_STRUCTURES Fundamental data structures */


///////////////////////////////////////////////////////////
/// @name Direction macros
///@{

/** Input parameter. */
#define IN

/** Output parameter. */
#define OUT

/** Optional parameter. */
#define OPTIONAL

///@}


///////////////////////////////////////////////////////////
/// @name Encapsulation implementation in C
///@{

/** Unique protocol structure ID. Formed using macro STRUCT_ID_64.*/
typedef uint64_t STRUCT_ID;


#define STRUCT_ID_16(A, B) ((A) | ((B) << 8))

#define STRUCT_ID_32(A, B, C, D) \
   (STRUCT_ID_16(A, B) | (STRUCT_ID_16(C, D) << 16))

/** Generates a STRUCT_ID.
 *  The first 8 letters of the protocol name must be given as input.
 *  For correct operation, similar protocol names should be avoided.
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


/** By pointer to the protocol(This), get the pointer to the
 *  structure(ClassName) that implements it.
 */
#define GET_THIS(This, ClassName) \
   ClassName* this = GET_STRUCT_FIELD(This, ClassName, VTable); \
   if (this->StructureId != ClassName ## _STRUCT_ID) this = NULL;

///@}


#endif // __MISC_H__