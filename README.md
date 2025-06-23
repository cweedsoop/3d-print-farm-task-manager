# 3D Print Farm Task Manager

This is a lightweight, in-progress task management system for managing small to mid-scale 3D print farms. Built in C++, this application introduces basic task management logic, user account control, and workspace segmentation to help teams coordinate print jobs more effectively and reduce operational friction.

## 🛠️ Key Features

- **Account System**: Simple login and registration, with basic encryption and hashing.
- **Workspaces**: Printers can be grouped under shared team workspaces, improving task filtering and visibility.
- **Task Assignment**: Prevents overlapping print jobs by checking printer availability at time of task creation.
- **Printer Management**: Add, assign, and update printer statuses (idle, printing, broken, etc.).
- **Product Management**: Define products with custom attributes (color, filament type, etc.).
- **State Persistence**: Multi-file I/O structure allows session data to persist between runs.

## 📹 Demo

Watch the demo video:  
**YouTube Link:** https://youtu.be/_ttIPzP0MvA

## 🧪 Running the Project

This is a C++ console application built for Windows. To run:

1. Clone the repository:

```
git clone https://github.com/jingfu-peng/3d-print-farm-task-manager
```
2. Open the `.cpp` files in your preferred IDE (e.g., Visual Studio 2022).

3. Compile and run `main.cpp`.

> ⚠ Note: The project uses file I/O for persistent state. On first run, it will generate data files in the working directory.

### 📁 Sample Data

The repository includes pre-filled sample data files. These allow you to explore the application's core functionality without needing to manually register users or configure printers and products.

**Default Login Credentials:**
- **Username:** `asdf`
- **Password:** `asdf`

### ⚠️ Note on Sample Data

Please avoid manually editing the data files.  
These files follow a specific format expected by the application, and changing them directly may result in errors or corrupted states.

## 📌 Current Limitations

- Console-only interface (GUI planned via Qt)
- Windows-only at this stage
- Not connected to 3D printer APIs
- Basic encryption (not secure for production)

## 🧭 Roadmap

Planned improvements include:
- Refactored and modularized codebase
- Cross-platform GUI using Qt
- API integration for real-time printer status
- Mobile companion app with live sync
