#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

typedef void (*funcptr)();

void test() {
}

int main(int argc, char *argv[]) {
    funcptr func = NULL;
    char *mem = NULL, *secStart = NULL, exec[6];
    uint16_t e_shnum = 0;
    uint64_t e_shoff = 0, sh_offset = 0, r_offset = 0;
    uint32_t sh_name = 0;
    int sum = 0, len = 0, ret = 0, sectionNum = 0, i = 0;
    char *codeStart = NULL, *content = NULL, *pos = NULL;
    FILE *fp = NULL;
    
    if(argc < 2)
        return -1;
    if (!(fp = fopen(argv[1],"r"))) {
        printf("文件打开失败.\n");
        exit(-1);
    }
    fseek(fp, 0, SEEK_END);   //指针：移动到文件尾部
    len = ftell(fp);   //返回指针偏离文件头的位置(即文件中字符个数)
    printf("the file len is:%d\n", len);
    fseek(fp, 0, SEEK_SET);
    content = (char *)malloc(len);
    printf("the read len is:%d\n", len);
    ret = fread(content, len, 1, fp);
    printf("file hdr size is:%lu\n", sizeof(Elf64_Ehdr));
    printf("section hdr size is:%lu\n", sizeof(Elf64_Shdr));
    printf("Elf64_Half size is:%lu\n", sizeof(Elf64_Half));
    mem = (char *)&e_shnum;
    mem[0] = content[60];
    mem[1] = content[61];
    mem = (char *)&e_shoff;
    mem[0] = content[40];
    mem[1] = content[41];
    mem[2] = content[42];
    mem[3] = content[43];
    mem[4] = content[44];
    mem[5] = content[45];
    mem[6] = content[46];
    mem[7] = content[47];
//    printf("e_shoff is: %lu\n", e_shoff);
//    printf("sectionNum is: %d\n", e_shnum);
//    printf("uint32_t size is: %lu\n", sizeof(uint32_t));
//    printf("uint64_t size is: %lu\n", sizeof(uint64_t));
    for(i = 0; i<e_shnum; i++) {
        pos = content + e_shoff + 64*i;
        mem = (char *)&sh_name;
        mem[0] = pos[0];
        mem[1] = pos[1];
        mem[2] = pos[2];
        mem[3] = pos[3];
        printf("sh_name is %d\n", sh_name);
        mem = (char *)&sh_offset;
        secStart = pos + 24;
        mem[0] = secStart[0];
        mem[1] = secStart[1];
        mem[2] = secStart[2];
        mem[3] = secStart[3];
        mem[4] = secStart[4];
        mem[5] = secStart[5];
        mem[6] = secStart[6];
        mem[7] = secStart[7];
//        printf("secStart is: %lu\n",sh_offset);
        if(sh_offset == 960) {
            mem = (char *)&r_offset;
            mem[0] = content[960+0];
            mem[1] = content[960+1];
            mem[2] = content[960+2];
            mem[3] = content[960+3];
            mem[4] = content[960+4];
            mem[5] = content[960+5];
            mem[6] = content[960+6];
            mem[7] = content[960+7];
            printf("r_offset is: %lu\n", r_offset);
        }
    }

    for(i = 0; i<e_shnum; i++) {
        pos = content + e_shoff + 64*i;
        mem = (char *)&sh_name;
        mem[0] = pos[0];
        mem[1] = pos[1];
        mem[2] = pos[2];
        mem[3] = pos[3];
//        printf("sh_name is %d\n", sh_name);
        mem = (char *)&sh_offset;
        secStart = pos + 24;
        mem[0] = secStart[0];
        mem[1] = secStart[1];
        mem[2] = secStart[2];
        mem[3] = secStart[3];
        mem[4] = secStart[4];
        mem[5] = secStart[5];
        mem[6] = secStart[6];
        mem[7] = secStart[7];
//        printf("secStart is: %lu\n",sh_offset);
        if(sh_offset == 64) {
            printf("in if sh_offset == 64, sh_offset is: %lu\n", sh_offset);
            codeStart = content+sh_offset+r_offset;
//            func = (funcptr)codeStart;
            printf("r_offset is: %lu\n", r_offset);
            printf("codeStart is %lu\n", codeStart);
            printf("func address is: %d\n", func);
            exec[0] = 0x55;
            exec[1] = 0x48;
            exec[2] = 0x89;
            exec[3] = 0xe5;
            exec[4] = 0x5d;
            exec[5] = 0xc3;
            func = exec;
//            (*func)();     stilling core dump, will fix it.
//            printf("after call function pointer, sum is: %d\n", sum);
        }
    }
//    funcptr = codestart;
//    funcptr();
    fclose(fp);
    return 1;
}
