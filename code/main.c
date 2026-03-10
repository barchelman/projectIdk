
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

#define MAX_SIZE 1000






char* encrypt(char *text){
    unsigned key;
    if(text == NULL)
        return NULL;

    printf("Enter an encryption key: ");
    scanf("%u", &key);

    key = key % 256;   // prevent huge shifts

    for(int i = 0; text[i] != '\0'; i++){

        unsigned char value = (unsigned char)text[i];

        value = (value + key) % 256;   // shift ASCII safely

        text[i] = (char)value;
    }

    return text;
}


unsigned decryptValidation(){
unsigned decryptpass;
printf("\nEnter Decrypt key:  ");
scanf("%u",&decryptpass);
return decryptpass;
}

char* getTextFromFile() {
    FILE *file = fopen("str.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n","str.txt");
        return NULL;
    }

    // go to the end to get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);  // go back to beginning

    if (fileSize <= 0) {
        fclose(file);
        return NULL;
    }

    // allocate memory for text (+1 for null terminator)
    char *text = (char*)malloc(fileSize + 1);
    if (text == NULL) {
        fclose(file);
        printf("Memory allocation failed\n");
        exit(1);
    }

    fread(text, 1, fileSize, file);
    text[fileSize] = '\0';  // null terminate

    fclose(file);
    return text;  // caller must free
}



char* decrypt(char *text, unsigned key){
    if(text == NULL)
        return NULL;

    key = key % 256;  // ensure key is within 0-255 range

    for(int i = 0; text[i] != '\0'; i++){
        unsigned char value = (unsigned char)text[i];

        // reverse the shift safely
        value = (value + 256 - key) % 256;

        text[i] = (char)value;
    }

    return text;
}

void store (char* text){
FILE* fptr;
fptr = fopen("str.txt", "a");
    // checking if the file is 
    // opened successfully
    if (fptr == NULL) {
        printf("The file is not opened.");
    
    }
    else{
        

        fputs(text,fptr);
      
        printf("\n\nText saved successfully to %s\n", "str.txt");
                    }  
        
        fclose(fptr);
    



}


int entryPoint(){
    int entrySelectionNum;
    printf("Enter a proper number\n");
    printf("Input text--->1\n");
    printf("Read text---->2\n");
    printf("Enter Your Selection:");
    scanf("%i",&entrySelectionNum);
    return entrySelectionNum;
}

char* inputText(){

    char *text = NULL;
    size_t totalSize = 0;

    char buffer[1024];

    getchar(); // clear leftover newline

    printf("Write your text.\n");
    printf("Type END on a new line to finish.\n\n");

    while(1){

        fgets(buffer, sizeof(buffer), stdin);

        if(strcmp(buffer,"END\n")==0)
            break;

        size_t len = strlen(buffer);

        char *temp = realloc(text, totalSize + len + 1);
            if(temp == NULL){
                free(text);
                printf("Memory allocation failed\n");
                exit(1);}
            text = temp;

        memcpy(text + totalSize, buffer, len);

        totalSize += len;

        text[totalSize] = '\0';
    }

    return text;   // return the string
    
}
    
    //TODO: add a system so that you can write again
    //TODO: confirm that user wants to save




int main()
{
    int selection = entryPoint();
    switch (selection) {
        case 1:{
            // Input text, encrypt, and save
            char *text = inputText();
            encrypt(text);
            store(text);
            free(text);
            break;
        }
        case 2:{
            // Get decryption key
            unsigned decryptKey = decryptValidation();

            // Read text from file
            char* text = getTextFromFile();
            if(text == NULL){
                printf("No text to decrypt.\n");
                break;
            }

            // Decrypt text
            decrypt(text, decryptKey);

            // Print decrypted text
            printf("\nDecrypted text:\n%s\n", text);

            free(text);
            break;
        }
        default: {
            printf("Invalid selection.\n");
            break;
        }
    }
    return 0;
}