# Example Input and Output

---

## Example Input:

- **Cache Size**: 32
- **Memory Size**: 65536
- **Block Size**: 16
- **Number of Addresses**: 13
- **Mode of Addressing**: 
  - 1. Hexadecimal
- **Addresses**: 
  - 1 1 134 212 1 135 213 162 161 2 44 41 221

---

## Example Output:

**Welcome to Direct Mapped Cache Simulator**

### Direct Mapped Cache:

A direct-mapped cache is a type of cache memory organization where each main memory block can be mapped to only one specific cache block. It is characterized by a one-to-one mapping between memory addresses and cache locations. When a memory block is accessed, it is placed in the cache at a predetermined location determined by a hashing function. If another memory block maps to the same cache location, it will overwrite the existing block. This simplicity makes direct-mapped caches efficient in terms of hardware implementation but can lead to cache conflicts when multiple memory blocks map to the same cache location, causing performance degradation.

### Write Policies Used:
1. Write Back
2. Write On Allocate

---


Enter memory size in bytes (power of 2) : 65536  
Enter cache size in bytes (power of 2) : 32  
Enter block size in bytes (power of 2) : 16  

Enter number of memory addresses : 13  
Enter which type of addressing you want :  
1. Hexadecimal Addressing  
2. Decimal Addressing  
**1**

Enter memory address sequence of load instructions:  
1  
1  
134  
212  
1  
135  
213  
162  
161  
2  
44  
41  
221  

---

## Final Report:

### All Address Configuration:

#### Decimal:

| Address | Tag | Index | Offset | Data (Block Number) | Hit/Miss |
|---------|-----|-------|--------|---------------------|----------|
| 1       | 0   | 0     | 1      | 0                   | M        |
| 1       | 0   | 0     | 1      | 0                   | H        |
| 308     | 9   | 1     | 4      | 19                  | M        |
| 530     | 16  | 1     | 2      | 33                  | M        |
| 1       | 0   | 0     | 1      | 0                   | H        |
| 309     | 9   | 1     | 5      | 19                  | M        |
| 531     | 16  | 1     | 3      | 33                  | M        |
| 354     | 11  | 0     | 2      | 22                  | M        |
| 353     | 11  | 0     | 1      | 22                  | H        |
| 2       | 0   | 0     | 2      | 0                   | M        |
| 68      | 2   | 0     | 4      | 4                   | M        |
| 65      | 2   | 0     | 1      | 4                   | H        |
| 545     | 17  | 0     | 1      | 34                  | M        |

#### Hexadecimal:

| Address | Tag | Index | Offset | Data (Block Number) | Hit/Miss |
|---------|-----|-------|--------|---------------------|----------|
| 1       | 0   | 0     | 1      | 0                   | M        |
| 1       | 0   | 0     | 1      | 0                   | H        |
| 134     | 9   | 1     | 4      | 13                  | M        |
| 212     | 10  | 1     | 2      | 21                  | M        |
| 1       | 0   | 0     | 1      | 0                   | H        |
| 135     | 9   | 1     | 5      | 13                  | M        |
| 213     | 10  | 1     | 3      | 21                  | M        |
| 162     | B   | 0     | 2      | 16                  | M        |
| 161     | B   | 0     | 1      | 16                  | H        |
| 2       | 0   | 0     | 2      | 0                   | M        |
| 44      | 2   | 0     | 4      | 4                   | M        |
| 41      | 2   | 0     | 1      | 4                   | H        |
| 221     | 11  | 0     | 1      | 22                  | M        |

#### Binary:

| Address              | Tag        | Index      | Offset     | Data (Block Number)  | Hit/Miss |
|----------------------|------------|------------|------------|----------------------|----------|
| 1                    | 0          | 0          | 1          | 0                    | M        |
| 1                    | 0          | 0          | 1          | 0                    | H        |
| 100110100            | 1001       | 1          | 100        | 10011                | M        |
| 1000010010           | 10000      | 1          | 10         | 100001               | M        |
| 1                    | 0          | 0          | 1          | 0                    | H        |
| 100110101            | 1001       | 1          | 101        | 10011                | M        |
| 1000010011           | 10000      | 1          | 11         | 100001               | M        |
| 101100010            | 1011       | 0          | 10         | 10110                | M        |
| 101100001            | 1011       | 0          | 1          | 10110                | H        |
| 10                   | 0          | 0          | 10         | 0                    | M        |
| 1000100              | 10         | 0          | 100        | 100                  | M        |
| 1000001              | 10         | 0          | 1          | 100                  | H        |
| 1000100001           | 10001      | 0          | 1          | 100010               | M        |

---

### Final Cache Configuration:

#### Decimal:

| Index | Valid | Tag | Data (Block Number) | Dirty Bit |
|-------|-------|-----|---------------------|-----------|
| 0     | 1     | 17  | 34                  | 0         |
| 1     | 1     | 16  | 33                  | 0         |

#### Hexadecimal:

| Index | Valid | Tag | Data (Block Number) | Dirty Bit |
|-------|-------|-----|---------------------|-----------|
| 0     | 1     | 11  | 22                  | 0         |
| 1     | 1     | 10  | 21                  | 0         |

#### Binary:

| Index      | Valid | Tag        | Data (Block Number)  | Dirty Bit |
|------------|-------|------------|----------------------|-----------|
| 0          | 1     | 10001      | 100010               | 0         |
| 1          | 1     | 10000      | 100001               | 0         |

---

### Hit Addresses:

#### Decimal:
1  
1  
353  
65  

#### Hexadecimal:
1  
1  
161  
41  

#### Binary:
1  
1  
101100001  
1000001  

---

### Miss Addresses:

#### Decimal:
1  
308  
530  
309  
531  
354  
2  
68  
545  

#### Hexadecimal:
1  
134  
212  
135  
213  
162  
2  
44  
221  

#### Binary:
1  
100110100  
1000010010  
100110101  
1000010011  
101100010  
10  
1000100  
1000100001  

---

### Final Statistics:

- **Memory Size**: 65536  
- **Cache Size**: 32  
- **Block Size**: 16  
- **Number of Hits**: 4  
- **Hit Rate**: 0.307692%  
- **Number of Misses**: 9  
- **Miss Rate**: 0.692308%