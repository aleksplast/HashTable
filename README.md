# HashTable
## Goals of this project

In this project i had two main goals:
1. Creating hashtable for fast word finding.
2. Optimizing algorith using assembler, SIMD instructions and other methods.

## What is hashtable

Let's start by defining, what is hashtable actually.

In this project hashtable is a table of linked lists and a hash functions attached to it. We will use text of immortal Hamlet by William Shakespeare for filling the hashtable. For each word we will first count hash of it, then put it to corresponding list.

We will test 7 different hash functions in the first part, then the best one we will optimize in the second part.

# Chapter I: different hash functions

Let's take a look at different hash functions, for each one we will look at the amount of collisions in each list.

### Function, that always returns 1

~~~C++
unsigned int HashReturn1(const char* input)
{
    return 1;
}
~~~

Here are the plot for this function:

### Function, that returns ASCII code of the first letter.
~~~C++
unsigned int HashReturnFirstASCII(const char* input)
{
    return input[0];
}
~~~

Here are the plot:

### Function, that returns lenght of the word.
~~~C++
unsigned int HashReturnLen(const char* input)
{
    return strlen(input);
}
~~~

Plot for this one:

### Function, that returns sum of ASCII codes of the letters in the word.
~~~C++
unsigned int HashReturnSumASCII(const char* input)
{
    unsigned int sum = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        sum += input[i];
    }

    return sum;
}
~~~

And here comes the plot:

### Function, that uses $rol$ command from assembler.
~~~C++
unsigned int RolHash(const char* input)
{
    unsigned int hash = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        hash = RolFunc(hash, 1) ^ input[i];
    }

    return hash;
}
~~~

ROL plot:

### Function, that uses $ror$ command from assembler.
~~~C++
unsigned int RorHash(const char* input)
{
    unsigned int hash = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        hash = RorFunc(hash, 1) ^ input[i];
    }

    return hash;
}
~~~

ROR plot:

### MurMurHash (google it, if you don't know).

Plot for this one looking good:

### (Not done yet) CRC hash (again, google it).

This one's plot looking good too.
