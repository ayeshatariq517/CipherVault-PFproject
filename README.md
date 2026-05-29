<div align="center">

```
██████╗  █████╗ ███████╗███████╗██╗    ██╗ ██████╗ ██████╗ ██████╗ 
██╔══██╗██╔══██╗██╔════╝██╔════╝██║    ██║██╔═══██╗██╔══██╗██╔══██╗
██████╔╝███████║███████╗███████╗██║ █╗ ██║██║   ██║██████╔╝██║  ██║
██╔═══╝ ██╔══██║╚════██║╚════██║██║███╗██║██║   ██║██╔══██╗██║  ██║
██║     ██║  ██║███████║███████║╚███╔███╔╝╚██████╔╝██║  ██║██████╔╝
╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝ ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ 
                                                                      
              ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗ 
              ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗
              ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝
              ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗
              ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║
              ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
```

**A secure, terminal-based password vault — built from scratch in C.**

[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge)]()
[![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)]()
[![Level](https://img.shields.io/badge/Level-Fundamentals%20Project-orange?style=for-the-badge)]()

</div>

---

## 🔐 What is Password Manager?

**Password Manager** is a console-based application written in pure C that allows users to securely register, log in, store, and retrieve passwords for different applications. Every password is encrypted before being saved to disk — meaning even if someone opens the file, they'll see nothing but scrambled characters.

This project was built as a **Programming Fundamentals** course capstone, demonstrating real-world use of file I/O, string manipulation, encryption logic, and structured user authentication — all without a single external library.

---

## ✨ Features

| Feature | Description |
|---|---|
| 🧑‍💼 **User Registration** | Create a personal account with a username and password |
| 🔑 **Secure Login** | Authenticate before accessing your vault |
| 🔒 **Password Encryption** | All stored passwords are encrypted using ASCII shift cipher |
| 🔓 **Password Decryption** | Decrypt and view passwords after re-authentication |
| 💪 **Strength Checker** | Instantly evaluates your password as Weak / Medium / Strong |
| 🚫 **Input Validation** | Rejects invalid passwords (e.g. passwords with spaces) |
| 📂 **Per-User Storage** | Each user's passwords are saved in their own private file |
| 🔁 **Multi-Session Support** | Register and log in multiple users in one run |

---

## 🛠️ How It Works

```
┌─────────────────────────────────────────────┐
│               PASSWORD MANAGER              │
│─────────────────────────────────────────────│
│  [1] Register    → Creates users.txt entry  │
│  [2] Login       → Validates credentials    │
│  [3] Exit                                   │
└─────────────────────────────────────────────┘
            │
            ▼ (After Login)
┌─────────────────────────────────────────────┐
│               USER VAULT MENU               │
│─────────────────────────────────────────────│
│  [1] Add Password   → Encrypt & store       │
│  [2] View Passwords → Display encrypted     │
│                     → Decrypt on demand     │
│  [3] Logout                                 │
└─────────────────────────────────────────────┘
```

### 🔐 Encryption Logic

Each character in the password is shifted by **+11** in its ASCII value when stored, and shifted back by **-11** when retrieved. This ensures passwords are never stored in plain text.

```c
// Encrypting
encryptedPass[i] = password[i] + 11;

// Decrypting
decryptedPass[i] = encryptedPass[i] - 11;
```

### 💪 Password Strength Criteria

| Strength | Criteria |
|---|---|
| 🔴 **Weak** | Less than 6 characters, or missing character variety |
| 🟡 **Medium** | 6–10 characters with a mix of letters and digits/symbols |
| 🟢 **Strong** | 10+ characters with uppercase, lowercase, digits, AND symbols |

---

## 🚀 Getting Started

### Prerequisites
- A C compiler: `gcc` (recommended) or `clang`
- A terminal / command prompt

### Compile & Run

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/password-manager.git
cd password-manager

# Compile
gcc main.c -o password_manager

# Run
./password_manager        # Linux / macOS
password_manager.exe      # Windows
```

---

## 📁 Project Structure

```
password-manager/
│
├── main.c              ← All source code (single-file project)
├── users.txt           ← Auto-generated: stores registered users
├── <username>.txt      ← Auto-generated per user: stores encrypted passwords
└── README.md           ← You are here
```

> ⚠️ `users.txt` and `<username>.txt` files are auto-created at runtime and are excluded from version control via `.gitignore`.

---

## 📸 Sample Session

```
--------------------------------
Welcome to Password Manager!
--------------------------------

Main Menu:
1. Register
2. Login
3. Exit
Enter your choice: 1

    ----------------------------
    1. Registering a new user...
    ----------------------------
    Enter username: ali
    Enter password (no spaces allowed): MyPass@123
    Registration successful.

Main Menu:
1. Register
2. Login
3. Exit
Enter your choice: 2

    ------------------
    Logging in...
    ------------------
    Enter username: ali
    Enter password: MyPass@123
    Login successful!

**********************
Welcome, ali!
***********************

User Menu:
1. Add Password
2. View Passwords
3. Logout
Enter your choice: 1

    Enter application name: Gmail
    Enter password (no spaces allowed): Gmail#Secure99!
    Password strength: Strong
    Password saved successfully!
```

---

## 🧠 Concepts Demonstrated

This project was built to demonstrate mastery of core programming fundamentals:

- ✅ Functions and modular design
- ✅ File I/O (`fopen`, `fgets`, `fscanf`, `fprintf`, `fclose`)
- ✅ String manipulation (`strcpy`, `strcat`, `strcmp`, `strchr`, `strcspn`)
- ✅ Character classification (`isupper`, `islower`, `isdigit`)
- ✅ Loops, conditionals, and switch statements
- ✅ Input validation and error handling
- ✅ Basic encryption/decryption logic
- ✅ Struct-free multi-user data management

---

## ⚠️ Disclaimer

This project was built for **educational purposes** as part of a Programming Fundamentals course. The encryption used (ASCII shifting) is a **Caesar cipher variant** and is **not suitable for real-world secure storage**. For production use, consider AES-256 encryption and a proper hashing algorithm like bcrypt for passwords.

---

## 👨‍💻 Author

Built with ❤️ and a lot of `printf` debugging.

> *"First, solve the problem. Then, write the code."* — John Johnson

---

<div align="center">
  <sub>⭐ If you found this project useful or interesting, consider giving it a star!</sub>
</div>
