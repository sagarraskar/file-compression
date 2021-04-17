# file-compression

compressing a file using the "Huffman algorithm".
"Huffman algorithm" uses a tree data structure to reduce the size of 
the file.
It uses the frequency of the characters to assign new values to it in place 
of its own 8-bit ASCII value. This reduces the memory occupied 
by each of the character in the computer. So, instead of occupying the original 
1 byte in the memory it occupies the designated number of bits assigned to it.
This reduces the size of the file.

Steps to build Huffman Tree
Input is an array of unique characters along with their frequency of occurrences and output is Huffman Tree.

1. Create a leaf node for each unique character and build a min heap of all leaf nodes 
(Min Heap is used as a priority queue. The value of frequency field is used to compare 
two nodes in min heap. Initially, the least frequent character is at root).

2. Extract two nodes with the minimum frequency from the min heap.

3. Create a new internal node with a frequency equal to the sum of the two nodes 
frequencies. Make the first extracted node as its left child and the other extracted 
node as its right child. Add this node to the min heap.

4. Repeat steps#2 and #3 until the heap contains only one node. The remaining node 
is the root node and the tree is complete.

Give name 0 to the left child and 1 to the right child.
Now to create the codes for respective character traverse the tree from the root node to 
the respective character encountering respective 0 and 1 and keep forming a code until you 
reach the character you require.

Now in the compressed file, the new designated value to the character will be written 
in place the original 8-bit ASCII value of the character. 
The original file cannot be obtained unless we have the designated values to the characters 
that we obtained from the Huffman Tree. Hence we also will have to write the table of the codes 
in the compressed file to obtain the original file. 

To obtain the original file we need to compare every bit to the code in the table to replace it with 
the original 8-bit ASCII value, thus obtaining the original character from the file. In such way, we 
keep on replacing every respective code with the respective ASCII value to the character from the 
table.

Doing such we obtain the original, file that we had compressed. Thus, decompression is successful.

The program will run as follows:
## here the first two commands are for compression and
## later two demonstrate decompression
```
$ ./program -c1 <file> <compressed-file-name>
$ ./program -c2 <file> <compressed-file-name>
$ ./program -uc1 <compressed-file> <uncompressed-file>
$ ./program -uc2 <compressed-file> <uncompressed-file>
```
