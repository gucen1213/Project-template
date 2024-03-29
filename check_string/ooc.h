/***************************************************************************
 *   Copyright(C)2009-2012 by Gorgon Meducer<Embedded_zhuoran@hotmail.com> *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __OBJECT_ORIENTED_C_H__
#define __OBJECT_ORIENTED_C_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/



/* -----------------  Start of section using anonymous unions  -------------- */
#if defined(__CC_ARM)
  //#pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif


#ifndef this
#   define this        (*ptThis)
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

#define CLASS(__NAME)               __##__NAME

//! \brief macro for initializing an event
#define INIT_DELEGATE(__NAME/*,__ASYN*/)           delegate_init(&(__NAME)/*, (__ASYN)*/)


 

#define DECLARE_CLASS(__NAME)                   \
     typedef union __NAME __NAME;                

#define DEF_CLASS(__NAME,...)                   \
    /*typedef union __NAME __NAME;  */          \
    typedef struct __##__NAME __##__NAME;       \
    struct __##__NAME {                         \
        __VA_ARGS__
          
#define END_DEF_CLASS(__NAME, ...)              \
    };                                          \
    union __NAME {                              \
        __VA_ARGS__                             \
        uint_fast8_t __NAME##__chMask[(sizeof(__##__NAME) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };

/*! \brief macro for initializing class in compiler-time
 *! \param __TYPE class name
 *! \param __OBJ target object
 *! \param ... initialization list
 */
#define INIT_CLASS_OBJ(__TYPE, __OBJ, ...)          \
            union {                                 \
                CLASS(__TYPE) __##__OBJ;            \
                __TYPE   __OBJ;                     \
            } = {                                   \
                .__##__OBJ = __VA_ARGS__,           \
            }

#define EXTERN_CLASS_OBJ( __TYPE, __OBJ )           \
            extern union {                          \
                CLASS(__TYPE) __##__OBJ;            \
                __TYPE   __OBJ;                     \
            };
    


#define EXTERN_CLASS(__NAME,...)                    \
    /*typedef union __NAME __NAME; */               \
    union __NAME {                                  \
        __VA_ARGS__                                 \
        uint_fast8_t __NAME##__chMask[(sizeof(struct{\
        __VA_ARGS__

#define END_EXTERN_CLASS(__NAME, ...)               \
        }) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };


//! \name interface definition
//! @{
#define DEF_INTERFACE(__NAME,...)                   \
            typedef struct __NAME __NAME;           \
            __VA_ARGS__                             \
            struct __NAME {

#define END_DEF_INTERFACE(__NAME)                   \
            };
//! @}

//! \name structure definition
//! @{
#define DEF_STRUCTURE(__NAME,...)                   \
            typedef struct __NAME __NAME;           \
            __VA_ARGS__                             \
            struct __NAME {

#define END_DEF_STRUCTURE(__NAME)                   \
            };
//! @}


//! \brief macro for inheritance

#define INHERIT_EX(__TYPE, __NAME)  \
            union {                 \
                __TYPE  __NAME;     \
                __TYPE;             \
            };

/*! \note When deriving a new class from a base class, you should use INHERIT 
 *        other than IMPLEMENT, although they looks the same now.
 */
#define INHERIT(__TYPE)             INHERIT_EX(__TYPE, base__##__TYPE)

/*! \note You can only use IMPLEMENT when defining INTERFACE. For Implement 
 *        interface when defining CLASS, you should use DEF_CLASS_IMPLEMENT 
 *        instead.
 */
#define IMPLEMENT(__INTERFACE)      INHERIT_EX(__INTERFACE, base__##__INTERFACE)

/*! \note if you have used INHERIT or IMPLEMENT to define a CLASS / INTERFACE, 
          you can use OBJ_CONVERT_AS to extract the reference to the inherited 
          object. 
  \*/
#define OBJ_CONVERT_AS(__OBJ, __INTERFACE)  (__OBJ.base__##__INTERFACE)
            
#define REF_OBJ_AS(__OBJ, __TYPE)       (&(__OBJ.base__##__TYPE))

#define REF_INTERFACE(__INTERFACE)      const __INTERFACE *ptMethod;
           

/*============================ TYPES =========================================*/


//typedef fsm_rt_t DELEGATE_HANDLE_FUNC(void *pArg, void *pParam);

//DECLARE_CLASS( DELEGATE_HANDLE )
////! \name general event handler
////! @{
//EXTERN_CLASS( DELEGATE_HANDLE )
//    DELEGATE_HANDLE_FUNC   *fnHandler;      //!< event handler
//    void                   *pArg;           //!< Argument
//    DELEGATE_HANDLE        *ptNext;         //!< next 
//END_EXTERN_CLASS(DELEGATE_HANDLE)
////! @}

//DECLARE_CLASS( DELEGATE )
////! \name event
////! @{
//EXTERN_CLASS(DELEGATE)
//    DELEGATE_HANDLE     *ptEvent;
//    DELEGATE_HANDLE     *ptBlockedList;
//    DELEGATE_HANDLE     **pptHandler;
//END_EXTERN_CLASS(DELEGATE)
////! @}

////! \name interface: u32_property_t
////! @{
//DEF_INTERFACE(u32_property_t)
//    bool (*Set)(uint32_t wValue);
//    uint32_t (*Get)(void);
//END_DEF_INTERFACE(u32_property_t)
////! @}

////! \name interface: u16_property_t
////! @{
//DEF_INTERFACE(u16_property_t)
//    bool (*Set)(uint_fast16_t wValue);
//    uint_fast16_t (*Get)(void);
//END_DEF_INTERFACE(u16_property_t)
////! @}

////! \name interface: u8_property_t
////! @{
//DEF_INTERFACE(u8_property_t)
//    bool (*Set)(uint_fast8_t wValue);
//    uint_fast8_t (*Get)(void);
//END_DEF_INTERFACE(u8_property_t)
////! @}


////! \name interface: i32_property_t
////! @{
//DEF_INTERFACE(i32_property_t)
//    bool (*Set)(int32_t wValue);
//    int32_t (*Get)(void);
//END_DEF_INTERFACE(i32_property_t)
////! @}

////! \name interface: i16_property_t
////! @{
//DEF_INTERFACE(i16_property_t)
//    bool (*Set)(int_fast16_t wValue);
//    int_fast16_t (*Get)(void);
//END_DEF_INTERFACE(i16_property_t)
////! @}

////! \name interface: u8_property_t
////! @{
//DEF_INTERFACE(i8_property_t)
//    bool (*Set)(int_fast8_t wValue);
//    int_fast8_t (*Get)(void);
//END_DEF_INTERFACE(i8_property_t)
////! @}

////! \name interface: bool_property_t
////! @{
//DEF_INTERFACE(bool_property_t)
//    bool (*Set)(bool bValue);
//    bool (*Get)(void);
//END_DEF_INTERFACE(bool_property_t)
////! @}

////! \name interface: bool_property_t
////! @{
//DEF_INTERFACE(en_property_t)
//    bool (*Enable)(void);
//    bool (*Disable)(void);
//END_DEF_INTERFACE(en_property_t)
////! @}


///*============================ GLOBAL VARIABLES ==============================*/
///*============================ LOCAL VARIABLES ===============================*/
///*============================ PROTOTYPES ====================================*/

///*! \brief initialize event 
// *! \param ptEvent target event
// *! \return the address of event item
// */
//extern DELEGATE *delegate_init(DELEGATE *ptEvent);

///*! \brief initialize event handler item
// *! \param ptHandler the target event handler item
// *! \param fnRoutine event handler routine
// *! \param pArg handler extra arguments
// *! \return the address of event handler item
// */
//extern DELEGATE_HANDLE *delegate_handler_init(
//    DELEGATE_HANDLE *ptHandler, DELEGATE_HANDLE_FUNC *fnRoutine, void *pArg);

///*! \brief register event handler to specified event
// *! \param ptEvent target event
// *! \param ptHandler target event handler
// *! \return access result
// */
//extern gsf_err_t register_delegate_handler(DELEGATE *ptEvent, DELEGATE_HANDLE *ptHandler);

///*! \brief unregister a specified event handler
// *! \param ptEvent target event
// *! \param ptHandler target event handler
// *! \return access result
// */
//extern gsf_err_t unregister_delegate_handler( DELEGATE *ptEvent, DELEGATE_HANDLE *ptHandler);

///*! \brief raise target event
// *! \param ptEvent the target event
// *! \param pArg event argument
// *! \return access result
// */
//extern fsm_rt_t invoke_delegate( DELEGATE *ptEvent, void *pParam);
#endif
/* EOF */
