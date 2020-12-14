#ifndef _test_h_
#define _test_h_

#define    D_POOL_SIZE 1024
#define    Q_POOL_SIZE 1024
#define  MEM_POOL_SIZE 1024
#define  REG_POOL_SIZE 1024
#define WIRE_POOL_SIZE 1024

struct Pool {
    char*    d[D_POOL_SIZE];
    char*    q[Q_POOL_SIZE];
    char*  mem[MEM_POOL_SIZE];
    char*  rom[REG_POOL_SIZE];
    char* wire[WIRE_POOL_SIZE];
};

void clock_domain_main(
    char*   d, char*   q,
    char* mem, char* reg,
    char* wire
) {

}


int foo() {
    return 1;
}

#endif // _test_h