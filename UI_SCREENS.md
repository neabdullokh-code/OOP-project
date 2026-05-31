# What each window shows (for design / AI prompts)

Application: **Study.Table()**, dark theme via `resources/styles/main.qss`. **All user-visible text in the app is English.**

## Shared header (Admin / Teacher / Student panels)

- Large role title (emoji in label): red — admin, yellow — teacher, green — student.
- Next: **"Hello, " + user name + "!"**
- Right: **Logout** button (danger / red accent style).

---

## 1. Login (`LoginWindow`)

**Window title:** `Study.Table() — Sign in`  
**Size:** fixed ~420×620, centered.

**Top to bottom:**

| Block | Content |
|-------|---------|
| Title | "📚 Study.Table()" (`titleLabel`) |
| Subtitle | "CRM for training centers" (`subtitleLabel`) |
| Divider | Horizontal line |
| Label | "Login" |
| Field | Line edit, placeholder "Enter login...", min height ~40 |
| Label | "Password" |
| Field | Password mode, placeholder "Enter password..." |
| Error | Hidden by default (`errorLabel`): e.g. "Please fill in all fields", "Invalid login or password", unknown role message |
| Button | **Sign in** — primary, ~44px tall, rounded, bold 16px |
| Bottom | Stretch, then **hints card** (`hintsFrame`): dark fill, border, radius. Title "Test accounts:" and three rows (Admin / Teacher / Student) with login/password in monospace |

Enter in password field triggers Sign in.

---

## 2. Admin panel (`AdminPanel`)

**Window title:** `Study.Table() — Administrator`  
**Size:** ~1000×650.

**Header:** "🔴 Administrator" + "Hello, …!" + **Logout**.

### Tab "📊 Statistics"

- Centered subtitle: "System overview".
- **Four stat cards** in a row: large number + label:
  - Total users
  - Total courses
  - Students
  - Teachers

### Tab "👥 Users"

**Toolbar:**

- **Add** (primary)
- **Edit**
- **Delete** (danger)

**Table** (no vertical row numbers, alternating rows, single row selection):

| Column | Content |
|--------|---------|
| ID | number |
| Name | text |
| Login | text |
| Role | "🔴 Administrator" / "🟡 Teacher" / "🟢 Student" |

### Tab "📚 Courses"

**Buttons:**

- **Create course** (primary)
- **Edit**
- **Delete** (danger)
- **Enroll student** (success)

**Table:**

| Column | Content |
|--------|---------|
| ID | number |
| Title | text |
| Teacher | name |
| Students | enrolled count |

### Modal dialogs (for mockups)

- **Add user:** "Add user" — Name (placeholder "Last First"), Login, Password, Role (Student / Teacher / Administrator). OK / Cancel.
- **Edit user:** "Edit user", same fields prefilled.
- **Delete user:** Confirm with name; warns grades and enrollments will be removed.
- **Create course:** "Create course" — Title, Description, Teacher dropdown. OK / Cancel.
- **Edit course:** "Edit course" — same pattern.
- **Delete course:** Confirm with course title; warns grades and enrollments.
- **Enroll student:** "Enroll student in course" — Student dropdown (not yet on course). OK / Cancel.

Typical dialog titles: Error, Notice, Confirm, No teachers, Cannot delete, Info, Enrollment — see `adminpanel.cpp` for exact English strings.

---

## 3. Teacher panel (`TeacherPanel`)

**Window title:** `Study.Table() — Teacher`  
**Size:** ~900×600.

**Header:** "🟡 Teacher" + greeting + **Logout**.

### Tab "📊 Statistics"

- Subtitle: "Your statistics".
- Three cards: number + "Your courses", "Your students", average grade or "—" + "Average grade".

### Tab "📝 Grades"

**Top row:**

- **"Select course:"** (bold)
- **Combo box** of this teacher’s courses (~300px min width)
- **Set grade** button (primary)

**Table:**

| Student | Grade | Date |
|---------|-------|------|
| Name | 0–100 or "—" | yyyy-MM-dd or "—" |

**Input dialog:** title "Grade", label "Grade for [student name]:", default 50, range 0–100.

If no row selected: "Notice" — "Select a student in the table."

---

## 4. Student panel (`StudentPanel`)

**Window title:** `Study.Table() — Student`  
**Size:** ~850×550.

**Header:** "🟢 Student" + greeting + **Logout**.

### Tab "📊 Statistics"

- "Your statistics".
- Two cards: enrolled course count + average grade or "—".

### Tab "📚 My courses"

**Table only:**

| Course | Teacher | Grade |
|--------|---------|-------|
| Title | Name | number or "—" |

### Tab "📝 Grades"

**Table:**

| Course | Grade | Date |
|--------|-------|------|

**Below table** (right): bold "Average grade: " + value (one decimal or "—"), accent color on value (`#89b4fa` in QSS).

---

## AI design prompt hint

*"Desktop CRM for education: dark theme, English UI only. Screens and copy as in UI_SCREENS.md; stat cards, data tables, primary/danger/success buttons."*
