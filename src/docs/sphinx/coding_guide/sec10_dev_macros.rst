.. ##
.. ## Copyright (c) 2016, Lawrence Livermore National Security, LLC.
.. ##
.. ## Produced at the Lawrence Livermore National Laboratory.
.. ##
.. ## All rights reserved.
.. ##
.. ## This file cannot be distributed without permission and
.. ## further review from Lawrence Livermore National Laboratory.
.. ##

.. _codemacros-label:

=======================================================
10 Common Code Development Macros, Types, etc.
=======================================================

This section provides guidelines for consistent use of macros and types
defined in the "common" and "slic" Toolkit components and in our build 
system that we use in day-to-day code development.

.. important:: Code that is guarded with macros described in this section 
               **must not** change the *externally-observable* execution 
               behavior of the code.

               The macros are intended to help users and developers avoid
               unintended or potentially erroneous usage, etc. not confuse them. 

------------------------------------
Null pointers
------------------------------------

10.1 For consistency and to make it easier to find where pointer types are
set to *null*, the `ATK_NULLPTR` macro **must** be used. For example,::

   double* var = ATK_NULLPTR;

This macro is defined in the `CommonTypes.hpp` header file in the "common"
component. This usage prevents inconsistencies that occur when different 
developers use conventions, such as '= 0', '= NULL', etc. to initialize
pointer types to null. It also allows us to easily use the standard 'nullptr' 
keyword/type introduced in C++ 11 when it is available.


------------------------------------
Unused variables
------------------------------------

10.2 To silence compiler warnings and express variable usage intent more 
clearly, macros in the `ATKMacros.hpp` header file in the "common" component 
**must** be used when appropriate. For example,::

    void my_function(int x, int ATK_DEBUG_PARAM(y))
    {
      // use variable y only for debug compilation
    }

Here, the `ATK_DEBUG_PARAM` macro indicates that the variable 'y' is only
used when the code is compiled in debug mode. It also removes the variable
name in the argument list in non-debug compilation to prevent unwanted
compiler warnings.

Please see the `ATKMacros.hpp` header file for other available macros and 
usage examples.


------------------------------------
Disabling compiler-generated methods
------------------------------------

10.3 To disable compiler-generated class/struct methods when this is desired 
and to clearly express this intent, the `ATKMacros.hpp` header file in the 
"common" component contains macros that **should** be used for this purpose. 
See :ref:`compilergenmethods-label` for more information about 
compiler-generated methods.

Please see the `ATKMacros.hpp` header file for other available macros and 
usage examples.


------------------------------------
Conditionally compiled code
------------------------------------

10.4 Macros defined by the CS Toolkit build system **must** be used to 
control conditional code compilation. 

For example, complex or multi-line code that is intended to be exposed only
for a debug build **must** be guarded using the `ATK_DEBUG` macro::

   void MyMethod(...) 
   {
   #if defined(ATK_DEBUG)
     // Code that performs debugging checks on object state, method args,
     // reports diagnostic messages, etc. goes here 
   #endif 

      // rest of method implementation
   }

The CS Toolkit build system provides various other macros for controlling 
conditionally-compiled code. Please see the `config.hpp` header file in
common for a complete list. The macro constants will be defined based on
CMake options given when the code is configured. 


------------------------------------
Error handling
------------------------------------

10.5 Macros provided in the "slic" component **should** be used to provide 
runtime checks for incorrect or questionable usage and informative messages 
for developers and users.

Runtime checks for incorrect or questionable usage and generation of 
informative warning, error, notice messages can be a tremendous help to 
users and developers. This is an excellent way to provide run-time debugging 
capabilities in code. Using the "slic" macros ensures that syntax and meaning
are consistent and that output information is handled similarly throughout 
the code. 

When certain conditions are encountered, the macros can emit failed boolean 
expressions and descriptive messages that help to understand potentially
problematic usage. Here's an example of common *SLIC* macro usage in the CS 
Toolkit::

   Bar* myCoolFunction(int in_val, Foo* in_foo)
   {
     if ( in_val < 0 || in_foo == ATK_NULLPTR )  
     {
       SLIC_CHECK_MSG( in_val >= 0, "in_val must be non-negative" );
       SLIC_CHECK( in_foo != ATK_NULL_PTR );
       return ATK_NULLPTR;
     } else if ( !in_foo->isSet() ) {
       SLIC_CHECK_MSG( in_foo->isSet(), 
                       "in_foo is not set, will use default settings");
       const int val = in_val >= 0 ? in_val : DEFAULT_VAL;
       in_foo->setDefaults( val );
     }
    
     Bar* bar = new Bar(in_foo);

     return bar;
   }

This example uses slic macros that are only active when the code is compiled
in debug mode. When compiled in release mode, for example, the macros are 
empty and so do nothing. Also, when a condition is encountered that is 
problematic, such as 'in_val < 0' or 'in_foo == ATK_NULLPTR', the code will
emit the condition and an optional message and not halt. This allows calling
code to catch the issue (in this case a null return value) and react. There
are other macros (e.g., SLIC_ASSERT) that will halt the code if that is 
desired.

Slic macros operate in one of two compilation-defined modes. Some macros are 
active only in for a debug compile. Others are active for any build type.
Macros provided for each of these modes can be used to halt the code or not 
after describing the condition that triggered them. The following table
summarizes the SLIC macros.

============== ================ ====================
  Macro type     When active?     Halts code?
============== ================ ====================
  ERROR          Always           Yes
  WARNING        Always           No
  ASSERT         Debug only       Yes
  CHECK          Debug only       No
============== ================ ====================

Typically, we use macros ERROR/WARNING macros rarely. They are used primarily
to catch cases that are obvious programming errors or would put an application 
in a state where continuing is seriously in doubt. CHECK macros are used most
often, since they provide useful debugging information and do not halt the 
code -- they allow users to catch cases from which they can recover. ASSERT
macros are used in cases where halting the code is desired, but only in 
debug mode.

Please see the `slic.hpp` header file to see which macros are available and 
how to use them. 

.. important:: It is important to apply these macros judiciously so that they
               benefit users and other developers. We want to help folks use 
               our software correctly and not "spam" them with too much 
               information.
