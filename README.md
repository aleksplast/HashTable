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

## Descriptions:

Here are 7 different hash functions we will use later:

1. Function, that always returns 1
2. Function, that returns ASCII code of the first letter.
3. Function, that returns lenght of the word.
4. Function, that returns sum of ASCII codes of the letters in the word.
5. Function, that uses $rol$ command from assembler.
6. Function, that uses $ror$ command from assembler.
7. MurMurHash (google it, if you don't know).
8. (Not done yet) CRC hash (again, google it).
