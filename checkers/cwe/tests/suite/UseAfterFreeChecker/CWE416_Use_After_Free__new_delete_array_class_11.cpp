/* TEMPLATE GENERATED TESTCASE FILE
Filename: CWE416_Use_After_Free__new_delete_array_class_11.cpp
Label Definition File: CWE416_Use_After_Free__new_delete_array.label.xml
Template File: sources-sinks-11.tmpl.cpp
*/
/*
 * @description
 * CWE: 416 Use After Free
 * BadSource:  Allocate data using new, initialize memory block, and Deallocate data using delete
 * GoodSource: Allocate data using new and initialize memory block
 * Sinks:
 *    GoodSink: Do nothing
 *    BadSink : Use data after delete[]
 * Flow Variant: 11 Control flow: if(globalReturnsTrue()) and if(globalReturnsFalse())
 * */

#include <wchar.h>

#include "std_testcase.h"

namespace CWE416_Use_After_Free__new_delete_array_class_11 {

#ifndef OMITBAD

void bad()
{
    TwoIntsClass* data;
    /* Initialize data */
    data = NULL;
    if (globalReturnsTrue()) {
        data = new TwoIntsClass[100];
        {
            size_t i;
            for (i = 0; i < 100; i++) {
                data[i].intOne = 1;
                data[i].intTwo = 2;
            }
        }
        /* POTENTIAL FLAW: Delete data in the source - the bad sink attempts to use data */
        delete[] data;
    }
    if (globalReturnsTrue()) {
        /* POTENTIAL FLAW: Use of data that may have been deleted */
        printIntLine(data[0].intOne);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not deleted */
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

/* goodB2G1() - use badsource and goodsink by changing the second globalReturnsTrue() to globalReturnsFalse() */
static void goodB2G1()
{
    TwoIntsClass* data;
    /* Initialize data */
    data = NULL;
    if (globalReturnsTrue()) {
        data = new TwoIntsClass[100];
        {
            size_t i;
            for (i = 0; i < 100; i++) {
                data[i].intOne = 1;
                data[i].intTwo = 2;
            }
        }
        /* POTENTIAL FLAW: Delete data in the source - the bad sink attempts to use data */
        delete[] data;
    }
    if (globalReturnsFalse()) {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    } else {
        /* FIX: Don't use data that may have been deleted already */
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not deleted */
        /* do nothing */
        ; /* empty statement needed for some flow variants */
    }
}

/* goodB2G2() - use badsource and goodsink by reversing the blocks in the second if */
static void goodB2G2()
{
    TwoIntsClass* data;
    /* Initialize data */
    data = NULL;
    if (globalReturnsTrue()) {
        data = new TwoIntsClass[100];
        {
            size_t i;
            for (i = 0; i < 100; i++) {
                data[i].intOne = 1;
                data[i].intTwo = 2;
            }
        }
        /* POTENTIAL FLAW: Delete data in the source - the bad sink attempts to use data */
        delete[] data;
    }
    if (globalReturnsTrue()) {
        /* FIX: Don't use data that may have been deleted already */
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not deleted */
        /* do nothing */
        ; /* empty statement needed for some flow variants */
    }
}

/* goodG2B1() - use goodsource and badsink by changing the first globalReturnsTrue() to globalReturnsFalse() */
static void goodG2B1()
{
    TwoIntsClass* data;
    /* Initialize data */
    data = NULL;
    if (globalReturnsFalse()) {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    } else {
        data = new TwoIntsClass[100];
        {
            size_t i;
            for (i = 0; i < 100; i++) {
                data[i].intOne = 1;
                data[i].intTwo = 2;
            }
        }
        /* FIX: Do not delete data in the source */
    }
    if (globalReturnsTrue()) {
        /* POTENTIAL FLAW: Use of data that may have been deleted */
        printIntLine(data[0].intOne);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not deleted */
    }
}

/* goodG2B2() - use goodsource and badsink by reversing the blocks in the first if */
static void goodG2B2()
{
    TwoIntsClass* data;
    /* Initialize data */
    data = NULL;
    if (globalReturnsTrue()) {
        data = new TwoIntsClass[100];
        {
            size_t i;
            for (i = 0; i < 100; i++) {
                data[i].intOne = 1;
                data[i].intTwo = 2;
            }
        }
        /* FIX: Do not delete data in the source */
    }
    if (globalReturnsTrue()) {
        /* POTENTIAL FLAW: Use of data that may have been deleted */
        printIntLine(data[0].intOne);
        /* POTENTIAL INCIDENTAL - Possible memory leak here if data was not deleted */
    }
}

void good()
{
    goodB2G1();
    goodB2G2();
    goodG2B1();
    goodG2B2();
}

#endif /* OMITGOOD */

}  // namespace CWE416_Use_After_Free__new_delete_array_class_11

/* Below is the main(). It is only used when building this testcase on
   its own for testing or for building a binary to use in testing binary
   analysis tools. It is not used when compiling all the testcases as one
   application, which is how source code analysis tools are tested. */

#ifdef INCLUDEMAIN

using namespace CWE416_Use_After_Free__new_delete_array_class_11; /* so that we can use good and bad easily */

int main(int argc, char* argv[])
{
    /* seed randomness */
    srand((unsigned)time(NULL));
#ifndef OMITGOOD
    printLine("Calling good()...");
    good();
    printLine("Finished good()");
#endif /* OMITGOOD */
#ifndef OMITBAD
    printLine("Calling bad()...");
    bad();
    printLine("Finished bad()");
#endif /* OMITBAD */
    return 0;
}

#endif
