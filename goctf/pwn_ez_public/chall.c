#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *guys[8] = {0};
size_t sizes[8] = {0};
int fd = -1;

size_t read_int(size_t base) {
    char buf[32] = {0};
    read(0, buf, 22);
    return strtoull(buf, NULL, base);
}

void add() {
    printf("idx: ");
    size_t idx = read_int(10);
    if (idx > 7) _exit(1);
    if (guys[idx] != NULL) _exit(1);
    printf("size: ");
    size_t size = read_int(10);
    if (size > 67) _exit(1);
    guys[idx] = calloc(size,1);
    sizes[idx] = size;
}

void edit() {
    printf("idx: ");
    size_t idx = read_int(10);
    if (idx > 7) _exit(1);
    if (guys[idx] == NULL) _exit(1);
    printf("data: ");
    read(0, guys[idx], sizes[idx]);
}

void del() {
    printf("idx: ");
    size_t idx = read_int(10);
    if (idx > 7) _exit(1);
    if (guys[idx] == NULL) _exit(1);
    free(guys[idx]);
    guys[idx] = NULL;
    sizes[idx] = 0;
}

void execve_self() {
    if (execve("./chall", NULL, NULL) == -1) _exit(1);
}

void rand_args(unsigned int args[64]) {
    unsigned int seed;
    if (read(fd, &seed, sizeof(seed)) != sizeof(seed)) _exit(1);
    srand(seed);
    for (int i = 0; i < 64; i++) args[i] = rand();
}

size_t cnt_arb_call = 0;
void arb_call() {
    if (cnt_arb_call++) _exit(1);
    unsigned int args[64] = {0};
    rand_args(args);
    printf(": ");
    void (*arbcall)(size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t,size_t);
    arbcall = (typeof(arbcall))read_int(16);
    arbcall(args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9],args[10],args[11],args[12],args[13],args[14],args[15],args[16],args[17],args[18],args[19],args[20],args[21],args[22],args[23],args[24],args[25],args[26],args[27],args[28],args[29],args[30],args[31],args[32],args[33],args[34],args[35],args[36],args[37],args[38],args[39],args[40],args[41],args[42],args[43],args[44],args[45],args[46],args[47],args[48],args[49],args[50],args[51],args[52],args[53],args[54],args[55],args[56],args[57],args[58],args[59],args[60],args[61],args[62],args[63]);
}

size_t cnt_sys_call = 0;
void sys_call() {
    if (cnt_sys_call++) _exit(1);
    unsigned int args[64] = {0};
    rand_args(args);
    unsigned int nr = -1;
    printf(": ");
    nr = read_int(16);
    unsigned int arg = -1;
    printf(": ");
    arg = read_int(16);
    syscall(nr,arg,args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9],args[10],args[11],args[12],args[13],args[14],args[15],args[16],args[17],args[18],args[19],args[20],args[21],args[22],args[23],args[24],args[25],args[26],args[27],args[28],args[29],args[30],args[31],args[32],args[33],args[34],args[35],args[36],args[37],args[38],args[39],args[40],args[41],args[42],args[43],args[44],args[45],args[46],args[47],args[48],args[49],args[50],args[51],args[52],args[53],args[54],args[55],args[56],args[57],args[58],args[59],args[60],args[61],args[62],args[63]);
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) _exit(1);
    while (1) {
        printf(">> ");
        size_t choice = read_int(10);
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                del();
                break;
            case 4:
                execve_self();
                break;
            case 5:
                arb_call();
                break;
            case 6:
                sys_call();
                break;
            default:
                _exit(0);
        }
    }
}
