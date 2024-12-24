# Direct Mapped Cache Simulator

A **C-based simulator** implementing a **direct-mapped cache** with **write-back** and **write-on-allocate** policies.

---

## 📋 Overview

This project simulates the behavior of a **direct-mapped cache memory system**, demonstrating cache hits and misses based on a sequence of memory accesses. Written in C, it offers a detailed look into how a direct-mapped cache operates, with various configuration options and performance metrics.

### 🔑 Key Features

- **Direct Mapping**: One-to-one mapping between memory addresses and cache locations.
- **Flexible Input Options**:
  - Supports both hexadecimal and decimal addressing.
  - Configurable cache, memory, and block sizes.
  - Multiple address input formats (space-separated or line-separated).
- **Write Policies**:
  - **Write-back**
  - **Write-on-allocate**
- **Detailed Analysis**:
  - Hit/Miss tracking
  - Cache state visualization
  - Address breakdown (Tag, Index, Offset)
  - Multiple output formats (Decimal, Hexadecimal, Binary)

---

## 🛠 How It Works

### 🔢 Address Breakdown

- **Instruction Length**: `log₂(memory size)`
- **Number of Tag Bits**: `log₂(memory size / cache size)`
- **Number of Index Bits**: `log₂(cache size / block size)`
- **Number of Offset Bits**: `log₂(block size)`
- **Number of Dirty Bits**: 1 bit

### 📊 Address Calculations

- **Addresses**: `address < 2^(instruction length)` or `address < memory size`
- **Tag Value**: `address >> (index_bits + offset_bits)`
- **Index Value**: `(address >> offset_bits) % 2^(index_bits)`
- **Offset Value**: `address & ((1 << offset_bits) - 1)`
- **Block Number**: `address / block_size`
- **Dirty Bit Value**: 0 for load, 1 for store

### ⚙️ Cache Operation Flow

1. The requested **address** is broken down into **Tag**, **Index**, and **Offset**.
2. The **cache table** at the corresponding **Index** is examined.
3. If the **valid bit** of the index is 0, a **cache miss** occurs.
4. If the tag matches, a **cache hit** is recorded.
5. On a **cache miss**, the data is retrieved from **main memory**.

---

## 📥 Input Requirements

- **Memory Size** (bytes, must be a power of 2)
- **Cache Size** (bytes, must be a power of 2)
- **Block Size** (bytes, must be a power of 2)
- **Number of Memory Addresses**
- **Addressing Mode**:
  - `1`: Hexadecimal
  - `2`: Decimal
- **Address Sequence**:
  - Space-separated
  - Line-separated

---

## 📊 Output Format

The simulator provides comprehensive output, including:

### 1. **Address Configuration**
   - **Formats**: Decimal, Hexadecimal, Binary
   - **Details**: Tag, Index, Offset, Block Number, and Hit/Miss status

### 2. **Cache Configuration**
   - **Current Cache State**:
     - Valid bits
     - Dirty bits
     - Stored tags and data

### 3. **Performance Statistics**
   - **Hit Count** and **Hit Rate**
   - **Miss Count** and **Miss Rate**
   - **Hit/Miss Address Sequences**

---

## 📝 Example Input and Output

For a detailed example of input and output, follow this [link](https://github.com/shivadarshan-devadiga/DIRECT-MAPPED-CACHE-USING-C/example.md).

---

## 🛠 Requirements

To run the simulator, you will need:

- **C Compiler**
- **Math Library** (`-lm` flag required for compilation)
- **Standard C Libraries**:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `math.h`

---

## 🚀 Building and Running

1. **Compile the program using a C compiler**:
   ```bash
   gcc direct_mapped_cache_simulator.c -o cache_simulator -lm
   ```

2. **Run the executable**:
   ```bash
   ./cache_simulator
   ```

---

## 👨‍💻 Contributors

- [Shivadarshan](https://github.com/shivadarshan-devadiga)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🛠 Feedback and Support

For any feedback or support regarding this project, please [open an issue](https://github.com/shivadarshan-devadiga/DIRECT-MAPPED-CACHE-USING-C/issues) on GitHub.

---

Thank you for exploring the **Direct Mapped Cache Simulator**!
