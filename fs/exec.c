#include "Gazzali.h"
#include "elf.h"

int sys_execve(const char *filename, char *const argv[], char *const envp[])
{
	int elffile;
//TODO: Cannot open file error
	if((elffile = sys_open(filename,0,0)) < 0) return -1;
	
	//	ReadELF Headers	
	Elf32_Ehdr ehdr;
	sys_read((unsigned int)elffile, &ehdr, sizeof(Elf32_Ehdr));

	// Check Magic
	if 	(	ehdr.e_ident[0]!=ELFMAG0||
			ehdr.e_ident[1]!=ELFMAG1||
			ehdr.e_ident[2]!=ELFMAG2||
			ehdr.e_ident[3]!=ELFMAG3) return -1;
	

	Elf32_Phdr *phdr = malloc(sizeof(Elf32_Phdr)*ehdr.e_phnum);
	Elf32_Shdr *shdr = malloc(sizeof(Elf32_Shdr)*ehdr.e_shnum);

	unsigned int i;
	sys_lseek(elffile, ehdr.e_phoff, SEEK_SET);
	for(i=0;i<ehdr.e_phnum;i++)sys_read(elffile, phdr+i, sizeof(Elf32_Phdr));
	
	sys_lseek(elffile, ehdr.e_shoff, SEEK_SET);
	for(i=0;i<ehdr.e_shnum;i++)sys_read(elffile, shdr+i, sizeof(Elf32_Shdr));

	// Load to memory
	i=0;
	sys_lseek(elffile,phdr[i].p_offset,SEEK_SET);
	int (*program) (char *const argv[], char *const envp[]) =malloc(phdr[i].p_memsz);
	sys_read(elffile,program,phdr[i].p_memsz);
	
	// Close ELF File
	sys_close(elffile);
	// Execute program
	return program(argv,envp);
}

