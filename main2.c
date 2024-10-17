/*
Darel Gomez
COP3502
February 20, 2024 
*/

#define NAME_LENGTH 20
#define MAX_PEOPLE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, p; // number of people attending and number of pairings who do not want to sit next to each other
char names[MAX_PEOPLE][NAME_LENGTH]; // list of names of people attending [sorted alphabetical]
int popcorn[MAX_PEOPLE];  // contains 1(true) if they bought popcorn or 0(false) for each person's index that bought popcorn
int pairings[MAX_PEOPLE][2]; // contains index pairings of people who can't sit next to each other

// Precondition: Input has been correctly stored in n, names, popcorn, and pairings 
// Postcondition: Prints the first vaid permutation found
//                - perm is an array to keep track of the permutation
//                - used is a helper array with a 1 or 0 in each element, denoting if a person has been used previously in the permutaiton
//                - k is an int to keep track of how many people have been used in the permutation
void permutations(int perm[MAX_PEOPLE], int used[MAX_PEOPLE], int k);

// Precondition: A permutation has been generated
// Postcondition: Returns 1(True) or 0(False) if every person without popcorn is sitting next to someone with popcorn
int valid_popcorn(int perm[MAX_PEOPLE]);

// Precondition: A permutation has been generated
// Postcondition: Returns 1(True) or 0(False) if none of the pairs of people who can't sit next to each other are sitting next to each other
int valid_pairings(int perm[MAX_PEOPLE]);

// Precondition: A permutation has been generated
// Postcondition: Returns 1(True) or 0(False) if the permutation is valid
int valid_permutation(int perm[MAX_PEOPLE]);

// Precondition: A name that exists in names array has been given
// Postcondition: Returns the index of that name, or -1 if not found.
int getindex(char name[MAX_PEOPLE]);

int main() {
    scanf("%d %d", &n, &p);

    for(int i = 0; i < n; i++) {
        scanf("%s %d", names[i], &popcorn[i]);
    }
    for(int i = 0; i < p; i++) {
        char n1[NAME_LENGTH], n2[NAME_LENGTH];
        scanf("%s %s", n1, n2);
        int i1 = getindex(n1);
        int i2 = getindex(n2);
        if(i1 != -1 && i2 != -1) {
            pairings[i][0] = i1;
            pairings[i][1] = i2;
        }
        else {
            printf("Name in [pairings] not found in [names]. Pair: %s %s\n", n1, n2);
            exit(-1);
        }
    }
    int perm[MAX_PEOPLE], used[MAX_PEOPLE];
    for(int i = 0; i < n; i++) {
        used[i] = 0;
    }

    permutations(perm, used, 0);
    printf("No valid permutation found.\n");

    return 0;
}

void permutations(int perm[MAX_PEOPLE], int used[MAX_PEOPLE], int k) {
    if(k == n) {
        if(valid_permutation(perm)) {
            for(int i = 0; i < n; i++) {
                printf("%s\n", names[perm[i]]);
            }
            exit(0);
        }
        return;
    }
    int count = 0;
    for(int i = 0; i<n; i++) {
        if(!used[i]) {
            used[i] = 1;
            perm[k] = i;
            permutations(perm, used, k+1);
            used[i] = 0;
        }
    }
}

int valid_popcorn(int perm[MAX_PEOPLE]) {
    for(int i = 0; i < n; i++) {
        if(popcorn[perm[i]]) {
            continue;
        }
        else if((i != n-1 && popcorn[perm[i+1]]) || (i != 0 && popcorn[perm[i-1]])) {
            continue;
        }
        else {
            return 0;
        }
    }
    return 1;
}

int valid_pairings(int perm[MAX_PEOPLE]) {
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < n; j++) {
            if(perm[j] == pairings[i][0]) {
                if(perm[j+1] == pairings[i][1]) {
                    return 0;
                }
                else {
                    break;
                }
            }
            else if(perm[j] == pairings[i][1]) {
                if(perm[j+1] == pairings[i][0]) {
                    return 0;
                }
                else {
                    break;
                }
            }
        }
    }
    return 1;
}

int valid_permutation(int perm[MAX_PEOPLE]) {
    return (valid_popcorn(perm) && valid_pairings(perm));
}

int getindex(char name[MAX_PEOPLE]) {
    for(int i = 0; i < n; i++) {
        if(!strcmp(name, names[i])) return i;
    }
    return -1;
}