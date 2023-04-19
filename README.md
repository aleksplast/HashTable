# HashTable
## Goals of this project

In this project i had two main goals:
1. Creating hashtable for fast word finding.
2. Optimizing algorithm using assembler, SIMD instructions and other methods.

## What is hashtable

Let's start by defining, what is hashtable actually.

For this we will need some definitions:
* **Key** - Any non-null object, in this project we will use strings as keys.
* **Hashvalue** - value for the corresponding key.
* **Hash Function** - function, that calculates hashvalue by given key.
* **Basket** - list in the hashtable.
* **Capacity** - number of buskets in the hashtable.
* **Collision** - case, where two different keys have the same hashvalue.
* **Load factor** - average size of buskets in the hashtable.

In this project **hashtable** is a table of linked lists and a hash functions attached to it. We will use text of Hamlet by William Shakespeare for filling the hashtable. For each word we will first count hashvalue of it, then put it to corresponding basket.


We will test 7 different hash functions in the first part and the best one we will optimize in the second part.

# Chapter I: different hash functions

Let's take a take a look at different hash functions, for each one we will look at the amount of collisions in each basket.

### Hash, that always returns 1

~~~C++
unsigned int HashReturn1(const char* input)
{
    return 1;
}
~~~
Here are the plot for this function: (Dispersion = 603397.56)
<img align="center"  src="./lib/Return 1 stat.png">

This is the ugliest thing i've seen in my life.

### Hash, that returns ASCII code of the first letter.
~~~C++
unsigned int HashReturnFirstASCII(const char* input)
{
    return input[0];
}
~~~
Here are the plot: (Dispersion = 19734.64)
<img align="center"  src="./lib/FirstASCII stat.png">

This one looks not as ugly as a previous one, but it still is.
### Hash, that returns lenght of the word.
~~~C++
unsigned int HashReturnLen(const char* input)
{
    return strlen(input);
}
~~~

Plot for this one: (Dispersion = 77765.57)
<img align="center"  src="./lib/StrlenStat.png">

Still not as good as we want.

### Hash, that returns sum of ASCII codes of the letters in the word.
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

And here comes the plot: (Dispersion = 90.73)

<img align="center"  src="./lib/ASCIIsum.png">

This one looks decent, but we can make better.

### Hash, that uses $rol$ command from assembler.
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

ROL plot: (Dispersion = 50.88)

<img align="center"  src="./lib/Rolstat.png">

We are getting better and better, let's now take a look at similar function

### Hash, that uses $ror$ command from assembler.
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

ROR plot: (Dispersion = 49.22)

<img align="center"  src="./lib/Rorstat.png">

This one is even better than the previous one.

### CRC32 Hash

Famous CRC32 hash goes like this:

~~~C++
unsigned int CRCHashC(const char* input)
{
    unsigned int hash = 0;
    int len = strlen(input);
    unsigned int data = 0;
    int width = (8 * sizeof(unsigned int));

    for (int i = 0; i < len; i++)
    {
        data = input[i] ^ (hash >> (width - 8));
        hash = crcTable[data] ^ (hash << 8);
    }

    return hash;
}
~~~

And here's the plot fot it: (Dispersion = 18.34)

<img align="center"  src="./lib/CRCstat.png">


### MurMurHash

Here is the code for famous MurMurHash (我喜欢猫)
~~~C++
unsigned int MurMurHash(const char* data)
{
    int lenght = strlen(data);
    unsigned int seed = 0;
    const int shift = 24;
    const unsigned int base = 0x5bd1e995;

    unsigned int hash = seed ^ lenght;

    const unsigned char* buffer = (const unsigned char*) data;

    while (lenght >= 4)
    {
        unsigned int curr = *(unsigned int*) buffer;

        curr *= base;
        curr ^= curr >> shift;
        curr *= base;

        hash *= base;
        hash ^= curr;

        buffer += 4;
        lenght -= 4;
    }

    switch (lenght)
    {
        case 3:
            hash ^= buffer[2] << 16;
        case 2:
            hash ^= buffer[1] << 8;
        case 1:
            hash ^= buffer[0];
            hash *= base;
    };

    hash ^= hash >> 13;
    hash *= base;
    hash ^= hash >> 15;

    return hash;
}
~~~

Plot for this one looking good: (Dispersion = 17.99)

<img align="center"  src="./lib/MurMurStat.png">

This one is the best so far. Let's stop at this variant and try to optimize what we have.

# Chapter II: Optimizations

## Experiment explanation

First of all, let's set out experiment conditions. As stated earlier, we will use text of Hamlet, written by William Shakespear to load the hashtable. Capacity of the hashtable will be 1000 baskets. Each word will be searched 10000 times. Using `callgrind` we will find hot spots of our programm. Programm will be compiled with `-O3` flag.

## Initial parameters

Before starting, let's take a look at a unoptimized programm (Remainder: programm compiled with `-O3` flag).

Callgrind layout for it looks like this:

**ВСТАВИТЬ НАКОНЕЦ КАРТИНКИ**

Let's put out base variant into the table.

| Optimization | Number of machine commands | Absolute speed growth | Relative speed growth |
| :----------: | :-------------------: | :------------------:       | :---------------------:     |
| No optimization |   16 740 227 454           |   1                | 1                   |

## Optimization 1

As we can see from callgrind layout for our base version, most hot spot is strcmp function. Let's try to optimize it by doing an inline assembly of our strcmp.

Code for it goes like this:

~~~C++
int inline strcmp_asm (const char* str1, const char* str2)
{
    int result = 0;
    asm(".intel_syntax noprefix\n\t"
        "mov rsi, %1\n\t"
        "mov rdi, %2\n\t"
        "Next:\n"
            "mov r11b, byte ptr [rsi]\n"
            "mov r10b, byte ptr [rdi]\n"
    	    "cmp r10b, 0\n"
    	    "je done\n"
    	    "cmp r11b, 0\n"
    	    "je done\n"
    	    "cmp r11b, r10b\n"
    	    "jne done\n"
    	    "inc rdi\n"
    	    "inc rsi\n"
    	    "jmp Next\n"
        "done:\n"
            "movzx rax, r10b\n"
            "movzx rbx, r11b\n"
    	    "sub rax, rbx\n"
        ".att_syntax"
        : "=r" (result) : "r" (str1), "r" (str2) : "rax", "rbx", "rsi", "rdi", "r10", "r11"
    );
    return result;
}
~~~

Let's look at a callgrind layout for this optimization.

**ВСТАВИТЬ НАКОНЕЦ КАРТИНКИ**

| Optimization | Number of machine commands | Absolute speed growth | Relative speed growth |
| :----------: | :-------------------: | :------------------:       | :---------------------:     |
| No optimization |   16 740 227 454           |   1                | 1                   |
| Optimization1 |   32 089 240 018           |   0.52                | 0.52                   |

We can notice significant drawback at programm speed, because of it we will not use this optimization later.

## Optimization 2

Second hot spot in base variant was a MurMurHash function. Let's rewrite it on assembler. 

Code goes like this:

~~~Assembly
MurMurHashAsm:
        push rbx

        mov ebx, esi            ; seed ^ lenght
        xor eax, eax

.Next:  imul eax, dword [rdi], BASE     ; curr *= base
        mov ecx, eax
        shr ecx, 24             ; curr >> shift

        xor eax, ecx            ; curr ^= curr >> shift

        imul ebx, ebx, BASE     ; hash *= base
        xor ebx, eax            ; hash ^= curr
        add rdi, 4              ; buffer += 4
        sub rsi, 4              ; lenght -= 4

        cmp rsi, 4              ; while (lenght >= 4)
        jge .Next

        mov eax, ebx            ; hash in rax
        xor ebx, ebx

        cmp rsi, 3
        je .Three
        cmp  rsi, 2
        je .Two

        jmp .Done

.Three: movzx ebx, byte [rdi + 2]  ; buffer[2]
        sal ebx, 16             ; buffer[2] << 16
        xor eax, ebx            ; hash ^= buffer[2] << 16
        xor ebx, ebx


.Two:   movzx ebx, byte [rdi + 1]  ; buffer[1]
        sal ebx, 8              ; buffer[1] << 8
        xor eax, ebx            ; hash ^= buffer[1] << 8
        xor ebx, ebx

.Done:  movzx ebx, byte [rdi]      ; buffer[0]
        xor ebx, ebx            ; hash ^= buffer[0]
        imul eax, eax, BASE     ; hash *= r12

        mov ebx, eax            ; hash in rbx
        shr ebx, 13             ; hash >> 13
        xor eax, ebx            ; hash ^= hash >> 13

        imul eax, eax, BASE     ; hash *= base
        mov ebx, eax            ; hash in rbx
        shr ebx, 15             ; hash >> 15
        xor eax, ebx            ; hash ^= hash >> 15

        pop rbx
        ret

.data

BASE equ 0x5bd1e995
~~~

| Optimization | Number of machine commands | Absolute speed growth | Relative speed growth |
| :----------: | :-------------------: | :------------------:       | :---------------------:     |
| No optimization |   16 740 227 454           |   1                | 1                   |
| Optimization1 |   32 089 240 018           |   0.52                | 0.52                   |
| Optimization2 |   16 260 100 266           |   1.03                | 1.97                   |

Finally, we were able te get some speed growth. This optimization remains in place.

## Optimization 3

