## Encapsulation in C

Sources: [educba](https://www.educba.com/encapsulation-in-c/), [Stackoverflow](https://stackoverflow.com/questions/29119284/data-encapsulation-in-c)

```C
// contact.h 

#ifndef CONTACT_H_
#define CONTACT_H_

typedef struct Contact Contact_t;
Contact_t * contact_init();

void delete_contact( Contact_t * this);
void contact_set(Contact_t *this, int mobile, int zip);
int contact_get_mobile(Contact_t *this);
int contact_get_zip(Contact_t *this);

#endif // CONTACT_H_
```

```C
// contact.c

#ifndef CONTACT_H_
typedef struct Contact
{
    int mobile;
    int zipcode;
}Contact_t;

// "constructor", allocate memory
Contact_t * contact_init()
{
    Contact_t * this;
    this = malloc(sizeof(Contact_t));
    return( this );
}

// "destructor", free memory
void delete_contact( Contact_t * this)
{
    free(this); 
}

void contact_set(Contact_t *this, int mobile, int zip)
{
    this->mobile = mobile;
    this->zipcode = zip;
}

int contact_get_mobile(Contact_t *this)
{
    return this->mobile;
}

int contact_get_zip(Contact_t *this)
{
    return this->zipcode;
}

#endif // CONTACT_H_
```

```C
// main 

int main()
{
    Contact_t * thomas;

    thomas = contact_init();
    contact_set(thomas, 99887766, 8500);

    printf("thomas, mobile: %d, zip: %d\n", 
        contact_get_mobile(thomas),
        contact_get_zip(thomas));

    delete_contact(thomas);
    return 0;
}

#endif // CONTACT_H_
```



