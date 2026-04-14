#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type)
{
    const char *type_str;

    switch (e_type) {
    case ET_NONE:
        type_str = "Unknown";
        break;
    case ET_REL:
        type_str = "Relocatable";
        break;
    case ET_EXEC:
        type_str = "Executable";
        break;
    case ET_DYN:
        type_str = "Shared Object/PIE";
        break;
    default:
        type_str = "Unknown";
        break;
    }
    printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[])
{
    char filepath[][256] = {
        "./17_myfile.o",
        "./17_myfile",
    };
    const size_t nfiles = sizeof(filepath) / sizeof(filepath[0]);
    size_t i;

    (void)argc;
    (void)argv;

    for (i = 0; i < nfiles; i++) {
        int fd;
        Elf64_Ehdr ehdr;
        ssize_t n;

        printf("File: %s\n", filepath[i]);
        fd = open(filepath[i], O_RDONLY);
        if (fd < 0) {
            perror("open");
            continue;
        }
        n = read(fd, &ehdr, sizeof(ehdr));
        if (n != (ssize_t)sizeof(ehdr)) {
            fprintf(stderr, "read ELF header failed\n");
            close(fd);
            continue;
        }
        close(fd);

        if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
            fprintf(stderr, "Not an ELF file (bad magic)\n");
            continue;
        }
        if (ehdr.e_ident[EI_CLASS] != ELFCLASS64) {
            fprintf(stderr, "Not ELF64\n");
            continue;
        }

        print_elf_type(ehdr.e_type);
        printf("\n");
    }

    return 0;
}
