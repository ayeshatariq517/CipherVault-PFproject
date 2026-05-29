#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define max 30

void Register();
int Login(char *user);
void Encrypt(char password[], char encryptedPass[]);
void Decrypt(char encryptedPass[], char decryptedPass[]);
void CheckPasswordStrength(const char password[]);
int IsValidPassword(char password[]); 
void AddPassword(char username[]); 
void ViewPassword(char username[]);

// Registering the user  
void Register() 
{
    char username[max], password[max], fileUsername[max];

    FILE *file = fopen("users.txt", "a+"); // Open in read and append mode

    if (file == NULL) 
    {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\tEnter username: ");
    scanf("%s", username);

    // Check for duplicate usernames
    while (fscanf(file, "%[^-]-%*s\n", fileUsername) != EOF) 
    {
        if (strcmp(username, fileUsername) == 0) 
        {
            printf("\tUsername already exists. Please choose a different username.\n");
            fclose(file);
            return;
        }
    }

    while (getchar() != '\n');
    // Prompt for password and validate it using IsValidPassword
    while (1) 
    {

        printf("\tEnter password (no spaces allowed): ");
        fgets(password, sizeof(password), stdin);  // Use fgets to read the entire password, including spaces

        // Remove the trailing newline character added by fgets
        password[strcspn(password, "\n")] = '\0';

        // Check for space in the password
        if (!IsValidPassword(password)) 
        {
            printf("\tPassword cannot contain spaces. Please try again.\n");

        } 
        else 
        {
            break;  // Valid password, exit the loop
        }
    }

    fprintf(file, "%s-%s\n", username, password);  // Store the username and password
    printf("\tRegistration successful.\n");

    fclose(file);
}




// Login function
int Login(char *user) 
{
    char username[max], password[max], fileUsername[max], filePassword[max];

    FILE *file = fopen("users.txt", "r");

    if (file == NULL) 
    {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\tEnter username: ");
    scanf("%s", username);

    // Clear the newline character left by scanf
    getchar();

    printf("\tEnter password: ");
    fgets(password, sizeof(password), stdin);  // Use fgets to read the password

    // Remove the trailing newline character added by fgets
    password[strcspn(password, "\n")] = '\0';

    while (fscanf(file, "%[^-]-%s\n", fileUsername, filePassword) != EOF) 
    {
        // Compare the input username and password with stored username and password
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) 
        {
            strcpy(user, username);
            printf("\tLogin successful!\n");
            fclose(file);
            return 1;
        }
    }
    printf("Invalid username or password.\n");
    fclose(file);
    return 0;
}




// Encrypt password by adding 5 to ASCII values
void Encrypt(char password[], char encryptedPass[]) 
{
    int len = strlen(password);

    for (int i = 0; i < len; i++) 
    {
        encryptedPass[i] = password[i] + 11;
    }
    encryptedPass[len] = '\0';
}

// Decrypt password by subtracting 5 from ASCII values
void Decrypt(char encryptedPass[], char decryptedPass[]) 
{
    int len = strlen(encryptedPass);

    for (int i = 0; i < len; i++) 
    {
        decryptedPass[i] = encryptedPass[i] - 11;
    }
    decryptedPass[len] = '\0';
}

// Function to check the strength of a password
void CheckPasswordStrength(const char password[]) {
    int length = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    // Iterate through each character of the password 
    for (int i = 0; i < length; i++) {
        if (isupper(password[i]))
            hasUpper = 1;
        else if (islower(password[i]))
            hasLower = 1;
        else if (isdigit(password[i]))
            hasDigit = 1;
        else
            hasSpecial = 1;  // Any other character is treated as special
    }

    // Determine the strength of the password
    if (length < 6) {
        printf("\tPassword strength: Weak\n");
    } else if (length <= 10 && (hasUpper || hasLower) && (hasDigit || hasSpecial)) {
        printf("\tPassword strength: Medium\n");
    } else if (length > 10 && hasUpper && hasLower && hasDigit && hasSpecial) {
        printf("\tPassword strength: Strong\n");
    } else {
        printf("\tPassword strength: Weak\n");
    }
}

// Function to check if the password is valid (no spaces allowed)
int IsValidPassword(char password[]) 
{
    // Check if the password contains spaces
    if (strchr(password, ' ') != NULL) {
        return 0;  // Invalid password, contains spaces
    }
    return 1;  // Valid password, no spaces
}


// Add a password for a specific application
void AddPassword(char username[]) 
{
    char app[max], password[max], encrypted[max];
    char fileName[max];

    strcpy(fileName, username);  // User-specific file
    strcat(fileName, ".txt");

    FILE *file = fopen(fileName, "a");

    if (file == NULL) 
    {
        printf("\tError opening file!\n");
        exit(1);
    }

    printf("\n\tEnter application name: ");
    getchar();  // Clear newline from previous input
    fgets(app, max, stdin);
    app[strcspn(app, "\n")] = '\0';  // Remove trailing newline character

    // Prompt for password and validate it using IsValidPassword
    while (1) 
    {
        printf("\tEnter password (no spaces allowed): ");
        fgets(password, sizeof(password), stdin);  // Use fgets to read the entire password, including spaces

        // Remove the trailing newline character added by fgets
        password[strcspn(password, "\n")] = '\0';

        // Check for space in the password
        if (!IsValidPassword(password)) 
        {
            printf("\tPassword cannot contain spaces. Please try again.\n");
        } 
        else 
        {
            break;  // Valid password, exit the loop
        }
    }

    CheckPasswordStrength(password);  // Evaluate password strength
    Encrypt(password, encrypted);    // Encrypt password
    fprintf(file, "%s-%s\n", app, encrypted);
    printf("\tPassword saved successfully!\n");

    fclose(file);
}

void ViewPassword(char username[]) 
{
    char filename[max], app[max], encrypted[max], decrypted[max];
    char rePassword[max];

    FILE *userFile, *loginFile;

    strcpy(filename, username);
    strcat(filename, ".txt");

    // Open the user's password file
    userFile = fopen(filename, "r");
    if (userFile == NULL) 
    {
        printf("\tNo passwords saved yet.\n");
        return;
    }

    // Display stored passwords in encrypted form
    printf("\n\tStored passwords (encrypted):\n");
    while (fgets(app, max, userFile) != NULL) 
    {
        app[strcspn(app, "\n")] = '\0';

        // Extract application name and encrypted password
        char *encrypted_password = strchr(app, '-');
        if (encrypted_password) 
        {
            *encrypted_password = '\0';  
            encrypted_password++; 
            printf("\t%s - %s\n", app, encrypted_password); 
        } 
        else 
        {
            printf("\tInvalid line format: %s\n", app);
        }
    }
    fclose(userFile);

    // Ask the user if they want to decrypt a password
    printf("\n\tDo you want to decrypt a password? (yes/no): ");
    char choice[max];
    scanf("%s", choice);

    if (strcmp(choice, "yes") == 0) 
    {
        printf("\tRe-enter your account password: ");
        scanf("%s", rePassword);

        // Authenticate the user's password
        loginFile = fopen("users.txt", "r");
        if (loginFile == NULL) 
        {
            perror("\tError opening users file");
            return;
        }

        int authenticated = 0;
        char fileUsername[max], filePassword[max];

        while (fscanf(loginFile, "%[^-]-%s\n", fileUsername, filePassword) != EOF) 
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(rePassword, filePassword) == 0) 
            {
                authenticated = 1;
                break;
            }
        }
        fclose(loginFile);

        if (authenticated) 
        {
            printf("\tAuthentication successful.\n");
            while (getchar() != '\n');

            // Prompt the user for the application name to decrypt
            char decryptApp[max];
            printf("\n\tEnter application name to decrypt: ");
            fgets(decryptApp, max, stdin);
            decryptApp[strcspn(decryptApp, "\n")] = '\0'; 

            userFile = fopen(filename, "r");
            if (userFile == NULL) 
            {
                perror("\t\tError opening user file");
                return;
            }

            int found = 0;
            char storedApp[max];
            while (fgets(app, max, userFile) != NULL) 
            {
                // Remove trailing newline character
                app[strcspn(app, "\n")] = '\0';

                // Extract application name and encrypted password
                char *encrypted_password = strchr(app, '-');
                if (encrypted_password) 
                {
                    *encrypted_password = '\0';
                    encrypted_password++;  // The encrypted password starts after the '-' 

                    if (strcmp(decryptApp, app) == 0) 
                    {  // Compare with the entered app name
                        Decrypt(encrypted_password, decrypted);
                        printf("\tDecrypted password for %s: %s\n", app, decrypted);
                        found = 1;
                        break;
                    }
                }
            }
            fclose(userFile);

            if (!found) 
            {
                printf("\tApplication '%s' not found.\n", decryptApp);
            }
        } 
        else 
        {
            printf("\tAuthentication failed.\n");
        }

    }
}

int main()
{
    int choice;
    char loggedInUser[max];

    printf("--------------------------------");
    printf("\nWelcome to Password Manager!\n");
    printf("--------------------------------");

    while (1) 
    {
        // Main menu
        printf("\n\nMain Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("\t----------------------------");
                printf("\n\t1. Registering a new user...\n");
                printf("\t----------------------------\n");
                Register();
                break;

            case 2:
                printf("\t------------------");
                printf("\n\tLogging in...\n");
                printf("\t------------------\n");
                if (Login(loggedInUser)) 
                {
                    int subChoice;
                    printf("\n**********************");
                    printf("\nWelcome, %s!\n", loggedInUser);
                    printf("***********************\n");

                    do {
                        // User menu after login
                        printf("\n\nUser Menu:\n");
                        printf("1. Add Password\n");
                        printf("2. View Passwords\n");
                        printf("3. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &subChoice);

                        switch (subChoice) 
                        {
                            case 1:
                                printf("\t----------------------------");
                                printf("\n\t1. Adding a new password...\n");
                                printf("\t----------------------------");
                                AddPassword(loggedInUser);
                                break;

                            case 2:
                                printf("\t----------------------------");
                                printf("\n\t2. Viewing saved passwords...\n");
                                printf("\t----------------------------\n");
                                ViewPassword(loggedInUser);
                                break;

                            case 3:
                                printf("\nYou have been logged out.\n");
                                break;

                            default:
                                printf("\nInvalid choice. Please try again.\n");
                        }

                    } while (subChoice != 3);
                }
                break;

            case 3:
                printf("\nThank you for using Password Manager. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}
