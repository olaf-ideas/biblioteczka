/**
 * Author: chilli
 * License: CC0
 * Description: Read an integer from stdin. Usage requires your program to pipe in 
 * input from file.
 * Usage: ./a.out < input.txt
 * Time: About 5x as fast as cin/scanf
 * Status: tested
 */

inline char gc() {
    static char buf[1 << 16];
    static size_t pos, len;
    if(pos >= len)  pos = 0, len = fread(buf, 1, sizeof(buf), stdin);
    // assert(pos < len); // end of file
    return buf[pos++];
}

inline int rd() { 
    int a, c;
    while((a = gc()) < 40);
    if(a == '-')    return -rd();
    while((c = gc()) > 47)  a = a * 10 + c - 480;
    return a - 48;
}

inline long long rdll() {
    long long a, c;
    while((a = gc()) < 40);
    if(a == '-')    return -rdll();
    while((c = gc()) > 47)  a = a * 10 + c - 480;
    return a - 48;
}
