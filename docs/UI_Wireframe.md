# UI Wireframe – VSS Activity Monitor (MFC)

This document defines the UI structure and interaction model for the
VSS Activity Monitor MFC application.

It is a **behavioral wireframe**, not a visual design mock.
All UI implementations must follow this structure unless explicitly updated.

---

## 1. Main Window Layout

+------------------------------------------------------+
| Menu / Toolbar |
+------------------------------------------------------+
| Filters / Controls |
| [Time Range] [Volume] [Result] [Process] [Start/Stop]|
+------------------------------------------------------+
| Tabs |
| [ Timeline | Transactions | Process | Raw Events ] |
| |
| Tab Content Area |
| |
+------------------------------------------------------+
| Status Bar |
+------------------------------------------------------+

---

## 2. Timeline Tab (Primary View)

### Purpose
Visualize VSS activity as a time-ordered sequence using swimlanes,
showing **who did what, and when**.

### Layout

+------------------------------------------------------+
| Timeline Controls |
| [Zoom -] [Zoom +] [Auto Follow ☐] [Clear] |
+------------------------------------------------------+
| Time Axis |
| 10:01 10:02 10:03 10:04 10:05 |
+------------------------------------------------------+
| Lane Header | Timeline Canvas |
|------------------------------------------------------|
| backup.exe (4120) | ●─────█────────● |
| vssvc.exe | ● ● ● █████ █ ● ● |
| volsnap.sys | ██████████ |
| Writers (System) | █ Freeze █ Thaw █ |
+------------------------------------------------------+


### Swimlane Rules
- Each lane represents one entity:
  - Requester process (name + PID)
  - vssvc.exe
  - volsnap
  - VSS writers (grouped)
- Lane order:
  1. Requester candidates
  2. vssvc.exe
  3. volsnap
  4. writers

### Glyphs
- **Point Event (●)**  
  - Instantaneous events (RPC call, request start)
- **Span Event (█)**  
  - Duration events (snapshot create, freeze/thaw)

### Interaction
- Mouse wheel: zoom in/out
- Mouse drag: horizontal pan
- Click event: select and highlight
- Hover event: tooltip display

### Tooltip Content
Time: 10:02:14.221
Operation: Snapshot Create
Volume: C:
Transaction ID: TX-2026-0008
Requester (estimated): backup.exe (PID 4120)
Confidence: 0.86
Evidence:

COM call within 12ms

Known backup tool

---

## 3. Transactions Tab

### Purpose
Provide a summarized, table-based view of VSS transactions.

### Layout

+------------------------------------------------------+
| Time | Operation | Volume | Requester |
|------------------------------------------------------|
| 10:02:14 | Snapshot Create | C: | backup.exe |
| 10:01:02 | Snapshot Delete | C: | unknown |
+------------------------------------------------------+



### Columns
- Start Time
- Operation
- Volume(s)
- Requester (estimated)
- Confidence
- Result

### Interaction
- Double-click row → jump to Timeline and highlight transaction

---

## 4. Process Tab

### Purpose
Inspect VSS activity from a single process perspective.

### Layout

Process: backup.exe (PID 4120)
Path: C:\Program Files\Backup\backup.exe
User: NT AUTHORITY\SYSTEM

VSS Activity:

10:02:14 Snapshot Create (C:) SUCCESS

09:45:01 Enumerate Writers



### Additional Panel
**Confidence Breakdown**
RPC Correlation : +0.40
Known Tool : +0.30
Time Proximity : +0.16
Final Confidence: 0.86


---

## 5. Raw Events Tab (Developer Mode)

### Purpose
Expose raw ETW events for debugging and development.

### Layout

[Timestamp] [Provider] [EventId] [PID] [Message]
10:02:14.345 Volsnap 36 - Snapshot started



### Notes
- Disabled by default
- Enabled via menu: View → Developer Mode

---

## 6. UI Behavior Rules

- Requester identity must ALWAYS be labeled as **estimated**
- Confidence and evidence must be visible somewhere in UI
- Timeline is the authoritative view
- List views must synchronize selection with Timeline

---

## 7. Non-Goals
- Pixel-perfect visual design
- Animations
- Custom theming

This document defines **structure and behavior only**.