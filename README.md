 # Categorized Task Board (CaTaBoard) (Name Tenative)
 Simple C++ CLI program for creating and managing Kanban-like task boards.
 > Authors: 
 [Isaias Bernal](https://github.com/IsaiasB1122)
 [Dang Nguyen](https://github.com/Nhin0928)
 [Cristian Roberts](https://github.com/crisapi)
 [Reuben Self](https://github.com/rselfucr)

 ## Project Description
 > CaTaBoard will be a console application where a user is able to maintain a local Directory of Task Boards, via a command REPL loop.
 > ### Primary Features
 > * Ability to customize the available Categories for Tasks (e.g. TODO, In Progress, Completed, Needs Review..)
 > * Creation of multiple Task Boards.
 > * Track members assigned to a Task or Task Board, and view statistics related to their contributions.
 > * Ability to assosciate extra information related to a Task or Task Board via a list of Notes, which can be appended to over time to not only describe tasks but also track issues and events during development.
 > * Ability to sort existing Tasks within a Task Board by recent activity, creation ID, and filter by Category or assigned Member.
 > * Full timestamped Log of all changing actions made in the Directory.
 > * Display a Task Board in a pretty table-like view with each Category having a column.
 > ### Potential Extra Features
 > * Users: Have a user set for each "session" (changeable via command) that is also logged for each action.
 > * Text Graphics Extras: Associate a color with each Category that will color the name of tasks in all output, generate charts like burndown charts, workload split charts, etc.
 > * Undo: Allow all actions recorded in the Log to be undone.
 > * Syncing: Configure a Directory to try to sync with a server of some sort.
 > ### Implementation Details
 > * C++ CLI application.
  > * Targeting unix (hard target: running on UCR CS SSH machines)
    (Ideally should be able to compile and run on windows, but certain terminal features which we may use are not completely platform independent.)
 > * No third party libraries outside of C++ stdlib are expected to be necessary.
 > * Persistent data structures such as the task Directory itself, Task Boards, etc, will be mapped to specific classes, and all functionality of those structures will be implemented as class methods. The Directory will be given as an argument when running and either be created or loaded. Writes will be made immediately after a changing command is ran, to avoid data loss due to crashing.
 > * The console interface will be entirely modular, meaning that no actual program functionality is implemented by code that handles parsing commands or returning command output. This will make the program more extensible, supporting hypothetical potential features like a GUI or web API.

## Project Interst
> We believe this project will be interesting for several reasons.
> 1. The topic will relate to what we are learning in this semester of CS100, and give us a chance to directly apply and reinforce that knowledge.
> 2. The program itself will have a practical application, while also being simple to implement and use.
> 3. The project will be an approachable opportunity to gain experience in concepts that are key to software development. (designing file formats, working with a system of classes, creating a system to parse and run commands, sorting, filtering, and managing database-like structures)

 > ## Phase II
 > In addition to completing the "User Interface Specification" and "Class Diagram" sections below, you will need to:
 > * Create an "Epic" (note) for each feature. Place these epics in the `Product Backlog` column
 > * Complete your first *sprint planning* meeting to plan out the next 7 days of work.
 >   * Break down the "Epics" into smaller actionable user stories (i.e. smaller development tasks). Convert them into issues and assign them to team members. Place these in the `TODO` column (aka Sprint Backlog).
 >   * These cards should represent roughly 7 days worth of development time for your team. Then, once the sprint is over you should be repeating these steps to plan a new sprint, taking you until your second scrum meeting with the reader in phase III.
 > * Each team member needs to submit the Individual Contributions Form on Canvas for this phase. In this form, you need to fill in the names of all team members, the percentage of work contributed by each member for phase  II, and a description of their contributions. Remember that each team member should submit the form individually.
 > * Schedule two check-ins using Calendly. Both time slots should be during your lab on week 6. Your entire team must be present for both check-ins.
 >   * The first check-in needs to be scheduled with your lab TA. During that meeting, you will discuss your project design/class diagram from phase II.
 >   * The second check-in should be scheduled with a reader. During that meeting you will discuss:
 >     * The tasks you are planning for the first sprint
 >     * How work will be divided between the team members
## User Interface Specification
 > Include a navigation diagram for your screens and the layout of each of those screens as desribed below. For all the layouts/diagrams, you can use any tool such as PowerPoint or a drawing program. (Specification requirement is adapted from the User Interface Design Document Template of CMSC 345 at the University of Maryland Global Campus)

### Navigation Diagram
> Draw a diagram illustrating how the user can navigate from one screen to another. Here is an [example](https://creately.com/diagram/example/ikfqudv82/user-navigation-diagram-classic?r=v). It can be useful to label each symbol that represents a screen so that you can reference the screens in the next section or the rest of the document if necessary. Give a brief description of what the diagram represents.

### Screen Layouts
> Include the layout of each of your screens. The layout should describe the screen’s major components such as menus and prompts for user inputs and expected output, or any graphical user interface components if applicable (e.g. buttons, text boxes, etc). Explain what is on the layout, and the purpose of each menu item, button, etc. If many screens share the same layout, start by describing the general layout and then list the screens that will be using that layout and the differences between each of them.

## Class Diagram
 > Include a **class diagram(s)** for your project and a **description** of the diagram(s). Your class diagram(s) should include all the main classes you plan for the project. This should be in sufficient detail that another group could pick up the project this point and successfully complete it. Use proper UML notation (as discussed in the course slides).
 
 > ## Phase III
 > You will need to schedule a check-in for the second scrum meeting with the same reader you had your first scrum meeting with (using Calendly). Your entire team must be present. This meeting will occur on week 8 during lab time.
 
 > BEFORE the meeting you should do the following:
 > * Update your class diagram from Phase II to include any feedback you received from your TA/grader.
 > * Considering the SOLID design principles, reflect back on your class diagram and think about how you can use the SOLID principles to improve your design. You should then update the README.md file by adding the following:
 >   * A new class diagram incorporating your changes after considering the SOLID principles.
 >   * For each update in your class diagram, you must explain in 3-4 sentences:
 >     * What SOLID principle(s) did you apply?
 >     * How did you apply it? i.e. describe the change.
 >     * How did this change help you write better code?
 > * Perform a new sprint plan like you did in Phase II.
 > * Make sure that your README file (and Project board) are up-to-date reflecting the current status of your project and the most recent class diagram. Previous versions of the README file should still be visible through your commit history.
>  * Each team member should also submit the Individual Contributions Form on Canvas for phase III. In this form, you need to fill in the names of all team members, the percentage of work contributed by each member for phase III, and a description of their contributions. Remember that each team member should submit the form individually.
 
> During the meeting with your reader you will discuss: 
 > * How effective your last sprint was (each member should talk about what they did)
 > * Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 > * Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 > * What tasks you are planning for this next sprint.

 
 > ## Final deliverable
 > All group members will give a demo to the reader during lab time. ou should schedule your demo on Calendly with the same reader who took your second scrum meeting. The reader will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Project board.
 > * Make sure your README file and Project board are up-to-date reflecting the current status of your project (e.g. any changes that you have made during the project such as changes to your class diagram). Previous versions should still be visible through your commit history.
>  * Each team member should also submit the Individual Contributions Form on Canvas for this final phase. In this form, you need to fill in the names of all team members, the percentage of work contributed by each member for the final phase, and a description of their contributions. Remember that each team member should submit the form individually.
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
