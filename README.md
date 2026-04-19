# 🎬 Ticket-Reservation System

A full-featured **cinema ticket reservation system** built in C++ as a team project, demonstrating core Object-Oriented Programming principles including inheritance, polymorphism, encapsulation, and abstraction.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Class Architecture](#class-architecture)
- [How to Run](#how-to-run)
- [Usage Guide](#usage-guide)
- [Seating & Pricing](#seating--pricing)
- [Tech Stack](#tech-stack)


---

## Overview

This project simulates a real-world cinema management system from the ground up. Users can register as a customer, browse available movies, select showtimes, pick and reserve seats, cancel bookings, and view analytics — all through an interactive console menu.

Built as a team project for our Computer Science coursework, it showcases a clean class hierarchy and modular design across 7 custom classes.

---

## Features

- 🎥 **Movie browsing** — view all available movies with genre, year, and duration
- 🪑 **Interactive seating layout** — real-time visualization of available (`-`) and booked (`X`) seats
- 🎟️ **Seat reservation** — book multiple seats with ticket type selection (Standard, Premium, Student)
- ❌ **Reservation management** — cancel specific seats or an entire reservation
- 📊 **Analytics dashboard** — per-movie stats and overall cinema performance metrics (revenue, occupancy rate, ticket sales by genre and seat type)
- 🕐 **Multiple showtimes** — 4 daily showings per movie (10:00, 13:00, 17:00, 21:00)
- 💰 **Tiered pricing** — VIP, Premium, and Regular seat categories

---

## Class Architecture

```
├── Enums.h              # Genre and SeatType enumerations
├── classSeats.h         # Seat grid, pricing tiers, availability tracking
├── classCustomer.h      # Customer profile (name, phone, email)
├── classMovies.h        # Movie data + showtime management
├── classReservation.h   # Reservation logic (book, cancel, display)
├── MovieAnalytics.h     # Per-movie statistics tracking
├── AnalyticsManager.h   # Aggregated cinema-wide analytics
└── main.cpp             # Entry point and menu system
```

**OOP Concepts Used:**
- **Encapsulation** — all class data is private with controlled access via getters/setters
- **Abstraction** — complex seat and reservation logic hidden behind clean interfaces
- **Polymorphism** — movie display and genre handling via virtual methods
- **Inheritance** — shared base behaviors across the class hierarchy

---

## How to Run

### Option 1 — Run the executable (Windows)
```
Double-click: "Ticket Reservation System.exe"
```

### Option 2 — Compile from source (requires g++)
```bash
g++ SRC/main.cpp -o cinema
./cinema
```

> **Requirements:** Windows OS, C++11 or later

---

## Usage Guide

1. **Launch** the program — you'll be prompted to enter your name, phone number, and email
2. Use the **numbered menu** to navigate:

| Option | Action |
|--------|--------|
| 1 | View available movies |
| 2 | View seating layout |
| 3 | Book seats |
| 4 | Cancel specific seats |
| 5 | Cancel entire reservation |
| 6 | View reservation details |
| 7 | View analytics for a movie |
| 8 | View overall cinema analytics |
| 9 | Exit |

---

## Seating & Pricing

The cinema has a **10×10 grid** (100 seats total):

| Rows | Seat Type | Price |
|------|-----------|-------|
| 1–2  | 👑 VIP     | $150  |
| 3–5  | ⭐ Premium  | $100  |
| 6–10 | 🎫 Regular  | $80   |

Seat display: `-` = Available &nbsp;|&nbsp; `X` = Booked

---

## Currently Available Movies

| # | Title | Genre | Year |
|---|-------|-------|------|
| 1 | The Matrix | Sci-Fi | 2024 |
| 2 | Comedy Club | Comedy | 2024 |
| 3 | سيكو سيكو | Comedy | 2024 |
| 4 | Avengers: Doomsday | Action | 2024 |
| 5 | البدلة | Comedy | 2024 |

---

## Tech Stack

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![OOP](https://img.shields.io/badge/OOP-Design-blueviolet?style=flat)
![Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=flat&logo=windows)

- Language: **C++**
- Paradigm: **Object-Oriented Programming**
- Architecture: **Modular header-based design**
- Build: **g++ / any C++11 compiler**

---

