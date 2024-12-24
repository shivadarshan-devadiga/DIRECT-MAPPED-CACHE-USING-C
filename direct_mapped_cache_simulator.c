#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct 
{
	int memory_size;
    int cache_size;
    int block_size;
    int size;
    int instrut_length;
    int index_bit;
	int tag_bit;
	int offset_bit;
	int *index;
	int *tag;
	int *offset;
	int *data;
    int hits;
    int misses;
    int *hit;
    int *miss;
	char *h_or_m;
	int *cache_index;
	int *valid;
	int *cache_tag;
	int *cache_data; 
	int *dirty;
} CacheSimulator;

int isPowerOf2(int n) 
{
    if (n<=0)
		return 0;
    return (n&(n-1))==0;
}

char* decimalToBinary(int num,int size) 
{
    char* binary = (char *) malloc((size+1) * sizeof(char));
    if (binary == NULL) 
	{
        printf("Memory allocation failed.\n");
        exit(1);
    }
    int index = 0;
    do 
	{
		binary[index++] = num%2+'0';
        num/=2;
    } while(num>0);
    binary[index] = '\0';
    int length = strlen(binary);
    for (int i=0;i<length/2;i++) 
	{
        char temp = binary[i];
        binary[i] = binary[length-i-1];
        binary[length-i-1] = temp;
    }
    return binary;
}


void initializeCacheSimulator(CacheSimulator* simulator,int memory_size,int cache_size,int block_size,int size) 
{
    simulator->memory_size = memory_size;
	simulator->cache_size = cache_size;
    simulator->block_size = block_size;
    simulator->size = size;
	simulator->instrut_length = (int) log2(memory_size);
	simulator->index_bit = (int) log2(cache_size/block_size);
	simulator->tag_bit = (int) log2(memory_size/cache_size);
	simulator->offset_bit = (int) log2(block_size);
	simulator->index = (int *) malloc(simulator->size * sizeof(int));
    simulator->tag = (int *) malloc(simulator->size * sizeof(int));
    simulator->offset = (int *) malloc(simulator->size * sizeof(int));
	int a = (int) pow(2,simulator->index_bit);
    simulator->data = (int *) malloc(simulator->size * sizeof(int));
    simulator->hits = 0;
    simulator->misses = 0;
    simulator->hit = (int *) malloc(simulator->size * sizeof(int));
    simulator->miss = (int *) malloc(simulator->size * sizeof(int));
	simulator->h_or_m = (char *) malloc(simulator->size * sizeof(char));
	simulator->cache_index = (int *) malloc(a * sizeof(int));
	simulator->valid = (int *) malloc(a * sizeof(int));
	simulator->cache_tag = (int *) malloc(cache_size * sizeof(int));
	simulator->cache_data = (int *) malloc(a * sizeof(int));
	simulator->dirty = (int *) malloc(a * sizeof(int));

	for(int i=0;i<a;i++) 
	{
		simulator->cache_index[i] = i;
        simulator->valid[i] = 0;
        simulator->cache_tag[i] = 0;
		simulator->cache_data[i] = 0;
		simulator->dirty[i] = 0;
	}
	
    for(int i=0;i<size;i++) 
	{
        simulator->index[i] = -1;
		simulator->tag[i] = -1;
		simulator->offset[i] = -1;
		simulator->hit[i] = -1;
        simulator->miss[i] = -1;
		simulator->data[i] = -1;
	}
}

int dec(char* address_sequence)
{
	char *endptr;
    long result = strtol(address_sequence,&endptr,16);
    if(*endptr!='\0') 
	{
        printf("Enter a valid address: \n");
        exit(1);
    }
    return (int) result;
}

char* hex(int address_sequence,int size)
{
	char *hex_address = (char *) malloc(size * sizeof(char));
	if(hex_address == NULL) 
    {
		printf("Memory allocation failed.");
        exit(1);
    }
	snprintf(hex_address,size,"%X",address_sequence);
	return hex_address;	
}

void accessMemoryAddress(CacheSimulator* simulator,int address,int index) 
{
	 int index_value = (address>>simulator->offset_bit)%((int) pow(2,simulator->index_bit));
	 simulator->index[index] = index_value;
	 int tag_value = address>>(simulator->index_bit+simulator->offset_bit);
	 simulator->tag[index] = tag_value;
	 int mask = (1<<(simulator->offset_bit))-1;
	 int offset_value = address&mask;
	 simulator->offset[index] = offset_value;
	 simulator->data[index] = address/simulator->block_size;
	 if(simulator->valid[index_value] == 0)
	 {
		 simulator->valid[index_value] = 1;
		 simulator->cache_data[index_value] = simulator->data[index];
		 simulator->dirty[index_value] = 0;
		 simulator->miss[simulator->misses] = address;
		 simulator->cache_tag[index_value] = tag_value;
		 simulator->misses = (simulator->misses)+1;
		 simulator->h_or_m[index] = 'M';
	 }
	 else
	 {
		if(simulator->cache_tag[index_value]==tag_value)
		{
			simulator->hit[simulator->hits] = address;
			simulator->hits = (simulator->hits)+1;
			simulator->h_or_m[index] = 'H';
		}
		else
		{
			simulator->cache_data[index_value] = simulator->data[index];
			simulator->cache_tag[index_value] = tag_value;
			simulator->miss[simulator->misses] = address;
			simulator->cache_tag[index_value] = tag_value;
			simulator->misses = (simulator->misses)+1;
			simulator->h_or_m[index] = 'M';		
		}
	 }
}

void printSimulationResultDecimal(CacheSimulator* simulator,int dec[],int size) 
{
	  char header1[] = "Address";
      char header2[] = "Tag";
      char header3[] = "Index";
      char header4[] = "Offset";
      char header5[] = "Data (Block Number)";
      char header6[] = "Hit/Miss";
	  printf("+---------+-----+-------+--------+---------------------+----------+\n");
      printf("| %-7s | %-3s | %-5s | %-6s | %-19s | %-8s |\n", header1, header2, header3, header4, header5, header6);
      printf("+---------+-----+-------+--------+---------------------+----------+\n");
	  for (int i=0;i<size;i++)
		  printf("| %-7d | %-3d | %-5d | %-6d | %-19d | %-8c |\n",dec[i],simulator->tag[i],simulator->index[i],simulator->offset[i],simulator->data[i],simulator->h_or_m[i]);
	  printf("+---------+-----+-------+--------+---------------------+----------+\n\n");
}

void printSimulationResultHex(CacheSimulator* simulator,char * address,int i)
{
	  printf("| %-7s | %-3X | %-5X | %-6X | %-19X | %-8c |\n",address,simulator->tag[i],simulator->index[i],simulator->offset[i],simulator->data[i],simulator->h_or_m[i]);	
}

void printSimulationResultBinary(CacheSimulator* simulator,int dec[],int size)
{
	  char header1[] = "Address";
      char header2[] = "Tag";
      char header3[] = "Index";
      char header4[] = "Offset";
      char header5[] = "Data (Block Number)";
      char header6[] = "Hit/Miss";
	  printf("+----------------------+------------+------------+------------+----------------------+----------+\n");
      printf("| %-20s | %-10s | %-10s | %-10s | %-20s | %-8s |\n", header1, header2, header3, header4, header5, header6);
      printf("+----------------------+------------+------------+------------+----------------------+----------+\n");
	  for (int i=0;i<size;i++)
	  {
		  char* address = decimalToBinary(dec[i],20);
		  char* tag = decimalToBinary(simulator->tag[i],10);
		  char* index = decimalToBinary(simulator->index[i],10);
		  char* offset = decimalToBinary(simulator->offset[i],10);
		  char* data = decimalToBinary(simulator->data[i],20);
		  printf("| %-20s | %-10s | %-10s | %-10s | %-20s | %-8c |\n",address,tag,index,offset,data,simulator->h_or_m[i]);
	  }
	  printf("+----------------------+------------+------------+------------+----------------------+----------+\n\n\n");
}

void printCacheDec(CacheSimulator* simulator)
{
	  int a = (int) pow(2,simulator->index_bit);
	  char header1[] = "Index";
      char header2[] = "Valid";
      char header3[] = "Tag";
      char header4[] = "Data (Block Number)";
      char header5[] = "Dirty Bit";
	  printf("+-------+-------+-----+---------------------+-----------+\n");
      printf("| %-5s | %-5s | %-3s | %-19s | %-9s |\n", header1, header2, header3, header4, header5);
      printf("+-------+-------+-----+---------------------+-----------+\n");
	  for (int i=0;i<a;i++)
		  printf("| %-5d | %-5d | %-3d | %-19d | %-9d |\n",simulator->cache_index[i],simulator->valid[i],simulator->cache_tag[i],simulator->cache_data[i],simulator->dirty[i]);
	  printf("+-------+-------+-----+---------------------+-----------+\n\n");
}

void printCacheHex(CacheSimulator* simulator)
{
	  int a = (int) pow(2,simulator->index_bit);
	  char header1[] = "Index";
      char header2[] = "Valid";
      char header3[] = "Tag";
      char header4[] = "Data (Block Number)";
      char header5[] = "Dirty Bit";
	  printf("+-------+-------+-----+---------------------+-----------+\n");
      printf("| %-5s | %-5s | %-3s | %-19s | %-9s |\n", header1, header2, header3, header4, header5);
      printf("+-------+-------+-----+---------------------+-----------+\n");
	  for (int i=0;i<a;i++)
		  printf("| %-5X | %-5X | %-3X | %-19X | %-9X |\n",simulator->cache_index[i],simulator->valid[i],simulator->cache_tag[i],simulator->cache_data[i],simulator->dirty[i]);
	  printf("+-------+-------+-----+---------------------+-----------+\n\n");
}

void printCacheBinary(CacheSimulator* simulator)
{
	  int a = (int) pow(2,simulator->index_bit);
	  char header1[] = "Index";
      char header2[] = "Valid";
      char header3[] = "Tag";
      char header4[] = "Data (Block Number)";
      char header5[] = "Dirty Bit";
	  printf("+------------+-------+------------+----------------------+-----------+\n");
      printf("| %-10s | %-5s | %-10s | %-20s | %-9s |\n", header1, header2, header3, header4, header5);
      printf("+------------+-------+------------+----------------------+-----------+\n");
	  for (int i=0;i<a;i++)
	  {
		  char* index = decimalToBinary(simulator->cache_index[i],10);
		  char* tag = decimalToBinary(simulator->cache_tag[i],10);
		  char* data = decimalToBinary(simulator->cache_data[i],20);
		  printf("| %-10s | %-5d | %-10s | %-20s | %-9d |\n",index,simulator->valid[i],tag,data,simulator->dirty[i]);
	  }
	  printf("+------------+-------+------------+----------------------+-----------+\n\n\n");
}

void  printHitDec(CacheSimulator* simulator)
{
      for(int i=0;i<simulator->hits;i++)
		printf("%d \n",simulator->hit[i]);
      printf("\n");	
}

void printHitHex(CacheSimulator* simulator)
{
      for(int i=0;i<simulator->hits;i++)
		printf("%X \n",simulator->hit[i]);
      printf("\n");	
}

void printHitBinary(CacheSimulator* simulator)
{
      for(int i=0;i<simulator->hits;i++)
	  {
		  char *hit = decimalToBinary(simulator->hit[i],100);
		  printf("%s \n",hit);
	  }
      printf("\n\n");	
	
}

void  printMissDec(CacheSimulator* simulator)
{
      for(int i=0;i<simulator->misses;i++)
		printf("%d \n",simulator->miss[i]);
      printf("\n");	
}

void printMissHex(CacheSimulator* simulator)
{
      for(int i=0;i<simulator->misses;i++)
		printf("%X \n",simulator->miss[i]);
      printf("\n");	
}

void printMissBinary(CacheSimulator* simulator)
{
      for(int i=0;i<simulator->misses;i++)
	  {
		  char *miss = decimalToBinary(simulator->miss[i],100);
		  printf("%s \n",miss);
	  }
      printf("\n\n");	
	
}

void freeCache(CacheSimulator* simulator) 
{
    free(simulator);
}

int main() 
{
    int cache_size,block_size,memory_size,size,choice;   
    
	printf("Welcome to direct mapped cache simulator \n\n");
	printf("Direct mapped cache : A direct-mapped cache is a type of cache memory organization where each main memory block can be mapped to only one specific cache block. It is characterized by a one-to-one mapping between memory addresses and cache locations. When a memory block is accessed, it is placed in the cache at a predetermined location determined by a hashing function. If another memory block maps to the same cache location, it will overwrite the existing block. This simplicity makes direct-mapped caches efficient in terms of hardware implementation but can lead to cache conflicts when multiple memory blocks map to the same cache location, causing performance degradation. \n\n");
    printf("Write policies used : \n1.Write Back \n2.Write On Allocate \n\n");
    printf("Enter memory size in bytes (power of 2) : ");
    scanf("%d",&memory_size);
	
	while(isPowerOf2(memory_size)!=1)
	{
		printf("Enter a valid memory size in bytes (power of 2) : ");
	    scanf("%d",&memory_size);
	}
	
    printf("Enter cache size in bytes (power of 2) : ");
    scanf("%d",&cache_size);
	
	while(isPowerOf2(cache_size)!=1 || cache_size>memory_size/2)
	{
		printf("Enter a valid cache size in bytes (power of 2) : ");
	    scanf("%d",&cache_size);
	}
	
    printf("Enter block size in bytes (power of 2) : ");
    scanf("%d",&block_size);
	
	while(isPowerOf2(block_size)!=1 || block_size+cache_size>memory_size)
	{
		printf("Enter a valid block size in bytes (power of 2) :");
	    scanf("%d",&block_size);
	}
	
    printf("\nEnter number of memory addresses : ");
    scanf("%d",&size);
	while(size<=0)
	{
		printf("Enter a valid number of memory addresses : ");
        scanf("%d",&size);
	}
	
    printf("Enter which type of addressing you want : \n1.Hexadecimal Addressing \n2.Decimal Addressing\n");
	scanf("%d",&choice);
	
	while(choice!=1&&choice!=2)
	{
		printf("Enter a valid addressing mode \n");
		printf("Enter which type of addressing you want : \n1.Hexadecimal Addressing \n2.Decimal Addressing \n");
	    scanf("%d",&choice);
	}
	
    printf("Enter memory address sequence of load instructions : \n");
	int loc = ceil((log2(memory_size))/4);
	int d_address;
	int dec_address[size];
	char h_address[size][loc+1];
	char hex_address[loc+1];
    int index = 0;
    if(choice==1)
	{
		while(index<size && scanf("%s",hex_address))
		{
			int a = dec(hex_address);
			if(a<memory_size && strlen(hex_address)<loc+1 && a>=0)
			{
				strcpy(h_address[index],hex_address);
		        dec_address[index] = a;
                index++;			
	    	}
			else
				printf("Enter a valid address\n");
    }
	}
    else
    {
		while(index<size && scanf("%d",&d_address))
		{
			if(d_address<memory_size&&d_address>=0)
	     	{
				dec_address[index] = d_address;
			    strcpy(h_address[index],hex(d_address,loc+1));
                index++;		
	    	}
			else
				printf("Enter a valid address\n");
        }
	}
	
    CacheSimulator simulator;
    initializeCacheSimulator(&simulator,memory_size,cache_size,block_size,size);
	printf("\n");
	
    for(int i=0;i<size;i++) 
		accessMemoryAddress(&simulator,dec_address[i],i);
	
	printf("\n\nFinal Report : \n\n\n");
	
	printf("All address configuration : \n\n");
	printf("Decimal : \n");
    printSimulationResultDecimal(&simulator,dec_address,size);
	printf("Hexadecimal : \n");
    char header1[] = "Address";
    char header2[] = "Tag";
    char header3[] = "Index";
    char header4[] = "Offset";
    char header5[] = "Data (Block Number)";
    char header6[] = "Hit/Miss";
	printf("+---------+-----+-------+--------+---------------------+----------+\n");
    printf("| %-7s | %-3s | %-5s | %-6s | %-19s | %-8s |\n", header1, header2, header3, header4, header5, header6);
    printf("+---------+-----+-------+--------+---------------------+----------+\n");
	for(int i=0;i<size;i++)
		printSimulationResultHex(&simulator,h_address[i],i);
	printf("+---------+-----+-------+--------+---------------------+----------+\n\n");
	printf("Binary : \n");
    printSimulationResultBinary(&simulator,dec_address,size);
	
	printf("Final cache configuration : \n\n");
	printf("Decimal : \n");
	printCacheDec(&simulator);
	printf("Hexadecimal : \n");
	printCacheHex(&simulator);
	printf("Binary : \n");
	printCacheBinary(&simulator);
	
	printf("Hit Addresses :\n\n");
	printf("Decimal : \n");
	printHitDec(&simulator);
	printf("Hexadecimal : \n");
	printHitHex(&simulator);
	printf("Binary : \n");
	printHitBinary(&simulator);
	
	printf("Miss Addresses :\n\n");
	printf("Decimal : \n");
	printMissDec(&simulator);
	printf("Hexadecimal : \n");
	printMissHex(&simulator);
	printf("Binary : \n");
	printMissBinary(&simulator);
	
	printf("Final Statistics :\n\n");
	printf("Memory size : %d\n",simulator.memory_size);
	printf("Cache size : %d\n",simulator.cache_size);
	printf("Block size : %d\n",simulator.block_size);
	printf("Number of hits :%d\n",simulator.hits);
	printf("Hit rate : %f%%\n",(float) simulator.hits/(float) size);
	printf("Number of misses :%d\n",simulator.misses);
	printf("Miss rate : %f%%\n",(float) simulator.misses/(float) size);
	
    freeCache(&simulator);
    return 0;
}