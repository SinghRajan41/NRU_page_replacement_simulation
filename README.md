# NRU_page_replacement_simulation

# NRU Page Replacement Algorithm Simulation

## 📖 Introduction to Not Recently Used (NRU) Algorithm
The **Not Recently Used (NRU)** page replacement algorithm is a memory management strategy that prioritizes evicting pages that have not been accessed or modified recently. It classifies pages into four categories based on two bits:
- **Referenced Bit**: Indicates if the page was accessed recently.
- **Modified Bit**: Indicates if the page was modified.

Pages are grouped into classes:
1. **Class 0**: Not referenced, not modified (lowest priority for eviction).
2. **Class 1**: Not referenced, modified.
3. **Class 2**: Referenced, not modified.
4. **Class 3**: Referenced, modified (highest priority for eviction).

The algorithm selects a victim page from the lowest non-empty class, balancing efficiency and simplicity.

## 🚀 Project Overview
This project simulates the NRU page replacement algorithm in a virtual memory environment. It tracks:
- **Page Faults**: When a requested page is not in RAM.
- **Page Hits**: When the page is already loaded in RAM.

Key metrics like fault rate and hit rate are calculated after 5,000 simulated memory references.

## 🧩 Components and Classes

### 1. **Core Simulation Classes**
#### `memory_management_unit` (MMU)
- Translates virtual addresses to physical addresses.
- Triggers page faults via the OS if a page is not in RAM.
- **Key Method**: `read_word_at()`.

#### `operating_system`
- Handles page faults by loading pages from disk to RAM.
- Uses NRU to evict pages when RAM is full.
- **Key Method**: `handle_page_fault()`.

#### `not_recently_used_page_replacement`
- Implements the NRU algorithm.
- **Key Method**: `get_victim_page()` to select a page for eviction.

### 2. **Memory Representation**
#### `non_volatile_memory` (Disk)
- Simulates secondary storage (e.g., a file `large_file.txt`).
- **Key Methods**: `read_page()`, `write_page()`.

#### `volatile_memory` (RAM)
- Represents physical memory with limited page frames.
- **Key Methods**: `read_page()`, `write_page_in_empty_space()`.

### 3. **Page Management**
#### `page_table` and `page_table_entry`
- **Page Table**: Maps virtual pages to physical frames.
- **Page Table Entry**: Stores metadata (present bit, referenced bit, modified bit, permissions).

#### `page`
- Represents a memory page with a fixed size (default: 64 words).

### 4. **Simulation Driver**
#### `main.cpp`
- Initializes virtual memory, disk, RAM, and the page table.
- Generates 5,000 random memory references via a simulated CPU.
- Outputs page fault and hit statistics.

## 🔄 Workflow
1. **Initialization**:
   - Disk is initialized with data from `large_file.txt`.
   - RAM and page tables are set up.

2. **Memory Reference**:
   - CPU generates a virtual address.
   - MMU checks the page table:
     - **Page Hit**: Directly reads from RAM.
     - **Page Fault**: OS loads the page from disk, evicting a page via NRU if needed.

3. **NRU Execution**:
   - Pages are classified into 4 categories.
   - The lowest-class page is evicted (e.g., a non-referenced, non-modified page).

## 📊 Metrics Collected
After 5,000 references:
