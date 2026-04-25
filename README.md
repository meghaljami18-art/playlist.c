# 🎧 Playlist Manager (C - Linked List)

A modular and dynamic playlist management system demonstrating linked list operations, pointer manipulation, and structured programming in C.

---

## 📌 Description

A console-based playlist management system implemented in C using a singly linked list.
This project allows users to dynamically manage songs with operations like insertion, deletion, searching, and reversing the playlist.

---

## 🚀 Features

- Add songs to playlist (O(1) using tail pointer)
- Insert song at specific position
- Delete song by title
- Search song by title
- Display playlist with track numbering and total duration
- Reverse playlist
- Calculate total playlist duration
- Automatic track renumbering after every insert, delete, or reverse

---

## 🧠 Concepts Used

- Structures (`struct`)
- Pointers and dynamic memory (`malloc`, `free`)
- Singly Linked List
- Traversal techniques
- String handling (`strcmp`)
- Input validation and buffer management
- Menu-driven programming

---

## 🛠️ How to Compile & Run

```bash
gcc playlist.c -o playlist
./playlist
```

> Requires a C compiler (GCC recommended). Works on Linux, macOS, and Windows (via MinGW or WSL).

---

## 📊 Sample Output

```
============================================
  🎵 PLAYLIST (3 songs | 12.46 mins total)
============================================
#1   Attention              charlie puth      3.32 min
#2   cinnamon girl          lana del rey      5.01 min
#3   love me like you do    ellie gouding     4.13 min
============================================
```

---

## 📁 Project Structure

```
playlist.c    # Main implementation
README.md
```

---

## ⚙️ Time Complexity

| Operation | Complexity |
|---|---|
| Insert (end) | O(1) |
| Insert (position) | O(n) |
| Delete | O(n) |
| Search | O(n) |
| Reverse | O(n) |
| Display | O(n) |

---

## ⚠️ Limitations

- Data is not saved permanently (no file handling)
- Case-sensitive search and delete
- Names with spaces require buffer-safe input handling

---

## 🚀 Future Improvements

- Doubly linked list (prev + next navigation)
- File handling (save/load playlist)
- Case-insensitive search
- Sort by title, artist, or duration
- GUI version

---

## 🎯 Learning Outcomes

- Strong understanding of singly linked list operations
- Improved pointer manipulation and memory management skills
- Hands-on experience with dynamic memory allocation (`malloc`, `free`)
- Applied input validation and buffer-safe string handling
- Better problem-solving and debugging ability
