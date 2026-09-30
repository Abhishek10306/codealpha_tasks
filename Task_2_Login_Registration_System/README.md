# Login and Registration System

A C++ based Login and Registration System developed as part of the CodeAlpha C++ Programming Internship.

## Project Overview

This project implements a basic user authentication system with registration and login functionality.

The C++ application validates usernames and passwords, prevents duplicate usernames, generates a random salt, hashes passwords before storing them, and verifies credentials during login.

A modern HTML, CSS and JavaScript interface is also included as a frontend demonstration.

## Features

* User registration
* Username validation
* Password validation
* Duplicate username detection
* Random salt generation
* Password hashing
* File-based credential storage
* User login
* Password verification
* Success and error messages
* Modern responsive web interface

## C++ Authentication Flow

```text
Registration
     ↓
Validate username
     ↓
Check duplicate username
     ↓
Validate password
     ↓
Generate random salt
     ↓
Create password hash
     ↓
Store username + salt + hash
```

Login:

```text
Username + Password
        ↓
Find stored username
        ↓
Read stored salt
        ↓
Hash entered password
        ↓
Compare hashes
        ↓
Login successful / failed
```

## Validation Rules

### Username

* Minimum 3 characters
* Maximum 20 characters
* Letters allowed
* Numbers allowed
* `_` allowed
* `.` allowed

### Password

* Minimum 8 characters
* Must contain at least one letter
* Must contain at least one number

## Technologies Used

* C++
* HTML
* CSS
* JavaScript

## Files

```text
Task_2_Login_Registration_System/
│
├── main.cpp
├── index.html
└── README.md
```

## C++ Data Storage

The C++ application creates a file named:

```text
users.txt
```

Passwords are not stored directly. The file stores:

```text
username salt password_hash
```

The password itself is not written to the file.

## How to Run the C++ Program

Compile:

```bash
g++ main.cpp -o login_system
```

Run on Linux/macOS:

```bash
./login_system
```

On Windows:

```bash
login_system.exe
```

## How to Run the Web Version

Open:

```text
index.html
```

in a modern web browser.

The web version is a frontend demonstration and stores demo account data in browser storage. It is not intended for production authentication.

## Testing

The following cases were tested:

1. Successful registration
2. Duplicate username
3. Successful login
4. Incorrect password
5. Unknown username
6. Invalid username
7. Weak password
8. Password confirmation mismatch
9. Logout

## Security Note

This project is intended for educational purposes.

For production authentication systems, passwords should be handled by a secure backend and a dedicated password-hashing algorithm such as Argon2, bcrypt or scrypt. Authentication systems should also use HTTPS, secure sessions, rate limiting and appropriate database security.

## Internship

CodeAlpha C++ Programming Internship

## Author

Abhishek Kumar
