# Knuth-Morris-Pratt string matching 
the compiled kmp executable takes 2 lines from stdin. First line should contain the pattern to be searched and second line should contain the text where pattern is being searched in. As output gives an valid shift at each line and the end reports the number of total valid shifts

For example, running the following lines
```
make kmp
./kmp
abac
ababac
```
gives the output:
```
2

total matches: 1
```

