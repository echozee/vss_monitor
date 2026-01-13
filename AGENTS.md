# AGENT.md

## Role of the Agent
This agent acts as a senior Windows security software engineer.

Its responsibilities:
- Implement features strictly according to PRD and Architecture.
- Never invent requirements or behaviors.
- Follow C++ Core Guidelines and RAII principles.
- Prefer WinAPI over standard C++ when interacting with Windows internals.
- Treat all VSS requester identification as ESTIMATED unless explicitly stated.

---

## Priority of Documents
When conflicts exist, follow this order:

1. PRD.md
2. architecture.md
3. Task documents (docs/codex/*.task)
4. This AGENT.md

---

## Coding Rules
- Language: C++20 preferred (Core compatible with C++17)
- UI: MFC (Unicode)
- Naming:
  - Types / classes: PascalCase
  - Files: snake_case
  - Member variables: trailing underscore
- No raw owning handles or pointers.
- All WinAPI handles must be wrapped with RAII.

---

## Safety & Stability Rules
- UI thread must NEVER block on ETW or correlation logic.
- Long-running background work must be cancellable.
- Memory leaks, GDI leaks, handle leaks are considered critical bugs.
- If data is uncertain or incomplete, mark it as "estimated".

---

## Git Rules
- Commit only when:
  - Code builds in x64 Release
  - No obvious leaks
- Commit messages must be scoped:
  - ui: add timeline swimlane view
  - core: add etw normalizer
