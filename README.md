# 🚖 SmartRide – Ride Sharing & Route Optimization System

## 📌 2.1 Project Title

**SmartRide – Ride Sharing & Route Optimization System Using Data Structures and Algorithms**

---

# 📝 2.2 Problem Statement

Ride-sharing services have become an important part of modern transportation. However, managing riders, vehicles, ride requests, route planning, fare calculation, and trip records efficiently can be challenging when the number of users increases.

Traditional systems may suffer from inefficient request handling, longer travel routes, increased waiting times, and poor vehicle utilization. To address these challenges, an optimized system is required that can process ride requests efficiently, determine suitable routes, support carpooling, and maintain ride records in an organized manner.

This project aims to develop a ride-sharing management system using Data Structures and Algorithms (DSA) to simulate the core functionalities of a real-world ride-sharing platform while ensuring efficient data management and route optimization.

---

# 🎯 2.3 Objectives

The primary objectives of this project are:

- To design and develop a ride-sharing management system using C++.
- To apply Data Structures and Algorithms in a practical real-world scenario.
- To manage riders and vehicles efficiently.
- To process ride requests in an organized manner.
- To optimize routes between locations.
- To implement carpool matching functionality.
- To calculate ride fares dynamically.
- To maintain trip history records.
- To improve understanding of DSA concepts through practical implementation.

---

# 🏗️ 2.4 System Overview / Architecture

SmartRide follows a modular architecture where each component is responsible for a specific task within the system.

### System Flow

```text
Rider Request
      │
      ▼
Request Queue
      │
      ▼
Route Planner
      │
      ▼
Carpool Matcher
      │
      ▼
Price Manager
      │
      ▼
Trip History Storage
      │
      ▼
Dashboard Output
```

### Main Modules

#### 👤 Rider Manager
Responsible for storing, managing, and retrieving rider information.

#### 🚗 Car Manager
Maintains vehicle details and availability information.

#### 📥 Request Queue
Handles incoming ride requests and processes them in a First-In-First-Out (FIFO) manner.

#### 🗺️ Route Planner
Calculates efficient routes between locations using graph-based algorithms.

#### 🤝 Carpool Matcher
Identifies riders with similar routes and matches them for shared rides.

#### 💰 Price Manager
Calculates ride fares based on trip details.

#### 📊 Trip History
Stores completed ride information for future reference.

#### 🖥️ Dashboard
Displays ride information and system outputs to the user.

---

# 🧠 2.5 Data Structures and Algorithms Used

The project incorporates several important Data Structures and Algorithms.

| Data Structure / Algorithm | Purpose |
|---------------------------|---------|
| Arrays / Vectors | Store rider, vehicle, and trip information |
| Queue | Manage ride requests efficiently |
| Graph | Represent city locations and road connections |
| Sorting Algorithms | Organize and arrange vehicle data |
| Route Optimization Algorithms | Find efficient travel paths |
| File Handling | Store and retrieve persistent data |

### Why These Data Structures?

#### Queue
Ride requests are processed in the same order they are received, making Queue an ideal choice.

#### Graph
A city can be represented as a network of connected locations. Graphs allow efficient route planning between locations.

#### Arrays / Vectors
Provide efficient storage and access for riders, vehicles, and trip records.

#### Sorting Algorithms
Help organize data and improve retrieval efficiency.

---

# ⚙️ 2.6 Implementation Approach

The project was implemented using a modular approach where each component handles a specific functionality.

### Step 1: Data Initialization
The system loads rider, vehicle, and request data from text files.

### Step 2: Rider and Vehicle Management
Users can access rider and vehicle information maintained by dedicated modules.

### Step 3: Request Processing
Incoming ride requests are added to a queue and processed sequentially.

### Step 4: Route Planning
The system calculates suitable routes between source and destination locations.

### Step 5: Carpool Matching
The system checks whether multiple riders can share a ride based on route similarity.

### Step 6: Fare Calculation
Ride costs are calculated using pricing rules defined within the Price Manager module.

### Step 7: Trip Recording
Completed rides are stored in the trip history for future analysis.

### Step 8: Dashboard Display
The final ride information is displayed to the user.

---

# 📈 2.7 Time and Space Complexity Analysis

The following table summarizes the complexity of major operations performed by the system.

| Operation | Time Complexity | Space Complexity |
|------------|----------------|----------------|
| Add Rider | O(1) | O(1) |
| Add Vehicle | O(1) | O(1) |
| Process Ride Request | O(1) | O(1) |
| Sort Vehicles | O(n log n) | O(n) |
| Route Search | O(V + E) | O(V) |
| Carpool Matching | O(n) | O(1) |
| Store Trip History | O(1) | O(n) |

Where:

- **n** = Number of riders or vehicles
- **V** = Number of locations (vertices)
- **E** = Number of connections between locations (edges)

### Observations

- Queue operations are highly efficient and execute in constant time.
- Graph-based route planning scales well with increasing locations.
- Sorting operations are performed only when required, improving overall efficiency.

---

# ▶️ 2.8 Execution Steps

### Step 1: Clone the Repository

```bash
git clone https://github.com/bhuvishag07/DSA-FINAL-PROJECT-.git
```

### Step 2: Navigate to the Project Folder

```bash
cd DSA-FINAL-PROJECT-
```

### Step 3: Compile the Project

```bash
make
```

### Step 4: Run the Application

```bash
./smartride
```

### Step 5: Interact with the System

Follow the menu options displayed on the screen to:

- Manage riders
- Manage vehicles
- Process ride requests
- Plan routes
- Calculate fares
- View trip history

---

# 🧪 2.9 Sample Inputs and Outputs

## Sample Input

```text
Rider Name: John
Pickup Location: Andheri
Drop Location: Bandra
Ride Type: Carpool
```

## Sample Output

```text
Ride Request Accepted

Optimal Route Found:
Andheri → Santacruz → Bandra

Carpool Match Found

Estimated Fare: ₹120

Trip Successfully Recorded
```

*Note: Actual outputs may vary depending on the input data and available routes.*

---

# 📸 2.10 Screenshots

Include screenshots of the following:

### Screenshot 1
Main Menu Interface

### Screenshot 2
Ride Request Processing

### Screenshot 3
Route Planning Output

### Screenshot 4
Carpool Matching Result

### Screenshot 5
Trip History Display

> Replace this section with actual screenshots captured while running the project.

---

# 📊 2.11 Results and Observations

The project successfully demonstrates the practical application of Data Structures and Algorithms in a real-world ride-sharing scenario.

### Key Results

- Efficient ride request processing using Queue.
- Route planning through graph-based modeling.
- Successful implementation of carpool matching functionality.
- Organized management of riders and vehicles.
- Dynamic fare calculation and trip tracking.

### Observations

- Queue structures simplify request management.
- Graphs provide an effective representation of city routes.
- Modular architecture improves maintainability and scalability.
- DSA concepts significantly improve system efficiency compared to manual processing approaches.

---

# ✅ 2.12 Conclusion

SmartRide successfully applies Data Structures and Algorithms to solve common challenges faced in ride-sharing systems. The project demonstrates how concepts such as Queues, Graphs, Sorting Algorithms, and File Handling can be integrated into a practical software application.

Through this project, valuable experience was gained in problem-solving, algorithm design, route optimization, modular programming, and object-oriented software development. The implementation highlights the importance of selecting appropriate data structures to improve performance and system organization.

Overall, SmartRide serves as a strong demonstration of how DSA concepts can be utilized to build efficient and scalable real-world applications.

---

# 👨‍💻 Developed By

**Bhuvisha Gohil**


**DSA Final Project** – **SmartRide Ride Sharing & Route Optimization System**

