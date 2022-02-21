#include <stdio.h>
#include <stdlib.h>


int* kmp_search(char* pat, char* txt);
int* compute_prefix_array(char* pat, size_t n);

int main(){

    char* pattern;
    char* text;
    char c;

    int i, tmp_size;

    i = 0;
    tmp_size = 64;

    pattern = malloc(tmp_size* sizeof(char));
    while( (c =getc(stdin) ) != '\n'){
        pattern[i++] = c;
        if(i >=tmp_size){
           tmp_size += tmp_size; 
           pattern = realloc(pattern, tmp_size * sizeof(char));
        }
    }

    pattern[i] = '\0';

    i = 0;
    tmp_size = 64;

    text = malloc(tmp_size* sizeof(char));
    while( (c =getc(stdin) ) != '\n'){
        text[i++] = c;
        if(i >=tmp_size){
           tmp_size += tmp_size; 
           text = realloc(text, tmp_size * sizeof(char));
        }
    }

    text[i] = '\0';

    int* matches = kmp_search(pattern, text);
    free(pattern);
    free(text);

    int total_matches = 0;
    for(i=0; matches[i] != -1; i++){
        printf("%d\n", matches[i]);
        total_matches++;
    }
    printf("\ntotal matches: %d\n", total_matches);
    //notice that if there are no matches we just print a new line and nothing else

    free(matches);
    return 0;
}

/*
    this function returns an array of valid shifts in string txt for pattern pat. Array is terminated with -1 to indicate there is no other valid matches.(just like '\0' for strings but we use -1 here since we can not have -1 as index). Both pat and txt must be null terminated char arrays

    Notes: but user responsible for freeing the returned array when it is not needed anymore
    EXAMPLES:    
        txt = "abcababzxczx"
        pat = "ab"
        
        return value is the address of the allocated array containing values 
        {0,3,5, -1}

        txt = "kkkkkkkkk"
        pat = "555"

        returns the addres of dynamically allocated array {-1}
*/
int* kmp_search(char* pat, char* txt){

    int i, j;
    int m;
    
    for(m = 0; pat[m] != '\0'; m++) 
        ;
    int* lpa = compute_prefix_array(pat, m);

    size_t size = 64;// size of return array (terminating -1 included)
    size_t next_shift = 0;// index of the next valid shift
    int* valid_shifts = (int*)calloc(size, sizeof(int));
    for(i = 0, j = -1; txt[i] != '\0'; i++){

        while(j> -1 && txt[i] != pat[j+1]){
            j = lpa[j];
        }
        if(txt[i] == pat[j+1]){
            j++;
        }
        if(j+1 == m){
            //TODO report i-j
            if( !(next_shift < size-1)){
                size *= 2;
                valid_shifts = realloc(valid_shifts, size * sizeof(int)); 
            }
            valid_shifts[next_shift++] = i-j;

            j = lpa[j];
        }

    }

    if( !(next_shift < size-1)){
        size++;
        valid_shifts = realloc(valid_shifts, size * sizeof(int)); 
    }
    valid_shifts[next_shift] = -1;//terminating -1

    free(lpa);
    return valid_shifts;
}

int* compute_prefix_array(char* pat, size_t m){

    int* prefix_array = calloc(m, sizeof(int));

    int k = -1;
    prefix_array[0] = k;
    for(int q=1; q<m; q++){
        while(k > -1 && pat[k+1] != pat[q]){
            k = prefix_array[k];
        }
        if(pat[k+1] == pat[q]){
            k++;
        }
        prefix_array[q] = k;
    }

    return prefix_array;
}
