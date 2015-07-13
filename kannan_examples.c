#include <stdio.h>
#include <stdlib.h>

// *v --> assuming 'v' is an address, return the thing at that address
// &v --> returns the address of 'v'

typedef struct {
    char* line1;
    char* line2;
    int zipCode;
} Address;

typedef struct {
    char* name;
    int age;
    //Address address;
} Person;

void initPerson(Person* pPerson)
{
    (*pPerson).name = "Missy";
    (*pPerson).age = 22;
}

Person* makePerson()
{
    Person* personAddress = malloc(sizeof(Person));
    initPerson(personAddress);
    return personAddress;
}

void addYearToAge(Person* pPerson)
{
    (*pPerson).age += 1;
}

int main(int argc, char** argv)
{
    Person* pPerson = makePerson();
    
    addYearToAge(pPerson);
    
    printf("name = %s\n", (*pPerson).name);
    printf("age = %d\n", pPerson->age);
  
    free(pPerson);
}


// ----------------------------------------------------------------------

 #include <stdio.h>
#include <stdlib.h>

// *v --> assuming 'v' is an address, return the thing at that address
// &v --> returns the address of 'v'

int main(int argc, char** argv)
{
    char* p = malloc(sizeof(char)*1000);
  
    *p = 'M';
    *(p+1) = 'i';
    *(p+2) = 's';
    *(p+3) = 's';
    *(p+4) = 'y';
    *(p+5) = '\0';
  
    char stuff[1000];
    char* q = &stuff[0];

    q[0] = 'M';
    q[1] = 'i';
    q[2] = 's';
    q[3] = 's';
    q[4] = 'y';
    q[5] = '\0';
  
    printf("%s %s\n", p, q);
    printf("%c\n", p[3]);
    printf("%c\n", 3[q]);
  
    free(p);
}
